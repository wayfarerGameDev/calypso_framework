#pragma once

// Dependencies
#include <dependencies/glad/glad.h>

// Open GL Version
#define CALYPSO_FRAMEWORK_RENDER_MODULE_OPENGL_ES_BOOTSTRAP_MAJOR_VERSION                      3
#define CALYPSO_FRAMEWORK_RENDER_MODULE_OPENGL_ES_BOOTSTRAP_MINOR_VERSION                      3
#define CALYPSO_FRAMEWORK_RENDER_MODULE_OPENGL_ES_BOOTSTRAP_CONTEXT_PROFILE                    3

/*------------------------------------------------------------------------------
Calypso Framework Render Module (OpenGl ES Bootstrap) : Log Callback
------------------------------------------------------------------------------*/

void calypso_framework_render_module_opengl_es_bootstrap_log_graphics_card()
{
    #ifdef CALYPSO_FRAMEWORK_LOG_MESSAGE_ENABLED
    const char* vendor = (const char*)glGetString(GL_VENDOR);
    const char* renderer = (const char*)glGetString(GL_RENDERER);
    CALYPSO_FRAMEWORK_LOG_MESSAGE("render_module_opengl_es_bootstrap",vendor,1);
    CALYPSO_FRAMEWORK_LOG_MESSAGE("render_module_opengl_es_bootstrap",renderer,1);
    #endif
}