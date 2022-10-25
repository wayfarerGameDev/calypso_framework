// Includes
#include "calypso_framework_app_sdl.c"

void start()
{
}

void end()
{

}

void update(float delta_time)
{
}

int main(int argc, char** argv)
{
    // Setup And Run App
    calypso_framework_app_sdl_init();
    calypso_framework_app_sdl_add_start_system(start);
    calypso_framework_app_sdl_add_end_system(end);
    calypso_framework_app_sdl_add_update_system(update);
    calypso_framework_app_sdl_run();

    // No Longer Running
    return 0;
}