//
//  vector.h
//  graphic
//
//  Created by jiayi on 09/02/2017.
//  Copyright © 2017 jiayi. All rights reserved.
//

#ifndef tvector2_h
#define tvector2_h

namespace minerva { namespace graphic {
    
    ///
    /// @brief vector classes
    ///
    /// TODO: maybe I should make it derived from
    /// allocator to be trackable. Let's see if I
    /// have to do this later.
    ///
    template<typename T>
    class tvector2
    {
    public:
        typedef T value_type;
        
    public:
        tvector2() : tvector2( 0, 0 ){}
        tvector2( T ix, T iy) : x(ix), y(iy) {}
        ~tvector2(){}
        
    public:
        static tvector2 s_vector_zero;
        
    public:
        tvector2( tvector2&& );
        tvector2& operator= ( tvector2&& );
        tvector2( const tvector2& );
        tvector2& operator= ( const tvector2& );
        
    public:        
        tvector2& operator+= ( const tvector2& );
        tvector2& operator-= ( const tvector2& );
        tvector2& operator*= ( const tvector2& );
        tvector2& operator/= ( const tvector2& );
        
        tvector2& operator+= ( T );
        tvector2& operator-= ( T );
        tvector2& operator*= ( T );
        tvector2& operator/= ( T );
        
        tvector2& operator++ ();
        tvector2  operator++ (int);
        tvector2& operator-- ();
        tvector2  operator-- (int);
        
    public:
        tvector2& normalize();
        T dot( const tvector2& v ) const;
        T length();
        
    public:
        T x, y;
    };
    
    
    template< typename T >
    tvector2<T> operator+ ( const tvector2<T>&, const tvector2<T>& );
    template< typename T >
    tvector2<T> operator+ ( const tvector2<T>&, T );
    
    template< typename T >
    tvector2<T> operator- ( const tvector2<T>&, const tvector2<T>& );
    template< typename T >
    tvector2<T> operator- ( const tvector2<T>&, T );
    
    template< typename T >
    tvector2<T> operator* ( const tvector2<T>&, const tvector2<T>& );
    template< typename T >
    tvector2<T> operator* ( const tvector2<T>&, T );
    
    template< typename T >
    tvector2<T> operator/ ( const tvector2<T>&, const tvector2<T>& );
    template< typename T >
    tvector2<T> operator/ ( const tvector2<T>&, T );
    template< typename T >
    tvector2<T> operator/ ( T, const tvector2<T>& );
    
    template< typename T >
    bool operator== ( const tvector2<T>& v1, const tvector2<T>& v2 );
    
    template< typename T >
    bool operator!= ( const tvector2<T>& v1, const tvector2<T>& v2 );
} }

#include "math/vector2.inl"

#define mi_log_vector2(flag, v) \
    mi_log("x="#flag";y="#flag"\n", v.x,v.y,v.z );

#endif /* tvector2_h */
