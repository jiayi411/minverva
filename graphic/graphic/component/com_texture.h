/*
 *  com_texture.h
 *  graphic
 *
 *  Created by jiayi on 15/03/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#ifndef com_texture_H
#define com_texture_H

#include "component/component.h"
#include "model/model.h"
#include "foundation/texture/texture_common.h"

namespace minerva { namespace graphic {
    
    class com_texture :  public component
    {
    public:
        friend class com_default_material;
        
    public:
        com_texture() : _texture_id(-1), _sampler(-1), _texture_index(-1), _ready(false){}
        virtual ~com_texture();
        
    public:
        com_texture( const com_texture& c );
        com_texture( com_texture&& c );
        com_texture& operator= ( const com_texture& c );
        com_texture& operator= ( com_texture&& c );
        
        /// light clone is gonna use same memory address
        virtual component* full_clone( model* ) ;
        
        /// deep clone is to make a complete new object with the same datas
        virtual component* copy_clone( model* );
        
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
        virtual const char* get_name() const { return "com_texture"; }
        
    protected:
        /// texture loaded
        void _on_texture_loaded( void* data );
        
    protected:
        half_set_full_get_ref( std::string, texture_file );     ///< texutre file name
        
        mg_uint _texture_id;                                              ///< opengl texture id
        protected_set_get( mg_uint, sampler );                            ///< sampler of texture
        protected_set_get( mg_uint, texture_index );                      ///< using by glActiveTexture, from GL_TEXTURE0 to GL_TEXTURE31
        protected_set_get( model_ptr, model );
        protected_set_get( foundation::texture_data_ptr, texture_data );  ///< texture data
        protected_set_get( bool, dirty );                                 ///< indicate if texture file name changed
        protected_set_get( bool, ready );                                 ///< texture is ready
    };
    
    make_smart( com_texture );
}}


#endif /* com_texture_h */
