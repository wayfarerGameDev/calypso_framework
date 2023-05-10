
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Calypso (Logging)
#define CALYPSO_FRAMEWORK_LOG_MESSAGE_ENABLED
#include "../calypso_framework_misc/calypso_framework_log.c"

// Calypso (SDL or GLFW)
#define USE_GLFW_OVER_SDL 1
#if(USE_GLFW_OVER_SDL)
#include "../calypso_framework_glfw/calypso_framework_glfw_app.c"
#include "../calypso_framework_glfw/calypso_framework_glfw_input.c"
#else
#include "../calypso_framework_sdl2/calypso_framework_sdl2_app.c"
#include "../calypso_framework_sdl2/calypso_framework_sdl2_input.c"
#endif

// Calypso (IO)
#include "../calypso_framework_io/calypso_framework_io_file.c"
#include "../calypso_framework_io/calypso_framework_io_tga.c"

// Calypso (Math)
#include "../calypso_framework_math/calypso_framework_math_colors.c"
#include "../calypso_framework_math/calypso_framework_math_matrix4.c"
#include "../calypso_framework_math/calypso_framework_math_random.c"

// Calypso (Render Modules)
#define CALYPSO_FRAMEWORK_OPENGL_ES_SHADER_DEBUGGING_ENABLED
#include "../calypso_framework_render_modules/calypso_framework_render_module_opengl_es_core.c"
#include "../calypso_framework_render_modules/calypso_framework_render_module_opengl_es_quad.c"
#include "../calypso_framework_render_modules/calypso_framework_render_module_opengl_es_shader.c"
#include "../calypso_framework_render_modules/calypso_framework_render_module_opengl_es_texture.c"
#include "../calypso_framework_render_modules/calypso_framework_render_module_opengl_es_pixel_buffer.c"

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
calypso_framework_render_module_opengl_es_quad_batch_t _renderer_quad_batch_textured_a;
calypso_framework_render_module_opengl_es_quad_batch_t _renderer_quad_batch_textured_b;
calypso_framework_renderer_pixel_opengl_es_pixel_buffer_t _renderer_pixel_buffer;
int _renderer_pixel_buffer_x = 1024;
int _renderer_pixel_buffer_y = 1024;

// TGA File
unsigned int _texture_a;
unsigned int _texture_b;

// Colors
const unsigned char* _c_color_white_array = _calypso_framework_math_colors_color_rgba_white;
const unsigned char* _c_color_red_array = _calypso_framework_math_colors_color_rgba_red;
const unsigned char* _c_color_yellow_array = _calypso_framework_math_colors_color_rgba_yellow;


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
        // Init OpenGL
        calypso_framework_render_module_opengl_es_core_init(calypso_framework_glfw_app_get_open_gl_proc_address());
        calypso_framework_renderer_pixel_opengl_es_init(_renderer_pixel_buffer_x,_renderer_pixel_buffer_y);

        // Default Shader Program (Batched)
        _renderer_default_shader_batched_program = calypso_framework_render_module_opengl_es_quad_create_default_shader_program_batched_quad_textured(calypso_framework_render_module_opengl_es_shader_create_shader);
       
        // Default Shader Program (Immediate)
        _renderer_default_shader_immediate_program = calypso_framework_render_module_opengl_es_quad_create_default_shader_program_quad_immediate(calypso_framework_render_module_opengl_es_shader_create_shader);
        calypso_framework_render_module_opengl_es_shader_set_current_shader_program(_renderer_default_shader_immediate_program);
        calypso_framework_render_module_opengl_es_shader_set_current_shader_program_parameter_vec4_f("color_in",_c_color_white_array[0] / 255, _c_color_white_array[1] / 255, _c_color_white_array[2] / 255, _c_color_white_array[3] / 255);
    
        // Pixel Buffer
        calypso_framework_renderer_pixel_opengl_es_create_pixel_buffer(&_renderer_pixel_buffer,_renderer_pixel_buffer_x,_renderer_pixel_buffer_y);
    }

    // Create render Quad (Immediate)
    calypso_framework_render_module_opengl_es_quad_build_quad_immediate();

    // Create Render Quad (Batched)
    {
        // A
        _renderer_quad_batch_textured_a = calypso_framework_render_module_opengl_es_quad_create_quad_batch_textured();
        calypso_framework_render_module_opengl_es_quad_set_quad_batch_data_zeroed_textured(&_renderer_quad_batch_textured_a);

        // B
        _renderer_quad_batch_textured_b = calypso_framework_render_module_opengl_es_quad_create_quad_batch_textured();
        calypso_framework_render_module_opengl_es_quad_set_quad_batch_data_zeroed_textured(&_renderer_quad_batch_textured_b);

        // Randomize
        {
            // Cache Max/Min Width/Height
            const int max_width = ((int)_renderer_viewport_width) * 0.0425f;
            const int min_width = -max_width;
            const int max_height = ((int)_renderer_viewport_height) * 0.0425f;
            const int min_height = -max_height;

            // Set Batch Data (A)
            float position[3] = {0,0,0};
            float color[4] = {0,0,0,1};
            float scale = 1;
            calypso_framework_random_rand_set_seed_as_time();
            for (int i = 0; i < CALYPSO_FRAMEWORK_RENDER_MODULE_OPENGL_ES_QUAD_QUAD_BATCH_INSTANCE_MAX_COUNT; i++)
            {
                position[0] = calypso_framework_math_random_rand_range_i(min_width,max_width);
                position[1] = calypso_framework_math_random_rand_range_i(min_height,max_height);
                position[2] = calypso_framework_math_random_rand_range_i(1,9);
                color[0] = calypso_framework_math_random_rand_range_f(10,255) / 255.0f;
                color[1] = calypso_framework_math_random_rand_range_f(10,255) / 255.0f;
                color[2] = calypso_framework_math_random_rand_range_f(10,255) / 255.0f;
                color[3] = 255.0f;
                scale = calypso_framework_math_random_rand_range_f(1,4);

                calypso_framework_render_module_opengl_es_quad_set_quad_batch_instance_data_transform_textured(&_renderer_quad_batch_textured_a,i,position,scale);
                calypso_framework_render_module_opengl_es_quad_set_quad_batch_instance_data_color_textured(&_renderer_quad_batch_textured_a,i,color);
                // calypso_framework_render_module_opengl_es_quad_set_quad_batch_instance_data_texture_index_textured(&_renderer_quad_batch_textured_a,i,i%2 ? 0 : 1);
            }
            calypso_framework_render_module_opengl_es_quad_build_quad_batch_textured(&_renderer_quad_batch_textured_a);

             // Set Batch Data (B)
            calypso_framework_random_rand_set_seed_as_time();
            for (int i = 0; i < 250; i++)
            {
                position[0] = calypso_framework_math_random_rand_range_i(min_width,max_width);
                position[1] = calypso_framework_math_random_rand_range_i(min_height,max_height);
                position[2] = calypso_framework_math_random_rand_range_i(1,9);
                color[0] = calypso_framework_math_random_rand_range_f(10,255) / 255.0f;
                color[1] = calypso_framework_math_random_rand_range_f(10,255) / 255.0f;
                color[2] = calypso_framework_math_random_rand_range_f(10,255) / 255.0f;
                color[3] = 255;

                calypso_framework_render_module_opengl_es_quad_set_quad_batch_instance_data_transform_textured(&_renderer_quad_batch_textured_b,i,position,4);
                calypso_framework_render_module_opengl_es_quad_set_quad_batch_instance_data_color_textured(&_renderer_quad_batch_textured_b,i,color);
                // calypso_framework_render_module_opengl_es_quad_set_quad_batch_instance_data_texture_index_textured(&_renderer_quad_batch_textured_b,i,i%2 ? 0 : 1);
            }
            calypso_framework_render_module_opengl_es_quad_build_quad_batch_textured(&_renderer_quad_batch_textured_b);
        }
    }

    // Load TGA (Test)
    {
        // A
        int image_width, image_height, image_column_count;
        unsigned char* image_data = stbi_load("content/testbed/test.tga",&image_width,&image_height,&image_column_count,0);
        _texture_a = calypso_framework_render_module_opengl_es_shader_create_texture_2d_bgra(image_data,image_width,image_height);
        free(image_data);

        // B
        image_data = stbi_load("content/testbed/test.png",&image_width,&image_height,&image_column_count,0);
        _texture_b = calypso_framework_render_module_opengl_es_shader_create_texture_2d_bgra(image_data,image_width,image_height);
        free(image_data);
    }
}

void end(void)
{    
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
        calypso_framework_math_matrix4_build_projection_ortho_matrix_f(0,_renderer_viewport_width,0,_renderer_viewport_height,-100,100,_renderer_viewport_projection_matrix);
        calypso_framework_math_matrix4_build_identity_matrix_f(_renderer_view_matrix);
        calypso_framework_math_matrix4_modify_scale_f(_renderer_viewport_scale_x,_renderer_viewport_scale_y,1,_renderer_view_matrix);
        calypso_framework_math_matrix4_modify_position_f(_renderer_viewport_position_x,_renderer_viewport_position_y,0,_renderer_view_matrix);
        calypso_framework_math_matrix4_modify_mult_f(_renderer_viewport_projection_matrix,_renderer_view_matrix,_renderer_projection_view_matrix);
    }

    // Render (Start)
    {        
        // Render Start
        calypso_framework_render_module_opengl_es_core_set_clear_color(10,10,10,255); // Don't need to  do this every frame but why not
        calypso_framework_render_module_opengl_es_core_clear();
    }

    // Render (Pixel Buffer)
    {
        for (int x = 0; x < _renderer_pixel_buffer_x; x++)
            for (int y = 0; y < _renderer_pixel_buffer_y; y++)
                calypso_framework_renderer_pixel_opengl_es_set_pixel_buffer_pixel(&_renderer_pixel_buffer,x,y,calypso_framework_math_random_rand() % 255,calypso_framework_math_random_rand() % 255,calypso_framework_math_random_rand() % 255, 255);
    
        // Render
        calypso_framework_renderer_pixel_opengl_es_render_pixel_buffer(&_renderer_pixel_buffer,1);        
    }

    // Render (Quad Batched)
    {
        calypso_framework_math_matrix4_build_identity_matrix_f(_renderer_model_matrix);
        calypso_framework_math_matrix4_modify_scale_f(50,50,1,_renderer_model_matrix);
        calypso_framework_math_matrix4_modify_position_f(0,0,0,_renderer_model_matrix);

        // A
        {
            // Bind Textures
            calypso_framework_render_module_opengl_es_shader_bind_texture_2d(_texture_a,0);

            // Update Shader Program
            calypso_framework_render_module_opengl_es_shader_set_current_shader_program(_renderer_default_shader_batched_program);
            calypso_framework_render_module_opengl_es_shader_set_current_shader_program_parameter_matrix4_f("projection_view_in",_renderer_projection_view_matrix[0],0); // Apply Viewport Projection And View
            calypso_framework_render_module_opengl_es_shader_set_current_shader_program_parameter_matrix4_f("model_in",_renderer_model_matrix[0],0); // Apply Transform
            calypso_framework_render_module_opengl_es_shader_set_current_shader_program_parameter_i("u_texture",0);

            // Render
            calypso_framework_render_module_opengl_es_quad_render_quad_batched_textured(&_renderer_quad_batch_textured_a);

            // Unbind Texture
            calypso_framework_render_module_opengl_es_shader_unbind_texture_2d();
        }

        // B
        {
            // Bind Textures
            calypso_framework_render_module_opengl_es_shader_bind_texture_2d(_texture_b,0);

            // Update Shader Program
            calypso_framework_render_module_opengl_es_shader_set_current_shader_program(_renderer_default_shader_batched_program);
            calypso_framework_render_module_opengl_es_shader_set_current_shader_program_parameter_matrix4_f("projection_view_in",_renderer_projection_view_matrix[0],0); // Apply Viewport Projection And View
            calypso_framework_render_module_opengl_es_shader_set_current_shader_program_parameter_matrix4_f("model_in",_renderer_model_matrix[0],0); // Apply Transform
            calypso_framework_render_module_opengl_es_shader_set_current_shader_program_parameter_i("u_texture",0);

            // Render
            calypso_framework_render_module_opengl_es_quad_render_quad_batched_textured(&_renderer_quad_batch_textured_b);

            // Unbind Texture
            calypso_framework_render_module_opengl_es_shader_unbind_texture_2d();
        }
    }

    // Render(Quad Immediate)
    {
        // Entity (Red)
        {
            // Model Matrix
            calypso_framework_math_matrix4_build_identity_matrix_f(_renderer_model_matrix);
            calypso_framework_math_matrix4_modify_scale_f(100,100,1,_renderer_model_matrix);
            calypso_framework_math_matrix4_modify_position_f(0,0,10,_renderer_model_matrix);

            // Update Shader Program
            calypso_framework_render_module_opengl_es_shader_set_current_shader_program(_renderer_default_shader_immediate_program);
            calypso_framework_render_module_opengl_es_shader_set_current_shader_program_parameter_matrix4_f("projection_view_in",_renderer_projection_view_matrix[0],0); // Apply Viewport Projection And View
            calypso_framework_render_module_opengl_es_shader_set_current_shader_program_parameter_vec4_f("color_in",_c_color_red_array[0] / 255, _c_color_red_array[1] / 255, _c_color_red_array[2] / 255, _c_color_red_array[3] / 255);
            calypso_framework_render_module_opengl_es_shader_set_current_shader_program_parameter_matrix4_f("model_in",_renderer_model_matrix[0],0); // Apply Transform

            // Render
            calypso_framework_render_module_opengl_es_quad_render_quad_immediate();
        }

        // Entity (Yellow)
        {
            // Model Matrix
            calypso_framework_math_matrix4_build_identity_matrix_f(_renderer_model_matrix);
            calypso_framework_math_matrix4_modify_scale_f(50,50,1,_renderer_model_matrix);
            calypso_framework_math_matrix4_modify_position_f(100,100,20,_renderer_model_matrix);

            // Update Shader Program
            calypso_framework_render_module_opengl_es_shader_set_current_shader_program(_renderer_default_shader_immediate_program);
            calypso_framework_render_module_opengl_es_shader_set_current_shader_program_parameter_matrix4_f("projection_view_in",_renderer_projection_view_matrix[0],0); // Apply Viewport Projection And View
            calypso_framework_render_module_opengl_es_shader_set_current_shader_program_parameter_vec4_f("color_in",_c_color_yellow_array[0] / 255, _c_color_yellow_array[1] / 255, _c_color_yellow_array[2] / 255, _c_color_yellow_array[3] / 255);
            calypso_framework_render_module_opengl_es_shader_set_current_shader_program_parameter_matrix4_f("model_in",_renderer_model_matrix[0],0); // Apply Transform
    
            // Render
            calypso_framework_render_module_opengl_es_quad_render_quad_immediate();
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

    calypso_framework_render_module_opengl_es_core_set_viewport(_renderer_viewport_width,_renderer_viewport_height);
}

int main(int argc, char** argv)
{
    // App (GLFW)
    #if(USE_GLFW_OVER_SDL)
    calypso_framework_glfw_app_init_with_opengl(CALYPSO_FRAMEWORK_RENDER_MODULE_OPENGL_ES_BOOTSTRAP_MAJOR_VERSION,CALYPSO_FRAMEWORK_RENDER_MODULE_OPENGL_ES_BOOTSTRAP_MINOR_VERSION,CALYPSO_FRAMEWORK_RENDER_MODULE_OPENGL_ES_BOOTSTRAP_CONTEXT_PROFILE);
    calypso_framework_glfw_app_set_title("Testbed : Renderer OpenglES (GLFW)");
    calypso_framework_glfw_app_set_events(start,end,update,resize);
    calypso_framework_glfw_app_set_window_resizable(1);
    calypso_framework_glfw_app_run();
    
    #else
    // App (SDL)
    calypso_framework_sdl2_app_init_with_opengl(CALYPSO_FRAMEWORK_RENDER_MODULE_OPENGL_ES_BOOTSTRAP_MAJOR_VERSION,CALYPSO_FRAMEWORK_RENDER_MODULE_OPENGL_ES_BOOTSTRAP_MINOR_VERSION,CALYPSO_FRAMEWORK_RENDER_MODULE_OPENGL_ES_BOOTSTRAP_CONTEXT_PROFILE);
    calypso_framework_sdl2_app_set_title("Testbed : Renderer2D OpenglES (SDL)");
    calypso_framework_sdl2_app_set_events(start,end,update,resize);
    calypso_framework_sdl2_app_run();
    #endif

   
    // We Done Baby
    return 0;
}