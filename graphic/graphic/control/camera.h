/*
 *  camera.h
 *  graphic
 *
 *  Created by jiayi on 07/03/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#ifndef camera_H
#define camera_H

#include "foundation/object/update_object.h"
#include "math/vector2.h"
#include "math/transform.h"

namespace minerva { namespace graphic {
    
    ///
    /// @brief the camera of the 3d environment
    ///
    ///
    class camera : public foundation::update_object
    {
    public:
        camera() : _dirty(false){}
        virtual ~camera(){}
        
    public:
        /// initialize camera
        void initialize();
        
        ///
        /// @brief rotate by self pivot
        ///
        /// recieve input from screen space
        /// @param dx delta movement of screen position X
        /// @param dy delta movement of screen position Y
        void rotation( float dx, float dy );
        
        ///
        /// @brief update the camera
        ///
        virtual void update( float f );
        
        ///
        /// @brief set position on screen coordinate
        ///
        /// @param x screen position of axis X
        /// @param y screen position of axis Y
        void set_screen_position( float x, float y );
        
        ///
        /// @brief get the view matrix
        ///
        matrix4x4 get_view_matrix() const;
        
    protected:
        /// transform
        set_get_ref( transform, transform );
        
        /// target or look-at
        set_get_ref( vector3, forward );
        
        /// up vector
        set_get_ref( vector3, up );
        
        /// dirty
        set_get( bool, dirty );
        
        /// screen position
        vector2 _screen_position;
        
        /// old screen position
        vector2 _old_screen_position;
    };
    
}}

#endif /* camera_h */
