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
    /// @brief model is an object that can take several components
    ///
    /// the model object is designed as an object that can equiped with
    /// as many as components. The capability of this model is defined by
    /// its components.
    class model : public node_object
    {
    public:
        model() {}
        virtual ~model();
        
    public:
        model( const model& m );
        model( model&& m );
        model& operator= ( const model& m );
        model& operator= ( model&& m );
        
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
