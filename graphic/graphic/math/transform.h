/*
 *  transform.h
 *  graphic
 *
 *  Created by jiayi on 23/02/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#ifndef transform_H
#define transform_H

#include "foundation/object/update_object.h"
#include "graphic.h"
#include "math/vector3.h"
#include "math/quaternion.h"

namespace minerva { namespace graphic {
    
    ///
    /// @brief transfor classes
    ///
    /// contain the translate, rotate and scale
    /// information that an object needed in
    /// rendering
    ///
    class transform : public foundation::allocator
    {
    public:
        transform() : _scale_x(1.f), _scale_y(1.f), _scale_z(1.f), _matrix_position(1){ _update_all(); }
        
        /// copy constructor
        transform( const transform& t );
        
        /// copy constructor with rhs
        transform( transform&& t );
        
        /// copy operator
        transform& operator= ( const transform& t );
        
        /// copy operator with rhs
        transform& operator= ( transform&& t );
        
        /// get total transform
        matrix4x4 get_final_matrix() const;
        
    public:
        /// set scale
        void set_scale( float scale );
        
    protected:
        /// update all
        void _update_all();
        
        /// update scale
        void _update_scale();
        
        /// update rotation
        void _update_rotation();
        
        /// update position
        void _update_position();
        
    protected:
        /// rotation represented by quaternion
        half_set_full_get_ref( quaternion, rotation );
        
        /// position
        half_set_full_get_ref( vector3, position );
        
        /// scale represented by a float
        half_set_full_get( float, scale_x );
        half_set_full_get( float, scale_y );
        half_set_full_get( float, scale_z );
        
        /// position matrix to be sent to opengl
        get_ref_const( matrix4x4, matrix_position );
        
        /// rotation matrix to be sent to opengl
        get_ref_const( matrix4x4, matrix_rotation );
        
        /// scale matrix to be sent to opengl
        get_ref_const( matrix4x4, matrix_scale );
    };
    
} }

#endif /* transform_h */
