namespace minerva { namespace graphic {
    
    template<typename T> vector2<T>::vector2( vector2<T>&& v )
    { x = v.x; y = v.y; }
    
    template<typename T> vector2<T>& vector2<T>::operator= ( vector2<T>&& v )
    { x = v.x; y = v.y; return *this; }
    
    template<typename T> vector2<T>& vector2<T>::operator+= ( const vector2<T>& v )
    { x += v.x; y += v.y; return *this; }
    
    template<typename T> vector2<T>& vector2<T>::operator-= ( const vector2<T>& v )
    { x -= v.x; y -= v.y; return *this; }
    
    template<typename T> vector2<T>& vector2<T>::operator*= ( const vector2<T>& v )
    { x *= v.x; y *= v.y; return *this; }
    
    template<typename T> vector2<T>& vector2<T>::operator/= ( const vector2<T>& v )
    { x /= v.x; y /= v.y; return *this; }
    
    template<typename T> vector2<T>& vector2<T>::operator+= ( T t )
    { x += t; y += t; return *this; }
    
    template<typename T> vector2<T>& vector2<T>::operator-= ( T t )
    { x -= t; y -= t; return *this; }
    
    template<typename T> vector2<T>& vector2<T>::operator*= ( T t )
    { x *= t; y *= t; return *this; }
    
    template<typename T> vector2<T>& vector2<T>::operator/= ( T t )
    { x /= t; y /= t; return *this; }
    
    template<typename T> vector2<T>& vector2<T>::operator++ ()
    { *this += 1; return *this; }
    
    template<typename T> vector2<T>  vector2<T>::operator++ (int)
    {
        vector2<T> v = *this;
        ++v;
        return v;
    }
    
    template<typename T> vector2<T>& vector2<T>::operator-- ()
    { *this -= 1; return *this; }
    
    template<typename T> vector2<T> vector2<T>::operator-- (int)
    {
        vector2<T> v = *this;
        --v;
        return v;
    }
    
    ////
    
    template<typename T>
    vector2<T> operator+ ( const vector2<T>& v1, const vector2<T>& v2 )
    { return vector2<T>( v1.x + v2.x, v1.y + v2.y); }
    
    template<typename T>
    vector2<T> operator+ ( const vector2<T>& v1, T t )
    { return vector2<T>( v1.x + t, v1.y + t ); }
    
    template<typename T>
    vector2<T> operator- ( const vector2<T>& v1, const vector2<T>& v2 )
    { return vector2<T>( v1.x - v2.x, v1.y - v2.y ); }
    
    template<typename T>
    vector2<T> operator- ( const vector2<T>& v1, T t )
    { return vector2<T>( v1.x - t, v1.y - t ); }
    
    template<typename T>
    vector2<T> operator* ( const vector2<T>& v1, const vector2<T>& v2 )
    { return vector2<T>( v1.x * v2.x, v1.y * v2.y ); }
    
    template<typename T>
    vector2<T> operator* ( const vector2<T>& v1, T t )
    { return vector2<T>( v1.x * t, v1.y * t ); }
    
    template<typename T>
    vector2<T> operator/ ( const vector2<T>& v1, const vector2<T>& v2 )
    { return vector2<T>( v1.x / v2.x, v1.y / v2.y ); }
    
    template<typename T>
    vector2<T> operator/ ( const vector2<T>& v1, T t )
    { return vector2<T>( v1.x / t, v1.y / t ); }
    
    template<typename T>
    vector2<T> operator/ ( T t, const vector2<T>& v1 )
    { return vector2<T>( t / v1.x, t / v1.y ); }
    
} }
