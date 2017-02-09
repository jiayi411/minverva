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
#include "object/smart_object.h"

namespace minerva { namespace foundation {
    
    /// texture data loaded from disk
    struct texture_data : public reference_object
    {
        /// ctor
        texture_data() : buffer(0) {}
        
        /// dtor
        ~texture_data() {
            if ( buffer ) {
                mi_free( buffer );
            }
        }
        std::string filename;   ///< filename with path
        uint format;            ///< texture format
        uint width;             ///< texture width
        uint height;            ///< texture height
        uint mipmap_count;      ///< mipmap count, 0 means no mimap
        uchar* buffer;          ///< texture data
    };
    
    make_smart( texture_data );
} }

#endif /* texture_common_h */
