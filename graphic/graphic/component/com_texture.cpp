/*
 *  com_texture.cpp
 *  graphic
 *
 *  Created by jiayi on 15/03/2017.
 *  Copyright © 2017 jiayi. All rights reserved.
 *
 */

#include "com_texture.h"
#include "foundation/texture/texture_manager.h"

using namespace minerva::graphic;

com_texture::~com_texture()
{
    _model = nullptr;
    glDeleteTextures( 1, &_texture_id );
}

/// initialize component
bool com_texture::initialize( model* m )
{
    _model = m;
    glGenTextures( 1, &_texture_id );
    return true;
}

/// update component
void com_texture::update_component( float delta )
{
    if (!_get_dirty()) { return; }
    
    _set_dirty( false );
    
    // check string
    if (_texture_file.empty()) { return; }
    
    the_texture_manager->load_texture_by_file_name(
                                                   _texture_file.c_str(),
                                                   std::bind(
                                                             &com_texture::_on_texture_loaded,
                                                             this,
                                                             std::placeholders::_1 )
                                                   );
}

void com_texture::on_render_component( float delta )
{
    if (!_get_ready()) { return; }
    
    if (_texture_id == -1) { mi_log("texture_id is -1"); return; }
    if (_sampler == -1) { mi_log("_sampler is -1"); return; }
    if (_texture_index == -1) { mi_log("texture_index is -1"); return; }
    
    glActiveTexture( _texture_index + GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, _texture_id );
    glUniform1i( _sampler, _texture_index );
    
    auto width = _texture_data->width;
    auto height = _texture_data->height;
    
    unsigned int blockSize = (_texture_data->format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    unsigned int offset = 0;
    
    
    /* load the mipmaps */
    for (auto level = 0; level < _texture_data->mipmap_count && (width || height); ++level)
    {
        auto size = (( width + 3 ) >> 2)*(( height + 3 ) >> 2) * blockSize;
        glCompressedTexImage2D( GL_TEXTURE_2D, level, _texture_data->format, width, height,
                               0, size, _texture_data->buffer + offset );
        
        offset += size;
        width  >>= 1;
        height >>= 1;
    }
}

/// render component
void com_texture::render_component( float delta )
{
    
}

void com_texture::set_texture_file(const std::string &t)
{
    _texture_file = t;
    _set_dirty( true );
    _set_ready( false );
}

void com_texture::_on_texture_loaded( void* data )
{
    _set_texture_data( ( foundation::texture_data* )(data) );
    _set_ready( true );
}
