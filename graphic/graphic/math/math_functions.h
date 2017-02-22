//
//  math_functions.h
//  graphic
//
//  Created by jiayi on 18/02/2017.
//  Copyright © 2017 jiayi. All rights reserved.
//

#ifndef math_functions_h
#define math_functions_h

#include "graphic/math/matrix4x4.h"

namespace minerva { namespace graphic {
    
    ///
    /// @brief static class that provide math functions
    ///
    /// math!!
    ///
    class math
    {
    public:
        /*-- Matrix Related Functions --*/
        template<typename T>
        static matrix4x4<T> inverse( const matrix4x4<T>& m );
        
        template<typename T>
        static matrix4x4<T> transpose( const matrix4x4<T>& m );
        
        template<typename T>
        static T determinant( const matrix4x4<T>& m );
    };
    
} }

#include "graphic/math/math_functions.inl"

#endif /* math_functions_h */
