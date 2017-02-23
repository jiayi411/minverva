//
//  matrix4x4.h
//  graphic
//
//  Created by jiayi on 17/02/2017.
//  Copyright © 2017 jiayi. All rights reserved.
//

#ifndef matrix4x4_h
#define matrix4x4_h

#include "graphic/math/vector4.h"

namespace minerva { namespace graphic {
    
    ///
    /// @brief matrix 4x4 classes
    ///
    /// TODO: maybe I should make it derived from
    /// allocator to be trackable. Let's see if I
    /// have to do this later.
    ///
    template<typename T>
    class matrix4x4
    {
        typedef vector4<T> column_type;
        typedef vector4<T> row_type;
        typedef size_t size_type;
        
    public:
        typedef T value_type;
        
    public:
        matrix4x4(){}
        matrix4x4( T t );
        matrix4x4( const matrix4x4& );
        matrix4x4& operator= ( const matrix4x4& );
        
        matrix4x4( matrix4x4&& source );
        matrix4x4& operator= ( matrix4x4&& source );
        
        matrix4x4( const column_type& c1, const column_type& c2,
                  const column_type& c3, const column_type& c4 );
        
        matrix4x4(
                  T x1, T y1, T z1, T w1,
                  T x2, T y2, T z2, T w2,
                  T x3, T y3, T z3, T w3,
                  T x4, T y4, T z4, T w4
                  );
        
    public:
        /*- Access Operators -*/
        column_type& operator[] ( size_type s );
        
        const column_type& operator[] ( size_type s ) const;
        
        /*- Unary Arithmetic Operators -*/
        template<typename U>
        matrix4x4<T>& operator+= ( U u );
        
        template<typename U>
        matrix4x4<T>& operator+= ( const matrix4x4<U>& m );
        
        template<typename U>
        matrix4x4<T>& operator-= ( U u );
        
        template<typename U>
        matrix4x4<T>& operator-= ( const matrix4x4<U>& m );
        
        template<typename U>
        matrix4x4<T>& operator*= ( U u );
        
        template<typename U>
        matrix4x4<T>& operator*= ( const matrix4x4<U>& m );
        
        template<typename U>
        matrix4x4<T>& operator/= ( U u );
        
        template<typename U>
        matrix4x4<T>& operator/= ( const matrix4x4<U>& m );
        
        /*- Increment & Decrement Operators -*/
        matrix4x4& operator++();
        
        matrix4x4& operator--();
        
        matrix4x4 operator++(int);
        
        matrix4x4 operator--(int);
        
        /*-- Matrix Related Functions --*/
        matrix4x4<T>& inverse();
        
        matrix4x4<T>& transpose();
        
        T determinant() const;
        
    protected:
        row_type _rows[4];
    };
    
    // arithmetic operators
    
    template<typename T>
    matrix4x4<T> operator+ ( const matrix4x4<T>& m, const T& t );
    
    template<typename T>
    matrix4x4<T> operator+ ( const T& t, const matrix4x4<T>& m );
    
    template<typename T>
    matrix4x4<T> operator+ ( const matrix4x4<T>& m1, const matrix4x4<T>& m2 );
    
    template<typename T>
    matrix4x4<T> operator- ( const matrix4x4<T>& m, const T& t );
    
    template<typename T>
    matrix4x4<T> operator- ( const T& t, const matrix4x4<T>& m );
    
    template<typename T>
    matrix4x4<T> operator- ( const matrix4x4<T>& m1, const matrix4x4<T>& m2 );
    
    template<typename T>
    matrix4x4<T> operator* ( const matrix4x4<T>& m, const T& t );
    
    template<typename T>
    matrix4x4<T> operator* ( const T& t, const matrix4x4<T>& m );
    
    template<typename T>
    typename matrix4x4<T>::column_type operator* ( const matrix4x4<T>& m, const typename matrix4x4<T>::column_type& v );
    
    template<typename T>
    typename matrix4x4<T>::row_type operator* ( const typename matrix4x4<T>::row_type& v, const matrix4x4<T>& m );
    
    template<typename T>
    matrix4x4<T> operator* ( const matrix4x4<T>& m1, const matrix4x4<T>& m2 );
    
    template<typename T>
    matrix4x4<T> operator/ ( const matrix4x4<T>& m1, const matrix4x4<T>& m2 );
    
    template<typename T, typename U>
    matrix4x4<T> operator/ ( const matrix4x4<T>& m, U );
    
    template<typename T, typename U>
    matrix4x4<T> operator/ ( U, const matrix4x4<T>& m );
    
    // boolean operators
    
    template<typename T>
    bool operator== ( const matrix4x4<T>& m1, const matrix4x4<T>& m2 );
    
    template<typename T>
    bool operator!= ( const matrix4x4<T>& m1, const matrix4x4<T>& m2 );
} }

#include "math/matrix4x4.inl"

#define mi_log_matrix4x4(flag, m) \
    mi_log( "Matrix:\n" ); \
    mi_log( #flag"    ,"#flag"    ,"#flag"    ,"#flag"\n", m[0][0], m[0][1], m[0][2], m[0][3] ); \
    mi_log( #flag"    ,"#flag"    ,"#flag"    ,"#flag"\n", m[1][0], m[1][1], m[1][2], m[1][3] ); \
    mi_log( #flag"    ,"#flag"    ,"#flag"    ,"#flag"\n", m[2][0], m[2][1], m[2][2], m[2][3] ); \
    mi_log( #flag"    ,"#flag"    ,"#flag"    ,"#flag"\n", m[3][0], m[3][1], m[3][2], m[3][3] );

#endif /* matrix4x4_h */
