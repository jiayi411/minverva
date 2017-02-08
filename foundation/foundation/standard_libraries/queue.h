//
//  queue.h
//  foundation
//
//  Created by jiayi on 19/01/2017.
//  Copyright © 2017 jiayi. All rights reserved.
//

#ifndef queue_h
#define queue_h

#include <queue>
template< typename T >
class mi_queue : public std::queue<T>
{
public:
    void clear() {
        std::queue<T>().swap( *this );
    }
};

#endif /* queue_h */
