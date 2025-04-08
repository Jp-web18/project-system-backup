#include "config.h"


#define MAX_AVAILABLE_QUIZZES 10

void takeQuizMenu() {
    int choice;

    do {
        printf("\n" COLOR_CYAN "Take Quizzes\n" COLOR_RESET);
        displayAvailableQuizzes();
        printf("[1] Take a quiz\n");
        printf("[2] Back to main menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline

        switch (choice) {
            case 1: {
                char filename[MAX_FILENAME_LENGTH];
                printf("Enter the filename of the quiz you want to take (without extension): ");
                fgets(filename, MAX_FILENAME_LENGTH, stdin);
                filename[strcspn(filename, "\n")] = 0;
                char fullFilename[MAX_FILENAME_LENGTH + 6];
                sprintf(fullFilename, "%s%s", filename, QUIZ_FILE_EXTENSION); // Now QUIZ_FILE_EXTENSION is recognized
                takeSelectedQuiz(fullFilename);
                break;
            }
            case 2:
                printf("Returning to main menu.\n");
                break;
            default:
                printf(COLOR_RED "Invalid choice. Please try again.\n" COLOR_RESET);
        }
    } while (choice != 2);
}

void displayAvailableQuizzes() {
    // In a real system, you would scan a directory for .quiz files.
    // For this simplified example, we'll just inform the user how to proceed.
    printf("Available quizzes (enter filename without extension to take):\n");
    printf(COLOR_YELLOW "Note: Quiz filenames are not listed automatically in this version.\n"
                   "You need to know the filename of the quiz you want to take.\n" COLOR_RESET);
    // If you want to implement automatic listing, you'd use directory traversal here.
}

void takeSelectedQuiz(const char *filename) {
    Quiz currentQuiz;
    FILE *fp = fopen(filename, "rb");

    if (fp == NULL) {
        printf(COLOR_RED "Error: Quiz file '%s' not found.\n" COLOR_RESET, filename);
        return;
    }

    fread(&currentQuiz, sizeof(Quiz), 1, fp);
    fclose(fp);

    char studentName[MAX_STUDENT_NAME_LENGTH];
    char section[MAX_SECTION_LENGTH];
    int pcNumber;

    printf("\n" COLOR_MAGENTA "Starting Quiz: %s\n" COLOR_RESET, currentQuiz.name);
    printf("Duration: %d minutes\n", currentQuiz.duration);

    printf("Enter your name: ");
    fgets(studentName, MAX_STUDENT_NAME_LENGTH, stdin);
    studentName[strcspn(studentName, "\n")] = 0;

    printf("Enter your section code: ");
    fgets(section, MAX_SECTION_LENGTH, stdin);
    section[strcspn(section, "\n")] = 0;

    printf("Enter your PC number: ");
    scanf("%d", &pcNumber);
    getchar(); // Consume newline

    if (hasStudentTakenQuiz(studentName, currentQuiz.name)) {
        printf(COLOR_RED "Error: You are not allowed to take this quiz again.\n" COLOR_RESET);
        return;
    }

    char answers[MAX_ITEMS][MAX_ANSWER_LENGTH];
    int score = 0;
    time_t startTime = time(NULL);
    time_t endTime = startTime + (currentQuiz.duration * 60); // Convert minutes to seconds

    printf("\n" COLOR_BLUE "Answer the following questions:\n" COLOR_RESET);
    for (int i = 0; i < currentQuiz.numItems; i++) {
        time_t currentTime = time(NULL);
        if (currentTime >= endTime) {
            printf(COLOR_YELLOW "\nTime's up!\n" COLOR_RESET);
            break;
        }
        printf("(%d/%d) %s\nYour answer: ", i + 1, currentQuiz.numItems, currentQuiz.items[i].question);
        fgets(answers[i], MAX_ANSWER_LENGTH, stdin);
        answers[i][strcspn(answers[i], "\n")] = 0;

        if (strcmp(answers[i], currentQuiz.items[i].correctAnswer) == 0) {
            score++;
        }

        if (i < currentQuiz.numItems - 1) {
            char finishChoice[10];
            printf("Are you finish answering the quiz? (yes/no): ");
            fgets(finishChoice, sizeof(finishChoice), stdin);
            finishChoice[strcspn(finishChoice, "\n")] = 0;
            if (strcmp(finishChoice, "yes") == 0 || strcmp(finishChoice, "YES") == 0) {
                printf(COLOR_YELLOW "Quiz ended early by student.\n" COLOR_RESET);
                break; // Exit the question loop
            }
        }
    }

    // After the quiz (either finished all questions or time's up)
    time_t now = time(NULL);
    struct tm *tm_now = localtime(&now);
    char dateTimeStr[20];
    strftime(dateTimeStr, sizeof(dateTimeStr), "%Y-%m-%d %H:%M:%S", tm_now);

    StudentResult result;
    strcpy(result.name, studentName);
    strcpy(result.section, section);
    result.pcNumber = pcNumber;
    strcpy(result.quizName, currentQuiz.name);
    result.score = score;
    result.totalItems = currentQuiz.numItems;
    strcpy(result.submissionDate, dateTimeStr);

    saveStudentResult(&result);
    printf(COLOR_GREEN "\nQuiz finished. Your score: %d/%d (%.2f%%)\n" COLOR_RESET,
           score, currentQuiz.numItems, (float)score / currentQuiz.numItems * 100);
} // Added the missing closing curly brace here