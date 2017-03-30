/*
 *  rectangle.cpp
 *  graphic
 *
 *  Created by jiayi on 29/03/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#include "rectangle.h"

using namespace minerva::graphic;

void rectangle::intialize_shape()
{
    add_vertex( -1, 1, 0 );
    add_vertex( -1, -1, 0 );
    add_vertex( 1, 1, 0 );
    add_vertex( 1, -1, 0 );
    
    add_face(0, 1, 2);
    add_face(2, 1, 3);
    
    add_uv( 0, 0 );
    add_uv( 0, 1 );
    add_uv( 1, 1 );
    add_uv( 1, 0 );
    
    add_color( .1, .1, .1 );
    add_color( .1, .1, .1 );
    add_color( .1, .1, .1 );
    add_color( .1, .1, .1 );
}
