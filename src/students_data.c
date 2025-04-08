#include "config.h"
#include "students_data.h"

void view_student_data() {
    system(CLEAR);

    DIR *d = opendir("records");
    struct dirent *dir;

    if (!d) {
        printf("No student records found.\n");
        sleep(2);
        return;
    }

    printf("Students name\tQuiz name\tScore\tDate\n");

    while ((dir = readdir(d)) != NULL) {
        if (strstr(dir->d_name, ".rec")) {
            char filepath[256];
            snprintf(filepath, sizeof(filepath), "records/%s", dir->d_name);
            FILE *fp = fopen(filepath, "r");

            if (!fp) continue;

            char name[100], section[50], pc[50], score[20];
            fgets(name, sizeof(name), fp);
            fgets(section, sizeof(section), fp);
            fgets(pc, sizeof(pc), fp);
            fgets(score, sizeof(score), fp);

            char quiz[50];
            sscanf(dir->d_name, "%[^_]", quiz);
            printf("%s\t%s\t%s", strtok(name + 6, "\n"), quiz, score + 7);

            fclose(fp);
        }
    }

    closedir(d);
    printf("\n");
    getchar(); getchar(); // Pause
}
