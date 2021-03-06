//
//  update_object.h
//  foundation
//
//  Created by jiayi on 06/02/2017.
//  Copyright © 2017 jiayi. All rights reserved.
//

#ifndef update_object_h
#define update_object_h

#include "object/reference_object.h"
#include "object/smart_object.h"

namespace minerva { namespace foundation {
    
    ///
    /// @brief providing an update() function
    ///
    class update_object : public reference_object
    {
        
        ///
        /// @brief update function
        /// @param delta the delta time from last frame
        ///
        virtual void update( float delta ){}
        
        ///
        /// @brief before rendering
        ///
        /// execute just before render
        ///
        virtual void on_render( float delta ){}
        
        ///
        /// @brief render function
        /// @param delta the delta time from last frame
        ///
        virtual void render( float delta ){}
    };
    
    make_smart( update_object );
} }


#endif /* update_object_h */
