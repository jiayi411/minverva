#include <cmath>
namespace minerva { namespace graphic {
    
    template<typename T>
    T mix( const T& t1, const T& t2, float a )
    { return t1 + a * ( t2 - t1 ); }
    
    template<typename T>
    vector3<T> cos( const vector3<T>& v )
    { return vector3<T>( std::cos(v.x), std::cos(v.y), std::cos(v.z) ); }
    
    template<typename T>
    vector3<T> sin( const vector3<T>& v )
    { return vector3<T>( std::sin(v.x), std::sin(v.y), std::sin(v.z) ); }

}}
