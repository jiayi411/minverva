/*
 *  camera.cpp
 *  graphic
 *
 *  Created by jiayi on 07/03/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#include "camera.h"

using namespace minerva;
using namespace minerva::graphic;

void camera::initialize()
{
    set_up( vector3( 0, 1, 0 ) );
    set_forward( vector3( 0, 0, -1 ) );
    _screen_position = vector2( 0xff, 0xff );
}

void camera::rotation(float dx, float dy)
{
    if (std::isnan( dx ) || std::isnan(dy) ) { return; }
    
    /// caculate rotation by Y
    quaternion& self_quaternion = _transform.get_rotation();
    
    // new y rotation
    vector3 forward = -vector3::s_vector_z;
    
    quaternion new_y_rotate;
    new_y_rotate.from_axis_angle( std::asinf( dx ), vector3::s_vector_y );
    self_quaternion = new_y_rotate * self_quaternion;
    forward = self_quaternion * forward;
    
    // new x rotation
    vector3 horizontal_axis = graphic::cross( forward, vector3::s_vector_y );
    quaternion new_x_rotate;
    new_x_rotate.from_axis_angle( std::asinf( dy ), horizontal_axis );
    self_quaternion = new_x_rotate * self_quaternion;
    forward = self_quaternion * forward;
    
    // new up
    set_up( graphic::cross( horizontal_axis, forward ).normalize() );
    
    // now we get quaternion, we can rotate target
    set_forward( forward.normalize() );
}

void camera::update(float f)
{
    if (!get_dirty()) { return; }
    
    vector2 delta = _screen_position - _old_screen_position;
    delta.normalize() /= 200;
    rotation( delta.x, delta.y );
    
    set_dirty( false );
}

void camera::set_screen_position( float x, float y )
{
    _old_screen_position = _screen_position;
    _screen_position.x = x;
    _screen_position.y = y;
    
    if (_old_screen_position.x == 0xff) { _old_screen_position = _screen_position; }
    
    set_dirty( true );
}

matrix4x4 camera::get_view_matrix() const
{
    vector3 t = _transform.get_position() + get_forward() * 3.f;
    return graphic::view( _transform.get_position(), t, get_up() );
}
