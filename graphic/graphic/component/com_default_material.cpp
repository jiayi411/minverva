/*
 *  com_default_material.cpp
 *  graphic
 *
 *  Created by jiayi on 15/03/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#include "com_default_material.h"
#include "renderer/renderer.h"
#include "foundation/foundation.h"

using namespace minerva::graphic;
using namespace minerva::foundation;

com_default_material::~com_default_material()
{
    _base_texture = nullptr;
    _model = nullptr;
}

com_default_material::com_default_material( const com_default_material& c )
{
    this->operator=(c);
}

com_default_material::com_default_material( com_default_material&& c )
{
    this->operator=(c);
}

com_default_material& com_default_material::operator= ( const com_default_material& c )
{
    technique::operator=(c);
    _model = c._model;
    _base_texture = c._base_texture;
    return *this;
}

com_default_material& com_default_material::operator= ( com_default_material&& c )
{    
    technique::operator=(c);
    _model = std::move(c._model);
    _base_texture = std::move(c._base_texture);
    return *this;
}

component* com_default_material::full_clone( model* m )
{
    com_default_material* temp = mi_new com_default_material();
    *temp = *this;
    temp->set_model( m );
    return temp;
}


component* com_default_material::copy_clone( model* m ) 
{
    com_default_material* temp = mi_new com_default_material();
    *temp = std::move(*this);
    temp->set_model( m );
    return temp;
}

/// initialize component
bool com_default_material::initialize( model* m )
{
    if (!_base_texture)
    { _base_texture = mi_new com_texture(); }
    
    
    if (!initialize_technique()) { return false; }
    
    _base_texture->initialize( m );
    _base_texture->_set_texture_index( 0 );
    
    set_model( m );
    return true;
}

/// update component
void com_default_material::update_component( float delta )
{
    _base_texture->update_component( delta );
}

void com_default_material::on_render_component( float delta )
{
    // enable technique
    enable();
    
    /// caculate mvp
    float ftime = the_core->get_life_time();
    camera_ptr cam = the_renderer->get_camera();
    
    matrix4x4 projection = cam->get_perspective_matrix();
    matrix4x4 view = cam->get_view_matrix();
    matrix4x4 model = _model->get_transform().get_final_matrix();
    
    matrix4x4 mvp = projection * view * model;
    
    
    GLuint matrixId = this->get_uniform( "mvp" );
    GLuint timeId = this->get_uniform( "time" );
    
    glUniformMatrix4fv( matrixId, 1, GL_TRUE, &mvp[0][0] );
    glUniform1f( timeId, ftime );    
    
//    _base_texture->on_render_component( delta );
}

/// render component
void com_default_material::render_component( float delta )
{
//    _base_texture->render_component( delta );
}

bool com_default_material::finalize()
{
    if (!technique::finalize()) { return false; }
    
    // set texture infomation
    mg_uint sampler_2d = get_uniform( "textureSampler" );
    _base_texture->_set_sampler( sampler_2d );
    
    return true;
}
