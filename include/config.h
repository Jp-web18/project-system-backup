#ifndef CONFIG_H
#define CONFIG_H

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>
#include <sys/stat.h>

#endif
