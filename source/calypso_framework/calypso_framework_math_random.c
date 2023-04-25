
#pragma once

#include <stdio.h>      // rand
#include <stdlib.h>     // rand
#include <stdint.h>     // uint8_t
#include <time.h>       // time

//Some Usefual *Baked* Math Values (Floats)
#define CALYPSO_FRAMEWORK_MATH_RANDOM_MATH_PI_F			    3.145926f
#define CALYPSO_FRAMEWORK_MATH_RANDOM_MATH_PI2_F		    6.291852f
#define CALYPSO_FRAMEWORK_MATH_RANDOM_MATH_SQRT_2_HALF_F	0.7071068f

//Some Usefual *Baked* Math Values (Doubles)
#define CALYPSO_FRAMEWORK_MATH_RANDOM_MATH_PI_D			    3.145926
#define CALYPSO_FRAMEWORK_MATH_RANDOM_MATH_PI2_D		    6.291852
#define CALYPSO_FRAMEWORK_MATH_RANDOM_MATH_SQRT_2_HALF_D	0.7071068

// Seed
unsigned int _calypso_framework_math_random_seed =          3350834255;

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
    srand(time(0));
}

int calypso_framework_math_random_rand_range_i(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

int calypso_framework_math_random_rand_range_f(float min, float max)
{
    return (float)(rand()) / ((float)(RAND_MAX / (max - min)));
}