
namespace minerva { namespace graphic {
    
    template<class T>
    void model::add_component( component* c )
    {
        std::size_t hash_id = std::hash<std::string>()(c->get_name());
        if (_components.find(hash_id) != _components.end()) {
            mi_log( "found a same type of T\n" ); return;
        }
        
        _components.emplace( std::make_pair( hash_id, c ) );
        if (!c->initialize( this )) {
            mi_log( "initialize component failed, type is: %s\n", (c->get_name()) );
        }
    }
    
    template<class T>
    void model::remove_component()
    {
        std::size_t hash_id = std::hash<T>();
        _components.erase( hash_id );
    }
    
    template<class T>
    T* model::get_component()
    {
        std::size_t hash_id = std::hash<T>();
        auto f = _components.find( hash_id );
        
        if (f == _components.end())
        { return nullptr; }
        
        return f->second;
    }
    
}}
