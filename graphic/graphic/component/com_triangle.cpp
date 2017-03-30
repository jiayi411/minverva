/*
 *  com_triangle.cpp
 *  graphic
 *
 *  Created by jiayi on 15/03/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#include "com_triangle.h"
#include "math/vector2.h"
#include "renderer/renderer.h"

using namespace minerva::graphic;

com_triangle::~com_triangle()
{
    glDeleteBuffers( 1, &_vertex_buffer_id );
    glDeleteBuffers( 1, &_uv_buffer_id );
    glDeleteBuffers( 1, &_color_buffer_id );
   // glDeleteBuffers( 1, &_indices_buffer_id );
    glDeleteVertexArrays( 1, &_vao_id );
    
    _rectangle_data = nullptr;
}

com_triangle::com_triangle( const com_triangle& c )
{
    this->operator=(c);
}

com_triangle::com_triangle( com_triangle&& c )
{
    this->operator=(c);
}

com_triangle& com_triangle::operator= ( const com_triangle& c )
{
    initialize( c._model );
    return *this;
}

com_triangle& com_triangle::operator= ( com_triangle&& c )
{
    _model = std::move(c._model);
    _vertex_buffer_id = c._vertex_buffer_id;
    _indices_buffer_id = c._indices_buffer_id;
    _color_buffer_id = c._color_buffer_id;
    _uv_buffer_id = c._uv_buffer_id;
    _vao_id = c._vao_id;
    
    _rectangle_data = std::move(c._rectangle_data);
    return *this;
}

component* com_triangle::full_clone( model* m ) 
{
    com_triangle* temp = mi_new com_triangle();
    *temp = *this;
    temp->set_model( m );
    return temp;
}

component* com_triangle::copy_clone( model* m )
{
    com_triangle* temp = mi_new com_triangle();
    *temp = std::move(*this);
    temp->set_model( m );
    return temp;
}


/// initialize component
bool com_triangle::initialize( model* m )
{
    set_model( m );
    
    _rectangle_data = mi_new rectangle();
    _rectangle_data->intialize_shape();
    
    uint vertex_count = _rectangle_data->get_vertex_count();
    
    _vertex_buffer_id = the_renderer->gen_bind_buffer( GL_ARRAY_BUFFER, vertex_count * sizeof( vector3 ), _rectangle_data->get_vertices_data(), GL_STATIC_DRAW );
    _color_buffer_id = the_renderer->gen_bind_buffer( GL_ARRAY_BUFFER, vertex_count * sizeof( color3 ), _rectangle_data->get_colors_data(), GL_STATIC_DRAW );
    _uv_buffer_id = the_renderer->gen_bind_buffer( GL_ARRAY_BUFFER, vertex_count * sizeof( vector2 ), _rectangle_data->get_uvs_data(), GL_STATIC_DRAW );
    _indices_buffer_id = the_renderer->gen_bind_buffer( GL_ELEMENT_ARRAY_BUFFER, _rectangle_data->get_faces().size() * sizeof( shape::face ), _rectangle_data->get_faces_data(), GL_STATIC_DRAW );
    
    _vao_id = the_renderer->generate_single_vao();
    the_renderer->enable_bind_attrib_pointer( 0, GL_ARRAY_BUFFER, GL_FLOAT, _vertex_buffer_id, 3, (mg_void*)0 );
    the_renderer->enable_bind_attrib_pointer( 1, GL_ARRAY_BUFFER, GL_FLOAT, _color_buffer_id, 3, (mg_void*)0 );
    the_renderer->enable_bind_attrib_pointer( 2, GL_ARRAY_BUFFER, GL_FLOAT, _uv_buffer_id, 2, (mg_void*)0 );
    the_renderer->bind_buffer( GL_ELEMENT_ARRAY_BUFFER, _indices_buffer_id );
    
    return true;
}

/// update component
void com_triangle::update_component( float delta )
{
    
}

void com_triangle::on_render_component( float delta )
{
    glBindVertexArray( _vao_id );
}

/// render component
void com_triangle::render_component( float delta )
{
    glDrawElements(GL_TRIANGLES, (mg_sizei)_rectangle_data->get_faces().size() * 3, GL_UNSIGNED_INT, (void*)0);
}
