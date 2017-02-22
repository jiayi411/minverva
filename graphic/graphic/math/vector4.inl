namespace minerva { namespace graphic {
    
    template<typename T> vector4<T>::vector4( vector4<T>&& v )
    { x = v.x; y = v.y; z = v.z; w = v.w; }
    
    template<typename T> vector4<T>& vector4<T>::operator= ( vector4<T>&& v )
    { x = v.x; y = v.y; z = v.z; w = v.w; return *this; }
    
    template<typename T> vector4<T>::vector4( const vector4<T>& v )
    { x = v.x; y = v.y; z = v.z; w = v.w; }
    
    template<typename T> vector4<T>& vector4<T>::operator= ( const vector4<T>& v )
    { x = v.x; y = v.y; z = v.z; w = v.w; return *this; }
    
    template<typename T> T& vector4<T>::operator[] ( size_type s )
    {
        switch(s)
        {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            case 3: return w;
        }
        mi_assert( 0 && "error index of vector4" );
        return x;
    }
    
    template<typename T>
    const T& vector4<T>::operator[] ( size_type s ) const
    {
        switch(s)
        {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            case 3: return w;
        }
        mi_assert( 0 && "error index of vector4" );
        return x;
    }
    
    template<typename T> vector4<T>& vector4<T>::operator+= ( const vector4<T>& v )
    { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
    
    template<typename T> vector4<T>& vector4<T>::operator-= ( const vector4<T>& v )
    { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
    
    template<typename T> vector4<T>& vector4<T>::operator*= ( const vector4<T>& v )
    { x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this; }
    
    template<typename T> vector4<T>& vector4<T>::operator/= ( const vector4<T>& v )
    { x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this; }
    
    template<typename T>
    template<typename U>
    vector4<T>& vector4<T>::operator+= ( U t )
    {
        T tt = static_cast<T>(t);
        x += tt; y += tt; z += tt; w += tt; return *this;
    }
    
    template<typename T>
    template<typename U>
    vector4<T>& vector4<T>::operator-= ( U t )
    {
        T tt = static_cast<T>(t);
        x -= tt; y -= tt; z -= tt; w -= tt; return *this;
    }
    
    template<typename T>
    template<typename U>
    vector4<T>& vector4<T>::operator*= ( U t )
    {
        T tt = static_cast<T>(t);
        x *= tt; y *= tt; z *= tt; w *= tt; return *this;
    }
    
    template<typename T>
    template<typename U>
    vector4<T>& vector4<T>::operator/= ( U t )
    {
        T tt = static_cast<T>(t);
        x /= tt; y /= tt; z /= tt; w /= tt; return *this;
    }
    
    template<typename T> vector4<T>& vector4<T>::operator++ ()
    { *this += 1; return *this; }
    
    template<typename T> vector4<T>  vector4<T>::operator++ (int)
    {
        vector4<T> v = *this;
        ++v;
        return v;
    }
    
    template<typename T> vector4<T>& vector4<T>::operator-- ()
    { *this -= 1; return *this; }
    
    template<typename T> vector4<T> vector4<T>::operator-- (int)
    {
        vector4<T> v = *this;
        --v;
        return v;
    }
    
    ////
    
    template<typename T>
    vector4<T> operator+ ( const vector4<T>& v1, const vector4<T>& v2 )
    { return vector4<T>( v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w ); }
    
    template<typename T, typename U>
    vector4<T> operator+ ( const vector4<T>& v1, U u )
    {
        T t = static_cast<T>(u);
        return vector4<T>( v1.x + t, v1.y + t, v1.z + t, v1.w + t );
    }
    
    template<typename T>
    vector4<T> operator- ( const vector4<T>& v1, const vector4<T>& v2 )
    { return vector4<T>( v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w ); }
    
    template<typename T, typename U>
    vector4<T> operator- ( const vector4<T>& v1, U u )
    {
        T t = static_cast<T>(u);
        return vector4<T>( v1.x - t, v1.y - t, v1.z - t, v1.w - t );
    }
    
    template<typename T>
    vector4<T> operator* ( const vector4<T>& v1, const vector4<T>& v2 )
    { return vector4<T>( v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w ); }
    
    template<typename T, typename U>
    vector4<T> operator* ( const vector4<T>& v1, U u )
    {
        T t = static_cast<T>(u);
        return vector4<T>( v1.x * t, v1.y * t, v1.z * t, v1.w * t );
    }
    
    template<typename T>
    vector4<T> operator/ ( const vector4<T>& v1, const vector4<T>& v2 )
    { return vector4<T>( v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w ); }
    
    template<typename T, typename U>
    vector4<T> operator/ ( const vector4<T>& v1, U u )
    {
        T t = static_cast<T>(u);
        return vector4<T>( v1.x / t, v1.y / t, v1.z / t, v1.w / t );
    }
    
    template<typename T, typename U>
    vector4<T> operator/ ( U u, const vector4<T>& v1 )
    {
        T t = static_cast<T>(u);
        return vector4<T>( t / v1.x, t / v1.y, t / v1.z, t / v1.w );
    }
    
} }
