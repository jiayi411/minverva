//
//  node_object.h
//  foundation
//
//  Created by jiayi on 07/02/2017.
//  Copyright © 2017 jiayi. All rights reserved.
//

#ifndef node_object_h
#define node_object_h

#include "foundation/object/update_object.h"
#include "foundation/object/smart_object.h"
#include "math/transform.h"

namespace minerva { namespace graphic {
    
    class node_object;
    make_smart( node_object );
    
    ///
    /// @brief providing a children object
    ///
    /// this is the very basic class for children
    /// management. All children should be decendent from
    /// update_object.
    class node_object : public foundation::update_object
    {
    public:
        node_object() : _tag(-1) {}
        virtual ~node_object();
        
        node_object( const node_object& node );
        node_object( node_object&& node );
        
        node_object& operator= ( const node_object& node );
        node_object& operator= ( node_object&& node );
        
    public:
        using node_container = mi_unordered_multimap<int, node_object_ptr>;
        
    public:
        ///
        /// @brief add child
        ///
        /// @param object child to be added
        /// @return this object, for continous adding
        virtual node_object* add_child( node_object* object );
        
        ///
        /// @brief add child
        ///
        /// @param tag object's tag
        /// @param object child to be added
        /// @return this object, for continous operation
        virtual node_object* add_child( int tag, node_object* object );
        
        ///
        /// @brief remove child
        ///
        /// @param object object to be removed
        /// @return this node, for continous operation
        virtual node_object* remove_child( node_object* object );
        
        ///
        /// @brief remove child
        ///
        /// @param tag object's tag
        /// @return this node, for continous operation
        virtual node_object* remove_child( int tag );
        
        ///
        /// @brief get child by tag
        ///
        /// @param tag child's tag
        /// @return only return the first node that finded
        virtual node_object* get_child_by_tag( int tag );
        
        ///
        /// @brief get children by tag, a little bit time consuming
        ///
        /// @param tag child's tag
        /// @return return a container
        virtual node_container get_children_by_tag( int tag );
        
        ///
        /// @brief update function
        /// @param delta the delta time from last frame
        ///
        virtual void update( float delta );
        
        ///
        /// @brief before rendering
        ///
        /// execute just before render
        ///
        virtual void on_render( float delta );
        
        ///
        /// @brief render function
        /// @param delta the delta time from last frame
        ///
        virtual void render( float delta );
        
    protected:
        set_get( int, tag );
        set_get_ref( transform, transform );     ///< transform
        set_get_ref( node_container, children ); ///< children
        set_get_ref( node_object_ptr, parent );  ///< parent
    };
    
} }

#endif /* node_object_h */
