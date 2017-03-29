/*
 *  com_camera_controller.cpp
 *  graphic
 *
 *  Created by jiayi on 28/03/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#include "component/com_camera_controller.h"
#include "renderer/renderer.h"

using namespace minerva::graphic;
using namespace minerva::foundation;

com_camera_controller::~com_camera_controller()
{
    
}

com_camera_controller::com_camera_controller( const com_camera_controller& c )
{
    this->operator=( c );
}

com_camera_controller::com_camera_controller( com_camera_controller&& c )
{
    this->operator=( c );
}

com_camera_controller& com_camera_controller::operator= ( const com_camera_controller& c )
{
    com_controller::operator=(c);
    _model = c._model;
    return *this;
}
com_camera_controller& com_camera_controller::operator= ( com_camera_controller&& c )
{
    com_controller::operator=(c);
    _model = std::move( c._model );
    return *this;
}

/// light clone is gonna use same memory address
component* com_camera_controller::full_clone( model* m )
{
    com_camera_controller* c = mi_new com_camera_controller();
    *c = *this;
    return c;
}

/// deep clone is to make a complete new object with the same datas
component* com_camera_controller::copy_clone( model* m )
{
    com_camera_controller* c = mi_new com_camera_controller();
    *c = std::move(*this);
    
    return c;
}

/// initialize component
bool com_camera_controller::initialize( model* m )
{
    com_controller::initialize(m);
    bind_key( ctrl_keyboard, GLFW_KEY_W, std::bind(
                                                   &com_camera_controller::_move_forward,
                                                   this,
                                                   std::placeholders::_1,
                                                   std::placeholders::_2,
                                                   std::placeholders::_3,
                                                   std::placeholders::_4 )
             );
    bind_key( ctrl_keyboard, GLFW_KEY_S, std::bind(
                                                   &com_camera_controller::_move_backward,
                                                   this,
                                                   std::placeholders::_1,
                                                   std::placeholders::_2,
                                                   std::placeholders::_3,
                                                   std::placeholders::_4 )
             );
    bind_key( ctrl_keyboard, GLFW_KEY_A, std::bind(
                                                   &com_camera_controller::_move_left,
                                                   this,
                                                   std::placeholders::_1,
                                                   std::placeholders::_2,
                                                   std::placeholders::_3,
                                                   std::placeholders::_4 )
             );
    bind_key( ctrl_keyboard, GLFW_KEY_D, std::bind(
                                                   &com_camera_controller::_move_right,
                                                   this,
                                                   std::placeholders::_1,
                                                   std::placeholders::_2,
                                                   std::placeholders::_3,
                                                   std::placeholders::_4 )
             );
    bind_key( ctrl_screen, GLFW_MOUSE_BUTTON_LEFT, std::bind(
                                                   &com_camera_controller::_rotate,
                                                   this,
                                                   std::placeholders::_1,
                                                   std::placeholders::_2,
                                                   std::placeholders::_3,
                                                   std::placeholders::_4 )
             );
    return true;
}

/// update component
void com_camera_controller::update_component( float delta )
{
    com_controller::update_component( delta );
}

/// move left
void com_camera_controller::_move_left( bool pressed,model* m, double, double )
{
    if (!pressed) { return; }
    
    camera* cam = static_cast<camera*>(m);
    transform& trans = cam->get_transform();
    trans.get_position() -= cam->get_right() * get_pace();
}

/// move right
void com_camera_controller::_move_right( bool pressed,model* m, double, double )
{
    if (!pressed) { return; }
    
    camera* cam = static_cast<camera*>(m);
    transform& trans = cam->get_transform();
    trans.get_position() += cam->get_right() * get_pace();
}

/// move forward
void com_camera_controller::_move_forward( bool pressed,model* m, double, double )
{
    if (!pressed) { return; }
    
    camera* cam = static_cast<camera*>(m);
    transform& trans = cam->get_transform();
    trans.get_position() += cam->get_forward() * get_pace();
}

/// move backward
void com_camera_controller::_move_backward( bool pressed,model* m, double, double )
{
    if (!pressed) { return; }
    
    camera* cam = static_cast<camera*>(m);
    transform& trans = cam->get_transform();
    trans.get_position() -= cam->get_forward() * get_pace();
}

/// rotate
void com_camera_controller::_rotate( bool pressed, model* m, double x, double y )
{
    if (!pressed) { return; }
    
    camera* cam = static_cast<camera*>(m);
    cam->update_screen_position( x, y );
}
