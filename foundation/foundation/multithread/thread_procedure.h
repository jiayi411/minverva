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

#include "memory/allocator.h"
#include "object/update_object.h"
#include "multithread/thread_request.h"
#include "standard_libraries/queue.h"
#include <atomic>
#include <condition_variable>
#include <thread>

namespace minerva { namespace foundation {
    
    ///
    /// @brief Deal with multithread task both in main thread and other threads
    ///
    /// This class is designed to proceed specific process
    /// like background loading and rendering and providing a basic
    /// functionality to those features.
    ///
    class thread_procedure : public update_object
    {
    public:
        thread_procedure(){}
        virtual ~thread_procedure();
        
        virtual e_thread_type get_type() const = 0;
        
        /// start thread
        virtual void start();
        
        /// update in thread
        virtual void update_thread(){}
        
        /// update in main thread
        virtual void update( float ){}
        
        /// push a request
        virtual void push_request( const thread_request_ptr& request );
        
    protected:        
        /// definition of request container
        using request_vector = mi_queue<thread_request_ptr>;
        
        request_vector _container[e_mutex_type::count]; ///< containers including a free-lock container
        std::mutex _mutex[e_mutex_type::count];         ///< mutex for ready and done container
        std::thread _thread;                            ///< thread to run this procedure        
    };
    
    make_smart( thread_procedure );
} }

#endif /* thread_procedure_h */
