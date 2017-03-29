/*
 *  com_camera_controller.h
 *  graphic
 *
 *  Created by jiayi on 28/03/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#ifndef com_camera_controller_H
#define com_camera_controller_H
#include "component/com_controller.h"

namespace minerva { namespace graphic {
    
    class com_camera_controller : public com_controller
    {
    public:
        com_camera_controller() : _pace(0.1f){}
        virtual ~com_camera_controller();
        
    public:
        com_camera_controller( const com_camera_controller& c );
        com_camera_controller( com_camera_controller&& c );
        com_camera_controller& operator= ( const com_camera_controller& c );
        com_camera_controller& operator= ( com_camera_controller&& c );
        
        /// light clone is gonna use same memory address
        virtual component* full_clone( model* ) ;
        
        /// deep clone is to make a complete new object with the same datas
        virtual component* copy_clone( model* ) ;
        
    public:
        
        /// initialize component
        virtual bool initialize( model* m );
        
        /// update component
        virtual void update_component( float delta );
        
        /// pre render process
        virtual void on_render_component( float delta ){}
        
        /// render component
        virtual void render_component( float delta ){}
        
        /// get name
        virtual const char* get_name() const  { return "com_camera_controller"; }
        
    protected:
        /// move left
        void _move_left( bool pressed,model* m, double, double );
        
        /// move right
        void _move_right( bool pressed,model* m, double, double );
        
        /// move forward
        void _move_forward( bool pressed,model* m, double, double );
        
        /// move backward
        void _move_backward( bool pressed,model* m, double, double );
        
        /// rotate
        void _rotate( bool pressed, model* m, double x, double y );
        
    protected:
        set_get(float, pace);
        
    };
}}

#endif /* com_camera_controller_h */
