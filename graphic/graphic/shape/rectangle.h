/*
 *  rectangle.h
 *  graphic
 *
 *  Created by jiayi on 29/03/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#ifndef rectangle_H
#define rectangle_H

#include "shape/shape.h"

namespace minerva { namespace graphic {
    
    class rectangle : public shape
    {
    public:
        rectangle(){}
        virtual ~rectangle(){}
        
        virtual void intialize_shape();
    };
    
    make_smart( rectangle );
}}

#endif /* rectangle_h */
