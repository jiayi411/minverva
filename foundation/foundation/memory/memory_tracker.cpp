/*!
 @file memory_tracker.h
 @brief tracking memory allocation and deallocation
 
 @author jiayi
 @date 17/01/2017
 */

#include "memory_tracker.h"

using namespace minerva::foundation;

memory_tracker::~memory_tracker()
{
    _groups.clear();
    _search.clear();
    _pointers.clear();
}

void memory_tracker::add(void *ptr, size_t size, const char *function, uint line)
{
    _mutex.lock();
    
    auto index = _get_memory_group_index_by_name( function, line );
    
    // if not found a record
    if ( index == -1 )
    {
        _groups.emplace_back( memory_group( function ) );
        index = _groups.size() - 1;
        
        // insert to _searchs and _pointers
        _search.emplace( std::make_pair( function, index ) );
    }
    
    // increase size count of memory_group
    size_t memory_index = _increase( index, size, line );
    
    _pointers.emplace( std::make_pair( *(ulong*)&ptr, index << 32 | memory_index ) );
    
    _mutex.unlock();
    
}

void memory_tracker::remove( void* ptr )
{
    // find the pointer
    auto pointer = _pointers.find( *(ulong*)&ptr );
    if ( pointer == _pointers.end() ){
        assert( "have not found the memory, maybe an error" && 0 );
        return;
    }
    
    _decrease( pointer->second );
}

void memory_tracker::output_informations()
{
    _mutex.lock();
    for ( auto iter = _groups.begin(); iter != _groups.end(); ++iter )
    {
        memory_group& group = *iter;
        // print infor of this group
        for( const auto s : group.size_count_array )
        {
            if( s.ui_count > 0 )
            { mi_log( "function: %s, line: %d, allocated count: %d, total memory: %.1f kbytes\n",
                     group.function_name.c_str(), s.n_line, s.ui_count, (s.t_size * s.ui_count) / 1024.0 ); }
        }
    }
    _mutex.unlock();
}


size_t memory_tracker::_get_memory_group_index_by_name( const std::string& function_name, uint line ) const
{
    size_t count = _search.count( function_name );
    if ( count <= 0 ){
        return -1;
    }
    
    auto iter = _search.find( function_name );
    
    for ( size_t i = 0; i < count; ++i, ++iter )
    {
        const memory_group& group = _groups[iter->second];
        for ( const auto& g : group.size_count_array )
        {
            if ( g.n_line == line ){
                return iter->second;
            }
        }
    }
    
    return -1;
}


size_t memory_tracker::_increase( size_t index, size_t size, uint line )
{
    if( index >= _groups.size() ){
        _mutex.unlock();
        return -1;
    }
    
    memory_group& group = _groups[index];
    
    for ( auto i = 0; i < group.size_count_array.size(); ++i )
    {
        memory_size_count_info& info = group.size_count_array[i];
        if ( info.n_line == line && info.t_size == size )
        {
            ++info.ui_count;
            _mutex.unlock();
            return i;
        }
    }
    
    // add a new one
    group.size_count_array.emplace_back( memory_size_count_info( line, size, 1 ) );
    
    size_t ret = group.size_count_array.size() - 1;
    return  ret;
}

void memory_tracker::_decrease( ullong index )
{
    size_t memory_index = index & 0x00000000ffffffff;
    size_t group_index = index >> 32;
    
    if ( group_index >= _groups.size() ){
        _mutex.unlock();
        return;
    }
    
    memory_group& group = _groups[group_index];
    if ( memory_index < group.size_count_array.size() ){
        mi_assert( group.size_count_array[memory_index].ui_count > 0 );
        --group.size_count_array[memory_index].ui_count;
    }
}
