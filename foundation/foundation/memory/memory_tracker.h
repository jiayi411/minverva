/*!
 @file memory_tracker.h
 @brief tracking memory allocation and deallocation
 
 @author jiayi
 @date 17/01/2017
 */

#ifndef memory_tracker_hpp
#define memory_tracker_hpp

#include "basic/defines.h"
#include "standard_libraries/unordered_multimap.h"
#include "standard_libraries/unordered_map.h"
#include "standard_libraries/vector.h"
#include <mutex>
#include <string>

namespace minerva
{
    namespace foundation
    {
        ///
        /// @brief Tracking memory allocations
        ///
        /// This is a thread-safe memory tracker, due to performance concerns, please
        /// do not use this class in a release version.
        ///
        class memory_tracker
        {
        public:
            /// Instance method
            static memory_tracker* get(){
                static memory_tracker s_this;
                return &s_this;
            }
            
        protected:
            memory_tracker(){}
            ///
            /// @brief size and count structure
            ///
            struct memory_size_count_info
            {
                /// ctor for structure
                memory_size_count_info( uint line, size_t size, uint count ) :
                n_line(line), t_size(size), ui_count(count){}
                
                uint n_line;                ///< line of file
                size_t t_size;              ///< size of each allocation in the same line
                uint ui_count;              ///< how many times does it do allocate
            };
            
            ///
            /// @brief group organized by line, function, size and count
            ///
            /// We organize the memory blocks by a key (function) and it's values.
            /// Due to a memory allocation may be occured more than once in a single function,
            /// so we use a container to distinguish different allocations, besides, the size may
            /// vary even in a same line, for instance, array allocation with different size, so
            /// we need to handle this too
            struct memory_group
            {
                /// ctor for structure
                memory_group( std::string&& funcn ):
                function_name( std::move( funcn ) ){};
                
                ~memory_group(){ size_count_array.clear(); }
                
                std::string function_name;                          ///< function
                mi_vector<memory_size_count_info> size_count_array; ///< size&count info for different line&function
            };
            
            typedef mi_vector< memory_group > memory_groups;                        ///< container of memory group
            typedef mi_unordered_multimap< std::string, size_t > memory_search;        ///< for memory search
            
            ///
            /// @brief for memory address record
            ///
            /// for finding purpose, func/index, high-32-bit are the _groups' index,
            /// low-32-bit are the size_count_array's index.
            typedef mi_unordered_map< ulong, ullong > pointer_search;
            
        public:
            ~memory_tracker();
            
            /// add a record
            void add( void* ptr, size_t size, const char* function, uint line );
            
            /// remove a record
            void remove( void* ptr );
            
            /// print allocated memory infomation
            void output_informations();
            
        protected:
            
            /// increase count based on index and size
            size_t _increase( size_t index, size_t size, uint line );
            
            /// decrease count based on index and size
            void _decrease( ullong index );
            
            /// finding memory_group by filename and line number
            size_t _get_memory_group_index_by_name( const std::string& function_name, uint line ) const;
            
            
        protected:
            memory_groups _groups;      ///< container for memory that allocated
            memory_search _search;      ///< used for quickly search
            pointer_search _pointers;   ///< pointers
            std::mutex _mutex;          ///< lock containers
        };
    }
}

/// for short
#define the_memory_tracker memory_tracker::get()

#endif /* memory_tracker_h */
