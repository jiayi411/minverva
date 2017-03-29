/*
 *  model.cpp
 *  graphic
 *
 *  Created by jiayi on 15/03/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#include "model/model.h"
#include "math/vector2.h"

using namespace minerva::graphic;

model::~model()
{
//    safe_delete_array( _vertices );
//    safe_delete_array( _uvs );
//    safe_delete_array( _colors );
//    safe_delete_array( _indices );
    for (auto& c : _components) {
        c.second = nullptr;
    }
    _components.clear();
}

model::model( const model& m )
{ this->operator=( m ); }

model::model( model&& m )
{ this->operator=( m ); }

model& model::operator= ( const model& m )
{
    _name = m.get_name();
    for (auto& c : m._components) {
        _components.emplace( c.first, c.second->full_clone( this ) );
    }
    return *this;
}

model& model::operator= ( model&& m )
{
    _name = std::move( m._name );
    for (auto& c : m._components) {
        _components.emplace( c.first, c.second->copy_clone( this ) );
    }
    return *this;
}

void model::update( float delta )
{
    node_object::update( delta );
    for (auto& c : _components) {
        c.second->update_component( delta );
    }
}

void model::on_render( float delta )
{
    node_object::on_render( delta );
    for (auto& c : _components) {
        c.second->on_render_component( delta );
    }
}

/// render
void model::render( float delta )
{
    on_render( delta );
    node_object::render( delta );
    for (auto& c : _components) {
        c.second->render_component( delta );
    }
}
