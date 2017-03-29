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
    
    safe_delete_array( _vertices );
    safe_delete_array( _uvs );
    safe_delete_array( _colors );
    //safe_delete_array( _indices );
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
    
    _vertices = c._vertices;
    _colors = c._colors;
    _uvs = c._uvs;
    
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
    
    _setup_uvs();
    _setup_colors();
    _setup_indices();
    _setup_vertices();
    
    _vao_id = the_renderer->generate_single_vao();
    
    the_renderer->enable_bind_attrib_pointer( 0, _vertex_buffer_id, 3, (mg_void*)0 );
    the_renderer->enable_bind_attrib_pointer( 1, _uv_buffer_id, 2, (mg_void*)0 );
    the_renderer->enable_bind_attrib_pointer( 2, _color_buffer_id, 3, (mg_void*)0 );
    
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
    glDrawArrays(GL_TRIANGLES, 0, sc_vertices_count);
}

void com_triangle::_setup_vertices()
{
    _vertices = new vector3[sc_vertices_count];
    _vertices[0] = vector3(-1.0f, -1.0f, 0.0f);
    _vertices[1] = vector3(1.0f, -1.0f, 0.0f);
    _vertices[2] = vector3(1.f,1.f,0.f);
    _vertices[3] = vector3(1.f,1.f,0.f);
    _vertices[4] = vector3(-1.f,-1.f,0.f);
    _vertices[5] = vector3(-1.f,1.f,0.f);
    
//    _model->set_vertices( vertices );
    
    // bind
    _vertex_buffer_id = the_renderer->bind_opengl_buffer( GL_ARRAY_BUFFER, sc_vertices_count * sizeof( vector3 ), _vertices, GL_STATIC_DRAW );
}

void com_triangle::_setup_colors()
{
    static const GLfloat g_color_buffer_data[] = {
        0.583f,  0.771f,  0.014f,
        0.609f,  0.115f,  0.436f,
        0.327f,  0.483f,  0.844f,
        0.822f,  0.569f,  0.201f,
        0.435f,  0.602f,  0.223f,
        0.310f,  0.747f,  0.185f
    };
    
    color3* colors = new color3[sc_vertices_count];
    for (auto i = 0; i < sc_vertices_count; ++i) {
        colors[i].r = g_color_buffer_data[3*i];
        colors[i].g = g_color_buffer_data[3*i+1];
        colors[i].b = g_color_buffer_data[3*i+2];
    }
    _colors = colors;
    
//    _model->set_colors( colors );
    
    // bind
    _color_buffer_id = the_renderer->bind_opengl_buffer( GL_ARRAY_BUFFER, sc_vertices_count * sizeof( color3 ), colors, GL_STATIC_DRAW );
}

void com_triangle::_setup_uvs()
{
    static const GLfloat g_uv_buffer_data[] = {
        0.000059f, 1.0f-0.000004f,
        0.000103f, 1.0f-0.336048f,
        0.335973f, 1.0f-0.335903f,
        1.000023f, 1.0f-0.000013f,
        0.667979f, 1.0f-0.335851f,
        0.999958f, 1.0f-0.336064f
    };
    
    vector2* uvs = new vector2[sc_vertices_count];
    for (auto i = 0; i < sc_vertices_count; ++i ) {
        uvs[i].x = g_uv_buffer_data[i*2];
        uvs[i].y = g_uv_buffer_data[i*2+1];
    }
    
    _uvs = uvs;
    
//    _model->set_uvs( uvs );
    
    // bind
    _uv_buffer_id = the_renderer->bind_opengl_buffer( GL_ARRAY_BUFFER, sc_vertices_count * sizeof( vector2 ), uvs, GL_STATIC_DRAW );
}

void com_triangle::_setup_indices()
{
    
}
