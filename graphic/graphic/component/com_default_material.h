/*
 *  com_default_material.h
 *  graphic
 *
 *  Created by jiayi on 15/03/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#ifndef com_default_material_H
#define com_default_material_H

#include "component/component.h"
#include "component/com_texture.h"
#include "shaders/technique.h"

namespace minerva { namespace graphic {
    
    class com_default_material : public technique, public component
    {
    public:
        com_default_material() {}
        virtual ~com_default_material();
        
    public:
        com_default_material( const com_default_material& c );
        com_default_material( com_default_material&& c );
        virtual com_default_material& operator= ( const com_default_material& c );
        virtual com_default_material& operator= ( com_default_material&& c );
        
        /// light clone is gonna use same memory address
        virtual component* full_clone( model* ) ;
        
        /// deep clone is to make a complete new object with the same datas
        virtual component* copy_clone( model* ) ;
        
    public:
        /// initialize component
        virtual bool initialize( model* m );
        
        /// update component
        virtual void update_component( float );
        
        /// pre render process
        virtual void on_render_component( float delta );
        
        /// render component
        virtual void render_component( float delta );
        
        /// get name
        virtual const char* get_name() const { return "com_default_material"; }
        
        /// overload finalize
        virtual bool finalize();
        
    protected:
        set_get( com_texture_ptr, base_texture );            ///< base texture
        set_get( model_ptr, model );                         ///< base model
    };
    
    make_smart( com_default_material );
    
}}

#endif /* com_default_material_h */
