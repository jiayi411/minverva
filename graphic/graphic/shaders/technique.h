/*
 *  technique.h
 *  graphic
 *
 *  Created by jiayi on 13/03/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#ifndef technique_H
#define technique_H

#include "foundation/object/update_object.h"
#include "graphic.h"
namespace minerva { namespace graphic {
    
    ///
    /// @brief base class for shader
    ///
    class technique : public foundation::update_object
    {
    public:
        enum e_shader_type {
            vertex_shader = GL_VERTEX_SHADER,
            fragment_shader = GL_FRAGMENT_SHADER
        };
        
    public:
        technique();
        virtual ~technique();
        
    public:
        /// initialize
        bool initialize();
        
        /// add shader by filename and shader type
        bool add_shader( e_shader_type shader_type, const std::string& file );
        
        /// finalize when add all shaders
        bool finalize();
        
        /// enable this technique
        void enable();
        
        /// get uniform location of shader
        mg_uint get_uniform( const std::string& name );
        
        /// get program parameter
        mg_int get_parameter( GLint param );
        
    protected:
        mg_uint_vector _shaders; ///< all loaded shaders
        mg_uint _program_id;     ///< shader program id
        
        
    };
} }

#endif /* technique_h */
