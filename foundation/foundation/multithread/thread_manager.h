/*
 *  thread_manager.h
 *  foundation
 *
 *  Created by jiayi on 06/02/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#ifndef thread_manager_H
#define thread_manager_H

#include "basic/singleton.h"
#include "standard_libraries/unordered_map.h"
#include "multithread/thread_request.h"
#include "multithread/thread_procedure.h"

namespace minerva { namespace foundation {
    
    ///
    /// @brief the multithread manager for all thread procedures
    ///
    /// This manager will be constantly updated on the main thread.
    /// It will contains all multithread procedures like background loading,
    /// rendering, etc.
    ///
    class thread_manager : public singleton<thread_manager>
    {
    public:
        ~thread_manager() { _procedures.clear(); }
        
        /// add thread procedures
        void add_procedure( e_thread_type type );
        
        /// start all thread procedures
        void start_all();
        
        /// update
        void update( float );
        
        /// push a request
        void push_request( const thread_request_ptr& request );
        
    protected:
        friend class singleton< thread_manager >;
        
        typedef mi_unordered_map<e_thread_type, thread_procedure_ptr> procedure_container;
        
        /// procedures
        procedure_container _procedures;
        
    protected:
        thread_manager(){}
    };
    
    #define the_thread_manager thread_manager::get()
} }

#endif /* thread_manager_h */
