//
//  matrix4x4.h
//  graphic
//
//  Created by jiayi on 17/02/2017.
//  Copyright © 2017 jiayi. All rights reserved.
//

#ifndef tmatrix4x4_h
#define tmatrix4x4_h

#include "math/vector4.h"

namespace minerva { namespace graphic {
    
    template<typename T> class tmatrix3x3;
    ///
    /// @brief matrix 4x4 classes
    ///
    /// TODO: maybe I should make it derived from
    /// allocator to be trackable. Let's see if I
    /// have to do this later.
    ///
    template<typename T>
    class tmatrix4x4
    {
        typedef tvector4<T> column_type;
        typedef tvector4<T> row_type;
        typedef size_t size_type;
        
    public:
        typedef T value_type;
        
    public:
        tmatrix4x4(){}
        explicit tmatrix4x4( T t );
        tmatrix4x4( const tmatrix4x4& );
        tmatrix4x4& operator= ( const tmatrix4x4& );
        
        tmatrix4x4( tmatrix4x4&& source );
        tmatrix4x4& operator= ( tmatrix4x4&& source );
        
        tmatrix4x4( const row_type& c1, const row_type& c2,
                  const row_type& c3, const row_type& c4 );
        
        tmatrix4x4( const tmatrix3x3<T>& m );
        tmatrix4x4& operator= ( const tmatrix3x3<T>& source );
        
        tmatrix4x4(
                  T x1, T x2, T x3, T x4,
                  T y1, T y2, T y3, T y4,
                  T z1, T z2, T z3, T z4,
                  T w1, T w2, T w3, T w4
                  );
        
    public:
        /*- Access Operators -*/
        column_type& operator[] ( size_type s );
        
        const column_type& operator[] ( size_type s ) const;
        
        /*- Unary Arithmetic Operators -*/
        template<typename U>
        tmatrix4x4<T>& operator+= ( U u );
        
        template<typename U>
        tmatrix4x4<T>& operator+= ( const tmatrix4x4<U>& m );
        
        template<typename U>
        tmatrix4x4<T>& operator-= ( U u );
        
        template<typename U>
        tmatrix4x4<T>& operator-= ( const tmatrix4x4<U>& m );
        
        template<typename U>
        tmatrix4x4<T>& operator*= ( U u );
        
        template<typename U>
        tmatrix4x4<T>& operator*= ( const tmatrix4x4<U>& m );
        
        template<typename U>
        tmatrix4x4<T>& operator/= ( U u );
        
        template<typename U>
        tmatrix4x4<T>& operator/= ( const tmatrix4x4<U>& m );
        
        /*- Increment & Decrement Operators -*/
        tmatrix4x4& operator++();
        
        tmatrix4x4& operator--();
        
        tmatrix4x4 operator++(int);
        
        tmatrix4x4 operator--(int);
        
        /*-- Matrix Related Functions --*/
        tmatrix4x4<T>& inverse();
        
        tmatrix4x4<T>& transpose();
        
        T determinant() const;
        
        tmatrix4x4& scale( T x, T y, T z );
        
    protected:
        row_type _rows[4];
    };
    
    // arithmetic operators
    
    template<typename T>
    tmatrix4x4<T> operator+ ( const tmatrix4x4<T>& m, const T& t );
    
    template<typename T>
    tmatrix4x4<T> operator+ ( const T& t, const tmatrix4x4<T>& m );
    
    template<typename T>
    tmatrix4x4<T> operator+ ( const tmatrix4x4<T>& m1, const tmatrix4x4<T>& m2 );
    
    template<typename T>
    tmatrix4x4<T> operator- ( const tmatrix4x4<T>& m, const T& t );
    
    template<typename T>
    tmatrix4x4<T> operator- ( const T& t, const tmatrix4x4<T>& m );
    
    template<typename T>
    tmatrix4x4<T> operator- ( const tmatrix4x4<T>& m1, const tmatrix4x4<T>& m2 );
    
    template<typename T>
    tmatrix4x4<T> operator* ( const tmatrix4x4<T>& m, const T& t );
    
    template<typename T>
    tmatrix4x4<T> operator* ( const T& t, const tmatrix4x4<T>& m );
    
    template<typename T>
    typename tmatrix4x4<T>::column_type operator* ( const tmatrix4x4<T>& m, const typename tmatrix4x4<T>::column_type& v );
    
    template<typename T>
    typename tmatrix4x4<T>::row_type operator* ( const typename tmatrix4x4<T>::row_type& v, const tmatrix4x4<T>& m );
    
    template<typename T>
    tmatrix4x4<T> operator* ( const tmatrix4x4<T>& m1, const tmatrix4x4<T>& m2 );
    
    template<typename T>
    tmatrix4x4<T> operator/ ( const tmatrix4x4<T>& m1, const tmatrix4x4<T>& m2 );
    
    template<typename T, typename U>
    tmatrix4x4<T> operator/ ( const tmatrix4x4<T>& m, U );
    
    template<typename T, typename U>
    tmatrix4x4<T> operator/ ( U, const tmatrix4x4<T>& m );
    
    // boolean operators
    
    template<typename T>
    bool operator== ( const tmatrix4x4<T>& m1, const tmatrix4x4<T>& m2 );
    
    template<typename T>
    bool operator!= ( const tmatrix4x4<T>& m1, const tmatrix4x4<T>& m2 );
} }

#include "math/matrix4x4.inl"

#define mi_log_matrix4x4(flag, m) \
    mi_log( "Matrix:\n" ); \
    mi_log( #flag"    ,"#flag"    ,"#flag"    ,"#flag"\n", m[0][0], m[0][1], m[0][2], m[0][3] ); \
    mi_log( #flag"    ,"#flag"    ,"#flag"    ,"#flag"\n", m[1][0], m[1][1], m[1][2], m[1][3] ); \
    mi_log( #flag"    ,"#flag"    ,"#flag"    ,"#flag"\n", m[2][0], m[2][1], m[2][2], m[2][3] ); \
    mi_log( #flag"    ,"#flag"    ,"#flag"    ,"#flag"\n", m[3][0], m[3][1], m[3][2], m[3][3] );

#endif /* matrix4x4_h */
