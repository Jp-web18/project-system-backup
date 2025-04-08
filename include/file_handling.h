#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H


// Structure to represent a quiz item
typedef struct {
    char question[MAX_QUESTION_LENGTH];
    char correctAnswer[MAX_ANSWER_LENGTH];
} QuizItem;

// Structure to represent a quiz
typedef struct {
    char filename[MAX_FILENAME_LENGTH];
    char name[MAX_QUIZ_NAME_LENGTH];
    int duration; // in minutes
    int numItems;
    QuizItem items[MAX_ITEMS];
} Quiz;

// Structure to represent a student's result
typedef struct {
    char name[MAX_STUDENT_NAME_LENGTH];
    char section[MAX_SECTION_LENGTH];
    int pcNumber;
    char quizName[MAX_QUIZ_NAME_LENGTH];
    int score;
    int totalItems;
    char submissionDate[20]; // e.g., "YYYY-MM-DD HH:MM:SS"
} StudentResult;

// Function prototypes for file handling
int saveQuiz(Quiz *quiz);
int loadQuizzes(Quiz quizzes[], int *numQuizzes);
int saveStudentResult(StudentResult *result);
int loadStudentResults(StudentResult results[], int *numResults);
int hasStudentTakenQuiz(const char *studentName, const char *quizName);

#endif