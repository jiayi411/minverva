namespace minerva { namespace graphic {
    
    template<typename T>
    matrix3x3<T>::matrix3x3( matrix3x3&& source )
    {
        _rows[0] = std::move(source[0]);
        _rows[1] = std::move(source[1]);
        _rows[2] = std::move(source[2]);
    }
    
    template<typename T>
    matrix3x3<T>& matrix3x3<T>::operator= ( matrix3x3<T>&& source )
    {
        _rows[0] = source[0];
        _rows[1] = source[1];
        _rows[2] = source[2];
        return *this;
    }
    
    template<typename T>
    matrix3x3<T>::matrix3x3( const matrix3x3& source )
    {
        _rows[0] = std::move(source[0]);
        _rows[1] = std::move(source[1]);
        _rows[2] = std::move(source[2]);
    }
    
    template<typename T>
    matrix3x3<T>::matrix3x3( const matrix4x4<T>& m )
    {
        _rows[0] = row_type( m[0] );
        _rows[1] = row_type( m[1] );
        _rows[2] = row_type( m[2] );
    }
    
    template<typename T>
    matrix3x3<T>& matrix3x3<T>::operator= ( const matrix3x3<T>& source )
    {
        _rows[0] = source[0];
        _rows[1] = source[1];
        _rows[2] = source[2];
        return *this;
    }
    
    template<typename T>
    matrix3x3<T>::matrix3x3( T t )
    {
        _rows[0] = row_type( t, 0, 0 );
        _rows[1] = row_type( 0, t, 0 );
        _rows[2] = row_type( 0, 0, t );
    }
    
    template<typename T>
    matrix3x3<T>::matrix3x3( const row_type& c1, const row_type& c2,
              const row_type& c3 )
    {
        _rows[0] = (c1);
        _rows[1] = (c2);
        _rows[2] = (c3);
    }
    
    template<typename T>
    matrix3x3<T>::matrix3x3(
              T x1, T x2, T x3, 
              T y1, T y2, T y3, 
              T z1, T z2, T z3
              )
    {
        _rows[0] = column_type( x1, x2, x3 );
        _rows[1] = column_type( y1, y2, y3 );
        _rows[2] = column_type( z1, z2, z3 );
    }
    
    /*- Access Operators -*/
    template<typename T>
    typename matrix3x3<T>::column_type& matrix3x3<T>::operator[] ( size_type s )
    { return _rows[s]; }
    
    template<typename T>
    const typename matrix3x3<T>::column_type& matrix3x3<T>::operator[] ( size_type s ) const
    { return _rows[s]; }
    
    /*- Unary Arithmetic Operators -*/
    template<typename T>
    template<typename U>
    matrix3x3<T>& matrix3x3<T>::operator+= ( U u )
    {
        _rows[0] += u;
        _rows[1] += u;
        _rows[2] += u;
        return *_rows;
    }
    
    template<typename T>
    template<typename U>
    matrix3x3<T>& matrix3x3<T>::operator+= ( const matrix3x3<U>& m )
    {
        _rows[0] += m[0];
        _rows[1] += m[1];
        _rows[2] += m[2];
        return *this;
    }
    
    template<typename T>
    template<typename U>
    matrix3x3<T>& matrix3x3<T>::operator-= ( U u )
    {
        _rows[0] -= u;
        _rows[1] -= u;
        _rows[2] -= u;
        return *_rows;
    }
    
    template<typename T>
    template<typename U>
    matrix3x3<T>& matrix3x3<T>::operator-= ( const matrix3x3<U>& m )
    {
        _rows[0] -= m[0];
        _rows[1] -= m[1];
        _rows[2] -= m[2];
        return *this;
    }
    
    template<typename T>
    template<typename U>
    matrix3x3<T>& matrix3x3<T>::operator*= ( U u )
    {
        _rows[0] *= u;
        _rows[1] *= u;
        _rows[2] *= u;
        return *this;
    }
    
    template<typename T>
    template<typename U>
    matrix3x3<T>& matrix3x3<T>::operator*= ( const matrix3x3<U>& m )
    {
        typename matrix3x3<T>::row_type const SrcA0 = _rows[0];
        typename matrix3x3<T>::row_type const SrcA1 = _rows[1];
        typename matrix3x3<T>::row_type const SrcA2 = _rows[2];
        
        typename matrix3x3<T>::row_type const SrcB0 = m[0];
        typename matrix3x3<T>::row_type const SrcB1 = m[1];
        typename matrix3x3<T>::row_type const SrcB2 = m[2];
        
        _rows[0] = SrcA0[0] * SrcB0 + SrcA0[1] * SrcB1 + SrcA0[2] * SrcB2;
        _rows[1] = SrcA1[0] * SrcB0 + SrcA1[1] * SrcB1 + SrcA1[2] * SrcB2;
        _rows[2] = SrcA2[0] * SrcB0 + SrcA2[1] * SrcB1 + SrcA2[2] * SrcB2;

        return *this;
    }
    
    template<typename T>
    template<typename U>
    matrix3x3<T>& matrix3x3<T>::operator/= ( U u )
    {
        _rows[0] /= u;
        _rows[1] /= u;
        _rows[2] /= u;
        return *this;
    }
    
    template<typename T>
    template<typename U>
    matrix3x3<T>& matrix3x3<T>::operator/= ( const matrix3x3<U>& m )
    {
        matrix3x3<U> copym(m);
        return * this = *this * copym.inverse();
    }
    
    /*- Increment & Decrement Operators -*/
    template<typename T>
    matrix3x3<T>& matrix3x3<T>::operator++()
    {
        ++_rows[0];
        ++_rows[1];
        ++_rows[2];
        return *this;
    }
    
    template<typename T>
    matrix3x3<T>& matrix3x3<T>::operator--()
    {
        --_rows[0];
        --_rows[1];
        --_rows[2];
        return *this;
    }
    
    template<typename T>
    matrix3x3<T> matrix3x3<T>::operator++(int)
    {
        matrix3x3 m = *this;
        ++m;
        return m;
    }
    
    template<typename T>
    matrix3x3<T> matrix3x3<T>::operator--(int)
    {
        matrix3x3 m = *this;
        --m;
        return m;
    }
    
    /*-- Matrix Related Functions --*/
    template<typename T>
    matrix3x3<T>& matrix3x3<T>::inverse()
    {
        matrix3x3<T> m = *this;
        T OneOverDeterminant = static_cast<T>(1) / (
                                                    + m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2])
                                                    - m[1][0] * (m[0][1] * m[2][2] - m[2][1] * m[0][2])
                                                    + m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]));
        
        matrix3x3<T>& Inverse = *this;
        Inverse[0][0] = + (m[1][1] * m[2][2] - m[2][1] * m[1][2]) * OneOverDeterminant;
        Inverse[1][0] = - (m[1][0] * m[2][2] - m[2][0] * m[1][2]) * OneOverDeterminant;
        Inverse[2][0] = + (m[1][0] * m[2][1] - m[2][0] * m[1][1]) * OneOverDeterminant;
        Inverse[0][1] = - (m[0][1] * m[2][2] - m[2][1] * m[0][2]) * OneOverDeterminant;
        Inverse[1][1] = + (m[0][0] * m[2][2] - m[2][0] * m[0][2]) * OneOverDeterminant;
        Inverse[2][1] = - (m[0][0] * m[2][1] - m[2][0] * m[0][1]) * OneOverDeterminant;
        Inverse[0][2] = + (m[0][1] * m[1][2] - m[1][1] * m[0][2]) * OneOverDeterminant;
        Inverse[1][2] = - (m[0][0] * m[1][2] - m[1][0] * m[0][2]) * OneOverDeterminant;
        Inverse[2][2] = + (m[0][0] * m[1][1] - m[1][0] * m[0][1]) * OneOverDeterminant;
        
        return *this;
    }
    
    template<typename T>
    matrix3x3<T>& matrix3x3<T>::transpose()
    {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < i; ++j) {
                std::swap( (*this)[i][j], (*this)[j][i] );
            }
        }
        return *this;
    }
    
    template<typename T>
    T matrix3x3<T>::determinant() const
    {
        const matrix3x3<T>& m = *this;
        return (+ m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2])
                - m[1][0] * (m[0][1] * m[2][2] - m[2][1] * m[0][2])
                + m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]));
    }
    
    // arithmetic operators
    
    template<typename T>
    matrix3x3<T> operator+ ( const matrix3x3<T>& m, const T& t )
    { return matrix3x3<T>( m[0] + t, m[1] + t, m[2] + t ); }
    
    template<typename T>
    matrix3x3<T> operator+ ( const T& t, const matrix3x3<T>& m )
    { return matrix3x3<T>( m[0] + t, m[1] + t, m[2] + t ); }
    
    template<typename T>
    matrix3x3<T> operator+ ( const matrix3x3<T>& m1, const matrix3x3<T>& m2 )
    { return matrix3x3<T>( m1[0] + m2[0], m1[1] + m2[1], m1[2] + m2[2] ); }
    
    template<typename T>
    matrix3x3<T> operator- ( const matrix3x3<T>& m, const T& t )
    { return matrix3x3<T>( m[0] - t, m[1] - t, m[2] - t ); }
    
    template<typename T>
    matrix3x3<T> operator- ( const T& t, const matrix3x3<T>& m )
    { return matrix3x3<T>( t - m[0], t - m[1], t - m[2] ); }
    
    template<typename T>
    matrix3x3<T> operator- ( const matrix3x3<T>& m1, const matrix3x3<T>& m2 )
    { return matrix3x3<T>( m1[0] - m2[0], m1[1] - m2[1], m1[2] - m2[2] ); }
    
    template<typename T>
    matrix3x3<T> operator* ( const matrix3x3<T>& m, const T& t )
    { return matrix3x3<T>( m[0] * t, m[1] * t, m[2] * t ); }
    
    template<typename T>
    matrix3x3<T> operator* ( const T& t, const matrix3x3<T>& m )
    { return matrix3x3<T>( m[0] * t, m[1] * t, m[2] * t ); }
    
    template<typename T>
    typename matrix3x3<T>::column_type operator* ( const matrix3x3<T>& m, const typename matrix3x3<T>::column_type& v )
    {
        return typename matrix3x3<T>::column_type( m[0] * v[0] + m[1] * v[1] + m[2] * v[2] );
    }
    
    template<typename T>
    typename matrix3x3<T>::row_type operator* ( const typename matrix3x3<T>::row_type& v, const matrix3x3<T>& m )
    {
        typename matrix3x3<T>::row_type r1 = v[0] * m[0];
        typename matrix3x3<T>::row_type r2 = v[1] * m[1];
        typename matrix3x3<T>::row_type r3 = v[2] * m[2];
        return typename matrix3x3<T>::row_type(
                                               r1.x + r1.y + r1.z ,
                                               r2.x + r2.y + r2.z ,
                                               r3.x + r3.y + r3.z
        );
    }
    
    template<typename T>
    matrix3x3<T> operator* ( const matrix3x3<T>& m1, const matrix3x3<T>& m2 )
    {
        matrix3x3<T> result = m1;
        return result *= m2;
    }
    
    template<typename T>
    matrix3x3<T> operator/ ( const matrix3x3<T>& m1, const matrix3x3<T>& m2 )
    {
        matrix3x3<T> result = m1;
        return result /= m2;
    }
    
    template<typename T, typename U>
    matrix3x3<T> operator/ ( const matrix3x3<T>& m, U t )
    { return matrix3x3<T>( m[0] / t, m[1] / t, m[2] / t ); }
    
    template<typename T, typename U>
    matrix3x3<T> operator/ ( U t, const matrix3x3<T>& m )
    { return matrix3x3<T>( t / m[0], t / m[1], t / m[2] ); }
    
    // boolean operators
    
    template<typename T>
    bool operator== ( const matrix3x3<T>& m1, const matrix3x3<T>& m2 )
    { return ( m1[0] == m2[0] && m1[1] == m2[1] && m1[2] == m2[2] ); }
    
    template<typename T>
    bool operator!= ( const matrix3x3<T>& m1, const matrix3x3<T>& m2 )
    { return !(m1 == m2); }
    
} }
