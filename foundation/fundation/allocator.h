/*!
    @file allocator.h
    @brief allocator for all objects

    @author jiayi
    @date 14/01/2017
*/


#pragma once
#include <stdlib.h>
#include <typeinfo>
#include <stdio.h>
#include "consts.h"

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
            
            ///
            /// @brief ctor
            ///
            allocator(){}
            
            ///
            /// @brief dtor
            ///
            ~allocator(){}
            
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
                free( ptr );
            }
            
        };
    }
}
