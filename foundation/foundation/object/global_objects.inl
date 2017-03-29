/*
 *  global_objects.cpp
 *  foundation
 *
 *  Created by jiayi on 26/03/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

namespace minerva { namespace foundation{
    
    template<typename T>
    global_objects<T>::~global_objects()
    {
        for (auto t : _objects) {
            safe_delete( t );
        }
        _objects.clear();
    }
    
    template<typename T>
    T* global_objects<T>::get_object( const char* key ) const
    {
        auto result = _objects.find( key );
        if (result != _objects.end()) {
            return result;
        }
        return nullptr;
    }
    
    template<typename T>
    bool global_objects<T>::add_object( const char* key, T* object )
    {
        auto result = get_object( key );
        if (result) {
            mi_log("global_objects' key already exist");
            return false;
        }
        
        _objects.emplace( std::make_pair( key, object ) );
        return true;
    }
    
} }
