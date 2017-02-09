//
//  foundation.h
//  foundation
//
//  Created by jiayi on 19/01/2017.
//  Copyright © 2017 jiayi. All rights reserved.
//

#ifndef foundation_h
#define foundation_h
#include "singleton.h"
#include "basic/timer.h"

namespace minerva { namespace foundation {
  
    ///
    /// @brief foundation related functions
    ///
    class core : public singleton<core>
    {
    public:
        /// initialize all singleton objects
        static void initialize_singletons();
        
        /// destroy all singleton objects
        static void destroy_singletons();
        
    public:
        ///
        /// @brief get frame time
        ///
        /// This function should be execute every frame
        ///
        /// @return the duration time from the last frame
        ///
        inline long get_frame_time() {
            if (_timer.is_started()) {
                return _timer.get_last_duration();
            }            
            _timer.start();
            return 0;
        }
        
        ///
        /// @brief get fps based on the duration of a single frame
        ///
        /// @return the FPS
        ///
        inline uint get_fps( long time_single_frame_millisecond ) {
            if (time_single_frame_millisecond == 0) {
                return 9999;
            }
            uint fps = 60000 / time_single_frame_millisecond;
            return fps;
        }
        
        
    protected:
        timer::duration<timer::milliseconds> _timer;
        
    };
    
#define the_core core::get()
    
} }

#endif /* foundation_h */
