/*
 *  quaternion.cpp
 *  graphic
 *
 *  Created by jiayi on 23/02/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */
#include <limits>
namespace minerva { namespace graphic {
   
    template<typename T>
    quaternion<T>::quaternion( const quaternion<T>& q )
    { this->x = q.x; this->y = q.y; this->z = q.z, this->w = q.w; }
    
    template<typename T>
    quaternion<T>::quaternion( quaternion<T>&& q )
    { this->x = q.x; this->y = q.y; this->z = q.z, this->w = q.w; }
    
    template<typename T>
    quaternion<T>& quaternion<T>::operator= ( const quaternion<T>& q )
    { this->x = q.x; this->y = q.y; this->z = q.z, this->w = q.w; return *this; }
    
    template<typename T>
    quaternion<T>& quaternion<T>::operator= ( quaternion<T>&& q )
    { this->x = q.x; this->y = q.y; this->z = q.z, this->w = q.w; return *this; }
    
    template<typename T>
    quaternion<T>& quaternion<T>::operator+= ( const quaternion<T>& q )
    { this->x += q.x; this->y += q.y; this->z += q.z, this->w += q.w; return *this; }
    
    template<typename T>
    quaternion<T>& quaternion<T>::operator*= ( const quaternion<T>& q )
    {
        quaternion p = *this;
        this->w = p.w * q.w - p.x * q.x - p.y * q.y - p.z * q.z;
        this->x = p.w * q.x + p.x * q.w + p.y * q.z - p.z * q.y;
        this->y = p.w * q.y + p.y * q.w + p.z * q.x - p.x * q.z;
        this->z = p.w * q.z + p.z * q.w + p.x * q.y - p.y * q.x;
        return *this;
    }
    
    template<typename T>
    template<typename U>
    quaternion<T>& quaternion<T>::operator= ( const quaternion<U>& q )
    {
        this->x = static_cast<T>(q.x);
        this->y = static_cast<T>(q.y);
        this->z = static_cast<T>(q.z);
        this->w = static_cast<T>(q.w);
        return *this;
    }
    
    template<typename T>
    template<typename U>
    quaternion<T>& quaternion<T>::operator*= ( U u )
    {
        T t = static_cast<T>(u);
        this->x *= t;
        this->y *= t;
        this->z *= t;
        this->w *= t;
        return *this;
    }
    
    template<typename T>
    template<typename U>
    quaternion<T>& quaternion<T>::operator/= ( U u )
    {
        T t = static_cast<T>(u);
        this->x /= t;
        this->y /= t;
        this->z /= t;
        this->w /= t;
        return *this;
    }
    
    template<typename T>
    T quaternion<T>::length() const
    {
        return sqrt( this->dot(*this) );
    }
    
    template<typename T>
    T quaternion<T>::dot( const quaternion<T>& q ) const
    { return ( q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w ); }
    
    template<typename T>
    quaternion<T>& quaternion<T>::conjugate()
    { this->x = -this->x; this->y = -this->y; this->z = -this->z; return *this; }
    
    template<typename T>
    quaternion<T>& quaternion<T>::inverse()
    {
        T d = this->dot( *this );
        conjugate() /= d;
        return *(this);
    }
    
    template<typename T>
    quaternion<T>& quaternion<T>::normalize()
    {
        T len = length();
        if (len <= T(0)) {
            this->x = 0; this->y = 0; this->z = 0; this->w = 1;
            return *this;
        }
        
        T one_over_length = T(1) / len;
        *this *= one_over_length;
        return *this;
    }
    
    template<typename T>
    quaternion<T>& quaternion<T>::cross( const quaternion& q2 )
    {
        quaternion<T>& q1 = *this;
        *this = quaternion<T>(
        q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
        q1.w * q2.y + q1.y * q2.w + q1.z * q2.x - q1.x * q2.z,
        q1.w * q2.z + q1.z * q2.w + q1.x * q2.y - q1.y * q2.x,
        q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z);
        
        return *this;
    }
    
    template<typename T>
    template<typename U>
    vector3<U> quaternion<T>::operator*= ( const vector3<U>& v )
    {
        quaternion<T> q( v.x, v.y, v.z, 0 );
        quaternion<T> inv = *this;
        return *this * q * inv.inverse();
    }
    
    template<typename T>
    quaternion<T>& quaternion<T>::from_euler( const vector3<T>& euler )
    {
        vector3<T> c = cos(euler * T(0.5));
        vector3<T> s = sin(euler * T(0.5));
        
        this->w = c.x * c.y * c.z + s.x * s.y * s.z;
        this->x = s.x * c.y * c.z - c.x * s.y * s.z;
        this->y = c.x * s.y * c.z + s.x * c.y * s.z;
        this->z = c.x * c.y * s.z - s.x * s.y * c.z;
        return *this;
    }
    
    template<typename T>
    quaternion<T>& quaternion<T>::from_axis_angle( float angle, const vector3<T>& axis )
    {
        float half_angle = 0.5f * angle;
        float sin_angle = std::sin(half_angle);
        
        this->x = axis.x * sin_angle;
        this->y = axis.y * sin_angle;
        this->z = axis.z * sin_angle;
        this->w = std::cos(half_angle);
        return *this;
    }
    
    template<typename T>
    T quaternion<T>::pitch() const
    { return T(atan(T(2) * (y * z + w * x), w * w - x * x - y * y + z * z)); }
    
    template<typename T>
    T quaternion<T>::yaw() const
    { return asin(T(-2) * (x * z - w * y)); }
    
    template<typename T>
    T quaternion<T>::roll() const
    { return T(atan(T(2) * (x * y + w * z), w * w + x * x - y * y - z * z)); }
    
    template<typename T>
    quaternion<T> quaternion<T>::slerp( const quaternion<T>& y, float a )
    {
        quaternion<T>& x = *this;
        quaternion<T> z = y;
        
        T cosTheta = dot(y);
        
        // If cosTheta < 0, the interpolation will take the long way around the sphere.
        // To fix this, one quat must be negated.
        if (cosTheta < T(0))
        {
            z        = -y;
            cosTheta = -cosTheta;
        }
        
        // Perform a linear interpolation when cosTheta is close to 1 to avoid side effect of sin(angle) becoming a zero denominator
        if(cosTheta > T(1) - std::numeric_limits<T>::epsilon())
        {
            // Linear interpolation
            return quaternion<T>(
                                 graphic::mix<T>(x.x, z.x, a),
                                 graphic::mix<T>(x.y, z.y, a),
                                 graphic::mix<T>(x.z, z.z, a),
                                 graphic::mix<T>(x.w, z.w, a));
        }
        else
        {
            // Essential Mathematics, page 467
            T angle = acos(cosTheta);
            return (sin((T(1) - a) * angle) * x + sin(a * angle) * z) / sin(angle);
        }

    }
    
    
    //* - - - - - - - - - - - - -*//
    template< typename T >
    quaternion<T> operator-( const quaternion<T>& q )
    { return quaternion<T>( -q.x, -q.y, -q.z, -q.w ); }
    
    template< typename T, typename U >
    quaternion<T> operator*( const quaternion<T>& q1, U u )
    {
        quaternion<T> q = q1;
        return q *= static_cast<T>(u);
    }
    
    template< typename T, typename U >
    quaternion<T> operator*( U u, const quaternion<T>& q1 )
    {
        quaternion<T> q = q1;
        return q *= static_cast<T>(u);
    }
    
    template< typename T, typename U >
    quaternion<T> operator/( const quaternion<T>& q1, U u )
    {
        quaternion<T> q = q1;
        return q /= static_cast<T>(u);
    }
    
    template< typename T>
    quaternion<T> operator+( const quaternion<T>& q1, const quaternion<T>& q2 )
    {
        quaternion<T> v = q1;
        return v += q2;
    }
    
} }
