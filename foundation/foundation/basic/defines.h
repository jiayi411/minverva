//
//  defines.h
//  foundation
//
//  Created by jiayi on 14/01/2017.
//  Copyright © 2017 jiayi. All rights reserved.
//

#pragma once
#include <assert.h>
#include <string>

#ifdef DEBUG
#define MI_DEBUG
#endif // DEBUG



#ifdef MI_DEBUG
#define mi_new new( __FILE__, __LINE__, __FUNCTION__ )
#define mi_delete delete
#define mi_malloc(size) minerva::foundation::allocator::std_malloc( size, __LINE__, __FUNCTION__ )
#define mi_free(o) minerva::foundation::allocator::std_free(o)
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

#define mi_assert assert

// log
#define mi_log printf

// thread
#define thread_safe

// datas
using llong = long long;
using ulong = unsigned long;
using ullong = unsigned long long;
using uint = unsigned int;
using ushort = unsigned short;
using uchar = unsigned char;

// structs
struct EnumClassHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

template <typename Key>
using HashType = typename std::conditional<std::is_enum<Key>::value, EnumClassHash, std::hash<Key>>::type;

