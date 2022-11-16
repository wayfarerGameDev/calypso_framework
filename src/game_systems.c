#pragma once

#include "game_includes.c"

// Logging Callback
typedef void (*game_systems_log_callback_t)(const char* log_msg, const Uint8 log_type);

// System
typedef void (*game_systems_system_t)(void);

// System Stages
#define GAME_SYSTEMS_SYSTEM_STAGE_DISABLED                 CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STATE_DISABLED      
#define GAME_SYSTEMS_SYSTEM_STAGE_ENABLED                  CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STATE_ENABLED       
#define GAME_SYSTEMS_SYSTEM_STAGE_ONESHOT                  CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STATE_ONESHOT       
#define GAME_SYSTEMS_SYSTEM_STAGE_EARLY_STARTUP            CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STAGE_EARLY_STARTUP 
#define GAME_SYSTEMS_SYSTEM_STAGE_LATE_STARTUP             CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STAGE_LATE_STARTUP  
#define GAME_SYSTEMS_SYSTEM_STAGE_STARTUP                  CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STAGE_STARTUP       
#define GAME_SYSTEMS_SYSTEM_STAGE_EARLY_SHUTDOWN           CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STAGE_EARLY_SHUTDOWN
#define GAME_SYSTEMS_SYSTEM_STAGE_LATE_SHUTDOWN            CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STAGE_LATE_SHUTDOWN 
#define GAME_SYSTEMS_SYSTEM_STAGE_SHUTDOWN                 CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STAGE_SHUTDOWN      
#define GAME_SYSTEMS_SYSTEM_STAGE_EARLY_UPDATE             CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STAGE_EARLY_UPDATE  
#define GAME_SYSTEMS_SYSTEM_STAGE_LATE_UPDATE              CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STAGE_LATE_UPDATE   
#define GAME_SYSTEMS_SYSTEM_STAGE_UPDATE                   CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STAGE_UPDATE

/**
* \brief Set system's log callback
* \return void
*/
void game_systems_set_log_callback(game_systems_log_callback_t log_callback)
{
    calypso_framework_systems_set_log_callback(log_callback);
}

/**
* \brief Enable system
* \param system void function with no paramaters
*/
void game_systems_enable_system(game_systems_system_t system)
{
    calypso_framework_systems_enable_system(system);
}

/**
* \brief Disable system
* \param system void function with no paramaters
*/
void game_systems_disable_system(game_systems_system_t system)
{
    calypso_framework_systems_disable_system(system);
}

/**
* \brief Oneshot system
* \param system void function with no paramaters
*/
void game_systems_one_shot_system(game_systems_system_t system)
{
    calypso_framework_systems_one_shot_system(system);
}

/**
* \brief Add system
* \param system void function with no paramaters
* \param system_stage int
* \return void
*/
void game_systems_add_system(game_systems_system_t system, int system_stage)
{
   calypso_framework_systems_add_system(system,system_stage);
}

/**
* \brief Add app system that is disabled
* \param system void function with no paramaters
* \param system_stage int
* \return void
*/
void game_systems_add_system_disabled(game_systems_system_t system, int system_stage)
{
   calypso_framework_systems_add_system_disabled(system,system_stage);
}

/**
* \brief Add app system that is to play once and than disable
* \param system void function with no paramaters
* \param system_stage int
* \return void
*/
void game_systems_add_system_one_shot(game_systems_system_t system, int system_stage)
{
    calypso_framework_systems_add_system_one_shot(system,system_stage);
}

/**
* \brief Do startup statge systems
* \return void
*/
void game_systems_do_startup_stage_systems()
{
    calypso_framework_systems_do_startup_stage_systems();
}

/**
* \brief Do startup shutdown systems
* \return void
*/
void game_systems_do_shutdown_stage_systems()
{
    calypso_framework_systems_do_shutdown_stage_systems();
}

/**
* \brief Do startup statge systems
* \return void
*/
void game_systems_do_update_stage_systems()
{
    calypso_framework_systems_do_update_stage_systems();
}