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
    typedef tvector3<float> color3;
    typedef tvector4<float> vector4;
    typedef tvector4<float> color4;
    typedef tquaternion<float> quaternion;
    
    /* -- opengl types to minerva types */
    typedef GLuint mg_uint;
    typedef GLenum mg_enum;
    typedef GLint mg_int;
    typedef GLfloat mg_float;
    typedef GLbitfield mg_bitfield;
    typedef GLsizei mg_sizei;
    typedef GLboolean mg_bollean;
    typedef GLbyte mg_byte;
    typedef GLshort mg_short;
    typedef GLubyte mg_ubyte;
    typedef GLushort mg_ushort;
    typedef GLulong mg_ulong;
    typedef GLclampf mg_clampf;
    typedef GLdouble mg_double;
    typedef GLclampd mg_clampd;
    typedef GLvoid mg_void;
    typedef ptrdiff_t mg_intptr;
    typedef ptrdiff_t mg_sizeiptr;
    
    typedef mi_vector<mg_uint> mg_uint_vector;
    
    void mi_check_glerror();
    
    /* -- vertex array type  --*/
    namespace vbo_type {
        enum {
            position,
            indices,
            uv1,
            uv2,
            color,
        };
    }
    
    /// generate and bind to opengl buffer
    mg_uint bind_opengl_buffer( mg_uint type, mg_sizeiptr size, mg_void* buffer, mg_uint draw_type );
    
    /// generate vao
    mg_uint generate_single_vao();
    
    /// enable, bind, and set attrib pointer
    void enable_bind_attrib_pointer( mg_uint index, mg_uint buffer_id, mg_int size, mg_void* offset_pointer);
    
} }


#pragma GCC visibility pop
#endif
