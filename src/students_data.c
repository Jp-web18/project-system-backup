#include "config.h"



void view_student_data() {
    system(CLEAR);

    DIR *d = opendir("records");
    struct dirent *dir;

    if (!d) {
        printf("No student records found.\n");
        sleep(2);
        return;
    }

    printf("%-20s %-20s %-10s %-10s\n", "Student Name", "Quiz Name", "Score", "Date");
    printf("-------------------- -------------------- ---------- ----------\n");

    while ((dir = readdir(d)) != NULL) {
        if (strstr(dir->d_name, ".rec")) {
            char filepath[256];
            snprintf(filepath, sizeof(filepath), "records/%s", dir->d_name);
            FILE *fp = fopen(filepath, "r");

            if (!fp) continue;

            char line[100];
            char name[100] = "";
            char section[50] = "";
            char pc[50] = "";
            char score_str[20] = "";
            char file_date[11] = ""; // To store the extracted date
            char quiz[50] = "";
            int score_val, total_items;

            if (fgets(line, sizeof(line), fp)) sscanf(line, "Name: %99[^\n]", name);
            if (fgets(line, sizeof(line), fp)) sscanf(line, "Section: %49[^\n]", section);
            if (fgets(line, sizeof(line), fp)) sscanf(line, "PC: %49[^\n]", pc);
            if (fgets(line, sizeof(line), fp)) sscanf(line, "Score: %d/%d %10[^\n]", &score_val, &total_items, file_date);

            sscanf(dir->d_name, "%[^_]", quiz);
            snprintf(score_str, sizeof(score_str), "%d/%d", score_val, total_items); // Reformat score

            printf("%-20s %-20s %-10s %-10s\n", name, quiz, score_str, file_date);

            fclose(fp);
        }
    }

    closedir(d);
    printf("\n");
    printf("Press Enter to go back to the main menu...\n");
    getchar();
}