/*
 *  thread_procedure.cpp
 *  foundation
 *
 *  Created by jiayi on 05/02/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#include "thread_procedure.h"


using namespace minerva::foundation;

thread_procedure::~thread_procedure()
{
    for (int i = 0; i < e_mutex_type::count; ++ i ) {
        _mutex[i].lock();
        _container[i].clear();
        _mutex[i].unlock();
    }
}

void thread_procedure::push_request( const thread_request_ptr& request )
{
    // add
    _container[e_mutex_type::prepare].emplace( request );
}

void thread_procedure::start()
{
    _thread = std::thread(std::bind(&thread_procedure::update_thread, this ));
    _thread.detach();
}
