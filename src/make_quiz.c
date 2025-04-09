#include "config.h"



void make_quiz_menu() {
    int choice;

    while (1) {
        system(CLEAR); 
        printf("Make a quiz\n\n");
        printf("[1] Make another quiz\n");
        printf("[2] Edit existing quizzes\n");
        printf("[3] Back to main menu\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // Clear the newline character from the input buffer

        switch (choice) {
            case 1:
                create_new_quiz();
                break;
            case 2:
                edit_existing_quiz();
                break;
            case 3:
                return;
            default:
                printf("Invalid choice. Try again.\n");
                sleep(1);
        }
    }
}

void create_new_quiz() {
    char filename[100];
    int num_items, duration;
    char correct_answers[100];
    FILE *quiz_file;  // Declare quiz_file variable here

    printf("Enter quiz file name: ");
    scanf("%s", filename);

    // Ensure the quizzes directory exists
    // For Windows, check if the directory exists using GetFileAttributes
    if (access("quizzes", F_OK) == -1) {
        // Directory does not exist, try to create it
        if (mkdir("quizzes") != 0) {
            perror("Failed to create quizzes directory");
            return;
        }
    }

    // Check if file already exists
    quiz_file = fopen(filename, "r");
    if (quiz_file) {
        printf("Quiz file already exists. Do you want to overwrite it? (y/n): ");
        char choice;
        scanf(" %c", &choice);  // Notice the space before %c to avoid input buffer issues
        if (choice != 'y' && choice != 'Y') {
            printf("Quiz not saved.\n");
            fclose(quiz_file);
            return;  // Abort saving the quiz
        }
        fclose(quiz_file);  // Close file after checking
    }

    printf("Enter time duration in minutes: ");
    scanf("%d", &duration);

    printf("Enter number of items: ");
    scanf("%d", &num_items);

    printf("Enter correct answers (no spaces, %d characters): ", num_items);
    scanf("%s", correct_answers);

    // Validate that the number of correct answers matches the number of items
    if ((int)strlen(correct_answers) != num_items) {
        printf("Error: The number of correct answers must match the number of quiz items.\n");
        return;
    }

    char full_filename[128];
    snprintf(full_filename, sizeof(full_filename), "quizzes/%s.quiz", filename);

    FILE *fp = fopen(full_filename, "w");
    if (fp == NULL) {
        perror("Failed to create quiz file");
        return;
    }

    fprintf(fp, "%d\n%d\n%s\n", duration, num_items, correct_answers);
    fclose(fp);

    printf("Are you done making the quiz?\n");
    printf("[1] Yes\n[2] No\nEnter your choice: ");
    int confirm;
    scanf("%d", &confirm);
    if (confirm == 1) {
        printf("Quiz saved successfully.\n");
    } else {
        remove(full_filename);
        printf("Quiz discarded.\n");
    }

    sleep(1);
}

void edit_existing_quiz() {
    printf("Editing existing quizzes feature not implemented yet.\n");
    sleep(1);
}
