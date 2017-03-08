//
//  matrix3x3.h
//  graphic
//
//  Created by jiayi on 17/02/2017.
//  Copyright © 2017 jiayi. All rights reserved.
//

#ifndef matrix3x3_h
#define matrix3x3_h

#include "graphic/math/vector3.h"
#include "graphic/math/matrix4x4.h"

namespace minerva { namespace graphic {
    
    ///
    /// @brief matrix 4x4 classes
    ///
    /// TODO: maybe I should make it derived from
    /// allocator to be trackable. Let's see if I
    /// have to do this later.
    ///
    template<typename T>
    class matrix3x3
    {
        typedef vector3<T> column_type;
        typedef vector3<T> row_type;
        typedef size_t size_type;
        
    public:
        typedef T value_type;
        
    public:
        matrix3x3(){}
        explicit matrix3x3( T t );
        matrix3x3( const matrix3x3& );
        matrix3x3& operator= ( const matrix3x3& );
        
        matrix3x3( matrix3x3&& source );
        matrix3x3& operator= ( matrix3x3&& source );
        
        matrix3x3( const row_type& c1, const row_type& c2,
                  const row_type& c3 );
        
        matrix3x3(
                  T x1, T x2, T x3, 
                  T y1, T y2, T y3, 
                  T z1, T z2, T z3
                  );
        
        matrix3x3( const matrix4x4<T>& m );
        
    public:
        /*- Access Operators -*/
        row_type& operator[] ( size_type s );
        
        const row_type& operator[] ( size_type s ) const;
        
        /*- Unary Arithmetic Operators -*/
        template<typename U>
        matrix3x3<T>& operator+= ( U u );
        
        template<typename U>
        matrix3x3<T>& operator+= ( const matrix3x3<U>& m );
        
        template<typename U>
        matrix3x3<T>& operator-= ( U u );
        
        template<typename U>
        matrix3x3<T>& operator-= ( const matrix3x3<U>& m );
        
        template<typename U>
        matrix3x3<T>& operator*= ( U u );
        
        template<typename U>
        matrix3x3<T>& operator*= ( const matrix3x3<U>& m );
        
        template<typename U>
        matrix3x3<T>& operator/= ( U u );
        
        template<typename U>
        matrix3x3<T>& operator/= ( const matrix3x3<U>& m );
        
        /*- Increment & Decrement Operators -*/
        matrix3x3& operator++();
        
        matrix3x3& operator--();
        
        matrix3x3 operator++(int);
        
        matrix3x3 operator--(int);
        
        /*-- Matrix Related Functions --*/
        matrix3x3<T>& inverse();
        
        matrix3x3<T>& transpose();
        
        T determinant() const;
        
    protected:
        row_type _rows[3];
    };
    
    // arithmetic operators
    
    template<typename T>
    matrix3x3<T> operator+ ( const matrix3x3<T>& m, const T& t );
    
    template<typename T>
    matrix3x3<T> operator+ ( const T& t, const matrix3x3<T>& m );
    
    template<typename T>
    matrix3x3<T> operator+ ( const matrix3x3<T>& m1, const matrix3x3<T>& m2 );
    
    template<typename T>
    matrix3x3<T> operator- ( const matrix3x3<T>& m, const T& t );
    
    template<typename T>
    matrix3x3<T> operator- ( const T& t, const matrix3x3<T>& m );
    
    template<typename T>
    matrix3x3<T> operator- ( const matrix3x3<T>& m1, const matrix3x3<T>& m2 );
    
    template<typename T>
    matrix3x3<T> operator* ( const matrix3x3<T>& m, const T& t );
    
    template<typename T>
    matrix3x3<T> operator* ( const T& t, const matrix3x3<T>& m );
    
    template<typename T>
    typename matrix3x3<T>::column_type operator* ( const matrix3x3<T>& m, const typename matrix3x3<T>::column_type& v );
    
    template<typename T>
    typename matrix3x3<T>::row_type operator* ( const typename matrix3x3<T>::row_type& v, const matrix3x3<T>& m );
    
    template<typename T>
    matrix3x3<T> operator* ( const matrix3x3<T>& m1, const matrix3x3<T>& m2 );
    
    template<typename T>
    matrix3x3<T> operator/ ( const matrix3x3<T>& m1, const matrix3x3<T>& m2 );
    
    template<typename T, typename U>
    matrix3x3<T> operator/ ( const matrix3x3<T>& m, U );
    
    template<typename T, typename U>
    matrix3x3<T> operator/ ( U, const matrix3x3<T>& m );
    
    // boolean operators
    
    template<typename T>
    bool operator== ( const matrix3x3<T>& m1, const matrix3x3<T>& m2 );
    
    template<typename T>
    bool operator!= ( const matrix3x3<T>& m1, const matrix3x3<T>& m2 );
    
    // typedefs
    typedef matrix3x3<float> matrix3x3f;
    typedef matrix3x3<int> matrix3x3i;
    typedef matrix3x3<double> matrix3x3d;
} }

#include "math/matrix3x3.inl"

#define mi_log_matrix3x3(flag, m) \
    mi_log( "Matrix:\n" ); \
    mi_log( #flag"    ,"#flag"    ,"#flag"\n", m[0][0], m[0][1], m[0][2]); \
    mi_log( #flag"    ,"#flag"    ,"#flag"\n", m[1][0], m[1][1], m[1][2]); \
    mi_log( #flag"    ,"#flag"    ,"#flag"\n", m[2][0], m[2][1], m[2][2]);

#endif /* matrix3x3_h */
