namespace minerva { namespace graphic {
    
    template<typename T>
    tmatrix4x4<T>::tmatrix4x4( tmatrix4x4&& source )
    {
        _rows[0] = std::move(source[0]);
        _rows[1] = std::move(source[1]);
        _rows[2] = std::move(source[2]);
        _rows[3] = std::move(source[3]);
    }
    
    template<typename T>
    tmatrix4x4<T>& tmatrix4x4<T>::operator= ( tmatrix4x4<T>&& source )
    {
        _rows[0] = source[0];
        _rows[1] = source[1];
        _rows[2] = source[2];
        _rows[3] = source[3];
        return *this;
    }
    
    template<typename T>
    tmatrix4x4<T>::tmatrix4x4( const tmatrix4x4& source )
    {
        _rows[0] = std::move(source[0]);
        _rows[1] = std::move(source[1]);
        _rows[2] = std::move(source[2]);
        _rows[3] = std::move(source[3]);
    }
    
    template<typename T>
    tmatrix4x4<T>& tmatrix4x4<T>::operator= ( const tmatrix4x4<T>& source )
    {
        _rows[0] = source[0];
        _rows[1] = source[1];
        _rows[2] = source[2];
        _rows[3] = source[3];
        return *this;
    }
    
    template<typename T>
    tmatrix4x4<T>::tmatrix4x4( T t )
    {
        _rows[0] = row_type( t, 0, 0, 0 );
        _rows[1] = row_type( 0, t, 0, 0 );
        _rows[2] = row_type( 0, 0, t, 0 );
        _rows[3] = row_type( 0, 0, 0, t );        
    }
    
    template<typename T>
    tmatrix4x4<T>::tmatrix4x4( const row_type& c1, const row_type& c2,
              const row_type& c3, const row_type& c4 )
    {
        _rows[0] = (c1);
        _rows[1] = (c2);
        _rows[2] = (c3);
        _rows[3] = (c4);
    }
    
    template<typename T>
    tmatrix4x4<T>::tmatrix4x4( const tmatrix3x3<T>& m )
    {
        _rows[0] = m[0];
        _rows[1] = m[1];
        _rows[2] = m[2];
        _rows[3] = row_type(0,0,0,1);
    }
    
    template<typename T>
    tmatrix4x4<T>& tmatrix4x4<T>::operator= ( const tmatrix3x3<T>& source )
    {
        _rows[0] = source[0];
        _rows[1] = source[1];
        _rows[2] = source[2];
        _rows[3][0] = 0;
        _rows[3][1] = 0;
        _rows[3][2] = 0;
        _rows[3][3] = 1;
        return *this;
    }
    
    template<typename T>
    tmatrix4x4<T>::tmatrix4x4(
              T x1, T x2, T x3, T x4,
              T y1, T y2, T y3, T y4,
              T z1, T z2, T z3, T z4,
              T w1, T w2, T w3, T w4
              )
    {
        _rows[0] = column_type( x1, x2, x3, x4 );
        _rows[1] = column_type( y1, y2, y3, y4 );
        _rows[2] = column_type( z1, z2, z3, z4 );
        _rows[3] = column_type( w1, w2, w3, w4 );
    }
    
    /*- Access Operators -*/
    template<typename T>
    typename tmatrix4x4<T>::column_type& tmatrix4x4<T>::operator[] ( size_type s )
    { return _rows[s]; }
    
    template<typename T>
    const typename tmatrix4x4<T>::column_type& tmatrix4x4<T>::operator[] ( size_type s ) const
    { return _rows[s]; }
    
    /*- Unary Arithmetic Operators -*/
    template<typename T>
    template<typename U>
    tmatrix4x4<T>& tmatrix4x4<T>::operator+= ( U u )
    {
        _rows[0] += u;
        _rows[1] += u;
        _rows[2] += u;
        _rows[3] += u;
        return *_rows;
    }
    
    template<typename T>
    template<typename U>
    tmatrix4x4<T>& tmatrix4x4<T>::operator+= ( const tmatrix4x4<U>& m )
    {
        _rows[0] += m[0];
        _rows[1] += m[1];
        _rows[2] += m[2];
        _rows[3] += m[3];
        return *this;
    }
    
    template<typename T>
    template<typename U>
    tmatrix4x4<T>& tmatrix4x4<T>::operator-= ( U u )
    {
        _rows[0] -= u;
        _rows[1] -= u;
        _rows[2] -= u;
        _rows[3] -= u;
        return *_rows;
    }
    
    template<typename T>
    template<typename U>
    tmatrix4x4<T>& tmatrix4x4<T>::operator-= ( const tmatrix4x4<U>& m )
    {
        _rows[0] -= m[0];
        _rows[1] -= m[1];
        _rows[2] -= m[2];
        _rows[3] -= m[3];
        return *this;
    }
    
    template<typename T>
    template<typename U>
    tmatrix4x4<T>& tmatrix4x4<T>::operator*= ( U u )
    {
        _rows[0] *= u;
        _rows[1] *= u;
        _rows[2] *= u;
        _rows[3] *= u;
        return *this;
    }
    
    template<typename T>
    template<typename U>
    tmatrix4x4<T>& tmatrix4x4<T>::operator*= ( const tmatrix4x4<U>& m )
    {
        typename tmatrix4x4<T>::column_type const SrcA0 = _rows[0];
        typename tmatrix4x4<T>::column_type const SrcA1 = _rows[1];
        typename tmatrix4x4<T>::column_type const SrcA2 = _rows[2];
        typename tmatrix4x4<T>::column_type const SrcA3 = _rows[3];
        
        typename tmatrix4x4<T>::column_type const SrcB0 = m[0];
        typename tmatrix4x4<T>::column_type const SrcB1 = m[1];
        typename tmatrix4x4<T>::column_type const SrcB2 = m[2];
        typename tmatrix4x4<T>::column_type const SrcB3 = m[3];
        
        _rows[0] = SrcA0[0] * SrcB0 + SrcA0[1] * SrcB1 + SrcA0[2] * SrcB2 + SrcA0[3] * SrcB3;
        _rows[1] = SrcA1[0] * SrcB0 + SrcA1[1] * SrcB1 + SrcA1[2] * SrcB2 + SrcA1[3] * SrcB3;
        _rows[2] = SrcA2[0] * SrcB0 + SrcA2[1] * SrcB1 + SrcA2[2] * SrcB2 + SrcA2[3] * SrcB3;
        _rows[3] = SrcA3[0] * SrcB0 + SrcA3[1] * SrcB1 + SrcA3[2] * SrcB2 + SrcA3[3] * SrcB3;

        return *this;
    }
    
    template<typename T>
    template<typename U>
    tmatrix4x4<T>& tmatrix4x4<T>::operator/= ( U u )
    {
        _rows[0] /= u;
        _rows[1] /= u;
        _rows[2] /= u;
        _rows[3] /= u;
        return *this;
    }
    
    template<typename T>
    template<typename U>
    tmatrix4x4<T>& tmatrix4x4<T>::operator/= ( const tmatrix4x4<U>& m )
    {
        tmatrix4x4<U> copym(m);
        return * this = *this * copym.inverse();
    }
    
    /*- Increment & Decrement Operators -*/
    template<typename T>
    tmatrix4x4<T>& tmatrix4x4<T>::operator++()
    {
        ++_rows[0];
        ++_rows[1];
        ++_rows[2];
        ++_rows[3];
        return *this;
    }
    
    template<typename T>
    tmatrix4x4<T>& tmatrix4x4<T>::operator--()
    {
        --_rows[0];
        --_rows[1];
        --_rows[2];
        --_rows[3];
        return *this;
    }
    
    template<typename T>
    tmatrix4x4<T> tmatrix4x4<T>::operator++(int)
    {
        tmatrix4x4 m = *this;
        ++m;
        return m;
    }
    
    template<typename T>
    tmatrix4x4<T> tmatrix4x4<T>::operator--(int)
    {
        tmatrix4x4 m = *this;
        --m;
        return m;
    }
    
    /*-- Matrix Related Functions --*/
    template<typename T>
    tmatrix4x4<T>& tmatrix4x4<T>::inverse()
    {
        tmatrix4x4<T>& m = *this;
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
        
        tvector4<T> Fac0(Coef00, Coef00, Coef02, Coef03);
        tvector4<T> Fac1(Coef04, Coef04, Coef06, Coef07);
        tvector4<T> Fac2(Coef08, Coef08, Coef10, Coef11);
        tvector4<T> Fac3(Coef12, Coef12, Coef14, Coef15);
        tvector4<T> Fac4(Coef16, Coef16, Coef18, Coef19);
        tvector4<T> Fac5(Coef20, Coef20, Coef22, Coef23);
        
        tvector4<T> Vec0(m[1][0], m[0][0], m[0][0], m[0][0]);
        tvector4<T> Vec1(m[1][1], m[0][1], m[0][1], m[0][1]);
        tvector4<T> Vec2(m[1][2], m[0][2], m[0][2], m[0][2]);
        tvector4<T> Vec3(m[1][3], m[0][3], m[0][3], m[0][3]);
        
        tvector4<T> Inv0(Vec1 * Fac0 - Vec2 * Fac1 + Vec3 * Fac2);
        tvector4<T> Inv1(Vec0 * Fac0 - Vec2 * Fac3 + Vec3 * Fac4);
        tvector4<T> Inv2(Vec0 * Fac1 - Vec1 * Fac3 + Vec3 * Fac5);
        tvector4<T> Inv3(Vec0 * Fac2 - Vec1 * Fac4 + Vec2 * Fac5);
        
        tvector4<T> SignA(+1, -1, +1, -1);
        tvector4<T> SignB(-1, +1, -1, +1);
        
        tvector4<T> first_column( m[0] );
        
        tmatrix4x4<T> Inverse(Inv0 * SignA, Inv1 * SignB, Inv2 * SignA, Inv3 * SignB);
        m[0] = Inv0 * SignA;
        m[1] = Inv1 * SignB;
        m[2] = Inv2 * SignA;
        m[3] = Inv3 * SignB;
        
        tvector4<T> Row0(m[0][0], m[1][0], m[2][0], m[3][0]);
        
        tvector4<T> Dot0(first_column * Row0);
        T Dot1 = (Dot0.x + Dot0.y) + (Dot0.z + Dot0.w);
        
        T OneOverDeterminant = static_cast<T>(1) / Dot1;
        
        m *= OneOverDeterminant;
        return m;
    }
    
    template<typename T>
    tmatrix4x4<T>& tmatrix4x4<T>::transpose()
    {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < i; ++j) {
                std::swap( (*this)[i][j], (*this)[j][i] );
            }
        }
        return *this;
    }
    
    template<typename T>
    T tmatrix4x4<T>::determinant() const
    {
        const tmatrix4x4<T>& m = *this;
        T SubFactor00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
        T SubFactor01 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
        T SubFactor02 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
        T SubFactor03 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
        T SubFactor04 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
        T SubFactor05 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
        
        tvector4<T> DetCof(
                           + (m[1][1] * SubFactor00 - m[1][2] * SubFactor01 + m[1][3] * SubFactor02),
                           - (m[1][0] * SubFactor00 - m[1][2] * SubFactor03 + m[1][3] * SubFactor04),
                           + (m[1][0] * SubFactor01 - m[1][1] * SubFactor03 + m[1][3] * SubFactor05),
                           - (m[1][0] * SubFactor02 - m[1][1] * SubFactor04 + m[1][2] * SubFactor05));
        
        return
        m[0][0] * DetCof[0] + m[0][1] * DetCof[1] +
        m[0][2] * DetCof[2] + m[0][3] * DetCof[3];
    }
    
    template<typename T>
    tmatrix4x4<T>& tmatrix4x4<T>::scale( T x, T y, T z )
    {
        _rows[0][0] = x;
        _rows[1][1] = y;
        _rows[2][2] = z;
        _rows[3][3] = T(1);
        return *this;
    }
    
    // arithmetic operators
    
    template<typename T>
    tmatrix4x4<T> operator+ ( const tmatrix4x4<T>& m, const T& t )
    { return tmatrix4x4<T>( m[0] + t, m[1] + t, m[2] + t, m[3] + t ); }
    
    template<typename T>
    tmatrix4x4<T> operator+ ( const T& t, const tmatrix4x4<T>& m )
    { return tmatrix4x4<T>( m[0] + t, m[1] + t, m[2] + t, m[3] + t ); }
    
    template<typename T>
    tmatrix4x4<T> operator+ ( const tmatrix4x4<T>& m1, const tmatrix4x4<T>& m2 )
    { return tmatrix4x4<T>( m1[0] + m2[0], m1[1] + m2[1], m1[2] + m2[2], m1[3] + m2[3] ); }
    
    template<typename T>
    tmatrix4x4<T> operator- ( const tmatrix4x4<T>& m, const T& t )
    { return tmatrix4x4<T>( m[0] - t, m[1] - t, m[2] - t, m[3] - t ); }
    
    template<typename T>
    tmatrix4x4<T> operator- ( const T& t, const tmatrix4x4<T>& m )
    { return tmatrix4x4<T>( t - m[0], t - m[1], t - m[2], t - m[3] ); }
    
    template<typename T>
    tmatrix4x4<T> operator- ( const tmatrix4x4<T>& m1, const tmatrix4x4<T>& m2 )
    { return tmatrix4x4<T>( m1[0] - m2[0], m1[1] - m2[1], m1[2] - m2[2], m1[3] - m2[3] ); }
    
    template<typename T>
    tmatrix4x4<T> operator* ( const tmatrix4x4<T>& m, const T& t )
    { return tmatrix4x4<T>( m[0] * t, m[1] * t, m[2] * t, m[3] * t ); }
    
    template<typename T>
    tmatrix4x4<T> operator* ( const T& t, const tmatrix4x4<T>& m )
    { return tmatrix4x4<T>( m[0] * t, m[1] * t, m[2] * t, m[3] * t ); }
    
    template<typename T>
    typename tmatrix4x4<T>::column_type operator* ( const tmatrix4x4<T>& m, const typename tmatrix4x4<T>::column_type& v )
    {
        return typename tmatrix4x4<T>::column_type( m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3] * v[3] );
    }
    
    template<typename T>
    typename tmatrix4x4<T>::row_type operator* ( const typename tmatrix4x4<T>::row_type& v, const tmatrix4x4<T>& m )
    {
        typename tmatrix4x4<T>::row_type r1 = v[0] * m[0];
        typename tmatrix4x4<T>::row_type r2 = v[1] * m[1];
        typename tmatrix4x4<T>::row_type r3 = v[2] * m[2];
        typename tmatrix4x4<T>::row_type r4 = v[3] * m[3];
        return typename tmatrix4x4<T>::row_type(
                                               r1.x + r1.y + r1.z + r1.w,
                                               r2.x + r2.y + r2.z + r2.w,
                                               r3.x + r3.y + r3.z + r3.w,
                                               r4.x + r4.y + r4.z + r4.w
        );
    }
    
    template<typename T>
    tmatrix4x4<T> operator* ( const tmatrix4x4<T>& m1, const tmatrix4x4<T>& m2 )
    {
        tmatrix4x4<T> result = m1;
        return result *= m2;
    }
    
    template<typename T>
    tmatrix4x4<T> operator/ ( const tmatrix4x4<T>& m1, const tmatrix4x4<T>& m2 )
    {
        tmatrix4x4<T> result = m1;
        return result /= m2;
    }
    
    template<typename T, typename U>
    tmatrix4x4<T> operator/ ( const tmatrix4x4<T>& m, U t )
    { return tmatrix4x4<T>( m[0] / t, m[1] / t, m[2] / t, m[3] / t ); }
    
    template<typename T, typename U>
    tmatrix4x4<T> operator/ ( U t, const tmatrix4x4<T>& m )
    { return tmatrix4x4<T>( t / m[0], t / m[1], t / m[2], t / m[3] ); }
    
    // boolean operators
    
    template<typename T>
    bool operator== ( const tmatrix4x4<T>& m1, const tmatrix4x4<T>& m2 )
    {
        return ( m1[0] == m2[0] && m1[1] == m2[1] && m1[2] == m2[2] && m1[3] == m2[3] );
    }
    
    template<typename T>
    bool operator!= ( const tmatrix4x4<T>& m1, const tmatrix4x4<T>& m2 )
    {
        return !(m1 == m2);
    }
    
} }
