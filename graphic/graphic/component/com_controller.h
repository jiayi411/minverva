/*
 *  com_controller.h
 *  graphic
 *
 *  Created by jiayi on 28/03/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#ifndef com_controller_H
#define com_controller_H

#include "component/component.h"
#include "model/model.h"

namespace minerva { namespace graphic {
    
    ///
    /// @brief DESCRIPTION
    ///
    /// DETAILS
    class com_controller : public component
    {
    public:
        enum {
            ctrl_keyboard,
            ctrl_screen,
//            ctrl_joystick,
            ctrl_count
        };
        /// keyboard, mouse & touch event
        typedef std::function<void(bool,model*,double,double)> function_event;
        
    public:
        com_controller() : _model(nullptr){}
        virtual ~com_controller();
        
    public:
        /* -- Copy Constructors -- **/
        com_controller( const com_controller& c );
        com_controller( com_controller&& c );
        com_controller& operator= ( const com_controller& c );
        com_controller& operator= ( com_controller&& c );
        
        ///
        /// @brief fully clone this object to a new one
        ///
        /// instead of just assign pointers to the new component,
        /// this method will create new space for all variables,
        /// so it is called 'full' clone.
        ///
        /// @param m target model need to be attached
        /// @return the new component
        virtual component* full_clone( model* m ) ;
        
        ///
        /// @brief copy variables to a new component
        ///
        /// This method will create a new component with the
        /// same address of its variables, so it is called 'copy'
        /// , it's not create any new spaces for variables.
        ///
        /// @param m target model need to be attached
        /// @return the new component
        virtual component* copy_clone( model* m ) ;
        
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
        virtual const char* get_name() const  { return "com_controller"; }
        
    public:
        ///
        /// @brief bind key to event function
        ///
        /// @param type input device type
        /// @param key specified key
        /// @param func callback function
        void bind_key( uint type, uint key, const function_event& func );
        
    protected:
        typedef mi_unordered_multimap<uint, function_event> events_container;
        typedef mi_unordered_map<uint, bool> mark_container;
        
        events_container _events[ctrl_count];
        mark_container _marks[ctrl_count];
        
    protected:
        set_get( model_ptr, model );
    };
}}


#endif /* com_controller_h */
