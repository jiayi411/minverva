//
//  texture_common.h
//  foundation
//
//  Created by jiayi on 01/02/2017.
//  Copyright © 2017 jiayi. All rights reserved.
//

#ifndef texture_common_h
#define texture_common_h

#include "defines.h"

namespace minerva { namespace foundation {
    
    /// texture data loaded from disk
    struct texture_data
    {
        /// ctor
        texture_data() : buffer(0) {}
        
        /// dtor
        ~texture_data() {
            if ( buffer ) {
                free( buffer );
            }
        }
        uint format;        ///< texture format
        uint width;         ///< texture width
        uint height;        ///< texture height
        uint mipmap_count;  ///< mipmap count, 0 mean no mimap
        uchar* buffer;      ///< texture data
    };
} }

#endif /* texture_common_h */
