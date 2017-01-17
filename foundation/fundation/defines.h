//
//  defines.h
//  foundation
//
//  Created by jiayi on 14/01/2017.
//  Copyright © 2017 jiayi. All rights reserved.
//

#pragma once

#ifdef DEBUG
#define MI_DEBUG 1
#else
#define MI_DEBUG 0
#endif // DEBUG

#if MI_DEBUG
#define mi_new new( __FILE__, __LINE__, __FUNCTION__ )
#define mi_delete delete
#else
#define mi_new new
#define mi_delete delete
#endif // MI_DEBUG

// delete related
#define safe_delete( obj ) \
    if( obj ){ \
        mi_delete obj; } \

#define safe_delete_array( arr )\
    if( arr ){ \
        mi_delete[] arr; } \

