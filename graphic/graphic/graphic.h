/*
 *  graphic.hpp
 *  graphic
 *
 *  Created by jiayi on 09/02/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#ifndef graphic_
#define graphic_

/* The classes below are exported */
#pragma GCC visibility push(default)

#include <GL/glew.h>
#include "foundation/standard_libraries/vector.h"

namespace minerva { namespace graphic {
    
    
    template<typename T> class tmatrix3x3;
    template<typename T> class tmatrix4x4;
    template<typename T> class tvector2;
    template<typename T> class tvector3;
    template<typename T> class tvector4;
    template<typename T> class tquaternion;
    
    typedef tmatrix3x3<float> matrix3x3;
    typedef tmatrix4x4<float> matrix4x4;
    typedef tvector2<float> vector2;
    typedef tvector3<float> vector3;
    typedef tvector4<float> vector4;
    typedef tquaternion<float> quaternion;
    
    typedef mi_vector<GLuint> gluint_vector;
    
    void mi_check_glerror();
    
} }


#pragma GCC visibility pop
#endif
