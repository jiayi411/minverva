//
//  main.cpp
//  test
//
//  Created by jiayi on 14/01/2017.
//  Copyright © 2017 jiayi. All rights reserved.
//

#include "foundation/memory/memory_tracker.h"
#include "foundation/singleton.h"
#include "foundation/standard_libraries/vector.h"
#include <iostream>

using namespace minerva::foundation;

class test_singleton : public singleton< test_singleton >
{
    
public:
    ~test_singleton(){}
    
    
    void test(){ printf("singleton success\n"); }
};

template<> test_singleton* singleton<test_singleton>::_this = nullptr;

///

class test_allocator : public allocator
{
public:
    void test(){ printf("allocator success %d\n", i); }
    
    int i = 0;
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    test_singleton::initialize();
    
    test_singleton* foo = test_singleton::get();
    foo->test();
    
    test_singleton::destroy();
    
    // allocator
    mi_vector<test_allocator*> allocators;
    for ( int i = 0; i < 100; ++i ){
        allocators.emplace_back( mi_new test_allocator() );
    }
    the_memory_tracker->output_informations();
    
    return 0;
}
