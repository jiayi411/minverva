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

#include "foundation/object/reference_object.h"

namespace minerva { namespace graphic {
    ///
    /// @brief transfor classes
    ///
    /// contain the translate, rotate and scale
    /// information that an object needed in
    /// rendering
    ///
    class transform : public foundation::reference_object
    {
    public:
        transform() : _scale(0.f){}
        
        /// copy constructor
        transform( const transform& t );
        
        /// copy constructor with rhs
        transform( transform&& t );
        
        /// copy operator
        transform& operator= ( const transform& t );
        
        /// copy operator with rhs
        transform& operator= ( transform&& t );
        
    public:
        /// set scale
        const quaternion& get_quaternion() const;
        
    protected:
        /// rotation represented by quaternion
        quaternion _rotation;
        
        /// position
        vector3  _position;
        
        /// scale represented by a float to save space
        float _scale;
    };
    
} }

#endif /* transform_h */
