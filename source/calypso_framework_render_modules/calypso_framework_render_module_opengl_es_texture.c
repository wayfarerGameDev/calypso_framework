#pragma once

// Dependencies
#include <dependencies/glad/glad.h>

/*------------------------------------------------------------------------------
Calypso Framework Render Module (OpenGl ES Texture) : Create Texture
------------------------------------------------------------------------------*/

const unsigned int calypso_framework_render_module_opengl_es_shader_create_texture_2d_rgba(const unsigned char* bytes, const int width, const int height)
{
    // Create | Bind Texture
    unsigned int texture;
    glGenTextures(1,&texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set TExture Parameter (Filter) (Nearest)
    glTextureParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Set Texture Parameter (Filter) (Nearest)
    glTextureParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Create Texture From Bytes
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);

    // Generate Mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);

    // Unbind Texture
    glBindTexture(GL_TEXTURE_2D,0);

    // Return
    return texture;
}

const unsigned int calypso_framework_render_module_opengl_es_shader_create_texture_2d_bgra(const unsigned char* bytes, const int width, const int height)
{
    // Create | Bind Texture
    unsigned int texture;
    glGenTextures(1,&texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set TExture Parameter (Filter) (Nearest)
    glTextureParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Set Texture Parameter (Filter) (Nearest)
    glTextureParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Create Texture From Bytes
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, bytes);

    // Generate Mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);

    // Unbind Texture
    glBindTexture(GL_TEXTURE_2D,0);

    // Return
    return texture;
}

/*------------------------------------------------------------------------------
Calypso Framework Render Module (OpenGl ES Texture) : Un/Bind Texture
------------------------------------------------------------------------------*/

void calypso_framework_render_module_opengl_es_shader_bind_texture_2d(const unsigned int texture, const unsigned int texture_slot)
{
    glActiveTexture(GL_TEXTURE0 + texture_slot);
    glBindTexture(GL_TEXTURE_2D,texture);
}

void calypso_framework_render_module_opengl_es_shader_unbind_texture_2d()
{
    glBindTexture(GL_TEXTURE_2D,0);
}

/*------------------------------------------------------------------------------
license
------------------------------------------------------------------------------

MIT License
Copyright (c) 2023 Nicholas Gennady Korta
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/