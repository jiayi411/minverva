/*
 *  quaternion.h
 *  graphic
 *
 *  Created by jiayi on 23/02/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#ifndef quaternion_H
#define quaternion_H

#include "graphic/math/vector3.h"
#include "graphic/math/matrix4x4.h"
#include "graphic/math/matrix3x3.h"
#include "graphic/math/math_functions.h"

namespace minerva { namespace graphic {
    
    ///
    /// @brief quaternion
    template<typename T>
    class quaternion
    {
    public:
        quaternion() : quaternion(0,0,0,0){}
        quaternion( T a, T b, T c, T d ) : x(a), y(b), z(c), w(d){}
        quaternion( T w, const vector3<T>& v ) : quaternion( v.x, v.y, v.z, w ){}
        
        quaternion( const quaternion& );
        quaternion( quaternion&& );
        quaternion& operator= ( const quaternion& );
        quaternion& operator= ( quaternion&& );
        
        template<typename U>
        quaternion& operator= ( const quaternion<U>& q );
        
    public:
        quaternion& operator+= ( const quaternion& q );
        quaternion& operator*= ( const quaternion& q );        
        
        template<typename U>
        quaternion& operator*= ( U u );
        
        template<typename U>
        vector3<U> operator*= ( const vector3<U>& v );
        
        template<typename U>
        quaternion& operator/= ( U u );
        
        T length() const;
        
        T dot( const quaternion& q ) const;
        
        quaternion& conjugate();
        
        quaternion& inverse();
        
        quaternion& normalize();
        
        quaternion& cross( const quaternion& q );
        
        quaternion& from_euler( const vector3<T>& euler );
        
        quaternion& from_axis_angle( float angle, const vector3<T>& axis );
        
        T pitch() const;
        T yaw() const;
        T roll() const;
        
        T angle() const;
        vector3<T> axis() const;
        
        quaternion slerp( const quaternion& q2, float s );
        quaternion lerp( const quaternion& q2, float s );
        
    public:
        T x, y, z, w;
    };
    
    template< typename T >
    quaternion<T> operator-( const quaternion<T>& q );
    
    template< typename T, typename U >
    quaternion<T> operator*( const quaternion<T>& q1, U u );
    template< typename T, typename U >
    quaternion<T> operator*( U u, const quaternion<T>& q1 );
    
    template< typename T, typename U >
    quaternion<T> operator/( const quaternion<T>& q1, U u );
    
    template< typename T>
    quaternion<T> operator+( const quaternion<T>& q1, const quaternion<T>& q2 );
    
    /* conversion */
    /// Converts a quaternion to a 3 * 3 matrix.
    template <typename T>
    matrix3x3<T> matrix3_cast(quaternion<T> const & x);
    
    /// Converts a quaternion to a 4 * 4 matrix.
    template <typename T>
    matrix4x4<T> matrix4_cast(quaternion<T> const & x);
    
    /// Converts a 3 * 3 matrix to a quaternion.
    template <typename T>
    quaternion<T> quaternion_cast(matrix3x3<T> const & x);
    
    /// Converts a 4 * 4 matrix to a quaternion.
    template <typename T>
    quaternion<T> quaternion_cast(matrix4x4<T> const & x);
    
    
} }

#include "graphic/math/quaternion.inl"

#define mi_log_quaternion(flag, q) \
    mi_log("x:"#flag",y:"#flag",z:"#flag",w:"#flag"\n", q.x, q.y, q.z, q.w);

#endif /* quaternion_h */
