/*
 *  rectangle.cpp
 *  graphic
 *
 *  Created by jiayi on 29/03/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#include "rectangle.h"

using namespace minerva::graphic;

void rectangle::initialize_shape()
{
    add_vertex( -1, 1, 0 );
    add_vertex( -1, -1, 0 );
    add_vertex( 1, 1, 0 );
    add_vertex( 1, -1, 0 );
    
    add_face(0, 1, 2);
    add_face(2, 1, 3);
    
    add_uv( 0, 0 );
    add_uv( 0, 1 );
    add_uv( 1, 1 );
    add_uv( 1, 0 );
    
    add_color( .1, .1, .1 );
    add_color( .1, .1, .1 );
    add_color( .1, .1, .1 );
    add_color( .1, .1, .1 );
}

void sphere::initialize_shape()
{
    add_vertex( -1, 1, 0 );
    add_vertex( 1, 1, 0 );
    add_vertex( -1, -1, 0 );
    add_vertex( 1, -1, 0 );
    
    add_vertex( 0, -1, 1 );
    add_vertex( 0, 1, 1 );
    add_vertex( 0, -1, -1 );
    add_vertex( 0, 1, -1 );
    
    add_vertex( 1, 0, -1 );
    add_vertex( 1, 0, 1 );
    add_vertex( -1, 0, -1 );
    add_vertex( -1, 0, 1 );
    
    add_face( 0, 11, 5 );
    add_face( 0, 5, 1 );
    add_face( 0, 1, 7 );
    add_face( 0, 7, 10 );
    add_face( 0, 10, 11 );
    
    add_face( 1, 5, 9 );
    add_face( 5, 11, 4 );
    add_face( 11, 10, 2 );
    add_face( 10, 7, 6 );
    add_face( 7, 1, 8 );
    
    add_face( 3, 9, 4 );
    add_face( 3, 4, 2 );
    add_face( 3, 2, 6 );
    add_face( 3, 6, 8 );
    add_face( 3, 8, 9 );
    
    add_face( 4, 9, 5 );
    add_face( 2, 4, 11 );
    add_face( 6, 2, 10 );
    add_face( 8, 6, 7 );
    add_face( 9, 8, 1 );
    
    add_color(1,0,0);
    add_color(0,1,0);
    add_color(0,0,1);
    add_color(1,1,0);
    
    add_color(0,1,1);
    add_color(1,0,1);
    add_color(1,0,0);
    add_color(0,1,0);
    
    add_color(0,0,1);
    add_color(1,1,0);
    add_color(0,1,1);
    add_color(1,0,1);
    
    set_level( 4 );
}

uint sphere::_get_mid_point( uint index1, uint index2 )
{
    uint key = (std::min(index1, index2) << 16) | std::max(index1, index2);
    if (_cache.find(key) != _cache.end()) {
        return _cache[key];
    }
    
    const vector3& v1 = get_vertex_by_index(index1);
    const vector3& v2 = get_vertex_by_index(index2);
    vector3 mid = ( v1 + v2 ) / 2.f;
    
    uint idx = add_vertex( mid );
    _cache[key] = idx;
    return idx;
}

void sphere::set_level( int n )
{
    if (_level >= n) { return; }
    _level = n;
    
    
    while (n-- > 0) {
        face_container new_faces;
        for (auto& f : _faces) {
            uint idx1 = _get_mid_point(f[0], f[1]);
            uint idx2 = _get_mid_point(f[1], f[2]);
            uint idx3 = _get_mid_point(f[0], f[2]);
            
            new_faces.emplace_back(face(f[0], idx1, idx3));
            new_faces.emplace_back(face(idx1, idx2, idx3));
            new_faces.emplace_back(face(idx1, f[1], idx2));
            new_faces.emplace_back(face(idx3, idx2, f[2]));
        }
        _faces = std::move(new_faces);
    }
}
