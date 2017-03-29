//
//  component.h
//  graphic
//
//  Created by jiayi on 15/03/2017.
//  Copyright © 2017 jiayi. All rights reserved.
//

#ifndef component_h
#define component_h

#include "foundation/object/update_object.h"

namespace minerva { namespace graphic {
    
    class model;
    
    ///
    /// @brief component interface for model
    ///
    class component : public foundation::reference_object
    {
    public:
        /// initialize component
        virtual bool initialize( model* m ) = 0;
        
        /// update component
        virtual void update_component( float delta ) = 0;
        
        /// pre render process
        virtual void on_render_component( float delta ) = 0;
        
        /// render process
        virtual void render_component( float delta ) = 0;
        
        /// get component name
        virtual const char* get_name() const = 0;
        
        /// light clone is gonna use same memory address
        virtual component* full_clone( model* ) = 0;
        
        /// deep clone is to make a complete new object with the same datas
        virtual component* copy_clone( model* ) = 0;
    };
    
    make_smart( component );

} }

#endif /* component_h */
