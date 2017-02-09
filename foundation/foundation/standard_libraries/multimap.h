//
//  multimap.h
//  foundation
//
//  Created by jiayi on 19/01/2017.
//  Copyright © 2017 jiayi. All rights reserved.
//

#ifndef multimap_h
#define multimap_h

#include <multimap>
#include "basic/defines.h"
template< typename Key, typename T >
using mi_multimap = std::multimap<Key, T, HashType<T>>;

#endif /* multimap_h */
