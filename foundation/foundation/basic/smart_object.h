/*
 *  smart_object.h
 *  foundation
 *
 *  Created by jiayi on 04/02/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#ifndef smart_object_H
#define smart_object_H

#include "basic/reference_object.h"

namespace minerva { namespace foundation {
    
    ///
    /// @brief The basic class of any smart object
    ///
    /// Smart object is an object that maintain its lifecycle
    /// automatically, it cannot be new/delete from outside. This
    /// class is thread safety.
    ///
    template< class T >
    class smart_object
    {
    public:
        /// create a new object, this is the only function to do that
//        static T* create_smart() { return mi_new T(); }
        
    public:
        /// for rhs operator
        inline smart_object& operator= ( smart_object&& );
        
        /// assign a reference to the object
        inline smart_object& operator= ( const smart_object& );
        
        /// assign a pointer to the object
        inline smart_object& operator= ( T* );
        
        /// compare operators 1/4
        inline bool operator== ( T* );
        
        /// compare operators 2/4
        inline bool operator== ( const smart_object& );
        
        /// compare operators 3/4
        inline bool operator!= ( T* );
        
        /// compare operators 4/4
        inline bool operator!= ( const smart_object& );
        
        /// convert operator
        inline operator T*() const;
        
        /// dereference operator
        inline T& operator*() const;
        
        /// pointer operator
        inline T* operator->() const;
        
        
    public:
        inline ~smart_object();
        inline smart_object( T* object = nullptr );
        inline smart_object( smart_object&& );
        
        smart_object( const smart_object& );
        
    protected:
        T* _object = nullptr;
        std::atomic_flag _smart_lock;   ///< lock
    };
    
    ////////////////////////////////////////////////////////////////////////
    #define make_smart( T ) \
        class T;\
        typedef smart_object<T> T##_ptr;
    ////////////////////////////////////////////////////////////////////////
    template<class T> smart_object<T>::~smart_object()
    {
        while (_smart_lock.test_and_set());
        if (_object) { _object->decrease_reference(); }
        _smart_lock.clear();
    }
    
    template<class T> smart_object<T>::smart_object( T* object /*=nullptr*/)
    {
        _smart_lock.clear();
        if (object)
        {
            _object = object;
            _object->increase_reference();
        }
    }
    
    template<class T> smart_object<T>::smart_object( const smart_object& smart )
    {
        _smart_lock.clear();
        _object = smart._object;
        _object->increase_reference();
    }
    
    template<class T> smart_object<T>::smart_object( smart_object&& smart )
    {
        _smart_lock.clear();
        if (_object) { _object->decrease_reference(); }
        _object = smart._object;
        if (_object) { _object->increase_reference(); }        
    }
    
    template<class T> smart_object<T>& smart_object<T>::operator=( smart_object&& pointer )
    {
        while (_smart_lock.test_and_set());
        if (_object) { _object->decrease_reference(); }
        _object = pointer._object;
        if (_object) { _object->increase_reference(); }
        _smart_lock.clear();
        return *this;
    }
    
    template<class T> smart_object<T>& smart_object<T>::operator=( const smart_object& pointer )
    {
        while (_smart_lock.test_and_set());
        if (_object) { _object->decrease_reference(); }
        _object = pointer._object;
        if (_object) { _object->increase_reference(); }
        _smart_lock.clear();
        return *this;
    }
    
    template<class T> smart_object<T>& smart_object<T>::operator=( T* object )
    {
        while (_smart_lock.test_and_set());
        if (_object) { _object->decrease_reference(); }
        _object = object;
        if (_object) { _object->increase_reference(); }
        _smart_lock.clear();
        return *this;
    }
    
    template<class T> smart_object<T>::operator T*() const
    { return _object; }
    
    template<class T> T& smart_object<T>::operator *() const
    { return *_object; }
    
    template<class T> T* smart_object<T>::operator->() const
    { return _object; }
    
    template<class T> bool smart_object<T>::operator== ( T* object )
    { return _object == object; }
    
    template<class T> bool smart_object<T>::operator!= ( T* object )
    { return _object != object; }
    
    template<class T> bool smart_object<T>::operator== ( const smart_object& smart )
    { return _object == smart._object; }
    
    template<class T> bool smart_object<T>::operator!= ( const smart_object& smart )
    { return _object != smart._object; }
} }

#endif /* smart_object_h */
