/*
 *  texture_manager.h
 *  foundation
 *
 *  Created by jiayi on 08/02/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#ifndef texture_manager_H
#define texture_manager_H

#include "basic/singleton.h"
#include "standard_libraries/unordered_map.h"
#include "texture/texture_common.h"

namespace minerva { namespace foundation {
    
    ///
    /// @brief manage texture's life cycle
    ///
    /// A thread-safe texture manager that deals with I/O and
    /// manage the life cycle of each texture data, openGL stuff, etc.
    ///
    class texture_manager : public singleton<texture_manager>
    {
    public:
        typedef std::function<void(texture_data*)> function_load_finished;
        
    public:
        ~texture_manager();
        
        /// load texture by file name
        void load_texture_by_file_name( const std::string& file_name, const function_load_finished& callback_finished ) thread_safe;
        
        /// after loading by thread, it will come to this function
        void load_texture_finish( texture_data* data );
        
    protected:
        texture_manager(){}
        friend class singleton<texture_manager>;
        
    protected:
        ///< key is the hash of file name
        typedef mi_unordered_map< std::size_t, texture_data_ptr > texture_data_container;
        texture_data_container _container;  ///< texture_datas
        
        /// in order to support multithread, I need to store a permanent std::string
        typedef mi_unordered_map< std::size_t, std::string > string_container;
        string_container _strings;
        
        ///
        /// @brief container for store multiple same request
        ///
        /// When the client push multiple request toward the same file name,
        /// we don't need to load the texture multiple times, so here, pushing
        /// every request's callback to a container and clear these callback when the
        /// load function finished, besides, once there has at least one callback in
        /// this container, the request would be discarded due to duplication.
        ///
        typedef mi_unordered_multimap< std::size_t, function_load_finished > callback_container;
        callback_container _callbacks; ///< the callback container
    };
    
    #define the_texture_manager foundation::texture_manager::get()
    
} }


#endif /* texture_manager_h */
