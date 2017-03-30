/*
 *  shape.h
 *  graphic
 *
 *  Created by jiayi on 29/03/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#ifndef shape_H
#define shape_H

#include "model/node_object.h"

namespace minerva { namespace graphic {
    
    class shape : public node_object
    {
    public:
        struct face
        {
            face(int a, int b, int c)  { v[0] = a; v[1] = b; v[2] = c; }
            
            /// overload the [] operator
            int operator[] ( int index ) { return v[index]; }
            
            uint v[3]; ///< index of three vertices
        };
        
    public:
        shape(){}
        virtual ~shape();
        
        shape( const shape& s );
        shape( shape&& s );
        shape& operator= ( const shape& s );
        shape& operator= ( shape&& s );
        
        /// initialize shape
        virtual void initialize_shape() = 0;
        
        /// add vertex
        virtual uint add_vertex( vector3::value_type x, vector3::value_type y, vector3::value_type z );
        virtual uint add_vertex( const vector3& v );
        virtual uint add_vertex( vector3&& v );
        
        /// add color
        virtual void add_color( color3::value_type x, color3::value_type y, color3::value_type z );
        virtual void add_color( const color3& v );
        virtual void add_color( color3&& v );
        
        /// add uv
        virtual void add_uv( vector2::value_type u, vector2::value_type v );
        virtual void add_uv( const vector2& v );
        virtual void add_uv( vector2&& v );
        
        /// add face
        virtual void add_face( int index1, int index2, int index3 );
        virtual void add_face( const face& f );
        virtual void add_face( face&& f );
        
        /// get vertex
        const vector3& get_vertex_by_index( int index ) const;
        vector3& get_vertex_by_index( int index );
        
        /// get vertex count
        uint get_vertex_count() const { return static_cast<uint>(_vertices.size()); }
        uint get_color_count() const { return static_cast<uint>(_colors.size()); }
        uint get_uv_count() const { return static_cast<uint>(_uvs.size()); }
        uint get_face_count() const { return static_cast<uint>(_faces.size()); }
        
    public:
        vector3* get_vertices_data() { return _vertices.data(); }
        face* get_faces_data() { return _faces.data(); }
        vector2* get_uvs_data() { return _uvs.data(); }
        color3* get_colors_data() { return _colors.data(); }
        
    protected:
        typedef mi_vector<face> face_container;
        
    protected:
        set_get_ref( face_container, faces );  ///< faces container
        set_get_ref( vector3_container, vertices );  ///< vertices of the model
        set_get_ref( color3_container, colors );     ///< color of vertices
        set_get_ref( vector2_container, uvs );       ///< uvs
    };
    
    make_smart( shape );
    
} }

#endif /* shape_h */
