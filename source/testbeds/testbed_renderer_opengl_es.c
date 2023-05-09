
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Calypso (SDL or GLFW)
#define USE_GLFW_OVER_SDL 1
#if(USE_GLFW_OVER_SDL)
#include "../calypso_framework_glfw/calypso_framework_glfw_app.c"
#include "../calypso_framework_glfw/calypso_framework_glfw_input.c"
#else
#include "../calypso_framework_sdl2/calypso_framework_sdl2_app.c"
#include "../calypso_framework_sdl2/calypso_framework_sdl2_input.c"
#endif

// Calypso
#include "../calypso_framework_io/calypso_framework_io_file.c"
#include "../calypso_framework_io/calypso_framework_io_tga.c"
#include "../calypso_framework_math/calypso_framework_math_colors.c"
#include "../calypso_framework_math/calypso_framework_math_matrix4.c"
#include "../calypso_framework_math/calypso_framework_math_random.c"
#include "../calypso_framework_renderer/calypso_framework_renderer_2d_opengl_es.c"
#include "../calypso_framework_renderer/calypso_framework_renderer_pixel_opengl_es.c"

// Renderer (Viewport)
float _renderer_viewport_projection_matrix[4][4];
float _renderer_view_matrix[4][4];
float _renderer_projection_view_matrix[4][4];
float _renderer_viewport_position_x;
float _renderer_viewport_position_y;
float _renderer_viewport_width;
float _renderer_viewport_height;
float _renderer_viewport_scale_x;
float _renderer_viewport_scale_y;

// Render (Shader Programs)
float _renderer_model_matrix[4][4];
unsigned int _renderer_default_shader_immediate_program;
unsigned int _renderer_default_shader_batched_program;

// Renderer (Other)
struct calypso_framework_renderer_2d_opengl_es_quad_batch _renderer_pixel_buffer_textured;
calypso_framework_renderer_pixel_opengl_es_pixel_buffer_t _renderer_pixel_buffer;
int _renderer_pixel_buffer_x = 1024;
int _renderer_pixel_buffer_y = 1024;

// TGA File
unsigned int _texture;

// Colors
const unsigned char* _c_color_white_array = _calypso_framework_math_colors_color_rgba_white;
const unsigned char* _c_color_red_array = _calypso_framework_math_colors_color_rgba_red;
const unsigned char* _c_color_yellow_array = _calypso_framework_math_colors_color_rgba_yellow;


void log_msg(const char* log_msg, const unsigned char log_type)
{
    // Color Log
    if (log_type == 1)
        printf("\033[0;32m"); // Green
    else if (log_type == 2)
        printf("\033[33m"); // Yellow
    else if (log_type == 3)
        printf("\033[0;31m"); // Red
    else 
        printf("\033[0;00m"); // White
    
    // Log
    printf(log_msg);

    // Reset Log
    printf("\033[0;00m"); // White
}

void start(void)
{
    // Viewport Width / Height (GLFW)
    #if(USE_GLFW_OVER_SDL)
    _renderer_viewport_width = calypso_framework_glfw_app_get_window_width();
    _renderer_viewport_height = calypso_framework_glfw_app_get_window_height();
    
    #else
    // Viewport Width / Height (SDL)
    _renderer_viewport_width = calypso_framework_sdl2_app_get_window_width();
    _renderer_viewport_height = calypso_framework_sdl2_app_get_window_height();
    #endif

    // Init Renderer
    {
        // Viewport Width / Height (GLFW)
        #if(USE_GLFW_OVER_SDL)
        calypso_framework_renderer_2d_opengl_es_init(calypso_framework_glfw_app_get_open_gl_proc_address());
        #else
        calypso_framework_renderer_2d_opengl_es_init(calypso_framework_sdl2_app_get_open_gl_proc_address());
        #endif


        // Default Shader Program (Batched)
        _renderer_default_shader_batched_program = calypso_framework_renderer_2d_opengl_es_create_default_batched_shader_program_textured();
       
        // Default Shader Program (Immediate)
        _renderer_default_shader_immediate_program = calypso_framework_renderer_2d_opengl_es_create_default_immediate_shader_program();
        calypso_framework_renderer_2d_opengl_es_set_current_render_shader_program(_renderer_default_shader_immediate_program);
        calypso_framework_renderer_2d_opengl_es_set_current_shader_program_parameter_vec4f("color_in",_c_color_white_array[0] / 255, _c_color_white_array[1] / 255, _c_color_white_array[2] / 255, _c_color_white_array[3] / 255);
    }

    // Init Renderer (Pixel)
    {
        // Viewport Width / Height (GLFW)
        #if(USE_GLFW_OVER_SDL)
        calypso_framework_renderer_pixel_opengl_es_init(calypso_framework_glfw_app_get_open_gl_proc_address(),_renderer_pixel_buffer_x,_renderer_pixel_buffer_y);
        #else
        calypso_framework_renderer_pixel_opengl_es_init(calypso_framework_sdl2_app_get_open_gl_proc_address(),_renderer_pixel_buffer_x,_renderer_pixel_buffer_y);
        #endif

        // Create Pixel Buffer (Foreground | Midground)
        calypso_framework_renderer_pixel_opengl_es_create_pixel_buffer(&_renderer_pixel_buffer,_renderer_pixel_buffer_x,_renderer_pixel_buffer_y);
    }    

    // Create render Quad (Immediate)
    calypso_framework_renderer_2d_opengl_es_create_build_quad_immediate();

    // Create Render Quad (Batched)
    {
        _renderer_pixel_buffer_textured = calypso_framework_renderer_2d_opengl_es_create_quad_batch_textured();
        calypso_framework_renderer_2d_opengl_es_set_quad_batch_data_default_textured(&_renderer_pixel_buffer_textured);

        // Randomize
        {
            // Cache Max/Min Width/Height
            const int max_width = ((int)_renderer_viewport_width) * 0.04f;
            const int min_width = -max_width;
            const int max_height = ((int)_renderer_viewport_height) * 0.04f;
            const int min_height = -max_height;

            // Set Entities Data
            float position[2] = {0,0};
            float color[4] = {0,0,0,1};
            calypso_framework_random_rand_set_seed_as_time();
            for (int i = 0; i < CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_QUAD_BATCH_INSTANCE_MAX_COUNT; i++)
            {
                position[0] = calypso_framework_math_random_rand_range_i(min_width,max_width);
                position[1] = calypso_framework_math_random_rand_range_i(min_height,max_height);
                color[0] = calypso_framework_math_random_rand_range_f(10,255) / 255.0f;
                color[1] = calypso_framework_math_random_rand_range_f(10,255) / 255.0f;
                color[2] = calypso_framework_math_random_rand_range_f(10,255) / 255.0f;
                color[3] = calypso_framework_math_random_rand_range_f(10,255) / 255.0f;

                calypso_framework_renderer_2d_opengl_es_set_quad_batch_instance_data_transform_textured(&_renderer_pixel_buffer_textured,i,position,3);
                calypso_framework_renderer_2d_opengl_es_set_quad_batch_instance_data_color_textured(&_renderer_pixel_buffer_textured,i,color);
                calypso_framework_renderer_2d_opengl_es_set_quad_batch_instance_data_texture_index_textured(&_renderer_pixel_buffer_textured,i,i%2 ? 0 : 1);
            }
        }

        calypso_framework_renderer_2d_opengl_es_build_quad_batch_textured(&_renderer_pixel_buffer_textured); 
    }

    // Load TGA (Test)
    {
        int image_width, image_height, image_column_count;
        unsigned char* image_data = stbi_load("content/testbed/test_tga.tga",&image_width,&image_height,&image_column_count,0);
        _texture = calypso_framework_renderer_2d_opengl_es_create_texture_2d_bgra(image_data,image_width,image_height);
        free(image_data);
    }
}


void end(void)
{
    // Renderer
    calypso_framework_renderer_2d_opengl_es_deinit();
    calypso_framework_renderer_pixel_opengl_es_deinit();
    
    // Free Pixel Buffers
    calypso_framework_renderer_pixel_opengl_es_free_pixel_buffer(&_renderer_pixel_buffer);
}


void update(void)
{

    // Get Viewport width and Height
    {
        // Viewport Width / Height (GLFW)
        #if(USE_GLFW_OVER_SDL)
        _renderer_viewport_width = calypso_framework_glfw_app_get_window_width();
        _renderer_viewport_height = calypso_framework_glfw_app_get_window_height();

        #else
        // Viewport Width / Height (SDL)
        _renderer_viewport_width = calypso_framework_sdl2_app_get_window_width();
        _renderer_viewport_height = calypso_framework_sdl2_app_get_window_height();
        #endif
    }

    // MVP
    // Does not need to be done each frame but when *camra* changes but done like this for simplicity
    {
        // Viewport Transform
        _renderer_viewport_position_x = _renderer_viewport_width / 2;
        _renderer_viewport_position_y = _renderer_viewport_height / 2;
        _renderer_viewport_scale_x = 0.3f;
        _renderer_viewport_scale_y = 0.3f;

        // Viewport Matrix (Projection And View) (Ortho 2D)
        calypso_framework_math_matrix_build_projection_ortho_matrix4f(0,_renderer_viewport_width,0,_renderer_viewport_height,-1,1,_renderer_viewport_projection_matrix);
        calypso_framework_math_matrix_build_identity_matrix4f(_renderer_view_matrix);
        calypso_framework_math_matrix_modify_set_scale(_renderer_viewport_scale_x,_renderer_viewport_scale_y,1,_renderer_view_matrix);
        calypso_framework_math_matrix_modify_set_position(_renderer_viewport_position_x,_renderer_viewport_position_y,0,_renderer_view_matrix);
        calypso_framework_math_matrix_modify_mult(_renderer_viewport_projection_matrix,_renderer_view_matrix,_renderer_projection_view_matrix);
    }

    // Render (Start)
    {        
        // Render Start
        const unsigned char color[4] = {10,10,10,255};
        calypso_framework_renderer_2d_opengl_es_set_clear_color_by_byte_color_array(color); // Don't need to  do this every frame but why not
        calypso_framework_renderer_2d_opengl_es_clear();
    }

    // Render (Pixel Buffer)
    {
        for (int x = 0; x < _renderer_pixel_buffer_x; x++)
            for (int y = 0; y < _renderer_pixel_buffer_y; y++)
                calypso_framework_renderer_pixel_opengl_es_set_pixel_buffer_pixel(&_renderer_pixel_buffer,x,y,calypso_framework_math_random_rand() % 255,calypso_framework_math_random_rand() % 255,calypso_framework_math_random_rand() % 255, 255);
    
        // Render
        calypso_framework_renderer_pixel_opengl_es_render_pixel_buffer(&_renderer_pixel_buffer);
    }

    // Render (Quad Batched)
    {
        calypso_framework_math_matrix_build_identity_matrix4f(_renderer_model_matrix);
        calypso_framework_math_matrix_modify_set_scale(50,50,1,_renderer_model_matrix);
        calypso_framework_math_matrix_modify_set_position(0,0,0,_renderer_model_matrix);

        // Bind Textures
        calypso_framework_renderer_2d_opengl_es_bind_texture_2d(_texture);

        // Update Shader Program
        calypso_framework_renderer_2d_opengl_es_set_current_render_shader_program(_renderer_default_shader_batched_program);
        calypso_framework_renderer_2d_opengl_es_set_current_shader_program_parameter_matrix4f("projection_view_in",_renderer_projection_view_matrix[0]); // Apply Viewport Projection And View
        calypso_framework_renderer_2d_opengl_es_set_current_shader_program_parameter_matrix4f("model_in",_renderer_model_matrix[0]); // Apply Transform
        calypso_framework_renderer_2d_opengl_es_bind_current_shader_program_texture("u_texture",_texture);

        // Render
        calypso_framework_renderer_2d_opengl_es_render_quad_batched_textured(&_renderer_pixel_buffer_textured);

        // Unbind Texture
        calypso_framework_renderer_2d_opengl_es_unbind_texture_2d();
    }

    // Render(Quad Immediate)
    {
        // Entity (Red)
        {
            // Model Matrix
            calypso_framework_math_matrix_build_identity_matrix4f(_renderer_model_matrix);
            calypso_framework_math_matrix_modify_set_scale(100,100,1,_renderer_model_matrix);
            calypso_framework_math_matrix_modify_set_position(0,0,0,_renderer_model_matrix);

            // Update Shader Program
            calypso_framework_renderer_2d_opengl_es_set_current_render_shader_program(_renderer_default_shader_immediate_program);
            calypso_framework_renderer_2d_opengl_es_set_current_shader_program_parameter_matrix4f("projection_view_in",_renderer_projection_view_matrix[0]); // Apply Viewport Projection And View
            calypso_framework_renderer_2d_opengl_es_set_current_shader_program_parameter_vec4f("color_in",_c_color_red_array[0] / 255, _c_color_red_array[1] / 255, _c_color_red_array[2] / 255, _c_color_red_array[3] / 255);
            calypso_framework_renderer_2d_opengl_es_set_current_shader_program_parameter_matrix4f("model_in",_renderer_model_matrix[0]); // Apply Transform
    
            // Render
            calypso_framework_renderer_2d_opengl_es_render_quad_immediate();
        }

        // Entity (Yellow)
        {
            // Model Matrix
            calypso_framework_math_matrix_build_identity_matrix4f(_renderer_model_matrix);
            calypso_framework_math_matrix_modify_set_scale(50,50,1,_renderer_model_matrix);
            calypso_framework_math_matrix_modify_set_position(100,100,0,_renderer_model_matrix);

            // Update Shader Program
            calypso_framework_renderer_2d_opengl_es_set_current_render_shader_program(_renderer_default_shader_immediate_program);
            calypso_framework_renderer_2d_opengl_es_set_current_shader_program_parameter_matrix4f("projection_view_in",_renderer_projection_view_matrix[0]); // Apply Viewport Projection And View
            calypso_framework_renderer_2d_opengl_es_set_current_shader_program_parameter_vec4f("color_in",_c_color_yellow_array[0] / 255, _c_color_yellow_array[1] / 255, _c_color_yellow_array[2] / 255, _c_color_yellow_array[3] / 255);
            calypso_framework_renderer_2d_opengl_es_set_current_shader_program_parameter_matrix4f("model_in",_renderer_model_matrix[0]); // Apply Transform
    
            // Render
            calypso_framework_renderer_2d_opengl_es_render_quad_immediate();
        }
    }
}

void resize(void)
{
    // Viewport Width / Height (GLFW)
    #if(USE_GLFW_OVER_SDL)
    _renderer_viewport_width = calypso_framework_glfw_app_get_window_width();
    _renderer_viewport_height = calypso_framework_glfw_app_get_window_height();
    
    #else
    // Viewport Width / Height (SDL)
    _renderer_viewport_width = calypso_framework_sdl2_app_get_window_width();
    _renderer_viewport_height = calypso_framework_sdl2_app_get_window_height();
    #endif

    calypso_framework_renderer_2d_opengl_es_renderer_resize(_renderer_viewport_width,_renderer_viewport_height);
    // calypso_framework_renderer_pixel_opengl_es_renderer_resize(_renderer_viewport_width,_renderer_viewport_height); // Only Need To Do It On One
}

int main(int argc, char** argv)
{
    // Logging
    calypso_framework_renderer_2d_opengl_es_set_log_callback(log_msg);

    // App (GLFW)
    #if(USE_GLFW_OVER_SDL)
    calypso_framework_glfw_app_set_log_callback(log_msg);
    calypso_framework_glfw_app_init_with_opengl(CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_MAJOR_VERSION,CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_MINOR_VERSION,CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_CONTEXT_PROFILE);
    calypso_framework_glfw_app_set_title("Testbed : Renderer OpenglES (GLFW)");
    calypso_framework_glfw_app_set_events(start,end,update,resize);
    calypso_framework_glfw_app_set_window_resizable(1);
    calypso_framework_glfw_app_run();
    
    #else
    // App (SDL)
    calypso_framework_sdl2_app_set_log_callback(log_msg);
    calypso_framework_sdl2_app_init_with_opengl(CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_MAJOR_VERSION,CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_MINOR_VERSION,CALYPSO_FRAMEWORK_RENDERER_2D_OPENGL_ES_CONTEXT_PROFILE);
    calypso_framework_sdl2_app_set_title("Testbed : Renderer2D OpenglES (SDL)");
    calypso_framework_sdl2_app_set_events(start,end,update,resize);
    calypso_framework_sdl2_app_run();
    #endif

   
    // We Done Baby
    return 0;
}