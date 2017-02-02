//
//  main.cpp
//  test
//
//  Created by jiayi on 14/01/2017.
//  Copyright © 2017 jiayi. All rights reserved.
//

#include "foundation/memory/memory_tracker.h"
#include "foundation/singleton.h"
#include "foundation/standard_libraries/vector.h"
#include "foundation/texture/texture_loader.h"
//#include "testApp.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
using namespace glm;


using namespace minerva::foundation;

class test_singleton : public singleton< test_singleton >
{
    
public:
    ~test_singleton(){}
    
    
    void test(){ printf("singleton success\n"); }
};

template<> test_singleton* singleton<test_singleton>::_this = nullptr;

///

class test_allocator : public allocator
{
public:
    void test(){ printf("allocator success %d\n", i); }
    
    int i = 0;
};

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path){
    
    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    
    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if(VertexShaderStream.is_open()){
        std::string Line = "";
        while(getline(VertexShaderStream, Line))
            VertexShaderCode += "\n" + Line;
        VertexShaderStream.close();
    }else{
        printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
        getchar();
        return 0;
    }
    
    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if(FragmentShaderStream.is_open()){
        std::string Line = "";
        while(getline(FragmentShaderStream, Line))
            FragmentShaderCode += "\n" + Line;
        FragmentShaderStream.close();
    }
    
    GLint Result = GL_FALSE;
    int InfoLogLength;
    
    
    // Compile Vertex Shader
    printf("Compiling shader : %s\n", vertex_file_path);
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
    glCompileShader(VertexShaderID);
    
    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }
    
    
    
    // Compile Fragment Shader
    printf("Compiling shader : %s\n", fragment_file_path);
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    glCompileShader(FragmentShaderID);
    
    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        printf("%s\n", &FragmentShaderErrorMessage[0]);
    }
    
    
    
    // Link the program
    printf("Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);
    
    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }
    
    
    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);
    
    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);
    
    return ProgramID;
}

//int testApp::run() {
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    test_singleton::initialize();
    texture_loader::initialize();
    
    test_singleton* foo = test_singleton::get();
    foo->test();
    
    test_singleton::destroy();
    
    // allocator
    mi_vector<test_allocator*> allocators;
    for ( int i = 0; i < 100; ++i ){
        allocators.emplace_back( mi_new test_allocator() );
    }
    the_memory_tracker->output_informations();
    
    // for opengl
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }
    
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL
    
    // Open a window and create its OpenGL context
    GLFWwindow* window; // (In the accompanying source code, this variable is global)
    window = glfwCreateWindow( 1024, 768, "Tutorial 01", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window); // Initialize GLEW
    glewExperimental=true; // Needed in core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }
    
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    
    
    /// Tutorial 3 texture
    texture_data tex_data;
    if ( !the_texture_loader->load_dds_from_file_no_safe( "resources/uvtemplate.dds", &tex_data ) ) {
        mi_log( "error when loading dds" );
        return false;
    }
    
    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);
    
    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    unsigned int blockSize = (tex_data.format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    unsigned int offset = 0;
    
    /* load the mipmaps */
    for (unsigned int level = 0; level < tex_data.mipmap_count && (tex_data.width || tex_data.height); ++level)
    {
        unsigned int size = ((tex_data.width+3)/4)*((tex_data.height+3)/4)*blockSize;
        glCompressedTexImage2D(GL_TEXTURE_2D, level, tex_data.format, tex_data.width, tex_data.height,
                               0, size, tex_data.buffer + offset);
        
        offset += size;
        tex_data.width  /= 2;
        tex_data.height /= 2;
    }
    
    // uv
    static const GLfloat g_uv_buffer_data[] = {
        0.000059f, 1.0f-0.000004f,
        0.000103f, 1.0f-0.336048f,
        0.335973f, 1.0f-0.335903f,
        1.000023f, 1.0f-0.000013f,
        0.667979f, 1.0f-0.335851f,
        0.999958f, 1.0f-0.336064f
    };
    
    GLuint uvbuffer;
    glGenBuffers( 1, &uvbuffer );
    glBindBuffer( GL_ARRAY_BUFFER, uvbuffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW );
    ////////////////////////////////////////////////////////////////////////
    
    /// Tutorial 2 stuff
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
//        0.0f,  1.0f, 0.0f,
        1.f,1.f,0.f,
        1.f,1.f,0.f,
        -1.f,-1.f,0.f,
        -1.f,1.f,0.f
    };
    
    static const GLfloat g_color_buffer_data[] = {
        0.583f,  0.771f,  0.014f,
        0.609f,  0.115f,  0.436f,
        0.327f,  0.483f,  0.844f,
        0.822f,  0.569f,  0.201f,
        0.435f,  0.602f,  0.223f,
        0.310f,  0.747f,  0.185f
    };
    
    // This will identify our vertex buffer
    GLuint vertexbuffer;
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    
    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer );
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer );
    glBufferData(GL_ARRAY_BUFFER, sizeof( g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW );
    
    GLuint programID = LoadShaders( "resources/simple.vs", "resources/simple.fs" );
    
    // tutorial 3
    glm::mat4 projection = glm::perspective( glm::radians( 45.f ), 1024/768.f, 0.1f, 100.f );
    glm::mat4 view = glm::lookAt( glm::vec3(0,0,3), glm::vec3(0,0,0), glm::vec3(0,1,0) );
    glm::mat4 model = glm::mat4(1);
    glm::mat4 mvp = projection * view * model;
    
    // get uniforms
    GLuint matrixId = glGetUniformLocation( programID, "mvp" );
    GLuint timeId = glGetUniformLocation( programID, "time" );
    GLuint sampler2D = glGetUniformLocation( programID, "textureSampler" );
    
    
    
    do{
        // Draw nothing, see you in tutorial 2 !
       glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        
        
        glUseProgram( programID );
        
        // change rotation
        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        float ftime =float(now.time_since_epoch().count())/ 1000000000.0;
//        glm::mat4 model = glm::rotate( glm::radians(ftime), glm::vec3(0,0,1) ) * glm::mat4(1);
//        glm::mat4 mvp = projection * view * model;
        
        glUniformMatrix4fv( matrixId, 1, GL_FALSE, &mvp[0][0] );
        glUniform1f( timeId, ftime );
        
        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
                              0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                              3,                  // size
                              GL_FLOAT,           // type
                              GL_FALSE,           // normalized?
                              0,                  // stride
                              (void*)0            // array buffer offset
                              );
        // 2nd color buffer
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer );
        glVertexAttribPointer(
                              1,
                              3,
                              GL_FLOAT,
                              GL_FALSE,
                              0,
                              (void*)0
                              );
        
        // 3rd uv buffer
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer );
        glVertexAttribPointer(2,
                              2,
                              GL_FLOAT,
                              GL_FALSE,
                              0,
                              (void*)0
                              );
        
        // bind sampler2D
        glActiveTexture( GL_TEXTURE0 );
        glBindTexture( GL_TEXTURE_2D, textureID );
        glUniform1i( sampler2D, 0 );
        
        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 3 * 2); // Starting from vertex 0; 3 vertices total -> 1 triangle
        glDisableVertexAttribArray(0);
        
        
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
          glfwWindowShouldClose(window) == 0 );
    
    glDeleteBuffers( 1, &vertexbuffer );
    glDeleteBuffers( 1, &uvbuffer );
    glDeleteBuffers( 1, &colorbuffer );
    glDeleteVertexArrays( 1, &VertexArrayID );
    glDeleteTextures( 1, &textureID );
    glDeleteProgram( programID );
    
    glfwTerminate();
    
    return 0;
}
