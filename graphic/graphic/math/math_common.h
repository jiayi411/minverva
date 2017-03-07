//
//  math_functions.h
//  graphic
//
//  Created by jiayi on 18/02/2017.
//  Copyright © 2017 jiayi. All rights reserved.
//

#ifndef math_common_h
#define math_common_h

#include "graphic/math/vector3.h"

namespace minerva { namespace graphic {
    
    /// mix things
    template<typename T>
    T mix( const T& t1, const T& t2, float a );
    
    template<typename T>
    vector3<T> cos( const vector3<T>& v );
    
    template<typename T>
    vector3<T> sin( const vector3<T>& v );
    
} }

#include "graphic/math/math_common.inl"

#endif /* math_common_h */
