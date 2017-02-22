//
//  vector.h
//  graphic
//
//  Created by jiayi on 09/02/2017.
//  Copyright © 2017 jiayi. All rights reserved.
//

#ifndef vector2_h
#define vector2_h

namespace minerva { namespace graphic {
    
    ///
    /// @brief vector classes
    ///
    /// TODO: maybe I should make it derived from
    /// allocator to be trackable. Let's see if I
    /// have to do this later.
    ///
    template<typename T>
    class vector2
    {
    public:
        vector2() : vector2( 0, 0 ){}
        vector2( T ix, T iy) : x(ix), y(iy) {}
        ~vector2(){}
        
    public:
        vector2( vector2&& );
        vector2& operator= ( vector2&& );
        vector2( const vector2& ) = delete;
        vector2& operator= ( const vector2& ) = delete;
        
    public:        
        vector2& operator+= ( const vector2& );
        vector2& operator-= ( const vector2& );
        vector2& operator*= ( const vector2& );
        vector2& operator/= ( const vector2& );
        
        vector2& operator+= ( T );
        vector2& operator-= ( T );
        vector2& operator*= ( T );
        vector2& operator/= ( T );
        
        vector2& operator++ ();
        vector2  operator++ (int);
        vector2& operator-- ();
        vector2  operator-- (int);
        
    public:
        T x, y;
    };
    
    
    template< typename T >
    vector2<T> operator+ ( const vector2<T>&, const vector2<T>& );
    template< typename T >
    vector2<T> operator+ ( const vector2<T>&, T );
    
    template< typename T >
    vector2<T> operator- ( const vector2<T>&, const vector2<T>& );
    template< typename T >
    vector2<T> operator- ( const vector2<T>&, T );
    
    template< typename T >
    vector2<T> operator* ( const vector2<T>&, const vector2<T>& );
    template< typename T >
    vector2<T> operator* ( const vector2<T>&, T );
    
    template< typename T >
    vector2<T> operator/ ( const vector2<T>&, const vector2<T>& );
    template< typename T >
    vector2<T> operator/ ( const vector2<T>&, T );
    template< typename T >
    vector2<T> operator/ ( T, const vector2<T>& );
    
    /// vector2 in float
    typedef vector2<float> vector2f;
    
    /// vector2 in int
    typedef vector2<int> vector2i;
    
    /// vector2 in double
    typedef vector2<double> vector2d;
    
} }

#include "math/vector2.inl"

#define mi_log_vector2(flag, v) \
    mi_log("x="#flag";y="#flag"\n", v.x,v.y,v.z );

#endif /* vector2_h */
