/*
 *  technique.cpp
 *  graphic
 *
 *  Created by jiayi on 13/03/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#include "technique.h"
#include <fstream>

using namespace minerva::graphic;

technique::technique()
{ _program_id = 0; }

technique::~technique()
{
    for (auto& s : _shaders) {
        glDeleteShader(s);
    }
    
    _shaders.clear();
    
    if (_program_id != 0) {
        glDeleteProgram( _program_id );
        _program_id = 0;
    }
}

/// initialize
bool technique::initialize()
{
    _program_id = glCreateProgram();
    if (_program_id == 0) {
        mi_log( "initialize technique failed\n" );
        return false;
    }
    return true;
}

/// add shader by filename and shader type
bool technique::add_shader( e_shader_type shader_type, const std::string& file )
{
    std::string shader_code;
    std::ifstream shader_stream( file, std::ios::in );
    if (shader_stream.is_open()) {
        std::string line = "";
        while (getline(shader_stream, line))
            shader_code += "\n" + line;
        shader_stream.close();
    } else {
        mi_log("Impossible to open %s. Are you in the right directory ?\n", file.c_str());
        return false;
    }
    
    GLuint shader_object = glCreateShader(shader_type);
    
    if (shader_object == 0) {
        mi_log( "Error creating shader type %d\n", shader_type );
        return false;
    }
    
    // Save the shader object - will be deleted in the destructor
    _shaders.push_back(shader_object);
    
    // compiling
    mi_log( "Compiling shader : %s\n", file.c_str() );
    char const * code_pointer = shader_code.c_str();
    glShaderSource( shader_object, 1, &code_pointer , NULL );
    glCompileShader( shader_object );
    
    // Check Vertex Shader
    GLint result = GL_FALSE;
    int log_length;
    glGetShaderiv( shader_object, GL_COMPILE_STATUS, &result );
    glGetShaderiv( shader_object, GL_INFO_LOG_LENGTH, &log_length );
    if (log_length > 0) {
        std::vector<char> error_message( log_length + 1 );
        glGetShaderInfoLog( shader_object, log_length, NULL, &error_message[0] );
        mi_log( "%s\n", &error_message[0] );
        return false;
    }
    
    // attach to program
    glAttachShader( _program_id, shader_object );
    
    return true;
}

/// finalize when add all shaders
bool technique::finalize()
{
    GLint success = 0;
    GLchar error_log[1024] = { 0 };
    
    glLinkProgram( _program_id );
    
    glGetProgramiv( _program_id, GL_LINK_STATUS, &success);
    if (success == 0) {
        glGetProgramInfoLog( _program_id, sizeof(error_log), NULL, error_log );
        mi_log( "Error linking shader program: '%s'\n", error_log );
        return false;
    }
    
    glValidateProgram( _program_id );
    glGetProgramiv( _program_id, GL_VALIDATE_STATUS, &success );
    if (!success) {
        glGetProgramInfoLog( _program_id, sizeof(error_log), NULL, error_log );
        mi_log("Invalid shader program: '%s'\n", error_log );
        return false;
    }
    
    // Delete the intermediate shader objects that have been added to the program
    for (auto& s : _shaders) {
        glDeleteShader(s);
    }
    
    _shaders.clear();
    
    mi_check_glerror();
    
    return true;
}

/// enable this technique
void technique::enable()
{ glUseProgram( _program_id ); }

/// get uniform location of shader
mg_uint technique::get_uniform( const std::string& name )
{
    GLuint location = glGetUniformLocation( _program_id, name.c_str() );
    
    if (location == GL_INVALID_VALUE) {
        mi_log("Warning! Unable to get the location of uniform '%s'\n", name.c_str());
    }
    
    return location;
}

/// get program parameter
mg_int technique::get_parameter( GLint param )
{
    GLint ret;
    glGetProgramiv( _program_id, param, &ret );
    return ret;
}
