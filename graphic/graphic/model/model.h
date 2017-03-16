/*
 *  model.h
 *  graphic
 *
 *  Created by jiayi on 15/03/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#ifndef model_H
#define model_H

#include "model/node_object.h"
#include "component/component.h"
#include "graphic.h"

namespace minerva { namespace graphic {
    
    class component_protocol;
    
    ///
    /// @brief basic model that contains vertex, indices, etc.
    ///
    /// the model object is designed as component, you can add
    /// as many component as you want. For instance, adding a
    /// technique or uv or textures. This class only contains
    /// very basic items including vertices, indices and colors.
    class model : public node_object
    {
    public:
        model() {}//: _vertices(nullptr), _indices(nullptr), _colors(nullptr), _uvs(nullptr){}
        virtual ~model();
        
    public:
        /// add a component to model
        template<class T>
        void add_component( component* c );
        
        /// remove a component
        template<class T>
        void remove_component();
        
        /// get a component
        template<class T>
        T* get_component();        
        
        /// update model
        virtual void update( float delta );
        
        /// before render
        virtual void on_render( float delta);
        
        /// render
        virtual void render( float delta );
        
    protected:
        set_get_ref( std::string, name );
        
    public:
        using component_container = mi_unordered_map<std::size_t, component_ptr>;
        
    protected:
        component_container _components;
    };
    
    make_smart( model );
    
}}

#include "model/model.inl"

#endif /* model_h */
