namespace minerva { namespace graphic {
    
    
    /*-- Matrix Related Functions --*/
    
    template<typename T>
    matrix4x4<T> math::inverse( const matrix4x4<T>& m )
    {
        matrix4x4<T> copym = m;
        return copym.inverse();
    }
    
    template<typename T>
    matrix4x4<T> math::transpose( const matrix4x4<T>& m )
    {
        matrix4x4<T> copym = m;
        return copym.transpose();
    }

    template<typename T>
    T math::determinant( const matrix4x4<T>& m )
    {
        return m.determinant();
    }
}}
