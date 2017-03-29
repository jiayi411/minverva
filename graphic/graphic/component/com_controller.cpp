/*
 *  com_controller.cpp
 *  graphic
 *
 *  Created by jiayi on 28/03/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#include "component/com_controller.h"
#include "renderer/renderer.h"

using namespace minerva::graphic;
using namespace minerva::foundation;

com_controller::~com_controller()
{
    for (int i = 0; i < ctrl_count; ++i) {
        _events[i].clear();
        _marks[i].clear();
    }
}

com_controller::com_controller( const com_controller& c )
{
    this->operator=( c );
}

com_controller::com_controller( com_controller&& c )
{
    this->operator=( c );
}

com_controller& com_controller::operator= ( const com_controller& c )
{
    _model = c._model;
    
    for (int i = 0; i < ctrl_count; ++i) {
        _events[i] = c._events[i];
    }
    
    return *this;
}
com_controller& com_controller::operator= ( com_controller&& c )
{
    _model = std::move( c._model );
    
    for (int i = 0; i < ctrl_count; ++i) {
        _events[i] = std::move(c._events[i]);
    }
    
    return *this;
}

component* com_controller::full_clone( model* m )
{
    com_controller* c = mi_new com_controller();
    *c = *this;
    c->set_model( m );
    return c;
}

component* com_controller::copy_clone( model* m )
{
    com_controller* c = mi_new com_controller();
    *c = std::move(*this);
    c->set_model( m );
    return c;
}

bool com_controller::initialize( model* m )
{
    set_model( m );
    return true;
}

void com_controller::update_component( float delta )
{
    GLFWwindow* window = the_renderer->get_window();
    
    for (int i = 0; i < ctrl_count; ++i) {
        decltype( _events[i].equal_range(0) ) range;
        for (auto e = _events[i].begin(); e != _events[i].end(); e = range.second) {
            range = _events[i].equal_range( e->first );
            
            double x = 0, y = 0;
            bool pressed = false, mark = false;
            
            // get the key states
            if (i == ctrl_keyboard) {
                pressed = glfwGetKey( window, e->first ) == GLFW_PRESS;
            } else if(i == ctrl_screen) {
                pressed = glfwGetMouseButton( window, e->first ) == GLFW_PRESS;
                glfwGetCursorPos( window, &x, &y );
            }
            
            mark = _marks[i][e->first];
            
            // if the key was (not) pressed and is (not) pressed too, skip.
            if (!mark && mark == pressed) { continue; }
            
            // set state
            _marks[i][e->first] = pressed;
            
            // iterate all functions and execute
            for (auto k = range.first; k != range.second; ++k) {
                k->second( pressed, _model, x, y );
            }
        }
    }
}

void com_controller::bind_key( uint type, uint key, const function_event& func )
{
    if (type > ctrl_count) {
        mi_log("error key type:%d", type);
        return;
    }
    
    _events[type].emplace( key, func );
}
