/*
 *  thread_background_loading.h
 *  foundation
 *
 *  Created by jiayi on 07/02/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#ifndef thread_background_loading_H
#define thread_background_loading_H

#include "multithread/thread_procedure.h"

namespace minerva { namespace foundation {
    
    ///
    /// @brief Deal with multithread task both in main thread and other threads
    ///
    /// This class is designed to proceed specific process
    /// like background loading and rendering and providing a basic
    /// functionality to those features.
    ///
    class thread_background_loading : public thread_procedure
    {
    public:
        thread_background_loading(){}
        virtual ~thread_background_loading(){}
        
        virtual e_thread_type get_type() const { return e_thread_type::background_loading; }
        
        /// process in thread
        virtual void update_thread();
        
        /// update in main thread
        virtual void update( float );
        
    protected:
        /// prepare the queue. in main thread.
        virtual void _prepare_container();
        
        /// process in main thread
        virtual void _process_result();
        
    protected:
        std::condition_variable _condition;                 ///< condition for ready container
    };

} }

#endif /* thread_background_loading_h */
