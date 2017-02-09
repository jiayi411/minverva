/*!
 @file foundation.cpp
 @brief initiliaze foundation related classes
 
 @author jiayi
 @date 17/01/2017
 */

#include "foundation.h"
#include "texture/texture_loader.h"
#include "multithread/thread_manager.h"
#include "texture/texture_manager.h"

using namespace minerva::foundation;

template<> texture_loader* singleton<texture_loader>::_this = nullptr;
template<> thread_manager* singleton<thread_manager>::_this = nullptr;
template<> texture_manager* singleton<texture_manager>::_this = nullptr;
template<> core* singleton<core>::_this = nullptr;

#define singleton_initiliaze(T) \
    if (!T::initialize()) { \
        mi_log( #T"::initialize failed" ); \
    }\

void core::initialize_singletons()
{
    singleton_initiliaze( core );
    singleton_initiliaze( texture_loader );
    singleton_initiliaze( thread_manager );
    singleton_initiliaze( texture_manager );
}

void core::destroy_singletons()
{
    texture_manager::destroy();
    thread_manager::destroy();
    texture_loader::destroy();
    core::destroy();
}
