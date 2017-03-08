namespace minerva { namespace graphic {
    
    template<typename T> tvector2<T>::tvector2( tvector2<T>&& v )
    { x = v.x; y = v.y; }
    
    template<typename T> tvector2<T>& tvector2<T>::operator= ( tvector2<T>&& v )
    { x = v.x; y = v.y; return *this; }
    
    template<typename T> tvector2<T>& tvector2<T>::operator+= ( const tvector2<T>& v )
    { x += v.x; y += v.y; return *this; }
    
    template<typename T> tvector2<T>& tvector2<T>::operator-= ( const tvector2<T>& v )
    { x -= v.x; y -= v.y; return *this; }
    
    template<typename T> tvector2<T>& tvector2<T>::operator*= ( const tvector2<T>& v )
    { x *= v.x; y *= v.y; return *this; }
    
    template<typename T> tvector2<T>& tvector2<T>::operator/= ( const tvector2<T>& v )
    { x /= v.x; y /= v.y; return *this; }
    
    template<typename T> tvector2<T>& tvector2<T>::operator+= ( T t )
    { x += t; y += t; return *this; }
    
    template<typename T> tvector2<T>& tvector2<T>::operator-= ( T t )
    { x -= t; y -= t; return *this; }
    
    template<typename T> tvector2<T>& tvector2<T>::operator*= ( T t )
    { x *= t; y *= t; return *this; }
    
    template<typename T> tvector2<T>& tvector2<T>::operator/= ( T t )
    { x /= t; y /= t; return *this; }
    
    template<typename T> tvector2<T>& tvector2<T>::operator++ ()
    { *this += 1; return *this; }
    
    template<typename T> tvector2<T>  tvector2<T>::operator++ (int)
    {
        tvector2<T> v = *this;
        ++v;
        return v;
    }
    
    template<typename T> tvector2<T>& tvector2<T>::operator-- ()
    { *this -= 1; return *this; }
    
    template<typename T> tvector2<T> tvector2<T>::operator-- (int)
    {
        tvector2<T> v = *this;
        --v;
        return v;
    }
    
    ////
    
    template<typename T>
    tvector2<T> operator+ ( const tvector2<T>& v1, const tvector2<T>& v2 )
    { return tvector2<T>( v1.x + v2.x, v1.y + v2.y); }
    
    template<typename T>
    tvector2<T> operator+ ( const tvector2<T>& v1, T t )
    { return tvector2<T>( v1.x + t, v1.y + t ); }
    
    template<typename T>
    tvector2<T> operator- ( const tvector2<T>& v1, const tvector2<T>& v2 )
    { return tvector2<T>( v1.x - v2.x, v1.y - v2.y ); }
    
    template<typename T>
    tvector2<T> operator- ( const tvector2<T>& v1, T t )
    { return tvector2<T>( v1.x - t, v1.y - t ); }
    
    template<typename T>
    tvector2<T> operator* ( const tvector2<T>& v1, const tvector2<T>& v2 )
    { return tvector2<T>( v1.x * v2.x, v1.y * v2.y ); }
    
    template<typename T>
    tvector2<T> operator* ( const tvector2<T>& v1, T t )
    { return tvector2<T>( v1.x * t, v1.y * t ); }
    
    template<typename T>
    tvector2<T> operator/ ( const tvector2<T>& v1, const tvector2<T>& v2 )
    { return tvector2<T>( v1.x / v2.x, v1.y / v2.y ); }
    
    template<typename T>
    tvector2<T> operator/ ( const tvector2<T>& v1, T t )
    { return tvector2<T>( v1.x / t, v1.y / t ); }
    
    template<typename T>
    tvector2<T> operator/ ( T t, const tvector2<T>& v1 )
    { return tvector2<T>( t / v1.x, t / v1.y ); }
    
} }
