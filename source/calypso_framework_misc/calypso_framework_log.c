#pragma once

#define CALYPSO_FRAMEWORK_LOG_MESSAGE(log_category, log_message, log_type) \
do {                                                                       \
        /* Set Print Color (Log Type) */                                   \
        if (log_type == 1)                                                 \
            printf("\033[0;32m");                                          \
        else if (log_type == 2)                                            \
            printf("\033[33m");                                            \
        else if (log_type == 3)                                            \
            printf("\033[0;31m");                                          \
        else                                                               \
            printf("\033[0;00m");                                          \
                                                                           \
        /* Log*/                                                           \
        printf(log_category);                                              \
        printf(" : ");                                                     \
        printf(log_message);                                               \
        printf("\n");                                                      \
                                                                           \
        /* Set Print Color (White) */                                      \
        printf("\033[0;00m");                                              \
} while(0)