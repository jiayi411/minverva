/*
 *  com_default_material.cpp
 *  graphic
 *
 *  Created by jiayi on 15/03/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#include "com_default_material.h"

using namespace minerva::graphic;

com_default_material::~com_default_material()
{
    _base_texture = nullptr;
}

/// initialize component
bool com_default_material::initialize( model* m )
{
    if (!_base_texture)
    { _base_texture = mi_new com_texture(); }
    
    
    if (!initialize_technique()) { return false; }
    
    _base_texture->initialize( m );
    _base_texture->_set_texture_index( 0 );
    return true;
}

/// update component
void com_default_material::update_component( float delta )
{
    _base_texture->update_component( delta );
}

void com_default_material::on_render_component( float delta )
{
    enable();
    _base_texture->on_render_component( delta );    
}

/// render component
void com_default_material::render_component( float delta )
{
    _base_texture->render_component( delta );
}

bool com_default_material::finalize()
{
    if (!technique::finalize()) { return false; }
    
    // set texture infomation
    mg_uint sampler_2d = get_uniform( "textureSampler" );
    _base_texture->_set_sampler( sampler_2d );
    
    return true;
}
