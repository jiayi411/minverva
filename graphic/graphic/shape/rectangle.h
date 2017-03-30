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
        
        virtual void initialize_shape();
    };
    
    make_smart( rectangle );
    
    class sphere : public shape
    {
    public:
        sphere() : _level(0){}
        virtual ~sphere(){}
        
        virtual void initialize_shape();
        
        void set_level( int n );
        
    protected:
        // key, index
        typedef mi_unordered_map<uint, uint> cache_container;
        
    protected:
        uint _get_mid_point( uint index1, uint index2 );
        int _level; // refining
        cache_container _cache;
    };
}}

#endif /* rectangle_h */
