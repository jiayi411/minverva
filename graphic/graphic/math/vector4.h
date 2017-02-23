//
//  vector.h
//  graphic
//
//  Created by jiayi on 09/02/2017.
//  Copyright © 2017 jiayi. All rights reserved.
//

#ifndef vector4_h
#define vector4_h

#include <stddef.h>
#include "foundation/basic/defines.h"

namespace minerva { namespace graphic {
    
    ///
    /// @brief vector classes
    ///
    /// TODO: maybe I should make it derived from
    /// allocator to be trackable. Let's see if I
    /// have to do this later.
    ///
    template<typename T>
    class vector4
    {
        typedef size_t size_type;

    public:
        vector4() : vector4( 0, 0, 0, 0 ){}
        vector4( T t ) : vector4( t,t,t,t) {}
        vector4( T ix, T iy, T iz, T iw ) : x(ix), y(iy), z(iz), w(iw) {}
        ~vector4(){}
        
    public:
        vector4( vector4&& );
        vector4& operator= ( vector4&& );
        vector4( const vector4& );
        vector4& operator= ( const vector4& );
        
    public:
        T& operator[] ( size_type s );
        const T& operator[] ( size_type s ) const;
        
        vector4& operator+= ( const vector4& );
        vector4& operator-= ( const vector4& );
        vector4& operator*= ( const vector4& );
        vector4& operator/= ( const vector4& );
        
        template<typename U>
        vector4& operator+= ( U );
        
        template<typename U>
        vector4& operator-= ( U );
        
        template<typename U>
        vector4& operator*= ( U );
        
        template<typename U>
        vector4& operator/= ( U );
        
        vector4& operator++ ();
        vector4  operator++ (int);
        vector4& operator-- ();
        vector4  operator-- (int);
        
        /*-- mathematics --*/
        vector4& normalize();
        T dot( const vector4& v ) const;
        T length();
        
    public:
        union { T x, r; };
        union { T y, g; };
        union { T z, b; };
        union { T w, a; };
    };
    
    
    template< typename T >
    vector4<T> operator+ ( const vector4<T>&, const vector4<T>& );
    template< typename T, typename U >
    vector4<T> operator+ ( const vector4<T>&, U );
    
    template< typename T >
    vector4<T> operator- ( const vector4<T>&, const vector4<T>& );
    template< typename T, typename U >
    vector4<T> operator- ( const vector4<T>&, U );
    
    template< typename T >
    vector4<T> operator* ( const vector4<T>&, const vector4<T>& );
    template< typename T, typename U >
    vector4<T> operator* ( const vector4<T>&, U );
    template< typename T, typename U >
    vector4<T> operator* ( U, const vector4<T>& );
    
    template< typename T >
    vector4<T> operator/ ( const vector4<T>&, const vector4<T>& );
    template< typename T, typename U >
    vector4<T> operator/ ( const vector4<T>&, U );
    template< typename T, typename U >
    vector4<T> operator/ ( U, const vector4<T>& );
    
    /// vector4 in float
    typedef vector4<float> vector4f;
    
    /// vector4 in int
    typedef vector4<int> vector4i;
    
    /// vector4 in double
    typedef vector4<double> vector4d;
    
} }

#include "math/vector4.inl"

#define mi_log_vector4(flag, v) \
    mi_log("x="#flag";y="#flag";z="#flag";w="#flag"\n", v.x,v.y,v.z,v.w );

#endif /* vector4_h */
