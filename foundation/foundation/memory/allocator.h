/*!
    @file allocator.h
    @brief allocator for all objects

    @author jiayi
    @date 14/01/2017
*/


#pragma once

#include "defines.h"
#include "consts.h"
#include "memory/memory_tracker.h"
#include <stdlib.h>

namespace minerva
{
    namespace foundation
    {
        /// @brief base class of all objects in minerva
        ///
        /// Base class for override new & delete function and added tracing method when in debug mode
        ///
        class allocator
        {
        public:
            
            /// ctor
            allocator(){}
            
            /// dtor
            ~allocator(){}
            
            ///
            /// @brief malloc a buffer
            ///
            /// just use built-in malloc function
            /// @param[in] size object's size
            /// @param[in] line where the new located in the file
            /// @param[in] function the function where the new called
            static char* std_malloc ( size_t size, int line, const char* function )
            {
                void* buf = malloc( size );
#ifdef MI_DEBUG
                if( consts::trace_memory ){
                    the_memory_tracker->add( buf, size, function, line );
                }
#endif // MI_DEBUG
                return (char*)buf;
            }
            
            ///
            /// @brief free a buffer
            ///
            /// free an object, just for tracker
            ///
            /// @param[in] ptr pointer of object
            static void std_free ( void* ptr )
            {
#ifdef MI_DEBUG
                if( consts::trace_memory ){
                    the_memory_tracker->remove( ptr );
                    
                }
#endif // MI_DEBUG
                free( ptr );
            }

            
            ///
            /// @brief operator new with debug information
            ///
            /// only activated on debug mode, with a switch for tracing purpose
            ///
            /// @param[in] size object's size
            /// @param[in] file which file the new operator occured
            /// @param[in] line where the new located in the file
            /// @param[in] function the function where the new called
            void* operator new ( size_t size, const char* file, int line, const char* function )
            {
                void* buf = malloc( size );
#ifdef MI_DEBUG
                if( consts::trace_memory ){
                    the_memory_tracker->add( buf, size, function, line );
                }
#endif // MI_DEBUG
                return buf;
            }
            
            ///
            /// @brief operator new[] with debug information
            ///
            /// only activated on debug mode, with a switch for tracing purpose
            ///
            /// @param[in] size object's size
            /// @param[in] file which file the new operator occured
            /// @param[in] line where the new located in the file
            /// @param[in] function the function where the new called
            void* operator new[] ( size_t size, const char* file, int line, const char* function )
            {
                void* buf = malloc( size );
#ifdef MI_DEBUG
                if( consts::trace_memory ){
                    the_memory_tracker->add( buf, size, function, line );
                }
#endif // MI_DEBUG
                return buf;
            }
            
            ///
            /// @brief operator delete
            ///
            /// free an object, with a switch for tracing purpose
            ///
            /// @param[in] size object's size
            void* operator new ( size_t size )
            {
                void* buf = malloc( size );
                return buf;
            }
            
            ///
            /// @brief operator delete
            ///
            /// free an object, with a switch for tracing purpose
            ///
            /// @param[in] ptr pointer of object
            void operator delete ( void* ptr )
            {
#ifdef MI_DEBUG
                if( consts::trace_memory ){
                    the_memory_tracker->remove( ptr );
                    
                }
#endif // MI_DEBUG
                free( ptr );
            }
            
        };
    }
}
