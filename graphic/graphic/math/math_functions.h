//
//  math_functions.h
//  graphic
//
//  Created by jiayi on 18/02/2017.
//  Copyright © 2017 jiayi. All rights reserved.
//

#ifndef math_functions_h
#define math_functions_h


#include <cmath>

namespace minerva { namespace graphic {
    
    template<typename T> class tmatrix4x4;
    template<typename T> class tvector3;
    template<typename T> class tquaternion;
    
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
    static inline float radians( float degrees );
    
    /// convert raidan to degree
    static inline float degrees( float radians );
    
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
    static tmatrix4x4<T> perspective( float degrees, float width, float height, float near, float far );
    
    template<typename T>
    static tmatrix4x4<T> view( const tvector3<T>& eye, const tvector3<T>& target, const tvector3<T>& up );
    
    template<typename T>
    static tquaternion<T> conjugate( const tquaternion<T>& q );
    
    template<typename T>
    static tquaternion<T> inverse( const tquaternion<T>& q );
    
    template<typename T>
    static tquaternion<T> normalize( const tquaternion<T>& q );
    
    template<typename T>
    static tquaternion<T> cross( const tquaternion<T>& q1, const tquaternion<T>& q2 );
    
    template<typename T>
    static tquaternion<T> rotation( const tvector3<T>& v1, const tvector3<T>& v2 );
    
    /*-- Constants --*/
    template<typename T>
    static T pi() { return T(3.14159265358979323846264338327950288); }
    
    template<typename T>
    static T epsilon();
    
    /*-- Basic Mathematics --*/
    
    /// mix things
    template<typename T>
    T mix( const T& t1, const T& t2, float a );
    
    template<typename T>
    tvector3<T> cos( const tvector3<T>& v );
    
    template<typename T>
    tvector3<T> sin( const tvector3<T>& v );
    
} }

#include "math/math_functions.inl"

#endif /* math_functions_h */
