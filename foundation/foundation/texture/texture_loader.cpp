/*
 *  texture_loader.cpp
 *  foundation
 *
 *  Created by jiayi on 01/02/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#include "texture_loader.h"
#include <fstream>
#include <GL/glew.h>

using namespace minerva::foundation;

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

void* texture_loader::load_dds( void* v_file_name ) thread_safe
{
    texture_data* data = mi_new texture_data();
    std::string file_name = *(std::string*)(v_file_name);
    data->filename = file_name;
    
    if ( load_dds_from_file( ( file_name), data ) ) {
        return (void*)data;
    }
    
    return nullptr;
}

bool texture_loader::load_dds_from_file( const std::string& file_name,
                                                texture_data* data )
{
    char header[124];    
    
    std::ifstream stream( file_name, std::ios::binary | std::ios::in );
    if ( !stream.good() ) {
        mi_log("error occurs when loading file: %s", file_name.c_str());
        return false;
    }
    
    /* verify the type of file */
    char file_code[4];
    stream.read( file_code, 4 * sizeof(char) );
    if (strncmp(file_code, "DDS ", 4) != 0) {
        stream.close();
        mi_log( "File is not a DDS type: %s", file_name.c_str() );
        return 0;
    }
    
    /* get the surface desc */
    stream.read( header, 124 );
    
    unsigned int height      = *(unsigned int*)&(header[8 ]);
    unsigned int width         = *(unsigned int*)&(header[12]);
    unsigned int linearSize     = *(unsigned int*)&(header[16]);
    unsigned int mipMapCount = *(unsigned int*)&(header[24]);
    unsigned int fourCC      = *(unsigned int*)&(header[80]);
    
    unsigned int bufsize;
    
    /* how big is it going to be including all mipmaps? */
    bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
    char *buffer = (char*)mi_malloc(bufsize * sizeof(char));
    stream.read( buffer, bufsize * sizeof(char) );
    /* close the file pointer */
    stream.close();
    
    unsigned int format;
    switch(fourCC)
    {
        case FOURCC_DXT1:
        format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
        break;
        case FOURCC_DXT3:
        format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
        break;
        case FOURCC_DXT5:
        format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
        break;
        default:
        free(buffer);
        return 0;
    }
    
    // assign to the data
    if (data) {
        data->width = width;
        data->height = height;
        data->format = format;
        data->mipmap_count = mipMapCount;
        data->buffer = ( unsigned char* )buffer;
    }
    return true;
}
