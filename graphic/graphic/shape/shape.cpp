/*
 *  shape.cpp
 *  graphic
 *
 *  Created by jiayi on 29/03/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#include "shape.h"

using namespace minerva::graphic;

shape::~shape()
{
    _vertices.clear();
    _indices.clear();
    _uvs.clear();
    _colors.clear();
    _faces.clear();
}

shape::shape( const shape& s )
{ *this = s; }

shape::shape( shape&& s )
{ *this = s; }

shape& shape::operator= ( const shape& s )
{
    _vertices = s._vertices;
    _indices = s._indices;
    _uvs = s._uvs;
    _colors = s._colors;
    _faces = s._faces;
    return *this;
}

shape& shape::operator= ( shape&& s )
{
    _vertices = std::move(s._vertices);
    _indices = std::move(s._indices);
    _uvs = std::move(s._uvs);
    _colors = std::move(s._colors);
    _faces = std::move(s._faces);
    return *this;
}

void shape::add_vertex( vector3::value_type x, vector3::value_type y, vector3::value_type z )
{
    add_vertex( vector3(x,y,z) );
}

void shape::add_vertex( const vector3& v )
{
    _vertices.emplace_back( v );
}

void shape::add_vertex( vector3&& v )
{
    _vertices.emplace_back( v );
}

void shape::add_face( int index1, int index2, int index3 )
{
    add_face( face(index1, index2, index3) );
}

void shape::add_face( const face& f )
{
    _faces.emplace_back( f );
}

void shape::add_face( face&& f )
{
    _faces.emplace_back( f );
}

void shape::add_color( color3::value_type x, color3::value_type y, color3::value_type z )
{
    add_color( color3( x, y, z ) );
}

void shape::add_color( const color3& v )
{
    _colors.emplace_back( v );
}

void shape::add_color( color3&& v )
{
    _colors.emplace_back( v );
}

void shape::add_uv( vector2::value_type u, vector2::value_type v )
{
    add_uv( vector2( u, v ) );
}

void shape::add_uv( const vector2& v )
{
    _uvs.emplace_back( v );
}

void shape::add_uv( vector2&& v )
{
    _uvs.emplace_back( v );
}


const vector3& shape::get_vertex_by_index( int index ) const
{
    if (index < 0 || index > _vertices.size()) { return vector3::s_vector_zero; }
    
    return _vertices[index];
}

vector3& shape::get_vertex_by_index( int index )
{
    if (index < 0 || index > _vertices.size()) { return vector3::s_vector_zero; }
    
    return _vertices[index];
}
