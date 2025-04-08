#include "config.h"


void makeQuizMenu() {
    int choice;

    do {
        printf("\n" COLOR_CYAN "Make a quiz\n" COLOR_RESET);
        printf("[1] Make another quiz\n");
        printf("[2] Edit existing quizzes (Not implemented yet)\n");
        printf("[3] Back to main menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline

        switch (choice) {
            case 1:
                createNewQuiz();
                break;
            case 2:
                printf(COLOR_YELLOW "Editing quizzes is not implemented yet.\n" COLOR_RESET);
                break;
            case 3:
                printf("Returning to main menu.\n");
                break;
            default:
                printf(COLOR_RED "Invalid choice. Please try again.\n" COLOR_RESET);
        }
    } while (choice != 3);
}

void createNewQuiz() {
    Quiz newQuiz;
    int i;
    int done = 0;

    printf("\n" COLOR_YELLOW "Set up your new quiz:\n" COLOR_RESET);

    printf("Enter the filename for this quiz (without extension): ");
    fgets(newQuiz.filename, MAX_FILENAME_LENGTH, stdin);
    newQuiz.filename[strcspn(newQuiz.filename, "\n")] = 0; // Remove trailing newline

    printf("Enter the name of the quiz: ");
    fgets(newQuiz.name, MAX_QUIZ_NAME_LENGTH, stdin);
    newQuiz.name[strcspn(newQuiz.name, "\n")] = 0;

    printf("Enter the time duration of the quiz in minutes: ");
    scanf("%d", &newQuiz.duration);
    getchar(); // Consume newline

    printf("Enter the number of items in the quiz: ");
    scanf("%d", &newQuiz.numItems);
    getchar(); // Consume newline

    if (newQuiz.numItems > MAX_ITEMS) {
        printf(COLOR_RED "Error: Maximum number of items exceeded.\n" COLOR_RESET);
        return;
    }

    printf("\n" COLOR_GREEN "Enter the questions and correct answers:\n" COLOR_RESET);
    for (i = 0; i < newQuiz.numItems; i++) {
        printf("Question %d: ", i + 1);
        fgets(newQuiz.items[i].question, MAX_QUESTION_LENGTH, stdin);
        newQuiz.items[i].question[strcspn(newQuiz.items[i].question, "\n")] = 0;

        printf("Correct Answer for Question %d: ", i + 1);
        fgets(newQuiz.items[i].correctAnswer, MAX_ANSWER_LENGTH, stdin);
        newQuiz.items[i].correctAnswer[strcspn(newQuiz.items[i].correctAnswer, "\n")] = 0;
    }

    do {
        int choice;
        printf("\nAre you done making the quiz?\n");
        printf("[1] Yes\n");
        printf("[2] No (You will be prompted for questions again)\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline

        if (choice == 1) {
            if (saveQuiz(&newQuiz)) {
                printf(COLOR_GREEN "Quiz '%s' saved successfully as '%s.quiz'.\n" COLOR_RESET, newQuiz.name, newQuiz.filename);
            } else {
                printf(COLOR_RED "Error saving the quiz.\n" COLOR_RESET);
            }
            done = 1;
        } else if (choice == 2) {
            printf(COLOR_YELLOW "You will be prompted to re-enter the quiz details.\n" COLOR_RESET);
            // In a more advanced system, you might allow editing. For simplicity, we restart.
            createNewQuiz();
            return; // Exit this call to createNewQuiz
        } else {
            printf(COLOR_RED "Invalid choice. Please try again.\n" COLOR_RESET);
        }
    } while (!done);
}

void editExistingQuizzes() {
    printf(COLOR_YELLOW "This functionality is not implemented yet.\n" COLOR_RESET);
}