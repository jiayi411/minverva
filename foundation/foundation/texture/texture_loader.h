/*
 *  texture_loader.h
 *  foundation
 *
 *  Created by jiayi on 01/02/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#ifndef texture_loader_H
#define texture_loader_H

#include "basic/singleton.h"
#include "texture/texture_common.h"

namespace minerva { namespace foundation {
    
    ///
    /// @brief A global thread-safe texture loader
    ///
    /// Thread-safe texture loader, support DXTn,BMP,PNG
    /// and other popular texture format.
    ///
    class texture_loader : public singleton<texture_loader>
    {
    public:
        ~texture_loader(){}
        
        /// @breif Load .dds file, thread-safe
        void* load_dds( void* file_name ) thread_safe;
        
        /// @brief Load .dds file, not thread-safe
        ///
        /// @param[in] file_name texture's file name.
        /// @param[out] data output data
        /// @return whether the texture is loaded
        bool load_dds_from_file( const std::string& file_name, texture_data* data );
        
        
    protected:
        friend class singleton< texture_loader >;
        texture_loader(){}
    };
    
} }

/// for short
#define the_texture_loader texture_loader::get()

#endif /* texture_loader_h */
