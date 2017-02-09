//
//  unordered_map.h
//  foundation
//
//  Created by jiayi on 19/01/2017.
//  Copyright © 2017 jiayi. All rights reserved.
//

#ifndef unordered_map_h
#define unordered_map_h

#include <unordered_map>
#include "basic/defines.h"

template< typename Key, typename T >
using mi_unordered_map = std::unordered_map<Key, T, HashType<Key>>;

#endif /* unordered_map_h */
