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
    };
} }

#endif /* update_object_h */
