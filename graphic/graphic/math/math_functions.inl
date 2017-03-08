namespace minerva { namespace graphic {
    
    /*-- Matrix Related Functions --*/
    
    template<typename M>
    M inverse( const M& m )
    {
        M copym = m;
        return copym.inverse();
    }
    
    template<typename M>
    M transpose( const M& m )
    {
        M copym = m;
        return copym.transpose();
    }
    
    template<typename V>
    float dot( const V& v1, const V& v2 )
    {
        return v1.dot(v2);
    }
    
    template<typename V>
    V cross( const V& v1, const V& v2 )
    {
        return v1.cross(v2);
    }
    
    template<typename V>
    V normalize( const V& v )
    {
        V t = v;
        return t.normalize();
    }
    
    template<typename M>
    typename M::value_type determinant( const M& m )
    {
        return m.determinant();
    }
    
    float radians(float degrees)
    {
        return degrees * 0.01745329251994329576923690768489f;
    }
    
    float degrees(float radians)
    {
        return radians * 57.295779513082320876798154814105f;
    }
    
    template<typename T>
    tmatrix4x4<T> perspective(float degrees, float width, float height, float near, float far)
    {
        float aspect = width / height;
        float radian = radians( degrees );
        float range = far - near;//near - far;
        float tan_half = tanf( radian / 2.f );
        
        tmatrix4x4<T> m;
        m[0][0] = 1.f / ( aspect * tan_half );
        m[1][1] = 1.f / tan_half;
        m[2][2] = ( -near - far ) / range;
        m[2][3] = -( 2.f * far * near ) / range;
        m[3][2] = -1;
        return m;
    }
    
    template<typename T>
    tmatrix4x4<T> view( const tvector3<T>& eye, const tvector3<T>& target, const tvector3<T>& up )
    {
        tvector3<T> forward = ( target - eye ).normalize();
        tvector3<T> right = forward.cross( up ).normalize();
        tvector3<T> fup = right.cross( forward ); // why this code useful? it is just the up vector I think.
        
        return tmatrix4x4<T>(
                            right.x,        right.y,            right.z,          -dot(right, eye),
                            fup.x,          fup.y,                fup.z,          -dot(fup, eye),
                            -forward.x,      -forward.y,         -forward.z,          dot(forward, eye),
                            0,              0,                      0,                  1
                            );
    }
    
    template<typename T>
    tquaternion<T> conjugate( const tquaternion<T>& q )
    {
        tquaternion<T> v = q;
        return v.conjugate();
    }
    
    template<typename T>
    tquaternion<T> inverse( const tquaternion<T>& q )
    {
        tquaternion<T> v = q;
        return v.inverse();
    }
    
    template<typename T>
    tquaternion<T> normalize( const tquaternion<T>& q )
    {
        tquaternion<T> v = q;
        return v.normalize();
    }
    
    template<typename T>
    tquaternion<T> cross( const tquaternion<T>& q1, const tquaternion<T>& q2 )
    {
        tquaternion<T> v = q1;
        return v.cross(q2);
    }
    
    /*-- Basic Mathematics --*/
    
    template<typename T>
    T mix( const T& t1, const T& t2, float a )
    { return t1 + a * ( t2 - t1 ); }
    
    template<typename T>
    tvector3<T> cos( const tvector3<T>& v )
    { return tvector3<T>( std::cos(v.x), std::cos(v.y), std::cos(v.z) ); }
    
    template<typename T>
    tvector3<T> sin( const tvector3<T>& v )
    { return tvector3<T>( std::sin(v.x), std::sin(v.y), std::sin(v.z) ); }
}}
