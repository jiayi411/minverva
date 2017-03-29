/*
 *  timer.h
 *  foundation
 *
 *  Created by jiayi on 08/02/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#ifndef timer_H
#define timer_H

#include "basic/singleton.h"

using std::chrono::high_resolution_clock;

namespace minerva { namespace foundation {
    
    ///
    /// @brief providing time related methods
    ///
    class timer : public singleton<timer>
    {
    public:
        typedef std::chrono::duration<double, std::micro> milliseconds;
        typedef std::chrono::duration<double>  seconds;
        typedef std::chrono::minutes minutes;
        typedef std::chrono::hours hours;
        
        template<typename T>
        typename T::rep get_current_time() const {
            return ( std::chrono::high_resolution_clock::now().time_since_epoch() ).count();
        }
        
        ///
        /// @brief to caculate the duration time
        ///
        template <typename T>
        class duration : public allocator
        {
        public:
            typedef typename T::rep return_type;
            
        public:
            duration(){}
            
            /// overload ctor
            explicit duration( bool begin ) { if (begin) {start();} }
            
            /// started
            bool is_started() {
                return _started;
            }
            
            /// start timer
            void start() {
                _started = true;
                _start = std::chrono::high_resolution_clock::now();
                _last_end = _start;
            }
            
            ///
            /// @brief stop timer
            ///
            /// @return the duration of _end - _start
            ///
            return_type stop() {
                _end = _last_end = std::chrono::high_resolution_clock::now();
                return ( std::chrono::duration_cast<T>( _end - _start ) ).count();
            }
            
            ///
            /// @brief get duration from _end - _last_end
            ///
            /// @return the duration of _end - _start
            return_type get_last_duration() {
                _end = std::chrono::high_resolution_clock::now();
                return_type ret = ( std::chrono::duration_cast<T> ( _end - _last_end ) ).count();
                _last_end = _end;
                return ret;
            }
            
            /// get duration from the beginning
            return_type get_duration() {
                return ( std::chrono::duration_cast<T> ( std::chrono::high_resolution_clock::now() - _start ) ).count();
            }
            
        protected:
            bool _started = false;                          ///< turned to true once start() executed
            high_resolution_clock::time_point _start;
            high_resolution_clock::time_point _last_end;
            high_resolution_clock::time_point _end;
        };
        
    public:
        ~timer(){}
        
    protected:
        timer(){}
        friend class singleton<timer>;

    };
    
    #define the_timer timer::get()
} }

#endif /* timer_h */
