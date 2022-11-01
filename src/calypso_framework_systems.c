/// <summary>
/// Systems module
/// </summary>

#pragma once

// Logging Callback
typedef void (*calypso_framework_systems_log_callback_t)(const char* log_msg, const Uint8 log_type);
calypso_framework_systems_log_callback_t _calypso_framework_systems_log_callback;

// Systems
#define CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STATE_DISABLED             0
#define CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STATE_ENABLED              1
#define CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STATE_ONESHOT              2
#define CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STAGE_EARLY_STARTUP        0
#define CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STAGE_LATE_STARTUP         1
#define CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STAGE_STARTUP              2
#define CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STAGE_EARLY_SHUTDOWN       3
#define CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STAGE_LATE_SHUTDOWN        4
#define CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STAGE_SHUTDOWN             5
#define CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STAGE_EARLY_UPDATE         6
#define CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STAGE_LATE_UPDATE          7
#define CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STAGE_UPDATE               8
typedef void (*calypso_framework_systems_system_t)(void);
calypso_framework_systems_system_t* _calypso_framework_systems_systems;
int* _calypso_framework_systems_system_states;
int* _calypso_framework_systems_system_stages;
unsigned int _calypso_framework_systems_system_count = 0;

/**
* \brief Set system's log callback
* \return void
*/
void calypso_framework_systems_set_log_callback(calypso_framework_systems_log_callback_t log_callback)
{
    _calypso_framework_systems_log_callback = log_callback;
}

/**
* \brief Do system's log callback
* \return void
*/
void calypso_framework_systems_do_log_callback(const char* log_msg, const Uint8 log_type)
{
    if (_calypso_framework_systems_log_callback == NULL)
        return;

    _calypso_framework_systems_log_callback(log_msg,log_type);
}

/**
* \brief Enable system
* \param system void function with no paramaters
*/
void calypso_framework_systems_enable_system(calypso_framework_systems_system_t system)
{
    for (int i = 0; i < _calypso_framework_systems_system_count; i++)
        if (_calypso_framework_systems_systems[i] == system)
        {
            _calypso_framework_systems_system_states[i] = CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STATE_ENABLED;
            return;
        }

    calypso_framework_systems_do_log_callback("App: System not enabled (no such system)",2);
}

/**
* \brief Disable system
* \param system void function with no paramaters
*/
void calypso_framework_systems_disable_system(calypso_framework_systems_system_t system)
{
    for (int i = 0; i < _calypso_framework_systems_system_count; i++)
        if (_calypso_framework_systems_systems[i] == system)
        {
            _calypso_framework_systems_system_states[i] = CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STATE_DISABLED;
            return;
        }

    calypso_framework_systems_do_log_callback("App: System not disabled (no such system)",2);
}

/**
* \brief Oneshot system
* \param system void function with no paramaters
*/
void calypso_framework_systems_one_shot_system(calypso_framework_systems_system_t system)
{
    for (int i = 0; i < _calypso_framework_systems_system_count; i++)
        if (_calypso_framework_systems_systems[i] == system)
        {
            _calypso_framework_systems_system_states[i] = CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STATE_ONESHOT;
            return;
        }
}

/**
* \brief Add system
* \param system void function with no paramaters
* \param system_stage CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_APP_STAGE_EARLY_STARTUP || 0 : late startup
* \param system_stage CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_APP_STAGE_LATE_STARTUP || 1 : early startup
* \param system_stage CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_APP_STAGE_STARTUP || 2 : start
* \param system_stage CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_APP_STAGE_EARLY_SHUTDOWN || 3 : late shutdown
* \param system_stage CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_APP_STAGE_LATE_SHUTDOWN || 4 : early shutdown
* \param system_stage CALYPSO_FclsRAMEWORK_SYSTEMS_SYSTEM_APP_STAGE_SHUTDOWN || 5 : shutdown
* \param system_stage CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_APP_STAGE_EARLY_UPDATE || 6 : early update
* \param system_stage CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_APP_STAGE_LATE_UPDATE || 7 : late update
* \param system_stage CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_APP_STAGE_UPDATE || 8 : update
* \return void
*/
void calypso_framework_systems_add_system(calypso_framework_systems_system_t system, int system_stage)
{
    // Not Valid Group
    if (system_stage < 0 || system_stage > 8)
    {
        calypso_framework_systems_do_log_callback("App: Failed to add system (invalid system_stage)\n",3);
        return;
    }

    // Already Added
    for (int i = 0; i < _calypso_framework_systems_system_count; i++)
    {
        if (_calypso_framework_systems_systems[i] == system)
        {
            calypso_framework_systems_do_log_callback("App: Failed to add system (system already added)\n",2);
            return;
        }
    }

    // Add System
    _calypso_framework_systems_system_count++;
    _calypso_framework_systems_systems = realloc(_calypso_framework_systems_systems,_calypso_framework_systems_system_count* sizeof(calypso_framework_systems_system_t));
    _calypso_framework_systems_system_states = realloc(_calypso_framework_systems_system_states,_calypso_framework_systems_system_count* sizeof(int));
    _calypso_framework_systems_system_stages = realloc(_calypso_framework_systems_system_stages,_calypso_framework_systems_system_count* sizeof(int));
    _calypso_framework_systems_systems[_calypso_framework_systems_system_count - 1] = system;
    _calypso_framework_systems_system_states[_calypso_framework_systems_system_count - 1] = CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STATE_ENABLED;
    _calypso_framework_systems_system_stages[_calypso_framework_systems_system_count - 1] = system_stage;
    
}

/**
* \brief Add app system that is disabled
* \param system void function with no paramaters
* \param system_stage CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_APP_STAGE_EARLY_STARTUP || 0 : late startup
* \param system_stage CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_APP_STAGE_LATE_STARTUP || 1 : early startup
* \param system_stage CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_APP_STAGE_STARTUP || 2 : start
* \param system_stage CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_APP_STAGE_EARLY_SHUTDOWN || 3 : late shutdown
* \param system_stage CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_APP_STAGE_LATE_SHUTDOWN || 4 : early shutdown
* \param system_stage CALYPSO_FclsRAMEWORK_SYSTEMS_SYSTEM_APP_STAGE_SHUTDOWN || 5 : shutdown
* \param system_stage CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_APP_STAGE_EARLY_UPDATE || 6 : early update
* \param system_stage CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_APP_STAGE_LATE_UPDATE || 7 : late update
* \param system_stage CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_APP_STAGE_UPDATE || 8 : update
* \return void
*/
void calypso_framework_systems_add_system_disabled(calypso_framework_systems_system_t system, int system_stage)
{
    calypso_framework_systems_add_system(system,system_stage);
    calypso_framework_systems_disable_system(system);
}

/**
* \brief Add app system that is to play once and than disable
* \param system void function with no paramaters
* \param system_stage CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_APP_STAGE_EARLY_STARTUP || 0 : late startup
* \param system_stage CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_APP_STAGE_LATE_STARTUP || 1 : early startup
* \param system_stage CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_APP_STAGE_STARTUP || 2 : start
* \param system_stage CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_APP_STAGE_EARLY_SHUTDOWN || 3 : late shutdown
* \param system_stage CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_APP_STAGE_LATE_SHUTDOWN || 4 : early shutdown
* \param system_stage CALYPSO_FclsRAMEWORK_SYSTEMS_SYSTEM_APP_STAGE_SHUTDOWN || 5 : shutdown
* \param system_stage CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_APP_STAGE_EARLY_UPDATE || 6 : early update
* \param system_stage CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_APP_STAGE_LATE_UPDATE || 7 : late update
* \param system_stage CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_APP_STAGE_UPDATE || 8 : update
* \return void
*/
void calypso_framework_systems_add_system_one_shot(calypso_framework_systems_system_t system, int system_stage)
{
    calypso_framework_systems_add_system(system,system_stage);
    calypso_framework_systems_one_shot_system(system);
}

void calypso_framework_systems_do_startup_stage_systems()
{
     // Run Early Startup App Stage Systems
    for (int i = 0; i < _calypso_framework_systems_system_count; i++)
        if (_calypso_framework_systems_system_states[i] != CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STATE_DISABLED)
            if (_calypso_framework_systems_system_stages[i] == CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STAGE_EARLY_STARTUP)
            {
                if (_calypso_framework_systems_system_states[i] == CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STATE_ONESHOT)
                    _calypso_framework_systems_system_states[i] = CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STATE_DISABLED;

                _calypso_framework_systems_systems[i]();
            }
            
    // Run Startup App Stage Systems
    for (int i = 0; i < _calypso_framework_systems_system_count; i++)
        if (_calypso_framework_systems_system_states[i] != CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STATE_DISABLED)
            if (_calypso_framework_systems_system_stages[i] == CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STAGE_STARTUP)
            {
                if (_calypso_framework_systems_system_states[i] == CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STATE_ONESHOT)
                    _calypso_framework_systems_system_states[i] = CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STATE_DISABLED;

                _calypso_framework_systems_systems[i]();
            }

    // Run Late Startup App Stage Systems
    for (int i = 0; i < _calypso_framework_systems_system_count; i++)
        if (_calypso_framework_systems_system_states[i] != CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STATE_DISABLED)
            if (_calypso_framework_systems_system_stages[i] == CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STAGE_LATE_STARTUP)
            {
                if (_calypso_framework_systems_system_states[i] == CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STATE_ONESHOT)
                    _calypso_framework_systems_system_states[i] = CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STATE_DISABLED;

                _calypso_framework_systems_systems[i]();
            }
}

void calypso_framework_systems_do_shutdown_stage_systems()
{
     // Run Early Startup App Stage Systems
    for (int i = 0; i < _calypso_framework_systems_system_count; i++)
        if (_calypso_framework_systems_system_states[i] != CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STATE_DISABLED)
            if (_calypso_framework_systems_system_stages[i] == CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STAGE_EARLY_SHUTDOWN)
            {
                if (_calypso_framework_systems_system_states[i] == CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STATE_ONESHOT)
                    _calypso_framework_systems_system_states[i] = CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STATE_DISABLED;

                _calypso_framework_systems_systems[i]();
            }
            
    // Run Startup App Stage Systems
    for (int i = 0; i < _calypso_framework_systems_system_count; i++)
        if (_calypso_framework_systems_system_states[i] != CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STATE_DISABLED)
            if (_calypso_framework_systems_system_stages[i] == CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STAGE_SHUTDOWN)
            {
                if (_calypso_framework_systems_system_states[i] == CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STATE_ONESHOT)
                    _calypso_framework_systems_system_states[i] = CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STATE_DISABLED;

                _calypso_framework_systems_systems[i]();
            }

    // Run Late Startup App Stage Systems
    for (int i = 0; i < _calypso_framework_systems_system_count; i++)
        if (_calypso_framework_systems_system_states[i] != CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STATE_DISABLED)
            if (_calypso_framework_systems_system_stages[i] == CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STAGE_LATE_SHUTDOWN)
            {
                if (_calypso_framework_systems_system_states[i] == CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STATE_ONESHOT)
                    _calypso_framework_systems_system_states[i] = CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STATE_DISABLED;

                _calypso_framework_systems_systems[i]();
            }
}

void calypso_framework_systems_do_update_stage_systems()
{
     // Run Early Startup App Stage Systems
    for (int i = 0; i < _calypso_framework_systems_system_count; i++)
        if (_calypso_framework_systems_system_states[i] != CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STATE_DISABLED)
            if (_calypso_framework_systems_system_stages[i] == CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STAGE_EARLY_UPDATE)
            {
                if (_calypso_framework_systems_system_states[i] == CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STATE_ONESHOT)
                    _calypso_framework_systems_system_states[i] = CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STATE_DISABLED;

                _calypso_framework_systems_systems[i]();
            }
            
    // Run Startup App Stage Systems
    for (int i = 0; i < _calypso_framework_systems_system_count; i++)
        if (_calypso_framework_systems_system_states[i] != CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STATE_DISABLED)
            if (_calypso_framework_systems_system_stages[i] == CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STAGE_UPDATE)
            {
                if (_calypso_framework_systems_system_states[i] == CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STATE_ONESHOT)
                    _calypso_framework_systems_system_states[i] = CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STATE_DISABLED;

                _calypso_framework_systems_systems[i]();
            }

    // Run Late Startup App Stage Systems
    for (int i = 0; i < _calypso_framework_systems_system_count; i++)
        if (_calypso_framework_systems_system_states[i] != CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STATE_DISABLED)
            if (_calypso_framework_systems_system_stages[i] == CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STAGE_LATE_UPDATE)
            {
                if (_calypso_framework_systems_system_states[i] == CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STATE_ONESHOT)
                    _calypso_framework_systems_system_states[i] = CALYPSO_FRAMEWORK_SYSTEMS_SYSTEM_STATE_DISABLED;

                _calypso_framework_systems_systems[i]();
            }
}