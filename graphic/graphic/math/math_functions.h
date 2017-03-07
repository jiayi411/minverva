//
//  math_functions.h
//  graphic
//
//  Created by jiayi on 18/02/2017.
//  Copyright © 2017 jiayi. All rights reserved.
//

#ifndef math_functions_h
#define math_functions_h

#include "graphic/math/matrix4x4.h"
#include "graphic/math/vector3.h"
#include "graphic/math/quaternion.h"

namespace minerva { namespace graphic {
    
    /*-- Matrix Related Functions --*/
    
    /// Inverse a 4x4 matrix
    template<typename M>
    static M inverse( const M& m );
    
    /// get transpose of a matrix
    template<typename M>
    static M transpose( const M& m );
    
    /// get determinant of a matrix
    template<typename M>
    static typename M::value_type determinant( const M& m );
    
    /// convert degree to radian
    static float radians( float degrees );
    
    /// convert raidan to degree
    static float degrees( float radians );
    
    /// get dot of two vectors
    template<typename V>
    static float dot( const V& v1, const V& v2 );
    
    /// get cross of two vectors
    template<typename V>
    static V cross( const V& v1, const V& v2 );
    
    /// get normalize of the vector
    template<typename V>
    static V normalize( const V& v );
    
    ///
    /// @brief build perspective matrix
    ///
    /// 1 / (aspect*tan(α/2))           0                   0                       0
    ///             0               1 / tan(α/2)            0                       0
    ///             0                   0      (-near-far) / (near-far)  -(2*far*near)/(near-far)
    ///             0                   0                   1                       0
    template<typename T>
    static matrix4x4<T> perspective( float degrees, float width, float height, float near, float far );
    
    template<typename T>
    static matrix4x4<T> view( const vector3<T>& eye, const vector3<T>& target, const vector3<T>& up );
    
    template<typename T>
    static quaternion<T> conjugate( const quaternion<T>& q );
    
    template<typename T>
    static quaternion<T> inverse( const quaternion<T>& q );
    
    template<typename T>
    static quaternion<T> normalize( const quaternion<T>& q );
    
    template<typename T>
    static quaternion<T> cross( const quaternion<T>& q1, const quaternion<T>& q2 );
    
} }

#include "graphic/math/math_functions.inl"

#endif /* math_functions_h */
