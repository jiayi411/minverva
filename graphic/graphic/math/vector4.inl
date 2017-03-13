namespace minerva { namespace graphic {
    
    template<typename T> tvector4<T>::tvector4( tvector4<T>&& v )
    { x = v.x; y = v.y; z = v.z; w = v.w; }
    
    template<typename T> tvector4<T>& tvector4<T>::operator= ( tvector4<T>&& v )
    { x = v.x; y = v.y; z = v.z; w = v.w; return *this; }
    
    template<typename T> tvector4<T>::tvector4( const tvector4<T>& v )
    { x = v.x; y = v.y; z = v.z; w = v.w; }
    
    template<typename T> tvector4<T>& tvector4<T>::operator= ( const tvector4<T>& v )
    { x = v.x; y = v.y; z = v.z; w = v.w; return *this; }
    
    template<typename T>
    tvector4<T>::tvector4( const tvector3<T>& v )
    { x = v.x; y = v.y; z = v.z; w = 0; }
    
    template<typename T> T& tvector4<T>::operator[] ( size_type s )
    {
        switch(s)
        {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            case 3: return w;
        }
        mi_assert( 0 && "error index of tvector4" );
        return x;
    }
    
    template<typename T>
    const T& tvector4<T>::operator[] ( size_type s ) const
    {
        switch(s)
        {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            case 3: return w;
        }
        mi_assert( 0 && "error index of tvector4" );
        return x;
    }
    
    template<typename T> tvector4<T>& tvector4<T>::operator+= ( const tvector4<T>& v )
    { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
    
    template<typename T> tvector4<T>& tvector4<T>::operator-= ( const tvector4<T>& v )
    { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
    
    template<typename T> tvector4<T>& tvector4<T>::operator*= ( const tvector4<T>& v )
    { x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this; }
    
    template<typename T> tvector4<T>& tvector4<T>::operator/= ( const tvector4<T>& v )
    { x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this; }
    
    template<typename T>
    template<typename U>
    tvector4<T>& tvector4<T>::operator+= ( U t )
    {
        T tt = static_cast<T>(t);
        x += tt; y += tt; z += tt; w += tt; return *this;
    }
    
    template<typename T>
    template<typename U>
    tvector4<T>& tvector4<T>::operator-= ( U t )
    {
        T tt = static_cast<T>(t);
        x -= tt; y -= tt; z -= tt; w -= tt; return *this;
    }
    
    template<typename T>
    template<typename U>
    tvector4<T>& tvector4<T>::operator*= ( U t )
    {
        T tt = static_cast<T>(t);
        x *= tt; y *= tt; z *= tt; w *= tt; return *this;
    }
    
    template<typename T>
    template<typename U>
    tvector4<T>& tvector4<T>::operator/= ( U t )
    {
        T tt = static_cast<T>(t);
        x /= tt; y /= tt; z /= tt; w /= tt; return *this;
    }
    
    template<typename T> tvector4<T>& tvector4<T>::operator++ ()
    { *this += 1; return *this; }
    
    template<typename T> tvector4<T>  tvector4<T>::operator++ (int)
    {
        tvector4<T> v = *this;
        ++v;
        return v;
    }
    
    template<typename T> tvector4<T>& tvector4<T>::operator-- ()
    { *this -= 1; return *this; }
    
    template<typename T> tvector4<T> tvector4<T>::operator-- (int)
    {
        tvector4<T> v = *this;
        --v;
        return v;
    }
    
    ////
    template<typename T>
    tvector4<T>& tvector4<T>::normalize()
    { return *this /= length(); }
    
    template<typename T>
    T tvector4<T>::dot( const tvector4& v ) const
    {
        tvector4<T> ans = (*this) * v;
        return ( ans.x + ans.y + ans.z + ans.w );
    }
    
    template<typename T>
    T tvector4<T>::length()
    { return sqrtf( dot( *this ) ); }
    
    template<typename T>
    T tvector4<T>::length2()
    { return dot( *this ); }
    ////
    
    template<typename T>
    tvector4<T> operator+ ( const tvector4<T>& v1, const tvector4<T>& v2 )
    { return tvector4<T>( v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w ); }
    
    template<typename T, typename U>
    tvector4<T> operator+ ( const tvector4<T>& v1, U u )
    {
        T t = static_cast<T>(u);
        return tvector4<T>( v1.x + t, v1.y + t, v1.z + t, v1.w + t );
    }
    
    template<typename T>
    tvector4<T> operator- ( const tvector4<T>& v1, const tvector4<T>& v2 )
    { return tvector4<T>( v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w ); }
    
    template<typename T, typename U>
    tvector4<T> operator- ( const tvector4<T>& v1, U u )
    {
        T t = static_cast<T>(u);
        return tvector4<T>( v1.x - t, v1.y - t, v1.z - t, v1.w - t );
    }
    
    template<typename T>
    tvector4<T> operator* ( const tvector4<T>& v1, const tvector4<T>& v2 )
    { return tvector4<T>( v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w ); }
    
    template<typename T, typename U>
    tvector4<T> operator* ( const tvector4<T>& v1, U u )
    {
        T t = static_cast<T>(u);
        return tvector4<T>( v1.x * t, v1.y * t, v1.z * t, v1.w * t );
    }
    
    template<typename T, typename U>
    tvector4<T> operator* ( U u, const tvector4<T>& v1 )
    {
        T t = static_cast<T>(u);
        return tvector4<T>( v1.x * t, v1.y * t, v1.z * t, v1.w * t );
    }
    
    template<typename T>
    tvector4<T> operator/ ( const tvector4<T>& v1, const tvector4<T>& v2 )
    { return tvector4<T>( v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w ); }
    
    template<typename T, typename U>
    tvector4<T> operator/ ( const tvector4<T>& v1, U u )
    {
        T t = static_cast<T>(u);
        return tvector4<T>( v1.x / t, v1.y / t, v1.z / t, v1.w / t );
    }
    
    template<typename T, typename U>
    tvector4<T> operator/ ( U u, const tvector4<T>& v1 )
    {
        T t = static_cast<T>(u);
        return tvector4<T>( t / v1.x, t / v1.y, t / v1.z, t / v1.w );
    }
    
} }
