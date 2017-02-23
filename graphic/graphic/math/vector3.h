//
//  vector.h
//  graphic
//
//  Created by jiayi on 09/02/2017.
//  Copyright © 2017 jiayi. All rights reserved.
//

#ifndef vector3_h
#define vector3_h

namespace minerva { namespace graphic {
    
    ///
    /// @brief vector classes
    ///
    /// TODO: maybe I should make it derived from
    /// allocator to be trackable. Let's see if I
    /// have to do this later.
    ///
    template<typename T>
    class vector3
    {
        typedef size_t size_type;
        
    public:
        vector3() : vector3( 0, 0, 0 ){}
        vector3( T ix, T iy, T iz) : x(ix), y(iy), z(iz) {}
        ~vector3(){}
        
    public:
        vector3( vector3&& );
        vector3& operator= ( vector3&& );
        vector3( const vector3& );
        vector3& operator= ( const vector3& );
        
    public:
        T& operator[] ( size_type s );
        const T& operator[] ( size_type s ) const;
        
        vector3& operator+= ( const vector3& );
        vector3& operator-= ( const vector3& );
        vector3& operator*= ( const vector3& );
        vector3& operator/= ( const vector3& );
        
        vector3& operator+= ( T );
        vector3& operator-= ( T );
        vector3& operator*= ( T );
        vector3& operator/= ( T );
        
        vector3& operator++ ();
        vector3  operator++ (int);
        vector3& operator-- ();
        vector3  operator-- (int);
        
        /*-- mathematics --*/
        vector3& normalize();
        vector3 cross( const vector3& v ) const;
        T dot( const vector3& v ) const;
        T length() const;
        
    public:
        union { T x, r; };
        union { T y, g; };
        union { T z, b; };
    };
    
    
    template< typename T >
    vector3<T> operator+ ( const vector3<T>&, const vector3<T>& );
    template< typename T >
    vector3<T> operator+ ( const vector3<T>&, T );
    
    template< typename T >
    vector3<T> operator- ( const vector3<T>&, const vector3<T>& );
    template< typename T >
    vector3<T> operator- ( const vector3<T>&, T );
    
    template< typename T >
    vector3<T> operator* ( const vector3<T>&, const vector3<T>& );
    template< typename T >
    vector3<T> operator* ( const vector3<T>&, T );
    template< typename T >
    vector3<T> operator* ( T, const vector3<T>& );
    
    template< typename T >
    vector3<T> operator/ ( const vector3<T>&, const vector3<T>& );
    template< typename T >
    vector3<T> operator/ ( const vector3<T>&, T );
    template< typename T >
    vector3<T> operator/ ( T, const vector3<T>& );
    
    /// vector3 in float
    typedef vector3<float> vector3f;
    
    /// vector3 in int
    typedef vector3<int> vector3i;
    
    /// vector3 in double
    typedef vector3<double> vector3d;
    
} }

#include "math/vector3.inl"

#define mi_log_vector3(flag, v) \
    mi_log("x="#flag";y="#flag";z="#flag"\n", v.x,v.y,v.z );

#endif /* vector3_h */
