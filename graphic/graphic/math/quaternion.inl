/*
 *  tquaternion.cpp
 *  graphic
 *
 *  Created by jiayi on 23/02/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */
#include "graphic/graphic.h"
namespace minerva { namespace graphic {
   
    template<typename T>
    tquaternion<T>::tquaternion( const tquaternion<T>& q )
    { this->x = q.x; this->y = q.y; this->z = q.z, this->w = q.w; }
    
    template<typename T>
    tquaternion<T>::tquaternion( tquaternion<T>&& q )
    { this->x = q.x; this->y = q.y; this->z = q.z, this->w = q.w; }
    
    template<typename T>
    tquaternion<T>& tquaternion<T>::operator= ( const tquaternion<T>& q )
    { this->x = q.x; this->y = q.y; this->z = q.z, this->w = q.w; return *this; }
    
    template<typename T>
    tquaternion<T>& tquaternion<T>::operator= ( tquaternion<T>&& q )
    { this->x = q.x; this->y = q.y; this->z = q.z, this->w = q.w; return *this; }
    
    template<typename T>
    tquaternion<T>& tquaternion<T>::operator+= ( const tquaternion<T>& q )
    { this->x += q.x; this->y += q.y; this->z += q.z, this->w += q.w; return *this; }
    
    template<typename T>
    tquaternion<T>& tquaternion<T>::operator*= ( const tquaternion<T>& q )
    {
        tquaternion p = *this;
        this->w = p.w * q.w - p.x * q.x - p.y * q.y - p.z * q.z;
        this->x = p.w * q.x + p.x * q.w + p.y * q.z - p.z * q.y;
        this->y = p.w * q.y + p.y * q.w + p.z * q.x - p.x * q.z;
        this->z = p.w * q.z + p.z * q.w + p.x * q.y - p.y * q.x;
        return *this;
    }
    
    template<typename T>
    template<typename U>
    tquaternion<T>& tquaternion<T>::operator= ( const tquaternion<U>& q )
    {
        this->x = static_cast<T>(q.x);
        this->y = static_cast<T>(q.y);
        this->z = static_cast<T>(q.z);
        this->w = static_cast<T>(q.w);
        return *this;
    }
    
    template<typename T>
    template<typename U>
    tquaternion<T>& tquaternion<T>::operator*= ( U u )
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
    tquaternion<T>& tquaternion<T>::operator/= ( U u )
    {
        T t = static_cast<T>(u);
        this->x /= t;
        this->y /= t;
        this->z /= t;
        this->w /= t;
        return *this;
    }
    
    template<typename T>
    T tquaternion<T>::length() const
    {
        return sqrt( this->dot(*this) );
    }
    
    template<typename T>
    T tquaternion<T>::dot( const tquaternion<T>& q ) const
    { return ( x * q.x + y * q.y + z * q.z + w * q.w ); }
    
    template<typename T>
    tquaternion<T>& tquaternion<T>::conjugate()
    { this->x = -this->x; this->y = -this->y; this->z = -this->z; return *this; }
    
    template<typename T>
    tquaternion<T>& tquaternion<T>::inverse()
    {
        T d = this->dot( *this );
        conjugate() /= d;
        return *(this);
    }
    
    template<typename T>
    tquaternion<T>& tquaternion<T>::normalize()
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
    tquaternion<T>& tquaternion<T>::cross( const tquaternion& q2 )
    {
        tquaternion<T>& q1 = *this;
        *this = tquaternion<T>(
        q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
        q1.w * q2.y + q1.y * q2.w + q1.z * q2.x - q1.x * q2.z,
        q1.w * q2.z + q1.z * q2.w + q1.x * q2.y - q1.y * q2.x,
        q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z);
        
        return *this;
    }
    
    template<typename T>
    template<typename U>
    tvector3<U> tquaternion<T>::operator* ( const tvector3<U>& v )
    {
        tquaternion<T> q( v.x, v.y, v.z, 0 );
        tquaternion<T> inv = *this;
        tquaternion<T> ans = *this * q * inv.inverse();
        return tvector3<U>( ans.x, ans.y, ans.z );
    }
    
    template<typename T>
    tquaternion<T>& tquaternion<T>::from_euler( const tvector3<T>& euler )
    {
        tvector3<T> c = cos(euler * T(0.5));
        tvector3<T> s = sin(euler * T(0.5));
        
        this->w = c.x * c.y * c.z + s.x * s.y * s.z;
        this->x = s.x * c.y * c.z - c.x * s.y * s.z;
        this->y = c.x * s.y * c.z + s.x * c.y * s.z;
        this->z = c.x * c.y * s.z - s.x * s.y * c.z;
        return *this;
    }
    
    template<typename T>
    tquaternion<T>& tquaternion<T>::from_axis_angle( float angle, const tvector3<T>& axis )
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
    T tquaternion<T>::pitch() const
    { return T(atan(T(2) * (y * z + w * x), w * w - x * x - y * y + z * z)); }
    
    template<typename T>
    T tquaternion<T>::yaw() const
    { return asin(T(-2) * (x * z - w * y)); }
    
    template<typename T>
    T tquaternion<T>::roll() const
    { return T(atan(T(2) * (x * y + w * z), w * w + x * x - y * y - z * z)); }
    
    template<typename T>
    T tquaternion<T>::angle() const
    { return acos(w) * T(2); }
    
    template<typename T>
    tvector3<T> tquaternion<T>::axis() const
    {
        T tmp1 = static_cast<T>(1) - w * w;
        if(tmp1 <= static_cast<T>(0))
            return tvector3<T>(0, 0, 1);
        T tmp2 = static_cast<T>(1) / sqrt(tmp1);
        return tvector3<T>(x * tmp2, y * tmp2, z * tmp2);
    }
    
    template<typename T>
    tquaternion<T> tquaternion<T>::lerp( const tquaternion<T>& y, float a )
    { tquaternion<T>& x = *this; return x * (T(1) - a) + (y * a); }
    
    template<typename T>
    tquaternion<T> tquaternion<T>::slerp( const tquaternion<T>& y, float a )
    {
        tquaternion<T>& x = *this;
        tquaternion<T> z = y;
        
        T cosTheta = dot(y);
        
        // If cosTheta < 0, the interpolation will take the long way around the sphere.
        // To fix this, one quat must be negated.
        if (cosTheta < T(0))
        {
            z        = -y;
            cosTheta = -cosTheta;
        }
        
        // Perform a linear interpolation when cosTheta is close to 1 to avoid side effect of sin(angle) becoming a zero denominator
        if(cosTheta > T(1) - epsilon<T>())
        {
            // Linear interpolation
            return tquaternion<T>(
                                 graphic::mix<T>(x.x, z.x, a),
                                 graphic::mix<T>(x.y, z.y, a),
                                 graphic::mix<T>(x.z, z.z, a),
                                 graphic::mix<T>(x.w, z.w, a));
        }
        else
        {
            // Essential Mathematics, page 467
            T angle = acos(cosTheta);
            return (std::sin((T(1) - a) * angle) * x + std::sin(a * angle) * z) / std::sin(angle);
        }

    }
    
    
    //* - - - - - - - - - - - - -*//
    template< typename T >
    tquaternion<T> operator-( const tquaternion<T>& q )
    { return tquaternion<T>( -q.x, -q.y, -q.z, -q.w ); }
    
    template< typename T, typename U >
    tquaternion<T> operator*( const tquaternion<T>& q1, U u )
    {
        tquaternion<T> q = q1;
        return q *= static_cast<T>(u);
    }
    
    template< typename T, typename U >
    tquaternion<T> operator*( U u, const tquaternion<T>& q1 )
    {
        tquaternion<T> q = q1;
        return q *= static_cast<T>(u);
    }
    
    template< typename T>
    tquaternion<T> operator*( const tquaternion<T>& q1, const tquaternion<T>& q2 )
    {
        tquaternion<T> q = q1;
        q *= q2;
        return q;
    }
    
    template< typename T, typename U >
    tquaternion<T> operator/( const tquaternion<T>& q1, U u )
    {
        tquaternion<T> q = q1;
        return q /= static_cast<T>(u);
    }
    
    template< typename T>
    tquaternion<T> operator+( const tquaternion<T>& q1, const tquaternion<T>& q2 )
    {
        tquaternion<T> v = q1;
        return v += q2;
    }
    
    template <template<typename> class M, typename T>
    void _matrix_cast(tquaternion<T> const & q, M<T>* out_matrix )
    {
        T qxx(q.x * q.x);
        T qyy(q.y * q.y);
        T qzz(q.z * q.z);
        T qxz(q.x * q.z);
        T qxy(q.x * q.y);
        T qyz(q.y * q.z);
        T qwx(q.w * q.x);
        T qwy(q.w * q.y);
        T qwz(q.w * q.z);
        
        (*out_matrix)[0][0] = 1 - 2 * (qyy +  qzz);
        (*out_matrix)[1][0] = 2 * (qxy + qwz);
        (*out_matrix)[2][0] = 2 * (qxz - qwy);
        
        (*out_matrix)[0][1] = 2 * (qxy - qwz);
        (*out_matrix)[1][1] = 1 - 2 * (qxx +  qzz);
        (*out_matrix)[2][1] = 2 * (qyz + qwx);
        
        (*out_matrix)[0][2] = 2 * (qxz + qwy);
        (*out_matrix)[1][2] = 2 * (qyz - qwx);
        (*out_matrix)[2][2] = 1 - 2 * (qxx +  qyy);
    }
    
    template <typename T>
    tmatrix3x3<T> matrix3_cast(tquaternion<T> const & q)
    {
        tmatrix3x3<T> result(T(1));
        matrix3_cast( q, &result );
        return result;

    }
    template <typename T>
    void matrix3_cast(tquaternion<T> const & q, tmatrix3x3<T>* out_matrix )
    {
        _matrix_cast( q, out_matrix );
    }
    
    
    template <typename T>
    tmatrix4x4<T> matrix4_cast(tquaternion<T> const & x)
    { tmatrix4x4<T> result; matrix4_cast( x, &result ); return result; }
    
    template <typename T>
    void matrix4_cast(tquaternion<T> const & x, tmatrix4x4<T>* out_matrix )
    {
        _matrix_cast( x, out_matrix );
        (*out_matrix)[3][0] = 0;
        (*out_matrix)[3][1] = 0;
        (*out_matrix)[3][2] = 0;
        (*out_matrix)[3][3] = 1;
    }
    
    template <typename T>
    tquaternion<T> tquaternion_cast(tmatrix3x3<T> const & m)
    {
        T fourXSquaredMinus1 = m[0][0] - m[1][1] - m[2][2];
        T fourYSquaredMinus1 = m[1][1] - m[0][0] - m[2][2];
        T fourZSquaredMinus1 = m[2][2] - m[0][0] - m[1][1];
        T fourWSquaredMinus1 = m[0][0] + m[1][1] + m[2][2];
        
        int biggestIndex = 0;
        T fourBiggestSquaredMinus1 = fourWSquaredMinus1;
        if(fourXSquaredMinus1 > fourBiggestSquaredMinus1)
        {
            fourBiggestSquaredMinus1 = fourXSquaredMinus1;
            biggestIndex = 1;
        }
        if(fourYSquaredMinus1 > fourBiggestSquaredMinus1)
        {
            fourBiggestSquaredMinus1 = fourYSquaredMinus1;
            biggestIndex = 2;
        }
        if(fourZSquaredMinus1 > fourBiggestSquaredMinus1)
        {
            fourBiggestSquaredMinus1 = fourZSquaredMinus1;
            biggestIndex = 3;
        }
        
        T biggestVal = std::sqrt(fourBiggestSquaredMinus1 + T(1)) * T(0.5);
        T mult = static_cast<T>(0.25) / biggestVal;
        
        tquaternion<T> Result;
        switch(biggestIndex)
        {
            case 0:
                Result.w = biggestVal;
                Result.x = (m[2][1] - m[1][2]) * mult;
                Result.y = (m[0][2] - m[2][0]) * mult;
                Result.z = (m[1][0] - m[0][1]) * mult;
                break;
            case 1:
                Result.w = (m[2][1] - m[1][2]) * mult;
                Result.x = biggestVal;
                Result.y = (m[1][0] + m[0][1]) * mult;
                Result.z = (m[0][2] + m[2][0]) * mult;
                break;
            case 2:
                Result.w = (m[0][2] - m[2][0]) * mult;
                Result.x = (m[1][0] + m[0][1]) * mult;
                Result.y = biggestVal;
                Result.z = (m[2][1] + m[1][2]) * mult;
                break;
            case 3:
                Result.w = (m[1][0] - m[0][1]) * mult;
                Result.x = (m[0][2] + m[2][0]) * mult;
                Result.y = (m[2][1] + m[1][2]) * mult;
                Result.z = biggestVal;
                break;
                
            default:					// Silence a -Wswitch-default warning in GCC. Should never actually get here. Assert is just for sanity.
                assert(false);
                break;
        }
        return Result;

    }
    
    template <typename T>
    tquaternion<T> tquaternion_cast(tmatrix4x4<T> const & x)
    {
        return tquaternion_cast( tmatrix3x3<T>( x ) );
    }
    
} }
