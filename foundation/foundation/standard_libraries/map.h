//
//  map.h
//  foundation
//
//  Created by jiayi on 19/01/2017.
//  Copyright © 2017 jiayi. All rights reserved.
//

#ifndef map_h
#define map_h

#include <map>
#include "basic/defines.h"
template< typename Key, typename T >
using mi_map = std::map<Key, T, HashType<T>>;

#endif /* map_h */
