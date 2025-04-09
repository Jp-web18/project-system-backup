#include "config.h"

int main() {
    int choice;
    int running = 1; // Flag variable to control the loop

    while (running) {
        
        system(CLEAR); // or "cls" on Windows

        printf("\033[1;34mWelcome to the QuizWhiz System\033[0m\n\n");
        printf("[1] Make a Quiz\n");
        printf("[2] View student's data\n");
        printf("[3] View and Take Quizes\n");
        printf("[4] Exit the system\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume the newline character left in the buffer

        switch (choice) {
            case 1:
                make_quiz_menu();
                break;
            case 3:
                view_take_quizzes();
                break;
            case 2:
                view_student_data();
                break;
            case 4:
                printf("Exiting the system...\n");
                running = 0; // Set the flag to exit the loop
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                sleep(1);
        }
    }

    printf("Press Enter to exit...\n");
    getchar(); // Wait for user input before exiting

    return 0;
}