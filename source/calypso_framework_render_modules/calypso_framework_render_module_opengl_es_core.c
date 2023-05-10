#pragma once

// Dependencies
#include <dependencies/glad/glad.h>

// Open GL Version
#define CALYPSO_FRAMEWORK_RENDER_MODULE_OPENGL_ES_BOOTSTRAP_MAJOR_VERSION                      3
#define CALYPSO_FRAMEWORK_RENDER_MODULE_OPENGL_ES_BOOTSTRAP_MINOR_VERSION                      3
#define CALYPSO_FRAMEWORK_RENDER_MODULE_OPENGL_ES_BOOTSTRAP_CONTEXT_PROFILE                    3

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

void calypso_framework_render_module_opengl_es_core_init(void* opengl_processing_address)
{
    // OpenGL (Glad)
    gladLoadGLLoader(opengl_processing_address);

    // Blending
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LESS);

    // Start Clear Color (Cornflower blue)
    glClearColor(0.392f,0.584f,0.929f,1);

    // Log Graphics Card
    #ifdef CALYPSO_FRAMEWORK_LOG_MESSAGE_ENABLED
    CALYPSO_FRAMEWORK_LOG_MESSAGE("render_module_opengl_es_core","Initalized",1);
    calypso_framework_render_module_opengl_es_core_log_hardware();
    #endif
}

/*------------------------------------------------------------------------------
Calypso Framework Render Module (OpenGl ES Core) : Clear
------------------------------------------------------------------------------*/

void calypso_framework_render_module_opengl_es_core_set_clear_color(const float r, const float g, const float b, const float a)
{
    glClearColor(r,g,b,a);
}

void calypso_framework_render_module_opengl_es_core_clear()
{    
    glClearDepth(1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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