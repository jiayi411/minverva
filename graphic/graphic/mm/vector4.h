//
//  vector.h
//  graphic
//
//  Created by jiayi on 09/02/2017.
//  Copyright © 2017 jiayi. All rights reserved.
//

#ifndef vector4_h
#define vector4_h

namespace minerva { namespace graphic {
    
    ///
    /// @brief vector classes
    ///
    /// TODO: maybe I should make it derived from
    /// allocator to be trackable. Let's see if I
    /// have to do this later.
    ///
    template<typename T>
    class vector4
    {
    public:
        vector4() : x(0), y(0), z(0){}
        ~vector4(){}
        
    protected:
        union { T x, r; };
        union { T y, g; };
        union { T z, b; };
        union { T w, a; };
    };
} }

#endif /* vector4_h */
