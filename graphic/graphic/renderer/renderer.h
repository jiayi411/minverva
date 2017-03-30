/*
 *  renderer.h
 *  graphic
 *
 *  Created by jiayi on 26/03/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#ifndef renderer_H
#define renderer_H

#include "graphic.h"
#include "basic/singleton.h"
#include "model/camera.h"

class GLFWwindow;
namespace minerva { namespace graphic {
    
    class renderer : public foundation::singleton<renderer>
    {
    public:
        ~renderer();
        
        void mi_check_glerror();
        
        /// generate and bind to opengl buffer
        mg_uint gen_bind_buffer( mg_uint type, mg_sizeiptr size, mg_void* buffer, mg_uint draw_type );
        
        /// generate vao
        mg_uint generate_single_vao();
        
        /// bind buffer
        void bind_buffer( mg_uint type, mg_uint buffer_id );
        
        /// enable, bind, and set attrib pointer
        void enable_bind_attrib_pointer( mg_uint index, mg_uint buff_type, mg_uint data_type, mg_uint buffer_id, mg_int size, mg_void* offset_pointer);
        
    protected:
        set_get( camera_ptr, camera );
        set_get( GLFWwindow*, window );
    };
}}

#define the_renderer renderer::get()

#endif /* renderer_h */
