/*
 *  global_objects.h
 *  foundation
 *
 *  Created by jiayi on 26/03/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#ifndef global_objects_H
#define global_objects_H

#include "basic/singleton.h"
#include "standard_libraries/unordered_map.h"

namespace minerva { namespace foundation {
    
    template<typename T>
    class global_objects : public singleton<global_objects<T>>
    {
    public:
        ~global_objects();
        
        /// get object by key
        T* get_object( const char* key ) const;
        
        /// add object by key
        bool add_object( const char* key, T* object );
        
    protected:
        typedef mi_unordered_map<std::string, T*> object_container;
        object_container _objects;
    };
}}

#include "object/global_objects.inl"

#define the_global_objects global_objects::get()

#endif /* global_objects_h */
