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

#include "singleton.h"
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
        
        /// @brief Load .dds file, not thread-safe
        ///
        /// @param[in] file_name texture's file name.
        /// @param[out] data output data
        void load_dds_from_file_no_safe( const std::string& file_name, texture_data* data );
        
        
    protected:
        texture_loader(){}
    };
    
} }

#endif /* texture_loader_h */
