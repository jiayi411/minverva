/*
 *  graphic.cpp
 *  graphic
 *
 *  Created by jiayi on 09/02/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#include <iostream>
#include "graphic.hpp"
#include "graphicPriv.hpp"
#include "foundation/memory/memory_tracker.h"
#include "foundation/basic/singleton.h"
#include "foundation/standard_libraries/vector.h"
#include "foundation/texture/texture_loader.h"
#include "foundation/object/smart_object.h"
#include "foundation/foundation.h"


void graphic::HelloWorld(const char * s)
{
    graphicPriv *theObj = new graphicPriv;
    theObj->HelloWorldPriv(s);
    delete theObj;
};

void graphicPriv::HelloWorldPriv(const char * s) 
{
    std::cout << s << std::endl;
};

