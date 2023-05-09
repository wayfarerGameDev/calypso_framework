#pragma once

// Dependencies
#include <time.h>

//Some Usefual *Baked* Math Values (Floats)
#define CALYPSO_FRAMEWORK_MATH_RANDOM_MATH_PI_F			    3.145926f
#define CALYPSO_FRAMEWORK_MATH_RANDOM_MATH_PI2_F		    6.291852f
#define CALYPSO_FRAMEWORK_MATH_RANDOM_MATH_SQRT_2_HALF_F	0.7071068f

//Some Usefual *Baked* Math Values (Doubles)
#define CALYPSO_FRAMEWORK_MATH_RANDOM_MATH_PI_D			    3.145926
#define CALYPSO_FRAMEWORK_MATH_RANDOM_MATH_PI2_D		    6.291852
#define CALYPSO_FRAMEWORK_MATH_RANDOM_MATH_SQRT_2_HALF_D	0.7071068

// MAX | Seed | Next
#define CALYPSO_FRAMEWORK_MATH_RANDOM_RAND_MAX              32767
unsigned int _calypso_framework_math_random_seed            = 3350834255;
unsigned int _calypso_framework_math_random_next            = 1;

int calypso_framework_math_random_rand()
{
    _calypso_framework_math_random_next = _calypso_framework_math_random_next * 1103515245 + 12345;
    return (unsigned int)(_calypso_framework_math_random_next / 65536) % (CALYPSO_FRAMEWORK_MATH_RANDOM_RAND_MAX + 1);
}

void calypso_framework_math_random_srand(unsigned int seed) 
{
    _calypso_framework_math_random_next = seed;
}

void calypso_framework_math_random_rand_set_seed(const unsigned int seed)
{
    _calypso_framework_math_random_seed = seed;
}

float calypso_framework_math_random_rand_xorshift_float()
{
    int r = _calypso_framework_math_random_seed;
    r = r ^ (r << 13);
    r = r ^ (r >> 17);
    r = r ^ (r << 5);
    return (float)r;
}

double calypso_framework_math_random_rand_xorshift_double()
{
    int r = _calypso_framework_math_random_seed;
    r = r ^ (r << 13);
    r = r ^ (r >> 17);
    r = r ^ (r << 5);
    return (double)r;
}

int calypso_framework_math_random_rand_xorshift_int()
{
    int r = _calypso_framework_math_random_seed;
    r = r ^ (r << 13);
    r = r ^ (r >> 17);
    r = r ^ (r << 5);
    return r;
}

void calypso_framework_random_rand_set_seed_as_time()
{
    calypso_framework_math_random_srand(time(0));
}

int calypso_framework_math_random_rand_range_i(const int min, const int max)
{
    return (calypso_framework_math_random_rand() % (max - min + 1)) + min;
}

int calypso_framework_math_random_rand_range_f(const float min, const float max)
{
    return (float)(calypso_framework_math_random_rand()) / ((float)(CALYPSO_FRAMEWORK_MATH_RANDOM_RAND_MAX / (max - min)));
}