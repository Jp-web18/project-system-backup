#include "config.h"


int main() {
    int choice;

    printf(COLOR_CYAN "Welcome to the QuizWhiz System\n" COLOR_RESET);

    do {
        printf("\n[1] Make a Quiz\n");
        printf("[2] View and Take Quizzes\n");
        printf("[3] View student's data\n");
        printf("[4] Exit the system\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline

        switch (choice) {
            case 1:
                makeQuizMenu();
                break;
            case 2:
                takeQuizMenu();
                break;
            case 3:
                displayStudentData();
                break;
            case 4:
                printf("Exiting the QuizWhiz System. Goodbye!\n");
                break;
            default:
                printf(COLOR_RED "Invalid choice. Please try again.\n" COLOR_RESET);
        }
    } while (choice != 4);

    return 0;
}