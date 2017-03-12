/*
 *  transform.cpp
 *  graphic
 *
 *  Created by jiayi on 23/02/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */
#include "transform.h"

using namespace minerva::graphic;

/// copy constructor
transform::transform( const transform& t )
{ this->operator=( t ); }

/// copy constructor with rhs
transform::transform( transform&& t )
{ this->operator=( t ); }

/// copy operator
transform& transform::operator= ( const transform& t )
{
    _rotation = t._rotation;
    _position = t._position;
    _scale_x = t._scale_x;
    _scale_y = t._scale_y;
    _scale_z = t._scale_z;
    _update_all();
    return *this;
}

/// copy operator with rhs
transform& transform::operator= ( transform&& t )
{ return this->operator=( t ); }


void transform::set_scale( float scale )
{
    _scale_x = scale;
    _scale_y = scale;
    _scale_z = scale;
    
    _update_scale();
}

void transform::set_scale_x( float scale )
{
    _scale_x = scale;
    _update_scale();
}

void transform::set_scale_y( float scale )
{
    _scale_y = scale;
    _update_scale();
}

void transform::set_scale_z( float scale )
{
    _scale_z = scale;
    _update_scale();
}

void transform::set_rotation(const quaternion &t)
{
    _rotation = t;
    _update_rotation();
}

void transform::set_position(const vector3 &t)
{
    _position = t;
    _update_position();
}

void transform::_update_all()
{
    _update_scale();
    _update_rotation();
    _update_position();
}

void transform::_update_scale()
{ _matrix_scale.scale( _scale_x, _scale_y, _scale_z ); }

void transform::_update_rotation()
{
    graphic::matrix4_cast( _rotation, &_matrix_rotation );
}
void transform::_update_position()
{
    _matrix_position[0][3] = _position.x;
    _matrix_position[1][3] = _position.y;
    _matrix_position[2][3] = _position.z;
}
