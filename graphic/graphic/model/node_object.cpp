//
//  node_object.h
//  foundation
//
//  Created by jiayi on 07/02/2017.
//  Copyright © 2017 jiayi. All rights reserved.
//

#include "model/node_object.h"

using namespace minerva::graphic;

node_object::~node_object()
{
    for (auto& c : _children) {
        c.second = nullptr;
    }
    
    _children.clear();
}

node_object::node_object( const node_object& node )
{
    this->operator=( node );
}

node_object::node_object( node_object&& node )
{
    this->operator=( node );
}

node_object& node_object::operator= ( const node_object& node )
{
    const auto& children = node.get_children();
    _children = children;
    return *this;
}

node_object& node_object::operator= ( node_object&& node )
{
    const auto& children = node.get_children();
    _children = std::move(children);
    return *this;
}

node_object* node_object::add_child( node_object* object )
{
    check_pointer_return( object, this );
    add_child( object->get_tag(), object );
    return this;
}

node_object* node_object::add_child( int tag, node_object* object )
{
    check_pointer_return( object, this );
    _children.emplace( tag, object );
    return this;
}

node_object* node_object::remove_child( node_object* object )
{
    check_pointer_return( object, this );
    
    auto range = _children.equal_range( object->get_tag() );
    for (auto i = range.first; i != range.second; ++i) {
        if (i->second == object) {
            _children.erase( i );
            return this;
        }
    }
    return this;
}

node_object* node_object::remove_child( int tag )
{
    _children.erase( tag );
    return this;
}

node_object* node_object::get_child_by_tag( int tag )
{
    auto result = _children.find( tag );
    if (result != _children.end()) {
        return result->second;
    }
    return nullptr;
}

node_object::node_container node_object::get_children_by_tag( int tag )
{
    node_object::node_container result;
    auto range = _children.equal_range( tag );
    if (range.first == range.second) {
        return result;
    }
    
    for (auto i = range.first; i != range.second; ++i) {
        result.insert( std::make_pair( i->first, i->second ) );
    }
    
    return result;
}
