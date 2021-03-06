//
//  vector.h
//  graphic
//
//  Created by jiayi on 09/02/2017.
//  Copyright © 2017 jiayi. All rights reserved.
//

#ifndef tvector3_h
#define tvector3_h
#include "math/vector4.h"

namespace minerva { namespace graphic {
    
    ///
    /// @brief vector classes
    ///
    /// TODO: maybe I should make it derived from
    /// allocator to be trackable. Let's see if I
    /// have to do this later.
    ///
    template<typename T>
    class tvector3
    {
        typedef size_t size_type;
    public:
        typedef T value_type;
        
    public:
        tvector3() : tvector3( 0, 0, 0 ){}
        tvector3( T ix, T iy, T iz) : x(ix), y(iy), z(iz) {}
        tvector3( const tvector4<T>& v ) : tvector3( v.x, v.y, v.z ){}
        ~tvector3(){}
        
    public:
        static tvector3 s_vector_x;
        static tvector3 s_vector_y;
        static tvector3 s_vector_z;
        static tvector3 s_vector_zero;
        
    public:
        tvector3( tvector3&& );
        tvector3& operator= ( tvector3&& );
        tvector3( const tvector3& );
        tvector3& operator= ( const tvector3& );
        
    public:
        tvector3 operator- ();
        T& operator[] ( size_type s );
        const T& operator[] ( size_type s ) const;
        
        tvector3& operator+= ( const tvector3& );
        tvector3& operator-= ( const tvector3& );
        tvector3& operator*= ( const tvector3& );
        tvector3& operator/= ( const tvector3& );
        
        tvector3& operator+= ( T );
        tvector3& operator-= ( T );
        tvector3& operator*= ( T );
        tvector3& operator/= ( T );
        
        tvector3& operator++ ();
        tvector3  operator++ (int);
        tvector3& operator-- ();
        tvector3  operator-- (int);
        
        /*-- mathematics --*/
        tvector3& normalize();        
        tvector3 cross( const tvector3& v ) const;
        T dot( const tvector3& v ) const;
        T length() const;
        T length2() const;
        
    public:
        union { T x, r; };
        union { T y, g; };
        union { T z, b; };
    };
    
    
    template< typename T >
    tvector3<T> operator+ ( const tvector3<T>&, const tvector3<T>& );
    template< typename T >
    tvector3<T> operator+ ( const tvector3<T>&, T );
    
    template< typename T >
    tvector3<T> operator- ( const tvector3<T>&, const tvector3<T>& );
    template< typename T >
    tvector3<T> operator- ( const tvector3<T>&, T );
    
    template< typename T >
    tvector3<T> operator* ( const tvector3<T>&, const tvector3<T>& );
    template< typename T >
    tvector3<T> operator* ( const tvector3<T>&, T );
    template< typename T >
    tvector3<T> operator* ( T, const tvector3<T>& );
    
    template< typename T >
    tvector3<T> operator/ ( const tvector3<T>&, const tvector3<T>& );
    template< typename T >
    tvector3<T> operator/ ( const tvector3<T>&, T );
    template< typename T >
    tvector3<T> operator/ ( T, const tvector3<T>& );
    
    template< typename T >
    bool operator== ( const tvector3<T>& v1, const tvector3<T>& v2 );
    template< typename T >
    bool operator!= ( const tvector3<T>& v1, const tvector3<T>& v2 );
    
    template<typename T> tvector3<T> tvector3<T>::s_vector_zero;
    template<typename T> tvector3<T> tvector3<T>::s_vector_x;
    template<typename T> tvector3<T> tvector3<T>::s_vector_y;
    template<typename T> tvector3<T> tvector3<T>::s_vector_z;
    
} }

#include "math/vector3.inl"

#define mi_log_vector3(flag, v) \
    mi_log("x="#flag";y="#flag";z="#flag"\n", v.x,v.y,v.z );

#endif /* tvector3_h */
