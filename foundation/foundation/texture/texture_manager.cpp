/*
 *  texture_manager.cpp
 *  foundation
 *
 *  Created by jiayi on 08/02/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#include "texture_manager.h"
#include "thread_manager.h"
#include "texture_loader.h"


using namespace minerva::foundation;

texture_manager::~texture_manager()
{
    _container.clear();
    _callbacks.clear();
    _strings.clear();
}

void texture_manager::load_texture_by_file_name( const std::string& file_name,
                                                const function_load_finished& callback_finished ) thread_safe
{
    // caculate the hash of filename
    std::size_t hash_file_name = std::hash<std::string>{}(file_name);
    
    // store string
    auto string_pair = _strings.emplace( std::make_pair( hash_file_name, file_name ) );
    
    // check if the target file already in the process or loaded
    auto iter = _container.find( hash_file_name );
    if ( iter != _container.end() ) {
        texture_data_ptr& data_ptr = iter->second;
        callback_finished ( (texture_data*)data_ptr );
        return;
    } else {
        auto callback = _callbacks.find( hash_file_name );
        if ( callback != _callbacks.end() ) {
            // processing, so push to callback and waiting for finish
            _callbacks.emplace( std::make_pair( hash_file_name, callback_finished ) );
            return;
        }
    }
    
    auto f = [](void* data) {
        the_texture_manager->load_texture_finish( ( texture_data* )data );
    };
    
    mi_log("%s\n",string_pair.first->second.c_str());
    thread_request_ptr t_request = mi_new thread_request(
                                                         e_thread_type::background_loading,
                                                         std::bind( &texture_loader::load_dds, texture_loader::get(), (void*)(&string_pair.first->second) ),
                                                         f
                                                         );
    
    the_thread_manager->push_request( t_request );
    
    // push callback to hash table
    _callbacks.emplace( std::make_pair(hash_file_name, callback_finished) );
    
}

void texture_manager::load_texture_finish( texture_data* data )
{
    texture_data_ptr texture_data = data;
    
    // find the hash and clear map
    std::size_t hash_file_name = std::hash<std::string>{}(data->filename);
    auto its = _callbacks.equal_range( hash_file_name );
    for ( auto it = its.first; it != its.second; ++it )
    { it->second( data ); }
    
    // erase all callbacks
    _callbacks.erase( hash_file_name );
    
    // add data to container
    _container.emplace( std::make_pair( hash_file_name, texture_data ) );
}
