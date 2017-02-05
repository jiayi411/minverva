/*
 *  thread_procedure.h
 *  foundation
 *
 *  Created by jiayi on 05/02/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#ifndef thread_procedure_H
#define thread_procedure_H

#include <atomic>
#include <condition_variable>
#include "memory/allocator.h"

namespace minerva { namespace foundation {
    
    ///
    /// @brief Deal with multithread task both in main thread and other threads
    ///
    /// This class is designed to proceed specific process
    /// like background loading and rendering and providing a basic
    /// functionality to those features.
    ///
    class thread_procedure : public allocator
    {
        
    };
} }

#endif /* thread_procedure_h */
