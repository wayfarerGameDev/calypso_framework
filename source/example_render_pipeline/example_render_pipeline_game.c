#pragma once

#include "example_render_pipeline.c"

example_render_pipeline_texture_t _example_renderer_pipeline_game_texture;

void example_render_pipeline_game_start(void)
{
    // Load Content
    _example_renderer_pipeline_game_texture = example_render_pipeline_load_texture_file_tga("content/testbed/test.tga");
}

void example_render_pipeline_game_end(void)
{

}

void example_render_pipeline_game_update(void)
{

}

void example_render_pipeline_game_draw_world(void)
{
    // Render Quads (Immediate)
    {
        // Cadet Blue
        example_render_pipeline_set_render_color_hex(_calypso_framework_math_colors_color_hex_cadet_blue);
        example_render_pipeline_set_render_scale(100,100);
        example_render_pipeline_render_quad_immediate(100,100,20);

        // Cyan
        example_render_pipeline_set_render_color_hex(_calypso_framework_math_colors_color_hex_cyan);
        example_render_pipeline_set_render_scale(50,50);
        example_render_pipeline_render_quad_immediate(200,100,25);
    }

    // Render Quads (Immediate)(Wireframe)
    {
        // Enable Wireframe
        example_render_pipeline_set_wireframe_mode(1);

        // Cadet Blue
        example_render_pipeline_set_render_color_hex(_calypso_framework_math_colors_color_hex_white);
        example_render_pipeline_set_render_scale(100,100);
        example_render_pipeline_render_quad_immediate(100,100,20 + 1);

        // Cyan
        example_render_pipeline_set_render_color_hex(_calypso_framework_math_colors_color_hex_white);
        example_render_pipeline_set_render_scale(50,50);
        example_render_pipeline_render_quad_immediate(200,100,25 + 1);

        // Disable Wireframe
        example_render_pipeline_set_wireframe_mode(0);
    }

    // Render Quads (Batched)
    {
        // Bind Texture
        example_render_pipeline_bind_texture(&_example_renderer_pipeline_game_texture,0);

        // Unbind Texture
        example_render_pipeline_unbind_texture();
    }
}

void example_render_pipeline_game_draw_screen(void)
{   
}