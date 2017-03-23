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

void model::update( float delta )
{
    for (auto& c : _components) {
        c.second->update_component( delta );
    }
}

void model::on_render( float delta )
{
    for (auto& c : _components) {
        c.second->on_render_component( delta );
    }
}

/// render
void model::render( float delta )
{
    for (auto& c : _components) {
        c.second->render_component( delta );
    }
}
