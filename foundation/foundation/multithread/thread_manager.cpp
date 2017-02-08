/*
 *  thread_manager.cpp
 *  foundation
 *
 *  Created by jiayi on 06/02/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#include "multithread/thread_manager.h"
#include "multithread/thread_background_loading.h"

using namespace minerva::foundation;

void thread_manager::push_request(const thread_request_ptr &request)
{
    auto procedure = _procedures.find( request->get_data().type );
    if (procedure == _procedures.end())
    {
        mi_log( "Cannot find thread procedure type: %d",
               static_cast<int>( request->get_data().type ) );
        return;
    }
    
    procedure->second->push_request( request );
}

void thread_manager::add_procedure( e_thread_type type )
{
    if ( _procedures.find( type ) != _procedures.end() ) {
        mi_log( "Duplicate thread procedure type for: %d", static_cast<int>(type) );
        return;
    }
    
    thread_procedure_ptr procedure = nullptr;
    
    switch ( type )
    {
        case e_thread_type::background_loading:
            procedure = mi_new thread_background_loading();
            break;
            
        case e_thread_type::error:
            mi_log( "Error type in thread_manager::add_procedure" );
            break;
    }
    
    if ( procedure != nullptr )
    { _procedures.insert( std::make_pair( type, procedure ) ); }
}

void thread_manager::start_all()
{
    for ( auto &p : _procedures ) {
        p.second->start();
    }
}

void thread_manager::update( float delta )
{
    for ( auto &p : _procedures ) {
        p.second->update( delta );
    }
}
