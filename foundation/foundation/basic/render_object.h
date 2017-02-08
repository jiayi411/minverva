//
//  render_object.h
//  foundation
//
//  Created by jiayi on 07/02/2017.
//  Copyright © 2017 jiayi. All rights reserved.
//

#ifndef render_object_h
#define render_object_h

#include "basic/update_object"

namespace minerva { namespace foundation {
    
    ///
    /// @brief providing a render() function
    ///
    class render_object : public update_object
    {
        
        ///
        /// @brief render function
        /// @param delta the delta time from last frame
        ///
        virtual void render( float delta ){}
    };
} }

#endif /* render_object_h */
