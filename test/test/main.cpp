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
#include "graphic/math/matrix3x3.h"
#include "graphic/math/quaternion.h"
#include "graphic/graphic.h"
#include "graphic/math/transform.h"
#include "graphic/model/camera.h"
#include "graphic/renderer/technique.h"

#include "graphic/component/com_default_material.h"
#include "graphic/component/com_triangle.h"
#include "graphic/component/com_camera_controller.h"
#include "graphic/model/model.h"
#include "renderer/renderer.h"
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



void test_thread( void* data ) {
    static int count = 0;
    texture_data_ptr t_data = ( texture_data* )(data);
    //    mi_log( "width: %d, texture load count: %dw\n", t_data->width, ++count );
}

using namespace minerva;
using namespace std;
//int testApp::run() {
int main(int argc, const char * argv[]) {
    
    minerva::foundation::timer::duration<timer::milliseconds> v_duration(true);
    
    float duration = v_duration.stop();
    printf("time of vector:%f\n", duration);
    
    vector4 v2(1.2f, .4f, 2.f, 4.123f);
    vector4 t2(1.2f, .4f, 2.f, 4.123f);
    
    v_duration.start();
    for (int i = 0; i < 1; ++i) {
        float f2 = graphic::dot( v2, t2 );
    }
    duration = v_duration.stop();
    printf("time of vector:%f\n", duration);
    
    
    
//    glm::quat q_1(0.2f, 2,3,4 );
//    q_1 = glm::angleAxis(1.f, vec3(1,1,0));
//    quaternion q_2(2,3,4,0.2f);
//    q_2.from_axis_angle(1, vector3(1,1,0));
//        mi_log_quaternion("%f", q_1);
//        mi_log_quaternion("%f", q_2);
//    
//    mat4 = mat4x4(q_1);
//    matrix4 = graphic::transpose( graphic::matrix4_cast(q_2) );
//    
//    mi_log_matrix4x4("%f", mat4);
//    mi_log_matrix4x4("%f", matrix4);
    
    
    core::initialize_singletons();
    graphic::initialize_singletons();
    
    
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
    
    the_renderer->set_window( window );
    
    /// Tutorial 3 texture
    texture_data_ptr tex_data = mi_new texture_data;
    if ( !the_texture_loader->load_dds_from_file( "resources/uvtemplate.dds", tex_data ) ) {
        mi_log( "error when loading dds" );
        return false;
    }
    
    node_object_ptr root = mi_new node_object();
    
    model_ptr triangle_model_p_1 = mi_new model();
    model_ptr triangle_model_p_2 = mi_new model();
    
    model& triangle_model = *triangle_model_p_1;
    com_default_material_ptr default_material_ = nullptr;
    com_triangle_ptr triangle_ = nullptr;
    default_material_ = mi_new com_default_material();
    triangle_model.add_component<com_default_material>( default_material_ );
    triangle_ = mi_new com_triangle();
    triangle_model.add_component<com_triangle>( triangle_ );
    
    default_material_->add_shader( technique::vertex_shader, "resources/simple.vs" );
    default_material_->add_shader( technique::fragment_shader, "resources/simple.fs" );
    default_material_->finalize();
    
    com_texture_ptr texture_ = default_material_->get_base_texture();
    texture_->set_texture_file( "resources/uvtemplate.dds" );
    
    camera_ptr cam_p = mi_new camera();
    the_renderer->set_camera( cam_p );
    camera& cam = *cam_p;
    cam.initialize( camera::perspective_data( 1024, 768, 45.f, 0.1f, 100.f ) );
    cam.add_component<com_camera_controller>( mi_new com_camera_controller );
    
    graphic::transform& cam_trans = cam.get_transform();
    cam_trans.set_position( vector3( 0, 0, 10 ) );
    
    *triangle_model_p_2 = *triangle_model_p_1;
    
    root->add_child( cam_p );
    root->add_child( triangle_model_p_2 );
    root->add_child( triangle_model_p_1 );
    
    // start thread
    the_thread_manager->start_all();
    
    // timer
    
    do{
        long time = the_core->get_frame_time();
        
        // Draw nothing, see you in tutorial 2 !
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        float ftime = the_core->get_life_time();
        
        
        // rotation
        quaternion model_rotate;
        quaternion target_rotate;
        model_rotate.from_axis_angle(0, vector3(0,1,0));
        target_rotate.from_axis_angle(1, vector3(0,1,0));
        quaternion rotate = model_rotate.slerp( target_rotate, (std::sin(ftime)) );
        
        triangle_model.get_transform().set_rotation( rotate );
//        triangle_model.get_transform().set_scale( 1.5f );
        triangle_model.get_transform().set_position( vector3(-5.f, 0, 0) );
        
        target_rotate.from_axis_angle(1, vector3(1,1,0));
        rotate = model_rotate.slerp( target_rotate, (std::sin(ftime)) );
        triangle_model_p_2->get_transform().set_rotation( rotate );
        triangle_model_p_2->get_transform().set_position( vector3(5.f, 0, 0) );
        
        
        root->update(0);
        root->render(0);
        
        
        ////        glDisableVertexAttribArray(0);
        //        glBindVertexArray( NULL );
        
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
        
        // update manager
        the_thread_manager->update( 0.f );
        
        
        
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
          glfwWindowShouldClose(window) == 0 );
    
    triangle_model_p_1 = nullptr;
    triangle_model_p_2 = nullptr;
    cam_p = nullptr;
    glfwTerminate();
    
    the_core->destroy_singletons();
    graphic::destroy_singletons();
    
    // output memory
    the_memory_tracker->output_informations();
    
    return 0;
}



//        if( glfwGetKey( window, GLFW_KEY_Q) == GLFW_PRESS ) {
//            the_texture_manager->load_texture_by_file_name( "resources/uvtemplate.dds", std::bind( test_thread, std::placeholders::_1 ) );
//        }
//
//        if( glfwGetKey( window, GLFW_KEY_F) == GLFW_PRESS ) {
//            cam.look_at( vector3(0,0,0) );
//        }
