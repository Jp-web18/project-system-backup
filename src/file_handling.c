#include "config.h"
#include "../include/config.h"


#define QUIZ_FILE_EXTENSION ".quiz"
#define STUDENT_DATA_FILE "students_data.dat"

int saveQuiz(Quiz *quiz) {
    char fullFilename[MAX_FILENAME_LENGTH + 6]; // + extension
    sprintf(fullFilename, "%s%s", quiz->filename, QUIZ_FILE_EXTENSION);

    FILE *fp = fopen(fullFilename, "wb");
    if (fp == NULL) {
        perror("Error opening quiz file for writing");
        return 0; // Failure
    }

    fwrite(quiz, sizeof(Quiz), 1, fp);
    fclose(fp);
    return 1; // Success
}

int loadQuizzes(Quiz quizzes[], int *numQuizzes) {
    *numQuizzes = 0;
    // In a real system, you might need to scan a directory for .quiz files.
    // For this example, we'll assume quiz files are created and we'd need a way
    // to know their names to load them. This is a simplification.

    // A more robust approach would involve maintaining an index of quiz files.
    // For now, we'll leave this as a placeholder or require the user to know the filename.
    printf(COLOR_YELLOW "Warning: Quiz loading is a simplified implementation.\n" COLOR_RESET);
    return 0; // For now, no automatic loading
}

int saveStudentResult(StudentResult *result) {
    FILE *fp = fopen(STUDENT_DATA_FILE, "ab"); // Append in binary mode
    if (fp == NULL) {
        perror("Error opening student data file for writing");
        return 0; // Failure
    }

    fwrite(result, sizeof(StudentResult), 1, fp);
    fclose(fp);
    return 1; // Success
}

int loadStudentResults(StudentResult results[], int *numResults) {
    *numResults = 0;
    FILE *fp = fopen(STUDENT_DATA_FILE, "rb");
    if (fp == NULL) {
        // It's okay if the file doesn't exist yet
        return 0;
    }

    while (fread(&results[*numResults], sizeof(StudentResult), 1, fp) == 1) {
        (*numResults)++;
        if (*numResults >= MAX_STUDENTS) {
            fprintf(stderr, COLOR_RED "Warning: Maximum number of student records reached.\n" COLOR_RESET);
            break;
        }
    }

    fclose(fp);
    return 1; // Success (even if no records were loaded)
}

int hasStudentTakenQuiz(const char *studentName, const char *quizName) {
    StudentResult results[MAX_STUDENTS];
    int numResults = 0;
    loadStudentResults(results, &numResults);

    for (int i = 0; i < numResults; i++) {
        if (strcmp(results[i].name, studentName) == 0 && strcmp(results[i].quizName, quizName) == 0) {
            return 1; // Student has taken this quiz
        }
    }
    return 0; // Student has not taken this quiz
}