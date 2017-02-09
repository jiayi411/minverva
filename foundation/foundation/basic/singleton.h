/*!
 @file singleton.h
 @brief base class for singleton classes
 
 @author jiayi
 @date 17/01/2017
 */

#ifndef singleton_h
#define singleton_h

#include "basic/defines.h"
#include "memory/allocator.h"

namespace minerva
{
    namespace foundation
    {
        ///
        /// @brief This is a template class
        ///
        /// T represent the class that need to be singleton
        ///
        template< class T >
        class singleton : public allocator
        {
        public:
            ~singleton(){}
            
            /// Initialize the instance of T
            static bool initialize()
            {
                if( !_this ){
                    _this = mi_new T();
                }
                return _this != nullptr;
            }
            
            /// Destroy _this
            static void destroy()
            {
                safe_delete( _this );
            }
            
            /// Get the instance of T
            static T* get()
            {
                return _this;
            }
            
        protected:
            
            /// private constructor
            singleton(){}
            
        private:
            static T* _this; ///< The T object
        };
    }
}


#endif /* singleton_h */
