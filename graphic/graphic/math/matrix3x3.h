//
//  matrix3x3.h
//  graphic
//
//  Created by jiayi on 17/02/2017.
//  Copyright © 2017 jiayi. All rights reserved.
//

#ifndef tmatrix3x3_h
#define tmatrix3x3_h

#include "math/vector3.h"
#include "math/matrix4x4.h"

namespace minerva { namespace graphic {
    
    ///
    /// @brief matrix 4x4 classes
    ///
    /// TODO: maybe I should make it derived from
    /// allocator to be trackable. Let's see if I
    /// have to do this later.
    ///
    template<typename T>
    class tmatrix3x3
    {
        typedef tvector3<T> column_type;
        typedef tvector3<T> row_type;
        typedef size_t size_type;
        
    public:
        typedef T value_type;
        
    public:
        tmatrix3x3(){}
        explicit tmatrix3x3( T t );
        tmatrix3x3( const tmatrix3x3& );
        tmatrix3x3& operator= ( const tmatrix3x3& );
        
        tmatrix3x3( tmatrix3x3&& source );
        tmatrix3x3& operator= ( tmatrix3x3&& source );
        
        tmatrix3x3( const row_type& c1, const row_type& c2,
                  const row_type& c3 );
        
        tmatrix3x3(
                  T x1, T x2, T x3, 
                  T y1, T y2, T y3, 
                  T z1, T z2, T z3
                  );
        
        tmatrix3x3( const tmatrix4x4<T>& m );
        
    public:
        /*- Access Operators -*/
        row_type& operator[] ( size_type s );
        
        const row_type& operator[] ( size_type s ) const;
        
        /*- Unary Arithmetic Operators -*/
        template<typename U>
        tmatrix3x3<T>& operator+= ( U u );
        
        template<typename U>
        tmatrix3x3<T>& operator+= ( const tmatrix3x3<U>& m );
        
        template<typename U>
        tmatrix3x3<T>& operator-= ( U u );
        
        template<typename U>
        tmatrix3x3<T>& operator-= ( const tmatrix3x3<U>& m );
        
        template<typename U>
        tmatrix3x3<T>& operator*= ( U u );
        
        template<typename U>
        tmatrix3x3<T>& operator*= ( const tmatrix3x3<U>& m );
        
        template<typename U>
        tmatrix3x3<T>& operator/= ( U u );
        
        template<typename U>
        tmatrix3x3<T>& operator/= ( const tmatrix3x3<U>& m );
        
        /*- Increment & Decrement Operators -*/
        tmatrix3x3& operator++();
        
        tmatrix3x3& operator--();
        
        tmatrix3x3 operator++(int);
        
        tmatrix3x3 operator--(int);
        
        /*-- Matrix Related Functions --*/
        tmatrix3x3<T>& inverse();
        
        tmatrix3x3<T>& transpose();
        
        T determinant() const;
        
    protected:
        row_type _rows[3];
    };
    
    // arithmetic operators
    
    template<typename T>
    tmatrix3x3<T> operator+ ( const tmatrix3x3<T>& m, const T& t );
    
    template<typename T>
    tmatrix3x3<T> operator+ ( const T& t, const tmatrix3x3<T>& m );
    
    template<typename T>
    tmatrix3x3<T> operator+ ( const tmatrix3x3<T>& m1, const tmatrix3x3<T>& m2 );
    
    template<typename T>
    tmatrix3x3<T> operator- ( const tmatrix3x3<T>& m, const T& t );
    
    template<typename T>
    tmatrix3x3<T> operator- ( const T& t, const tmatrix3x3<T>& m );
    
    template<typename T>
    tmatrix3x3<T> operator- ( const tmatrix3x3<T>& m1, const tmatrix3x3<T>& m2 );
    
    template<typename T>
    tmatrix3x3<T> operator* ( const tmatrix3x3<T>& m, const T& t );
    
    template<typename T>
    tmatrix3x3<T> operator* ( const T& t, const tmatrix3x3<T>& m );
    
    template<typename T>
    typename tmatrix3x3<T>::column_type operator* ( const tmatrix3x3<T>& m, const typename tmatrix3x3<T>::column_type& v );
    
    template<typename T>
    typename tmatrix3x3<T>::row_type operator* ( const typename tmatrix3x3<T>::row_type& v, const tmatrix3x3<T>& m );
    
    template<typename T>
    tmatrix3x3<T> operator* ( const tmatrix3x3<T>& m1, const tmatrix3x3<T>& m2 );
    
    template<typename T>
    tmatrix3x3<T> operator/ ( const tmatrix3x3<T>& m1, const tmatrix3x3<T>& m2 );
    
    template<typename T, typename U>
    tmatrix3x3<T> operator/ ( const tmatrix3x3<T>& m, U );
    
    template<typename T, typename U>
    tmatrix3x3<T> operator/ ( U, const tmatrix3x3<T>& m );
    
    // boolean operators
    
    template<typename T>
    bool operator== ( const tmatrix3x3<T>& m1, const tmatrix3x3<T>& m2 );
    
    template<typename T>
    bool operator!= ( const tmatrix3x3<T>& m1, const tmatrix3x3<T>& m2 );
} }

#include "math/matrix3x3.inl"

#define mi_log_matrix3x3(flag, m) \
    mi_log( "Matrix:\n" ); \
    mi_log( #flag"    ,"#flag"    ,"#flag"\n", m[0][0], m[0][1], m[0][2]); \
    mi_log( #flag"    ,"#flag"    ,"#flag"\n", m[1][0], m[1][1], m[1][2]); \
    mi_log( #flag"    ,"#flag"    ,"#flag"\n", m[2][0], m[2][1], m[2][2]);

#endif /* tmatrix3x3_h */
