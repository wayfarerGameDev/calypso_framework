#pragma once

// Dependencies
#include <dependencies/glad/glad.h>

// Open GL Version
#define CALYPSO_FRAMEWORK_RENDER_MODULE_OPENGL_ES_CORE_MAJOR_VERSION                           3
#define CALYPSO_FRAMEWORK_RENDER_MODULE_OPENGL_ES_CORE_MINOR_VERSION                           3
#define CALYPSO_FRAMEWORK_RENDER_MODULE_OPENGL_ES_CORE_CONTEXT_PROFILE                         3

/*------------------------------------------------------------------------------
Calypso Framework Render Module (OpenGl ES Core) : Hardware
------------------------------------------------------------------------------*/

char* calypso_framework_render_module_opengl_es_core_get_hardware_vendor()
{
    return (char*)glGetString(GL_VENDOR);
}

char* calypso_framework_render_module_opengl_es_core_get_hardware_renderer()
{
    return (char*)glGetString(GL_RENDERER);
}

void calypso_framework_render_module_opengl_es_core_log_hardware()
{
    #ifdef CALYPSO_FRAMEWORK_LOG_MESSAGE_ENABLED
    CALYPSO_FRAMEWORK_LOG_MESSAGE("render_module_opengl_es_core",calypso_framework_render_module_opengl_es_core_get_hardware_vendor(),1);
    CALYPSO_FRAMEWORK_LOG_MESSAGE("render_module_opengl_es_core",calypso_framework_render_module_opengl_es_core_get_hardware_renderer(),1);
    #endif
}

/*------------------------------------------------------------------------------
Calypso Framework Render Module (OpenGl ES Core) : Init
------------------------------------------------------------------------------*/

void calypso_framework_render_module_opengl_es_core_init(const void* opengl_processing_address)
{
    // OpenGL (Glad)
    gladLoadGLLoader(opengl_processing_address);

    // Clear Defaults
    glClearColor(0.392f,0.584f,0.929f,1); // Cornfolower Blue
    glClearDepth(1);

    // Log Graphics Card
    #ifdef CALYPSO_FRAMEWORK_LOG_MESSAGE_ENABLED
    CALYPSO_FRAMEWORK_LOG_MESSAGE("render_module_opengl_es_core","Initalized",1);
    calypso_framework_render_module_opengl_es_core_log_hardware();
    #endif
}

/*------------------------------------------------------------------------------
Calypso Framework Render Module (OpenGl ES Core) : Enable | Disable
------------------------------------------------------------------------------*/

void calypso_framework_renderer_module_opengl_es_core_enable(const unsigned int value)
{
    glEnable(value);
}

void calypso_framework_renderer_module_opengl_es_core_disable(const unsigned int value)
{
    glDisable(value);
}

/*------------------------------------------------------------------------------
Calypso Framework Render Module (OpenGl ES Core) : Blend/Depth Functions
------------------------------------------------------------------------------*/

void calypso_framework_renderer_module_opengl_es_core_set_blend_function(const unsigned int value_a, const unsigned int value_b)
{
    glBlendFunc(value_a,value_b);
}

void calypso_framework_renderer_module_opengl_es_core_set_depth_function(const unsigned int value)
{
    glDepthFunc(value);
}

void calypso_framework_renderer_module_opengl_es_core_set_wireframe_mode(const unsigned char value)
{
    // Wire frame On
    if (value == 1)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Wire frame Off
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

/*------------------------------------------------------------------------------
Calypso Framework Render Module (OpenGl ES Core) : Clear
------------------------------------------------------------------------------*/

void calypso_framework_render_module_opengl_es_core_set_clear_color(const float r, const float g, const float b, const float a)
{
    glClearColor(r,g,b,a);
}

void calypso_framework_render_module_opengl_es_core_set_clear_depth(const float depth)
{
    glClearDepth(depth);
}

void calypso_framework_render_module_opengl_es_core_clear(const unsigned int mask)
{    
    glClear(mask);
}

/*------------------------------------------------------------------------------
Calypso Framework Render Module (OpenGl ES Core) : Viewport
------------------------------------------------------------------------------*/

void calypso_framework_render_module_opengl_es_core_set_viewport(const int width, const int height)
{
    // Set Viewport
    glViewport(0,0,width,height);
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