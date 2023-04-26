// /// <summary>
// /// Input module that uses GLFW as a base
// /// </summary>

// #pragma once

// // Includes
// #include <dependencies/GLFW/glfw3.h>

// // Input States
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_INPUT_STATE_UP                      0b00000000
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_INPUT_STATE_DOWN                    0b00000001
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_INPUT_STATE_PRESSED                 0b00000010
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_INPUT_STATE_RELEASED                0b00000011

// // Input Keys (Keyboard)(Arrows)
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_LEFT                        GLFW_SCANCODE_LEFT
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_RIGHT                       GLFW_SCANCODE_RIGHT
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_UP                          GLFW_SCANCODE_UP
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_DOWN                        GLFW_SCANCODE_DOWN

// // Input Keys (Keyboard)(Numbers)
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_0                           GLFW_SCANCODE_0
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_1                           GLFW_SCANCODE_1
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_2                           GLFW_SCANCODE_2
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_3                           GLFW_SCANCODE_3
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_4                           GLFW_SCANCODE_4
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_5                           GLFW_SCANCODE_5  
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_6                           GLFW_SCANCODE_6
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_7                           GLFW_SCANCODE_7
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_8                           GLFW_SCANCODE_8
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_9                           GLFW_SCANCODE_9

// // Input Keys (Keyboard)(Keypad Numbers)
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_KEYPAD_0                    GLFW_SCANCODE_KP_0
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_KEYPAD_00                   GLFW_SCANCODE_KP_00
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_KEYPAD_000                  GLFW_SCANCODE_KP_000
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_KEYPAD_1                    GLFW_SCANCODE_KP_1
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_KEYPAD_2                    GLFW_SCANCODE_KP_2
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_KEYPAD_3                    GLFW_SCANCODE_KP_3
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_KEYPAD_4                    GLFW_SCANCODE_KP_4
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_KEYPAD_5                    GLFW_SCANCODE_KP_5  
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_KEYPAD_6                    GLFW_SCANCODE_KP_6
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_KEYPAD_7                    GLFW_SCANCODE_KP_7
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_KEYPAD_8                    GLFW_SCANCODE_KP_8
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_KEYPAD_9                    GLFW_SCANCODE_KP_9

// // Input Keys (Keyboard)(Alphabet)
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_A                           GLFW_SCANCODE_A
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_B                           GLFW_SCANCODE_B
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_C                           GLFW_SCANCODE_C
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_D                           GLFW_SCANCODE_D
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_E                           GLFW_SCANCODE_E  
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_F                           GLFW_SCANCODE_F
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_G                           GLFW_SCANCODE_G
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_H                           GLFW_SCANCODE_H
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_I                           GLFW_SCANCODE_I
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_J                           GLFW_SCANCODE_J
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_K                           GLFW_SCANCODE_K
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_L                           GLFW_SCANCODE_L
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_M                           GLFW_SCANCODE_M
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_N                           GLFW_SCANCODE_N
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_O                           GLFW_SCANCODE_O
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_P                           GLFW_SCANCODE_P
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_Q                           GLFW_SCANCODE_Q
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_R                           GLFW_SCANCODE_R
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_S                           GLFW_SCANCODE_S
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_T                           GLFW_SCANCODE_T
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_U                           GLFW_SCANCODE_U
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_V                           GLFW_SCANCODE_V
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_W                           GLFW_SCANCODE_W
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_X                           GLFW_SCANCODE_X
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_Y                           GLFW_SCANCODE_Y
// #define CALYPSO_FRAMEWORK_INPUT_GLFW_KEYCODE_Z                           GLFW_SCANCODE_Z

// // State
// uint8_t _calypso_framework_input_glfw_keycode_state_array[255]; // glfw HAS 255 KEYS

// /**
// * \brief Show mouse cursor
// * \return void
// */
// void calypso_framework_input_glfw_show_mouse_cursor(void) 
// {
//     //glfw_ShowCursor(glfw_ENABLE);
// }

// /**
// * \brief Hide mouse cursor
// * \return void
// */
// void calypso_framework_input_glfw_hide_mouse_cursor(void) 
// {
//     //glfw_ShowCursor(glfw_DISABLE);
// }

// /**
// * \brief Get mouse cursor xy as float
// * \return void
// */
// void calypso_framework_input_glfw_get_mouse_cursor_xy_f(float* x, float* y) 
// {
//     int x_i;
//     int y_i;
//     //glfw_GetMouseState(&x_i,&y_i);
//     *x = x_i;
//     *y = y_i;
// }

// /**
// * \brief Get mouse cursor xy as double
// * \return void
// */
// void calypso_framework_input_glfw_get_mouse_cursor_xy_d(double* x, double* y) 
// {
//     int x_i;
//     int y_i;
//     //glfw_GetMouseState(&x_i,&y_i);
//     *x = (double)x_i;
//     *y = (double)y_i;
// }

// /**
// * \brief Updates input
// * \return void
// */
// void calypso_framework_input_glfw_update() 
// {
//     const uint8_t* keyboard_state = glfw_GetKeyboardState(NULL);

//     for (int i = 0; i < 255; i++)
//     {
//         int keyboard_state = glfwGetKey(window, GLFW_KEY_E);
//         if (keyboard_state)
//         {
//             if (_calypso_framework_input_glfw_keycode_state_array[i] != CALYPSO_FRAMEWORK_INPUT_GLFW_INPUT_STATE_UP)
//                 _calypso_framework_input_glfw_keycode_state_array[i] = CALYPSO_FRAMEWORK_INPUT_GLFW_INPUT_STATE_DOWN;
//             else 
//                  _calypso_framework_input_glfw_keycode_state_array[i] = CALYPSO_FRAMEWORK_INPUT_GLFW_INPUT_STATE_PRESSED;
//         }
//         else
//         {
//             if (_calypso_framework_input_glfw_keycode_state_array[i] != CALYPSO_FRAMEWORK_INPUT_GLFW_INPUT_STATE_DOWN && _calypso_framework_input_glfw_keycode_state_array[i] != CALYPSO_FRAMEWORK_INPUT_GLFW_INPUT_STATE_PRESSED)
//                 _calypso_framework_input_glfw_keycode_state_array[i] = CALYPSO_FRAMEWORK_INPUT_GLFW_INPUT_STATE_UP;
//             else
//                 _calypso_framework_input_glfw_keycode_state_array[i] = CALYPSO_FRAMEWORK_INPUT_GLFW_INPUT_STATE_RELEASED;
//         }
//     }
// }

// /**
// * \brief Get key up
// * \param key_code uint8_t
// * \return int
// */
// int calypso_framework_input_glfw_get_key_up(const uint8_t key_code) 
// {
//     return _calypso_framework_input_glfw_keycode_state_array[key_code] == CALYPSO_FRAMEWORK_INPUT_GLFW_INPUT_STATE_UP;
// }

// /**
// * \brief Get key down
// * \param key_code uint8_t
// * \return int
// */
// int calypso_framework_input_glfw_get_key_down(const uint8_t key_code) 
// {
//     return _calypso_framework_input_glfw_keycode_state_array[key_code] == CALYPSO_FRAMEWORK_INPUT_GLFW_INPUT_STATE_DOWN;
// }

// /**
// * \brief Get key pressed
// * \param key_code uint8_t
// * \return int
// */
// int calypso_framework_input_glfw_get_key_pressed(const uint8_t key_code) 
// {
//     return _calypso_framework_input_glfw_keycode_state_array[key_code] == CALYPSO_FRAMEWORK_INPUT_GLFW_INPUT_STATE_PRESSED;
// }

// /**
// * \brief Get key released
// * \param key_code uint8_t
// * \return int
// */
// int calypso_framework_input_glfw_get_key_released(const uint8_t key_code) 
// {
//     return _calypso_framework_input_glfw_keycode_state_array[key_code] == CALYPSO_FRAMEWORK_INPUT_GLFW_INPUT_STATE_RELEASED;
// }