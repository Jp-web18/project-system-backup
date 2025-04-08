#include "config.h"
#include "make_quiz.h"
#include "quiz.h"
#include "students_data.h"

int main() {
    int choice;

    while (1) {
        system(CLEAR); // or "cls" on Windows
        printf("\033[1;34mWelcome to the QuizWhiz System\033[0m\n\n");
        printf("[1] Make a Quiz\n");
        printf("[2] View and Take Quizes\n");
        printf("[3] View student's data\n");
        printf("[4] Exit the system\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                make_quiz_menu();
                break;
            case 2:
                view_take_quizzes();
                break;
            case 3:
                view_student_data();
                break;
            case 4:
                printf("Exiting the system...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
                sleep(1);
        }
    }

    return 0;
}
