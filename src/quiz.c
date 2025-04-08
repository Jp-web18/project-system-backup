#include "config.h"



void view_take_quizzes() {
    system(CLEAR);  // Use platform-independent CLEAR macro defined in config.h

    DIR *d;
    struct dirent *dir;
    int quiz_count = 0;

    d = opendir("quizzes");
    if (d) {
        printf("Available Quizzes:\n\n");
        while ((dir = readdir(d)) != NULL) {
            if (strstr(dir->d_name, ".quiz")) {
                printf("[%d] %s\n", ++quiz_count, dir->d_name);
            }
        }
        closedir(d);
    }

    if (quiz_count == 0) {
        printf("No quizzes made yet.\n");
        sleep(2);
        return;
    }

    int choice;
    printf("\n[1] Take a quiz\n[2] Back to main menu\nEnter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        take_quiz();
    }
}

void take_quiz() {
    char filename[100];
    char student_name[100], section[20], pc_number[10];
    char quizname[100];

    printf("Enter quiz filename (without .quiz): ");
    scanf("%s", quizname);

    snprintf(filename, sizeof(filename), "quizzes/%s.quiz", quizname);

    // Check if the quiz file exists
    if (!file_exists(filename)) {
        printf("Quiz not found.\n");
        sleep(2);
        return;
    }

    char record_file[128];
    snprintf(record_file, sizeof(record_file), "records/%s_%s.rec", quizname, getenv("USER"));

    // Check if the student has already taken the quiz
    if (file_exists(record_file)) {
        printf("You have already taken this quiz. Not allowed to take twice.\n");
        sleep(2);
        return;
    }

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Unable to open quiz");
        return;
    }

    int duration, items, score = 0;
    char correct_answers[100], user_answers[100];

    // Read quiz details
    fscanf(fp, "%d\n%d\n%s", &duration, &items, correct_answers);
    fclose(fp);

    printf("Time Duration: %d minutes\n", duration);
    printf("Enter your name: ");
    scanf(" %[^\n]", student_name);
    printf("Enter your section code: ");
    scanf("%s", section);
    printf("Enter your PC number: ");
    scanf("%s", pc_number);

    for (int i = 0; i < items; i++) {
        printf("Question #%d answer: ", i + 1);
        scanf(" %c", &user_answers[i]);
    }
    user_answers[items] = '\0';

    printf("Are you finish answering the quiz? [1] Yes [2] No: ");
    int done;
    scanf("%d", &done);
    if (done != 1) return;

    // Calculate the score
    for (int i = 0; i < items; i++) {
        if (user_answers[i] == correct_answers[i]) score++;
    }

    float percentage = ((float)score / items) * 100;

    // Save the result to a record file
    FILE *rec = fopen(record_file, "w");
    fprintf(rec, "Name: %s\nSection: %s\nPC: %s\nScore: %d/%d\nPercent: %.2f%%\n",
            student_name, section, pc_number, score, items, percentage);
    fprintf(rec, "Answers: %s\nCorrect: %s\n", user_answers, correct_answers);
    fclose(rec);
    chmod(record_file, 0444); // Make the record file read-only

    printf("Quiz submitted. Score: %d/%d (%.2f%%)\n", score, items, percentage);
    sleep(2);
}
