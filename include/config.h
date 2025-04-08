#ifndef CONFIG_H
#define CONFIG_H




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <dirent.h> // For listing files (if you implement automatic loading)


#include "file_handling.h"
#include "make_quiz.h"
#include "quiz.h"
#include "students_data.h"
#include "config.h"

// ANSI escape codes for font colors (optional, for better UI)
#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_WHITE   "\033[37m"

#define MAX_FILENAME_LENGTH 50
#define MAX_QUIZ_NAME_LENGTH 100
#define MAX_QUESTION_LENGTH 200
#define MAX_ANSWER_LENGTH 50
#define MAX_STUDENT_NAME_LENGTH 100
#define MAX_SECTION_LENGTH 10
#define MAX_ITEMS 100 // Maximum number of quiz items
#define MAX_STUDENTS 100 // Maximum number of students to store data for

#endif