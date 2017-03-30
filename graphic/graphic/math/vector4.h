//
//  vector.h
//  graphic
//
//  Created by jiayi on 09/02/2017.
//  Copyright © 2017 jiayi. All rights reserved.
//

#ifndef tvector4_h
#define tvector4_h

#include <stddef.h>
#include "foundation/basic/defines.h"

namespace minerva { namespace graphic {
    
    template<typename T> class tvector3;
    
    ///
    /// @brief vector classes
    ///
    /// TODO: maybe I should make it derived from
    /// allocator to be trackable. Let's see if I
    /// have to do this later.
    ///
    template<typename T>
    class tvector4
    {
        typedef size_t size_type;
        
    public:
        typedef T value_type;
        
    public:
        tvector4() : tvector4( 0, 0, 0, 0 ){}
        tvector4( T t ) : tvector4( t,t,t,t) {}
        tvector4( T ix, T iy, T iz, T iw ) : x(ix), y(iy), z(iz), w(iw) {}
        tvector4( const tvector3<T>& v );
        ~tvector4(){}
        
    public:
        static tvector4 s_vector_zero;
        
    public:
        tvector4( tvector4&& );
        tvector4& operator= ( tvector4&& );
        tvector4( const tvector4& );
        tvector4& operator= ( const tvector4& );
        
    public:
        T& operator[] ( size_type s );
        const T& operator[] ( size_type s ) const;
        
        tvector4& operator+= ( const tvector4& );
        tvector4& operator-= ( const tvector4& );
        tvector4& operator*= ( const tvector4& );
        tvector4& operator/= ( const tvector4& );
        
        template<typename U>
        tvector4& operator+= ( U );
        
        template<typename U>
        tvector4& operator-= ( U );
        
        template<typename U>
        tvector4& operator*= ( U );
        
        template<typename U>
        tvector4& operator/= ( U );
        
        tvector4& operator++ ();
        tvector4  operator++ (int);
        tvector4& operator-- ();
        tvector4  operator-- (int);
        
        /*-- mathematics --*/
        tvector4& normalize();
        T dot( const tvector4& v ) const;
        T length();
        T length2();
        
    public:
        union { T x, r; };
        union { T y, g; };
        union { T z, b; };
        union { T w, a; };
    };
    
    
    template< typename T >
    tvector4<T> operator+ ( const tvector4<T>&, const tvector4<T>& );
    template< typename T, typename U >
    tvector4<T> operator+ ( const tvector4<T>&, U );
    
    template< typename T >
    tvector4<T> operator- ( const tvector4<T>&, const tvector4<T>& );
    template< typename T, typename U >
    tvector4<T> operator- ( const tvector4<T>&, U );
    
    template< typename T >
    tvector4<T> operator* ( const tvector4<T>&, const tvector4<T>& );
    template< typename T, typename U >
    tvector4<T> operator* ( const tvector4<T>&, U );
    template< typename T, typename U >
    tvector4<T> operator* ( U, const tvector4<T>& );
    
    template< typename T >
    tvector4<T> operator/ ( const tvector4<T>&, const tvector4<T>& );
    template< typename T, typename U >
    tvector4<T> operator/ ( const tvector4<T>&, U );
    template< typename T, typename U >
    tvector4<T> operator/ ( U, const tvector4<T>& );
    
} }

#include "math/vector4.inl"

#define mi_log_vector4(flag, v) \
    mi_log("x="#flag";y="#flag";z="#flag";w="#flag"\n", v.x,v.y,v.z,v.w );

#endif /* tvector4_h */
