#pragma once

// Inclues
#include <stdbool.h> // bool

// Logging Callback
typedef void (*calypso_framework_entities_simple_log_callback_t)(const char* log_msg, const Uint8 log_type);
calypso_framework_entities_simple_log_callback_t _calypso_framework_entities_simple_log_callback;

// State
#define CALYPSO_FRAMEWORK_ENTITIES_SIMPLE_STATE_NULL         0
#define CALYPSO_FRAMEWORK_ENTITIES_SIMPLE_STATE_INIT         1
unsigned int _calypso_framework_entities_simple_state =      CALYPSO_FRAMEWORK_ENTITIES_SIMPLE_STATE_NULL;

// Entities (Count)
unsigned int* _calypso_framework_entities_simple_entity_count_max_ptr;
unsigned int* _calypso_framework_entities_simple_entity_count_current_ptr;

// Entities (Pool)
unsigned int* _calypso_framework_entities_simple_entity_pool_array;
unsigned int* _calypso_framework_entities_simple_entity_pool_array_count_current;

/**
* \brief Set enties simple log callback
* \return void
*/
void calypso_framework_entities_simple_set_log_callback(calypso_framework_entities_simple_log_callback_t log_callback)
{
    _calypso_framework_entities_simple_log_callback = log_callback;
}

/**
* \brief Do app's log callback
* \return void
*/
void calypso_framework_entities_simple_do_log_callback(const char* log_msg, const Uint8 log_type)
{
    if (_calypso_framework_entities_simple_log_callback != NULL)
        _calypso_framework_app_sdl_log_callback(log_msg,log_type);
}

/**
* \brief Init entities lite
* \return void
*/
void calypso_framework_entities_simple_init(const unsigned int entity_count_max)
{
    // Count Max
    void *memory = malloc(sizeof(int));
    _calypso_framework_entities_simple_entity_count_max_ptr =  (unsigned int*)memory;
    *_calypso_framework_entities_simple_entity_count_max_ptr = entity_count_max;

    // Count Current
     void *memory_b = malloc(sizeof(int));
    _calypso_framework_entities_simple_entity_count_current_ptr =  (unsigned int*)memory_b;
    *_calypso_framework_entities_simple_entity_count_current_ptr = 0;

    _calypso_framework_entities_simple_entity_pool_array = malloc(entity_count_max * sizeof(int));
    void *memory_c = malloc(sizeof(int));
    _calypso_framework_entities_simple_entity_pool_array_count_current =  (unsigned int*)memory_c;
    *_calypso_framework_entities_simple_entity_pool_array_count_current = 0;
}

/**
* \brief Get entity count current as ptr
* \return void
*/
unsigned int* calypso_framework_entities_simple_get_entity_count_current_ptr()
{
    return _calypso_framework_entities_simple_entity_count_current_ptr;
}

/**
* \brief Get entity count current as ptr
* \return void
*/
unsigned int* calypso_framework_entities_simple_get_entity_count_max_ptr()
{
    return _calypso_framework_entities_simple_entity_count_max_ptr;
}

/**
* \brief Get entities lite count max
* \return unsigned int : entity_count_max
*/
unsigned int calypso_framework_entities_simple_get_entity_count_max()
{
    return *_calypso_framework_entities_simple_entity_count_max_ptr;
}

/**
* \brief Get entities lite count current
* \return unsigned int : entity_count_current
*/
unsigned int calypso_framework_entities_simple_get_entity_count_current()
{
    return *_calypso_framework_entities_simple_entity_count_current_ptr;
}

/**
* \brief Create entity data bool array
* \return void
*/
bool* calypso_framework_entities_simple_register_component_bool(bool* array, const bool default_value)
{
    const int count = *_calypso_framework_entities_simple_entity_count_max_ptr;
    array = malloc(count * sizeof(bool));
    for (int i = 0; i < count; i++)
        array[i] = default_value;
    return array;
}

/**
* \brief Create entity data int array
* \return void
*/
int* calypso_framework_entities_simple_register_component_int(int* array, const int default_value)
{
    const int count = *_calypso_framework_entities_simple_entity_count_max_ptr;
    array = malloc(count * sizeof(int));
    for (int i = 0; i < count; i++)
        array[i] = default_value;  
    return array;
}

/**
* \brief Create entity data float array
* \return void
*/
float* calypso_framework_entities_simple_register_component_float(float* array, const float default_value)
{
    const int count = *_calypso_framework_entities_simple_entity_count_max_ptr;
    array = malloc(count * sizeof(float));
    for (int i = 0; i < count; i++)
        array[i] = default_value;
    return array;
}

// Macro : Entities Component Initialize Macro
#define CALYPSO_FRAMEWORK_ENTITIES_SIMPLE_REGISTER_COMPONENT(TYPE,UID,ARRAY,DEFAULT_VALUE) do\
{\
    unsigned int entity_count = *_calypso_framework_entities_simple_entity_count_max_ptr;\
    ARRAY = (TYPE*)malloc(entity_count * sizeof(TYPE));\
    for (int i = 0; i < entity_count; i++)\
        ARRAY[i] = DEFAULT_VALUE;\
} while (0)