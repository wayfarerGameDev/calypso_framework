#pragma once

inline int calypso_framework_math_min_i(const int a, const int b)
{
    if (a < b) return a; 
    return b;
}

inline int calypso_framework_math_max_i(const int a, const int b)
{
    if (a > b) return a;
    return b;
}