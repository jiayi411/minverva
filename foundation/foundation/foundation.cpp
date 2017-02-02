/*!
 @file foundation.cpp
 @brief initiliaze foundation related classes
 
 @author jiayi
 @date 17/01/2017
 */

#include "foundation.h"
#include "texture/texture_loader.h"

using namespace minerva::foundation;

template<> texture_loader* singleton<texture_loader>::_this = nullptr;
