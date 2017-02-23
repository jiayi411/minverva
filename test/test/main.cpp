//
//  main.cpp
//  test
//
//  Created by jiayi on 14/01/2017.
//  Copyright © 2017 jiayi. All rights reserved.
//

#include "foundation/memory/memory_tracker.h"
#include "foundation/basic/singleton.h"
#include "foundation/standard_libraries/vector.h"
#include "foundation/texture/texture_loader.h"
#include "foundation/object/smart_object.h"
//#include "testApp.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "foundation/foundation.h"
#include "multithread/thread_manager.h"
#include "texture/texture_manager.h"

#include "foundation/basic/timer.h"
#include "graphic/math/vector4.h"
#include "graphic/math/math_functions.h"
#include "graphic/math/matrix4x4.h"
using namespace glm;


using namespace minerva::foundation;
using namespace minerva::graphic;

class test_singleton : public singleton< test_singleton >
{
    
public:
    ~test_singleton(){}
    
    
    void test(){ printf("singleton success\n"); }
};

class test_smart : public reference_object
{
public:
    test_smart(int i ) : _i(i){}
    void test() { mi_log("%d", _i ); }
    
private:
    int _i;
};

make_smart( test_smart );

template<> test_singleton* singleton<test_singleton>::_this = nullptr;

///

class test_allocator : public allocator
{
public:
    virtual ~test_allocator() { mi_log("~\n"); }
    test_allocator() { mi_log("ctor\n"); }
//    test_allocator( test_allocator&& t ){
//        i = t.i;
//        t.i = 999;
//        mi_log("1\n");
//    }
//    test_allocator& operator= ( test_allocator&& t ){
//        i = t.i;
//        t.i = 99;
//        mi_log("2\n");
//        return *this;
//    }
//    test_allocator( test_allocator& ) = delete;
//    test_allocator& operator= ( const test_allocator&) = delete;
    
//    test_allocator( test_allocator& )
//    {
//        i = t.i;
//        t.i = 999;
//    }
//    test_allocator& operator= ( const test_allocator&)
//    {
//        i = t.i;
////        t.i = 99;
//        return *this;
//    }
    
    inline static void test_move(std::string& a1, std::string& a2) {
        
        a1.swap( a2 );
    }
    
    
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

void test_thread( void* data ) {
    static int count = 0;
    texture_data_ptr t_data = ( texture_data* )(data);
//    mi_log( "width: %d, texture load count: %dw\n", t_data->width, ++count );
}

//int testApp::run() {
int main(int argc, const char * argv[]) {
    
    glm::vec4 v1(1.2f, .4f, 2.f, 4.123f);
    glm::vec4 t1(1.2f, .4f, 2.f, 4.123f);
    //v1 = glm::cross( v1 * t1 );
    minerva::foundation::timer::duration<timer::milliseconds> v_duration(true);
    
    for (int i = 0; i < 1; ++i) {
        float f1 = glm::dot( v1, t1 );
    }
//    printf("%f\n", f1 );
//    mi_log_vector4(%f, v1);
    
    float duration = v_duration.stop();
    printf("time of vector:%f\n", duration);
    
    vector4<float> v2(1.2f, .4f, 2.f, 4.123f);
    vector4<float> t2(1.2f, .4f, 2.f, 4.123f);
    
    v_duration.start();
    for (int i = 0; i < 1; ++i) {
        float f2 = math::dot( v2, t2 );
    }
    duration = v_duration.stop();
    printf("time of vector:%f\n", duration);
    
//    printf("%f\n", f2 );
//    mi_log_vector4(%f, v2);
    
    matrix4x4<float> matrix(
                            1, 2, 3,  4,
                            5, 1, 6,  7,
                            8, 9, 1, 10,
                            11,12,13, 1
                            );
    
    glm::mat4x4 mat4(
                     1, 2, 3,  4,
                     5, 1, 6,  7,
                     8, 9, 1, 10,
                     11,12,13, 1
                     );
    
    mat4 = glm::transpose( mat4 );
//    mat4 /= 2;
//    mat4 = glm::inverse( mat4 );
//    float d1 = glm::determinant( mat4 );
//    printf("%.f\n", d1 );
//    mat4 = glm::perspective( glm::radians( 45.f ), 1024/768.f, 0.1f, 100.f );
    mi_log_matrix4x4( %f, mat4 );
    
    
    matrix.inverse();
//    matrix /= 2;
//    float d2 = math::determinant( matrix );
//    printf("%.f\n", d2 );
//    matrix = math::perspective<float>(45.f, 1024.f, 768, 0.1, 100);
    mi_log_matrix4x4( %f, matrix );
    
    core::initialize_singletons();
    
    
    // insert code here...
    std::cout << "Hello, World!\n";
    
    /// test smart_ptr's reference in std::bind
    test_smart_ptr smart_ = mi_new test_smart(98);
    auto func = std::bind(&test_smart::test, smart_ );
    
    test_singleton::initialize();
    
    /// test thread manager
    the_thread_manager->add_procedure( e_thread_type::background_loading );
    
    std::string thread_test_string = "resources/uvtemplate.dds";
    for ( int i = 0; i < 1; ++i ) {
        the_texture_manager->load_texture_by_file_name( "resources/uvtemplate.dds",
                                                       std::bind( test_thread, std::placeholders::_1 ) );
    }
    
//    v_smart.clear();
    
    test_singleton* foo = test_singleton::get();
    foo->test();
    
    test_singleton::destroy();
    
    // allocator
    mi_vector<test_allocator*> allocators;
    for ( int i = 0; i < 100; ++i ){
//        allocators.emplace_back( mi_new test_allocator() );
    }
    
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
    texture_data_ptr tex_data = mi_new texture_data;
    if ( !the_texture_loader->load_dds_from_file( "resources/uvtemplate.dds", tex_data ) ) {
        mi_log( "error when loading dds" );
        return false;
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
//    glm::mat4 projection2 = glm::perspective( glm::radians( 45.f ), 1024/768.f, 0.1f, 100.f );
//    glm::mat4 view2 = glm::lookAt( glm::vec3(0,0,3), glm::vec3(0,0,0), glm::vec3(0,1,0) );
//    glm::mat4 model2 = glm::mat4(1);
    
    matrix4x4<float> projection = math::perspective<float>(45.f, 1024, 768, 0.1f, 100.f);
    
    matrix4x4<float> model  = matrix4x4<float>(1);
    
    vector3<float> eye = vector3<float>(0,0,3);
    vector3<float> target = vector3<float>(0,0,0);
    matrix4x4<float> view = math::view( eye, target, vector3<float>(0,1,0) );
    matrix4x4<float> mvp = projection * view;// * model;
    
    
    // get uniforms
    GLuint matrixId = glGetUniformLocation( programID, "mvp" );
    GLuint timeId = glGetUniformLocation( programID, "time" );
    GLuint sampler2D = glGetUniformLocation( programID, "textureSampler" );
    
    
    // output memory
    the_memory_tracker->output_informations();
    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);
    
    // start thread
    the_thread_manager->start_all();
    do{
        
        long time = the_core->get_frame_time();
//        mi_log("fps:%d\n", the_core->get_fps(time) );
        if( glfwGetKey( window, GLFW_KEY_T) == GLFW_PRESS ) {
            
            // bind sampler2D
            glActiveTexture( GL_TEXTURE0 );
            glBindTexture( GL_TEXTURE_2D, textureID );
            glUniform1i( sampler2D, 0 );
            
            unsigned int blockSize = (tex_data->format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
            unsigned int offset = 0;
            
            
            /* load the mipmaps */
            for (unsigned int level = 0; level < tex_data->mipmap_count && (tex_data->width || tex_data->height); ++level)
            {
                unsigned int size = ((tex_data->width+3)/4)*((tex_data->height+3)/4)*blockSize;
                glCompressedTexImage2D(GL_TEXTURE_2D, level, tex_data->format, tex_data->width, tex_data->height,
                                       0, size, tex_data->buffer + offset);
                
                offset += size;
                tex_data->width  /= 2;
                tex_data->height /= 2;
            }
        }
        
        if( glfwGetKey( window, GLFW_KEY_W) == GLFW_PRESS) {
            
            view = math::view( eye, target, vector3<float>(0,1,0) );
            mvp = projection * view;// * model;
        } else if( glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS ) {
            
            view = math::view( eye, target, vector3<float>(0,1,0) );
            mvp = projection * view;// * model;
        } else if( glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS ) {
            target.x -= 0.1;
            eye.x -= 0.1;
            view = math::view( eye, target, vector3<float>(0,1,0) );
            mvp = projection * view;// * model;
        } else if( glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS ) {
            target.x += 0.1;
            eye.x += 0.1;
            view = math::view( eye, target, vector3<float>(0,1,0) );
            mvp = projection * view;// * model;
        }
        
        if( glfwGetKey( window, GLFW_KEY_Q) == GLFW_PRESS ) {
            the_texture_manager->load_texture_by_file_name( "resources/uvtemplate.dds", std::bind( test_thread, std::placeholders::_1 ) );
        }
        
        // Draw nothing, see you in tutorial 2 !
       glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        
        
        glUseProgram( programID );
        
        // change rotation
        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        float ftime =float(now.time_since_epoch().count())/ 1000000000.0;
//        glm::mat4 model = glm::rotate( glm::radians(ftime), glm::vec3(0,0,1) ) * glm::mat4(1);
//        glm::mat4 mvp = projection * view * model;
        
        glUniformMatrix4fv( matrixId, 1, GL_TRUE, &mvp[0][0] );
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
        
        
        
        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 3 * 2); // Starting from vertex 0; 3 vertices total -> 1 triangle
        glDisableVertexAttribArray(0);
        
        
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
        
        // update manager
        the_thread_manager->update( 0.f );
        
        
        
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
