/*
 *  quaternion.h
 *  graphic
 *
 *  Created by jiayi on 23/02/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#ifndef tquaternion_H
#define tquaternion_H

#include "math/vector3.h"
#include "math/matrix4x4.h"
#include "math/matrix3x3.h"
#include "math/math_functions.h"

namespace minerva { namespace graphic {
    
    ///
    /// @brief tquaternion
    template<typename T>
    class tquaternion
    {
    public:
        tquaternion() : tquaternion(0,0,0,0){}
        tquaternion( T a, T b, T c, T d ) : x(a), y(b), z(c), w(d){}
        tquaternion( T w, const tvector3<T>& v ) : tquaternion( v.x, v.y, v.z, w ){}
        
        tquaternion( const tquaternion& );
        tquaternion( tquaternion&& );
        tquaternion& operator= ( const tquaternion& );
        tquaternion& operator= ( tquaternion&& );
        
        template<typename U>
        tquaternion& operator= ( const tquaternion<U>& q );
        
    public:
        tquaternion& operator+= ( const tquaternion& q );
        tquaternion& operator*= ( const tquaternion& q );        
        
        template<typename U>
        tquaternion& operator*= ( U u );
        
        template<typename U>
        tvector3<U> operator* ( const tvector3<U>& v );
        
        template<typename U>
        tquaternion& operator/= ( U u );
        
        T length() const;
        
        T dot( const tquaternion& q ) const;
        
        tquaternion& conjugate();
        
        tquaternion& inverse();
        
        tquaternion& normalize();
        
        tquaternion& cross( const tquaternion& q );
        
        tquaternion& from_euler( const tvector3<T>& euler );
        
        tquaternion& from_axis_angle( float angle, const tvector3<T>& axis );
        
        T pitch() const;
        T yaw() const;
        T roll() const;
        
        T angle() const;
        tvector3<T> axis() const;
        
        tquaternion slerp( const tquaternion& q2, float s );
        tquaternion lerp( const tquaternion& q2, float s );
        
    public:
        T x, y, z, w;
    };
    
    template< typename T >
    tquaternion<T> operator-( const tquaternion<T>& q );
    
    template< typename T, typename U >
    tquaternion<T> operator*( const tquaternion<T>& q1, U u );
    template< typename T, typename U >
    tquaternion<T> operator*( U u, const tquaternion<T>& q1 );
    
    template< typename T>
    tquaternion<T> operator*( const tquaternion<T>& q1, const tquaternion<T>& q2 );
    
    template< typename T, typename U >
    tquaternion<T> operator/( const tquaternion<T>& q1, U u );
    
    template< typename T>
    tquaternion<T> operator+( const tquaternion<T>& q1, const tquaternion<T>& q2 );
    
    /* conversion */
    /// Converts a tquaternion to a 3 * 3 matrix.
    template <template<typename> class M, typename T>
    void _matrix_cast(tquaternion<T> const & x, M<T>* out_matrix );
    
    template <typename T>
    tmatrix3x3<T> matrix3_cast(tquaternion<T> const & x);
    template <typename T>
    void matrix3_cast(tquaternion<T> const & x, tmatrix3x3<T>* out_matrix );
    
    /// Converts a tquaternion to a 4 * 4 matrix.
    template <typename T>
    tmatrix4x4<T> matrix4_cast(tquaternion<T> const & x);
    template <typename T>
    void matrix4_cast(tquaternion<T> const & x, tmatrix4x4<T>* out_matrix );
    
    /// Converts a 3 * 3 matrix to a tquaternion.
    template <typename T>
    tquaternion<T> tquaternion_cast(tmatrix3x3<T> const & x);
    
    /// Converts a 4 * 4 matrix to a tquaternion.
    template <typename T>
    tquaternion<T> tquaternion_cast(tmatrix4x4<T> const & x);
    
    
} }

#include "math/quaternion.inl"

#define mi_log_quaternion(flag, q) \
    mi_log("x:"#flag",y:"#flag",z:"#flag",w:"#flag"\n", q.x, q.y, q.z, q.w);

#endif /* tquaternion_h */
