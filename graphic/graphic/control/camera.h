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
#include "model/model.h"

namespace minerva { namespace graphic {
    
    ///
    /// @brief the camera of the 3d environment
    ///
    ///
    class camera : public model
    {
    public:
        struct perspective_data
        {
            perspective_data(){}
            
            perspective_data( int w, int h, float d, float n, float f ) :
            width(w), height(h), degree(d), near(n), far(f){}
            
            int width = 0;
            int height = 0;
            float degree = 0.f;
            float near = 0.1f;
            float far = 10000.f;
        };
        
    public:
        camera() : _dirty(true){}
        virtual ~camera(){}
        
    public:
        /// initialize camera
        void initialize( const perspective_data& data );
        
        ///
        /// @brief update the camera
        ///
        virtual void update( float f );
        
        ///
        /// @brief set position on screen coordinate
        ///
        /// @param x screen position of axis X
        /// @param y screen position of axis Y
        void update_screen_position( float x, float y );
        
        ///
        /// @brief look at position
        ///
        /// @param position the position camera need to look at
        void look_at( const vector3& position );
        
        /// get right vector
        
        
        ///
        /// @brief get the view matrix
        ///
        matrix4x4 get_view_matrix() const;
        
        ///
        /// @brief get the projective matrix
        ///
        matrix4x4 get_perspective_matrix() const;
        
    protected:
        ///
        /// @brief rotate by self pivot
        ///
        /// receive input from screen space
        /// @param dx delta movement of screen position X
        /// @param dy delta movement of screen position Y
        void _rotation( float dx, float dy );
        
        /// caculate right vector
        void _caculate_right_vector();
        
    protected:
        /// perspective data
        set_get_ref( perspective_data, perspective_data );
        
        /// transform
        set_get_ref( transform, transform );
        
        /// target or look-at
        set_get_ref( vector3, forward );
        
        /// right vector
        get_ref( vector3, right );
        
        /// up vector
        set_get_ref( vector3, up );
        
        /// dirty
        set_get( bool, dirty );
        
        /// screen position
        vector2 _screen_position;
        
        /// old screen position
        vector2 _old_screen_position;
    };
    make_smart(camera);
    
}}

#endif /* camera_h */
