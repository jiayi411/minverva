namespace minerva { namespace graphic {
    
    template<typename T>
    matrix4x4<T>::matrix4x4( matrix4x4&& source )
    {
        columns[0] = std::move(source[0]);
        columns[1] = std::move(source[1]);
        columns[2] = std::move(source[2]);
        columns[3] = std::move(source[3]);
    }
    
    template<typename T>
    matrix4x4<T>& matrix4x4<T>::operator= ( matrix4x4<T>&& source )
    {
        columns[0] = source[0];
        columns[1] = source[1];
        columns[2] = source[2];
        columns[3] = source[3];
        return *this;
    }
    
    template<typename T>
    matrix4x4<T>::matrix4x4( const matrix4x4& source )
    {
        columns[0] = std::move(source[0]);
        columns[1] = std::move(source[1]);
        columns[2] = std::move(source[2]);
        columns[3] = std::move(source[3]);
    }
    
    template<typename T>
    matrix4x4<T>& matrix4x4<T>::operator= ( const matrix4x4<T>& source )
    {
        columns[0] = source[0];
        columns[1] = source[1];
        columns[2] = source[2];
        columns[3] = source[3];
        return *this;
    }
    
    template<typename T>
    matrix4x4<T>::matrix4x4( const column_type& c1, const column_type& c2,
              const column_type& c3, const column_type& c4 )
    {
        columns[0] = (c1);
        columns[1] = (c2);
        columns[2] = (c3);
        columns[3] = (c4);
    }
    
    template<typename T>
    matrix4x4<T>::matrix4x4(
              T x1, T y1, T z1, T w1,
              T x2, T y2, T z2, T w2,
              T x3, T y3, T z3, T w3,
              T x4, T y4, T z4, T w4
              )
    {
        columns[0] = column_type( x1, x2, x3, x4 );
        columns[1] = column_type( y1, y2, y3, y4 );
        columns[2] = column_type( z1, z2, z3, z4 );
        columns[3] = column_type( w1, w2, w3, w4 );
    }
    
    /*- Access Operators -*/
    template<typename T>
    typename matrix4x4<T>::column_type& matrix4x4<T>::operator[] ( size_type s )
    { return columns[s]; }
    
    template<typename T>
    const typename matrix4x4<T>::column_type& matrix4x4<T>::operator[] ( size_type s ) const
    { return columns[s]; }
    
    /*- Unary Arithmetic Operators -*/
    template<typename T>
    template<typename U>
    matrix4x4<T>& matrix4x4<T>::operator+= ( U u )
    {
        columns[0] += u;
        columns[1] += u;
        columns[2] += u;
        columns[3] += u;
        return *columns;
    }
    
    template<typename T>
    template<typename U>
    matrix4x4<T>& matrix4x4<T>::operator+= ( const matrix4x4<U>& m )
    {
        columns[0] += m[0];
        columns[1] += m[1];
        columns[2] += m[2];
        columns[3] += m[3];
        return *this;
    }
    
    template<typename T>
    template<typename U>
    matrix4x4<T>& matrix4x4<T>::operator-= ( U u )
    {
        columns[0] -= u;
        columns[1] -= u;
        columns[2] -= u;
        columns[3] -= u;
        return *columns;
    }
    
    template<typename T>
    template<typename U>
    matrix4x4<T>& matrix4x4<T>::operator-= ( const matrix4x4<U>& m )
    {
        columns[0] -= m[0];
        columns[1] -= m[1];
        columns[2] -= m[2];
        columns[3] -= m[3];
        return *this;
    }
    
    template<typename T>
    template<typename U>
    matrix4x4<T>& matrix4x4<T>::operator*= ( U u )
    {
        columns[0] *= u;
        columns[1] *= u;
        columns[2] *= u;
        columns[3] *= u;
        return *this;
    }
    
    template<typename T>
    template<typename U>
    matrix4x4<T>& matrix4x4<T>::operator*= ( const matrix4x4<U>& m )
    {
        typename matrix4x4<T>::column_type const SrcA0 = columns[0];
        typename matrix4x4<T>::column_type const SrcA1 = columns[1];
        typename matrix4x4<T>::column_type const SrcA2 = columns[2];
        typename matrix4x4<T>::column_type const SrcA3 = columns[3];
        
        typename matrix4x4<T>::column_type const SrcB0 = m[0];
        typename matrix4x4<T>::column_type const SrcB1 = m[1];
        typename matrix4x4<T>::column_type const SrcB2 = m[2];
        typename matrix4x4<T>::column_type const SrcB3 = m[3];
        
        columns[0] = SrcA0 * SrcB0[0] + SrcA1 * SrcB0[1] + SrcA2 * SrcB0[2] + SrcA3 * SrcB0[3];
        columns[1] = SrcA0 * SrcB1[0] + SrcA1 * SrcB1[1] + SrcA2 * SrcB1[2] + SrcA3 * SrcB1[3];
        columns[2] = SrcA0 * SrcB2[0] + SrcA1 * SrcB2[1] + SrcA2 * SrcB2[2] + SrcA3 * SrcB2[3];
        columns[3] = SrcA0 * SrcB3[0] + SrcA1 * SrcB3[1] + SrcA2 * SrcB3[2] + SrcA3 * SrcB3[3];

        return *this;
    }
    
    template<typename T>
    template<typename U>
    matrix4x4<T>& matrix4x4<T>::operator/= ( U u )
    {
        columns[0] /= u;
        columns[1] /= u;
        columns[2] /= u;
        columns[3] /= u;
        return *this;
    }
    
    template<typename T>
    template<typename U>
    matrix4x4<T>& matrix4x4<T>::operator/= ( const matrix4x4<U>& m )
    {
        matrix4x4<U> copym(m);
        return * this = *this * copym.inverse();
    }
    
    /*- Increment & Decrement Operators -*/
    template<typename T>
    matrix4x4<T>& matrix4x4<T>::operator++()
    {
        ++columns[0];
        ++columns[1];
        ++columns[2];
        ++columns[3];
        return *this;
    }
    
    template<typename T>
    matrix4x4<T>& matrix4x4<T>::operator--()
    {
        --columns[0];
        --columns[1];
        --columns[2];
        --columns[3];
        return *this;
    }
    
    template<typename T>
    matrix4x4<T> matrix4x4<T>::operator++(int)
    {
        matrix4x4 m = *this;
        ++m;
        return m;
    }
    
    template<typename T>
    matrix4x4<T> matrix4x4<T>::operator--(int)
    {
        matrix4x4 m = *this;
        --m;
        return m;
    }
    
    /*-- Matrix Related Functions --*/
    template<typename T>
    matrix4x4<T>& matrix4x4<T>::inverse()
    {
        matrix4x4<T>& m = *this;
        T Coef00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
        T Coef02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
        T Coef03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];
        
        T Coef04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
        T Coef06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
        T Coef07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];
        
        T Coef08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
        T Coef10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
        T Coef11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];
        
        T Coef12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
        T Coef14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
        T Coef15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];
        
        T Coef16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
        T Coef18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
        T Coef19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];
        
        T Coef20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
        T Coef22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
        T Coef23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];
        
        vector4<T> Fac0(Coef00, Coef00, Coef02, Coef03);
        vector4<T> Fac1(Coef04, Coef04, Coef06, Coef07);
        vector4<T> Fac2(Coef08, Coef08, Coef10, Coef11);
        vector4<T> Fac3(Coef12, Coef12, Coef14, Coef15);
        vector4<T> Fac4(Coef16, Coef16, Coef18, Coef19);
        vector4<T> Fac5(Coef20, Coef20, Coef22, Coef23);
        
        vector4<T> Vec0(m[1][0], m[0][0], m[0][0], m[0][0]);
        vector4<T> Vec1(m[1][1], m[0][1], m[0][1], m[0][1]);
        vector4<T> Vec2(m[1][2], m[0][2], m[0][2], m[0][2]);
        vector4<T> Vec3(m[1][3], m[0][3], m[0][3], m[0][3]);
        
        vector4<T> Inv0(Vec1 * Fac0 - Vec2 * Fac1 + Vec3 * Fac2);
        vector4<T> Inv1(Vec0 * Fac0 - Vec2 * Fac3 + Vec3 * Fac4);
        vector4<T> Inv2(Vec0 * Fac1 - Vec1 * Fac3 + Vec3 * Fac5);
        vector4<T> Inv3(Vec0 * Fac2 - Vec1 * Fac4 + Vec2 * Fac5);
        
        vector4<T> SignA(+1, -1, +1, -1);
        vector4<T> SignB(-1, +1, -1, +1);
        
        vector4<T> first_column( m[0] );
        
        matrix4x4<T> Inverse(Inv0 * SignA, Inv1 * SignB, Inv2 * SignA, Inv3 * SignB);
        m[0] = Inv0 * SignA;
        m[1] = Inv1 * SignB;
        m[2] = Inv2 * SignA;
        m[3] = Inv3 * SignB;
        
        vector4<T> Row0(m[0][0], m[1][0], m[2][0], m[3][0]);
        
        vector4<T> Dot0(first_column * Row0);
        T Dot1 = (Dot0.x + Dot0.y) + (Dot0.z + Dot0.w);
        
        T OneOverDeterminant = static_cast<T>(1) / Dot1;
        
        m *= OneOverDeterminant;
        return m;
    }
    
    template<typename T>
    matrix4x4<T>& matrix4x4<T>::transpose()
    {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < i; ++j) {
                std::swap( (*this)[i][j], (*this)[j][i] );
            }
        }
        return *this;
    }
    
    template<typename T>
    T matrix4x4<T>::determinant() const
    {
        const matrix4x4<T>& m = *this;
        T SubFactor00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
        T SubFactor01 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
        T SubFactor02 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
        T SubFactor03 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
        T SubFactor04 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
        T SubFactor05 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
        
        vector4<T> DetCof(
                           + (m[1][1] * SubFactor00 - m[1][2] * SubFactor01 + m[1][3] * SubFactor02),
                           - (m[1][0] * SubFactor00 - m[1][2] * SubFactor03 + m[1][3] * SubFactor04),
                           + (m[1][0] * SubFactor01 - m[1][1] * SubFactor03 + m[1][3] * SubFactor05),
                           - (m[1][0] * SubFactor02 - m[1][1] * SubFactor04 + m[1][2] * SubFactor05));
        
        return
        m[0][0] * DetCof[0] + m[0][1] * DetCof[1] +
        m[0][2] * DetCof[2] + m[0][3] * DetCof[3];
    }
    
    // arithmetic operators
    
    template<typename T>
    matrix4x4<T> operator+ ( const matrix4x4<T>& m, const T& t )
    { return matrix4x4<T>( m[0] + t, m[1] + t, m[2] + t, m[3] + t ); }
    
    template<typename T>
    matrix4x4<T> operator+ ( const T& t, const matrix4x4<T>& m )
    { return matrix4x4<T>( m[0] + t, m[1] + t, m[2] + t, m[3] + t ); }
    
    template<typename T>
    matrix4x4<T> operator+ ( const matrix4x4<T>& m1, const matrix4x4<T>& m2 )
    { return matrix4x4<T>( m1[0] + m2[0], m1[1] + m2[1], m1[2] + m2[2], m1[3] + m2[3] ); }
    
    template<typename T>
    matrix4x4<T> operator- ( const matrix4x4<T>& m, const T& t )
    { return matrix4x4<T>( m[0] - t, m[1] - t, m[2] - t, m[3] - t ); }
    
    template<typename T>
    matrix4x4<T> operator- ( const T& t, const matrix4x4<T>& m )
    { return matrix4x4<T>( t - m[0], t - m[1], t - m[2], t - m[3] ); }
    
    template<typename T>
    matrix4x4<T> operator- ( const matrix4x4<T>& m1, const matrix4x4<T>& m2 )
    { return matrix4x4<T>( m1[0] - m2[0], m1[1] - m2[1], m1[2] - m2[2], m1[3] - m2[3] ); }
    
    template<typename T>
    matrix4x4<T> operator* ( const matrix4x4<T>& m, const T& t )
    { return matrix4x4<T>( m[0] * t, m[1] * t, m[2] * t, m[3] * t ); }
    
    template<typename T>
    matrix4x4<T> operator* ( const T& t, const matrix4x4<T>& m )
    { return matrix4x4<T>( m[0] * t, m[1] * t, m[2] * t, m[3] * t ); }
    
    template<typename T>
    typename matrix4x4<T>::column_type operator* ( const matrix4x4<T>& m, const typename matrix4x4<T>::column_type& v )
    {
        return typename matrix4x4<T>::column_type( m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3] * v[3] );
    }
    
    template<typename T>
    typename matrix4x4<T>::row_type operator* ( const typename matrix4x4<T>::row_type& v, const matrix4x4<T>& m )
    {
        typename matrix4x4<T>::row_type r1 = v[0] * m[0];
        typename matrix4x4<T>::row_type r2 = v[1] * m[1];
        typename matrix4x4<T>::row_type r3 = v[2] * m[2];
        typename matrix4x4<T>::row_type r4 = v[3] * m[3];
        return typename matrix4x4<T>::row_type(
                                               r1.x + r1.y + r1.z + r1.w,
                                               r2.x + r2.y + r2.z + r2.w,
                                               r3.x + r3.y + r3.z + r3.w,
                                               r4.x + r4.y + r4.z + r4.w
        );
    }
    
    template<typename T>
    matrix4x4<T> operator* ( const matrix4x4<T>& m1, const matrix4x4<T>& m2 )
    {
        matrix4x4<T> result = m1;
        return result *= m2;
    }
    
    template<typename T>
    matrix4x4<T> operator/ ( const matrix4x4<T>& m1, const matrix4x4<T>& m2 )
    {
        matrix4x4<T> result = m1;
        return result /= m2;
    }
    
    template<typename T, typename U>
    matrix4x4<T> operator/ ( const matrix4x4<T>& m, U t )
    { return matrix4x4<T>( m[0] / t, m[1] / t, m[2] / t, m[3] / t ); }
    
    template<typename T, typename U>
    matrix4x4<T> operator/ ( U t, const matrix4x4<T>& m )
    { return matrix4x4<T>( t / m[0], t / m[1], t / m[2], t / m[3] ); }
    
    // boolean operators
    
    template<typename T>
    bool operator== ( const matrix4x4<T>& m1, const matrix4x4<T>& m2 );
    
    template<typename T>
    bool operator!= ( const matrix4x4<T>& m1, const matrix4x4<T>& m2 );
    
} }
