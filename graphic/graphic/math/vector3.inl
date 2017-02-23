namespace minerva { namespace graphic {
    
    template<typename T> vector3<T>::vector3( vector3<T>&& v )
    { x = v.x; y = v.y; z = v.z; }
    
    template<typename T> vector3<T>& vector3<T>::operator= ( vector3<T>&& v )
    { x = v.x; y = v.y; z = v.z; return *this; }
    
    template<typename T> vector3<T>::vector3( const vector3<T>& v )
    { x = v.x; y = v.y; z = v.z; }
    
    template<typename T> vector3<T>& vector3<T>::operator= ( const vector3<T>& v )
    { x = v.x; y = v.y; z = v.z; return *this; }
    
    template<typename T> vector3<T>& vector3<T>::operator+= ( const vector3<T>& v )
    { x += v.x; y += v.y; z += v.z; return *this; }
    
    template<typename T> vector3<T>& vector3<T>::operator-= ( const vector3<T>& v )
    { x -= v.x; y -= v.y; z -= v.z; return *this; }
    
    template<typename T> vector3<T>& vector3<T>::operator*= ( const vector3<T>& v )
    { x *= v.x; y *= v.y; z *= v.z; return *this; }
    
    template<typename T> vector3<T>& vector3<T>::operator/= ( const vector3<T>& v )
    { x /= v.x; y /= v.y; z /= v.z; return *this; }
    
    template<typename T> vector3<T>& vector3<T>::operator+= ( T t )
    { x += t; y += t; z += t; return *this; }
    
    template<typename T> vector3<T>& vector3<T>::operator-= ( T t )
    { x -= t; y -= t; z -= t; return *this; }
    
    template<typename T> vector3<T>& vector3<T>::operator*= ( T t )
    { x *= t; y *= t; z *= t; return *this; }
    
    template<typename T> vector3<T>& vector3<T>::operator/= ( T t )
    { x /= t; y /= t; z /= t; return *this; }
    
    template<typename T> vector3<T>& vector3<T>::operator++ ()
    { *this += 1; return *this; }
    
    template<typename T> vector3<T>  vector3<T>::operator++ (int)
    {
        vector3<T> v = *this;
        ++v;
        return v;
    }
    
    template<typename T> vector3<T>& vector3<T>::operator-- ()
    { *this -= 1; return *this; }
    
    template<typename T> vector3<T> vector3<T>::operator-- (int)
    {
        vector3<T> v = *this;
        --v;
        return v;
    }
    
    template<typename T> T& vector3<T>::operator[] ( size_type s )
    {
        switch(s)
        {
            case 0: return x;
            case 1: return y;
            case 2: return z;
        }
        mi_assert( 0 && "error index of vector3" );
        return x;
    }
    
    template<typename T>
    const T& vector3<T>::operator[] ( size_type s ) const
    {
        switch(s)
        {
            case 0: return x;
            case 1: return y;
            case 2: return z;
        }
        mi_assert( 0 && "error index of vector3" );
        return x;
    }
    
    ////
    template<typename T>
    vector3<T>& vector3<T>::normalize()
    { return *this /= length(); }
    
    template<typename T>
    vector3<T> vector3<T>::cross( const vector3<T>& v ) const
    {
        return vector3<T>(
                          this->y * v.z - this->z * v.y,
                          this->z * v.x - this->x * v.z,
                          this->x * v.y - this->y * v.x
                          );
    }
    
    template<typename T>
    T vector3<T>::dot( const vector3<T>& v ) const
    {
        vector3<T> ans = *this * v;
        return ans.x + ans.y + ans.z;
    }
    
    template<typename T>
    T vector3<T>::length() const
    { return sqrtf( dot( *this ) ); }
    
    ////
    
    template<typename T>
    vector3<T> operator+ ( const vector3<T>& v1, const vector3<T>& v2 )
    { return vector3<T>( v1.x + v2.x, v1.y + v2.y, v1.z + v2.z); }
    
    template<typename T>
    vector3<T> operator+ ( const vector3<T>& v1, T t )
    { return vector3<T>( v1.x + t, v1.y + t, v1.z + t ); }
    
    template<typename T>
    vector3<T> operator- ( const vector3<T>& v1, const vector3<T>& v2 )
    { return vector3<T>( v1.x - v2.x, v1.y - v2.y, v1.z - v2.z ); }
    
    template<typename T>
    vector3<T> operator- ( const vector3<T>& v1, T t )
    { return vector3<T>( v1.x - t, v1.y - t, v1.z - t ); }
    
    template<typename T>
    vector3<T> operator* ( const vector3<T>& v1, const vector3<T>& v2 )
    { return vector3<T>( v1.x * v2.x, v1.y * v2.y, v1.z * v2.z ); }
    
    template<typename T>
    vector3<T> operator* ( const vector3<T>& v1, T t )
    { return vector3<T>( v1.x * t, v1.y * t, v1.z * t ); }
    
    template<typename T>
    vector3<T> operator* ( T t, const vector3<T>& v1 )
    { return vector3<T>( v1.x * t, v1.y * t, v1.z * t ); }
    
    template<typename T>
    vector3<T> operator/ ( const vector3<T>& v1, const vector3<T>& v2 )
    { return vector3<T>( v1.x / v2.x, v1.y / v2.y, v1.z / v2.z ); }
    
    template<typename T>
    vector3<T> operator/ ( const vector3<T>& v1, T t )
    { return vector3<T>( v1.x / t, v1.y / t, v1.z / t ); }
    
    template<typename T>
    vector3<T> operator/ ( T t, const vector3<T>& v1 )
    { return vector3<T>( t / v1.x, t / v1.y, t / v1.z ); }
    
} }