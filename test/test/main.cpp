//
//  main.cpp
//  test
//
//  Created by jiayi on 14/01/2017.
//  Copyright © 2017 jiayi. All rights reserved.
//

#include <iostream>
#include "fundation/allocator.h"
#include "fundation/defines.h"

class fooclass : public minerva::foundation::allocator
{
public:
    fooclass(){}
    ~fooclass(){}
    
    void test(){ printf("xxxx"); }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    fooclass* foo = mi_new fooclass();
    foo->test();
    safe_delete( foo );
    
    return 0;
}
