/*
 *  thread_background_loading.cpp
 *  foundation
 *
 *  Created by jiayi on 07/02/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#include "thread_background_loading.h"

using namespace minerva::foundation;

void thread_background_loading::update_thread()
{
    while (1)
    {
        std::unique_lock<std::mutex> lock_ready( _mutex[e_mutex_type::ready] );
        _condition.wait( lock_ready, [this](){ return !_container[e_mutex_type::ready].empty(); } );
        
        thread_request_ptr& request = _container[e_mutex_type::ready].front();
        thread_request_data& data = request->get_data();
        
        // execute function from data
        data.out_data = data.function_in_thread();// data.in_data );
        
        // push to the 'done' queue
        _mutex[e_mutex_type::done].lock();
        _container[e_mutex_type::done].emplace( request );
        _mutex[e_mutex_type::done].unlock();
        
        // pop
        _container[e_mutex_type::ready].pop();
    }
}

void thread_background_loading::update( float )
{
    _prepare_container();
    _process_result();
}

void thread_background_loading::_prepare_container()
{
    if (!_mutex[e_mutex_type::ready].try_lock()) { return; }
    
    if ( _container[e_mutex_type::prepare].empty() ) {
        _mutex[e_mutex_type::ready].unlock();
        return;
    }
    
    // worker has things to do now.
    _container[e_mutex_type::ready].emplace( _container[e_mutex_type::prepare].front() );
    
    // unlock as quickly as it can
    _mutex[e_mutex_type::ready].unlock();
    
    // notify the thread to consume
    _condition.notify_all();
    
    // pop the prepare queue
    _container[e_mutex_type::prepare].pop();
    
    
}

void thread_background_loading::_process_result()
{
    if (!_mutex[e_mutex_type::done].try_lock()) { return; }
    
    if ( _container[e_mutex_type::done].empty() ) {
        _mutex[e_mutex_type::done].unlock();
        return;
    }
    
    thread_request_ptr& request = _container[e_mutex_type::done].front();
    thread_request_data& data = request->get_data();
    data.function_in_main_thread( data.out_data );
    
    // pop
    _container[e_mutex_type::done].pop();
    
    // unlock
    _mutex[e_mutex_type::done].unlock();
}
