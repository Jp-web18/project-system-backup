#include "config.h"


void displayStudentData() {
    StudentResult results[MAX_STUDENTS];
    int numResults = 0;

    loadStudentResults(results, &numResults);

    printf("\n" COLOR_CYAN "Students Data:\n" COLOR_RESET);
    if (numResults > 0) {
        printf("%-20s %-20s %-10s %-15s\n", "Students name", "Quiz name", "Score", "Date");
        printf("-------------------- -------------------- ---------- ----------------\n");
        for (int i = 0; i < numResults; i++) {
            printf("%-20s %-20s %d/%d       %-15s\n",
                   results[i].name,
                   results[i].quizName,
                   results[i].score,
                   results[i].totalItems,
                   results[i].submissionDate);
        }
    } else {
        printf(COLOR_YELLOW "No student data available yet.\n" COLOR_RESET);
    }
}