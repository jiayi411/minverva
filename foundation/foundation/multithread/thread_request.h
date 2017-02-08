/*
 *  thread_request.h
 *  foundation
 *
 *  Created by jiayi on 05/02/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#ifndef thread_request_H
#define thread_request_H

#include "object/smart_object.h"
#include "multithread/thread_common.h"

namespace minerva { namespace foundation {
    
    ///
    /// @brief Request when requesting a new task
    ///
    /// When requesting a new task in multithread, create
    /// this class and fill in the data
    ///
    class thread_request : public reference_object
    {
        typedef std::function<void*(void*)> function_thread;
        typedef std::function<void(void*)> function_main;
    public:
        /// ctor
        thread_request( e_thread_type type, void* in_data,
                    function_thread& f_thread,
                    function_main& f_main_thread )
        {
            _data.type = type;
            _data.in_data = in_data;
            _data.function_in_thread = f_thread;
            _data.function_in_main_thread = f_main_thread;
        }
        
        /// dtor
        virtual ~thread_request(){}
        
        /// copy constructor
        thread_request( thread_request&& );
        
        /// override operator= for rhs
        thread_request& operator= ( thread_request&& );
        
        /// get the request data
        const thread_request_data& get_data() const { return _data; }
        thread_request_data& get_data() { return _data; }
        
    protected:
        thread_request( const thread_request& ) = delete;
        thread_request& operator= ( const thread_request& ) = delete;
        
    protected:
        ///< thread request data
        thread_request_data _data;
    };
    
    make_smart( thread_request );
} }

#endif /* thread_request_h */
