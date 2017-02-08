/*
 *  thread_request.cpp
 *  foundation
 *
 *  Created by jiayi on 05/02/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#include "thread_request.h"

using namespace minerva::foundation;

thread_request::thread_request( thread_request&& t )
{
    _data = std::move( t._data );
}

thread_request& thread_request::operator= ( thread_request&& t )
{
    _data = std::move( t._data );
    return *this;
}
