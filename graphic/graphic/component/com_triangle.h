/*
 *  com_triangle.h
 *  graphic
 *
 *  Created by jiayi on 15/03/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#ifndef com_triangle_H
#define com_triangle_H

#include "component/component.h"
#include "model/model.h"

namespace minerva { namespace graphic {
    
    class com_triangle : public component
    {
    public:
        com_triangle() : _model(nullptr){}
        virtual ~com_triangle();
        
    public:
        com_triangle( const com_triangle& c );
        com_triangle( com_triangle&& c );
        com_triangle& operator= ( const com_triangle& c );
        com_triangle& operator= ( com_triangle&& c );
        
        /// light clone is gonna use same memory address
        virtual component* full_clone( model* ) ;
        
        /// deep clone is to make a complete new object with the same datas
        virtual component* copy_clone( model* ) ;
        
    public:
        
        /// initialize component
        virtual bool initialize( model* m );
        
        /// update component
        virtual void update_component( float delta );
        
        /// pre render process
        virtual void on_render_component( float delta );
        
        /// render component
        virtual void render_component( float delta );
        
        /// get name
        virtual const char* get_name() const  { return "com_triangle"; }
        
    protected:
        /*-- setup various things --*/
        void _setup_vertices();
        void _setup_colors();
        void _setup_uvs();
        void _setup_indices();
        
    protected:
        set_get( model_ptr, model );
        set_get( mg_uint, vertex_buffer_id );
        set_get( mg_uint, color_buffer_id );
        set_get( mg_uint, uv_buffer_id );
        set_get( mg_uint, indices_buffer_id );
        set_get( mg_uint, vao_id );
        
        set_get( vector3*, vertices );  ///< vertices of the model
        set_get( float*, indices );     ///< indices of the model
        set_get( color3*, colors );     ///< color of vertices
        set_get( vector2*, uvs );       ///< uvs
        
        static const int sc_vertices_count = 6;
    };
    
    make_smart( com_triangle );
    
}}

#endif /* com_triangle_h */
