/*
 *  reference_object.h
 *  foundation
 *
 *  Created by jiayi on 05/02/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#ifndef reference_object_H
#define reference_object_H

#include "memory/allocator.h"

namespace minerva { namespace foundation {
    
    ///
    /// @brief The basic class who need to count the reference
    ///
    /// This class is often used by smart_pointer to caculate
    /// the reference count
    ///
    class reference_object : public allocator
    {
    public:
        /// dctor
        virtual ~reference_object() { _reference = 0; }
        
    public:
        /// increase the reference count
        inline uint increase_reference() { return ++_reference; }
        
        /// decrease the reference count
        inline void decrease_reference()
        {
            mi_assert( _reference );
            --_reference;
            if (_reference == 0)
            { mi_delete this; }
        }
        
        /// return the reference count
        ///
        /// @return the value of _reference
        inline uint reference_count() const { return _reference; }
        
    protected:
        uint _reference = 0;    ///< reference count
    };
} }

#endif /* reference_object_h */
