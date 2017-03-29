/*
 *  graphic.cpp
 *  graphic
 *
 *  Created by jiayi on 09/02/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

//#include <iostream>
#include "graphic.h"
#include "math/vector2.h"
#include "math/vector3.h"
#include "math/vector4.h"
#include "renderer/renderer.h"

using namespace minerva::foundation;
using namespace minerva::graphic;

template<> vector2 vector2::s_vector_zero = vector2( 0.f, 0.f );

template<> vector3 vector3::s_vector_x = vector3( 1.f, 0.f, 0.f );
template<> vector3 vector3::s_vector_y = vector3( 0.f, 1.f, 0.f );
template<> vector3 vector3::s_vector_z = vector3( 0.f, 0.f, 1.f );
template<> vector3 vector3::s_vector_zero = vector3( 0.f, 0.f, 0.f );

template<> vector4 vector4::s_vector_zero = vector4( 0.f, 0.f, 0.f, 0.f );

template<> renderer* singleton<renderer>::_this = nullptr;

namespace minerva { namespace graphic {
    void initialize_singletons()
    {
        the_renderer->initialize();
    }
    
    void destroy_singletons()
    {
        the_renderer->destroy();
    }

}}
