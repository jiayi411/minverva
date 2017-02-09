//
//  thread_common.h
//  foundation
//
//  Created by jiayi on 06/02/2017.
//  Copyright © 2017 jiayi. All rights reserved.
//

#ifndef thread_common_h
#define thread_common_h

#include "basic/defines.h"

namespace minerva { namespace foundation {
    
    /// enum class for thread request type
    enum class e_thread_type
    {
        background_loading,
        error
    };
    
    /// enum for mutexs and containers
    namespace e_mutex_type
    {
        enum
        {
            prepare,
            ready,
            done,
            count
        };
    };
    
    /// thread request data
    struct thread_request_data
    {
        typedef std::function<void*(void)> function_thread;
        typedef std::function<void(void*)> function_main;
        
        ///< request type
        e_thread_type type = e_thread_type::error;
        
        ///< output data
        void* out_data = nullptr;
        
        ///< intput data
//        void* in_data = nullptr;
        
        ///< function need to be execute in thread
        function_thread function_in_thread;
        
        ///< function need to be execute in main thread
        function_main function_in_main_thread;        
        
        /// default constructor
        thread_request_data(){}
        
        /// overload operator
        thread_request_data& operator= ( thread_request_data&& t )
        {
            out_data = t.out_data;
//            in_data = t.in_data;
            function_in_main_thread = t.function_in_main_thread;
            function_in_thread = t.function_in_thread;
            return *this;
        }
        
        thread_request_data( thread_request_data&& t )
        {
            out_data = t.out_data;
//            in_data = t.in_data;
            function_in_main_thread = t.function_in_main_thread;
            function_in_thread = t.function_in_thread;
        }
        
        thread_request_data& operator= ( const thread_request_data& ) = delete;
        thread_request_data( const thread_request_data& ) = delete;
        
    };
    
} }

#endif /* thread_common_h */
