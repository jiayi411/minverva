namespace minerva { namespace graphic {
    
    
    /*-- Matrix Related Functions --*/
    
    template<typename M>
    M math::inverse( const M& m )
    {
        M copym = m;
        return copym.inverse();
    }
    
    template<typename M>
    M math::transpose( const M& m )
    {
        M copym = m;
        return copym.transpose();
    }

    template<typename V>
    float math::dot( const V& v1, const V& v2 )
    {
        return v1.dot(v2);
    }
    
    template<typename V>
    V math::cross( const V& v1, const V& v2 )
    {
        return v1.cross(v2);
    }
    
    template<typename V>
    V math::normalize( const V& v )
    {
        V t = v;
        return t.normalize();
    }
    
    template<typename M>
    typename M::value_type math::determinant( const M& m )
    {
        return m.determinant();
    }
    
    float math::radians(float degrees)
    {
        return degrees * 0.01745329251994329576923690768489f;
    }
    
    float math::degrees(float radians)
    {
        return radians * 57.295779513082320876798154814105f;
    }
    
    template<typename T>
    matrix4x4<T> math::perspective(float degrees, float width, float height, float near, float far)
    {
        float aspect = width / height;
        float radian = radians( degrees );
        float range = far - near;//near - far;
        float tan_half = tanf( radian / 2.f );
        
        matrix4x4<T> m;
        m[0][0] = 1.f / ( aspect * tan_half );
        m[1][1] = 1.f / tan_half;
        m[2][2] = ( -near - far ) / range;
        m[2][3] = -( 2.f * far * near ) / range;
        m[3][2] = -1;
        return m;
    }
    
    template<typename T>
    matrix4x4<T> math::view( const vector3<T>& eye, const vector3<T>& target, const vector3<T>& up )
    {
        vector3<T> forward = ( target - eye ).normalize();
        vector3<T> right = forward.cross( up ).normalize();
        vector3<T> fup = right.cross( forward );
        
        return matrix4x4<T>(
                                right.x,          fup.x,            -forward.x,          0,
                                right.y,          fup.y,            -forward.y,          0,
                                right.z,          fup.z,            -forward.z,          0,
                            -dot(right, eye), -dot(fup, eye),     dot(forward, eye),     1
                            );
        
    }
}}
