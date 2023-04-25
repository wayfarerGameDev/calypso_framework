// Includes
#include <stdio.h>      // rand
#include <stdlib.h>     // rand
#include <stdint.h>     // uint8_t
#include <time.h>       // time

#include "calypso_framework/calypso_framework_app_glfw.c"
#include "calypso_framework/calypso_framework_renderer_2d_opengl.c"

void start()
{
    
}

void end()
{

}

void update()
{
     int* c = malloc(100000 * sizeof(int));
     free(c);
}

int main(int argc, char** argv)
{
    calypso_framework_app_glfw_init_with_opengl(3,3,2);
    calypso_framework_app_glfw_set_events(start,end,update);
    calypso_framework_app_glfw_run();
    return 0;
}