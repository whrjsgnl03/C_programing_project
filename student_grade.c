#include <stdio.h>
#include <stdlib.h>

#define MAX_STUDENTS 100
#define MAX_SUBJECTS 10
#define MAX_NAME_LEN 20
#define SCANF_NAME_FMT "%19s"
#define MIN_SCORE 0
#define MAX_SCORE 100
#define ERR_MSG_OUT_OF_BOUNDS "[오류] 입력값은 %d에서 %d 사이의 정수여야 합니다. 다시 입력해 주세요: "
#define ERR_MSG_INVALID_INPUT "[오류] 올바른 숫자를 입력해 주세요: "
#define FMT_HEADER_NAME "%-10s"
#define FMT_HEADER_SUBJECT " | %-10s"
#define FMT_HEADER_AVG " | %-10s\n"
#define FMT_ROW_NAME "%-10s"
#define FMT_ROW_SCORE " | %3d점 (%c)"
#define FMT_ROW_AVG " | %5.1f점 (%c)\n"

/**
 * @brief Represents a student's grades and average scores.
 * Structure alignment is optimized to minimize padding (88 bytes -> 80 bytes).
 */
typedef struct {
    double average;            ///< Student's average score (8 bytes)
    int scores[MAX_SUBJECTS];  ///< Array of scores for each subject (40 bytes)
    char name[MAX_NAME_LEN];   ///< Student's name (20 bytes)
    char grades[MAX_SUBJECTS]; ///< Array of letter grades for each subject (10 bytes)
    char averageGrade;         ///< Letter grade for the average score (1 byte)
    // 1-byte padding is automatically inserted by the compiler for alignment
} Student;

/**
 * @brief Calculates the letter grade based on a numeric score.
 * 
 * @param score The numeric grade value.
 * @return char The calculated letter grade ('A', 'B', 'C', 'D', or 'E').
 */
char calculateGrade(const double score);

/**
 * @brief Clears the standard input buffer to discard trailing characters.
 */
void clearInputBuffer(void);

/**
 * @brief Safely reads an integer from standard input within a specified range.
 * 
 * @param min The minimum acceptable value.
 * @param max The maximum acceptable value.
 * @return int The validated integer read from the user.
 */
int getSafeInt(const int min, const int max);

int main(void) {
    char subjects[MAX_SUBJECTS][MAX_NAME_LEN];

    printf("과목 수 입력 (최대 %d): ", MAX_SUBJECTS);
    const int subjectCount = getSafeInt(1, MAX_SUBJECTS);

    for (int subjectIdx = 0; subjectIdx < subjectCount; subjectIdx++) {
        printf("%d번째 과목명 입력: ", subjectIdx + 1);
        scanf(SCANF_NAME_FMT, subjects[subjectIdx]);
        clearInputBuffer();
    }
    printf("\n");
    
    printf("학생 수 입력 (최대 %d): ", MAX_STUDENTS);
    const int studentCount = getSafeInt(1, MAX_STUDENTS);
    printf("\n");

    Student list[MAX_STUDENTS] = {0};

    // --- 1. 학생 정보 입력 및 계산 처리 (포인터 적용) ---
    for (int studentIdx = 0; studentIdx < studentCount; studentIdx++) {
        Student * const s = &list[studentIdx]; // 현재 학생의 주소를 포인터에 저장
        
        printf("[%d번째 학생]\n", studentIdx + 1);
        printf("이름: ");
        scanf(SCANF_NAME_FMT, s->name); // '.' 대신 '->' 사용
        clearInputBuffer();
        
        int sum = 0;
        for (int subjectIdx = 0; subjectIdx < subjectCount; subjectIdx++) {
            printf("%s 점수 입력: ", subjects[subjectIdx]);
            s->scores[subjectIdx] = getSafeInt(MIN_SCORE, MAX_SCORE);
            s->grades[subjectIdx] = calculateGrade((double)s->scores[subjectIdx]);
            sum += s->scores[subjectIdx];
        }
        s->average = (double)sum / (double)subjectCount;
        s->averageGrade = calculateGrade(s->average);
        printf("\n");
    }

    printf("--- 결과 ---\n");
    printf(FMT_HEADER_NAME, "이름");
    for (int subjectIdx = 0; subjectIdx < subjectCount; subjectIdx++) {
        printf(FMT_HEADER_SUBJECT, subjects[subjectIdx]);
    }
    printf(FMT_HEADER_AVG, "평균");
   
    // --- 2. 결과 출력 처리 (포인터 적용) ---
    for (int studentIdx = 0; studentIdx < studentCount; studentIdx++) {
        const Student * const s = &list[studentIdx]; // 출력할 학생의 주소를 const 포인터에 저장 (Read-only 명시)
        
        printf(FMT_ROW_NAME, s->name);
        for (int subjectIdx = 0; subjectIdx < subjectCount; subjectIdx++) {
            printf(FMT_ROW_SCORE, s->scores[subjectIdx], s->grades[subjectIdx]);
        }
        printf(FMT_ROW_AVG, s->average, s->averageGrade);
    }

    return EXIT_SUCCESS;
}

char calculateGrade(const double score) {
    if (score >= 90.0) {
        return 'A';
    }
    if (score >= 80.0) {
        return 'B';
    }
    if (score >= 70.0) {
        return 'C';
    }
    if (score >= 60.0) {
        return 'D';
    }
    return 'E';
}

void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Discard characters
    }
}

int getSafeInt(const int min, const int max) {
    int value;
    for (;;) {
        if (scanf("%d", &value) == 1) {
            if (value >= min && value <= max) {
                clearInputBuffer();
                return value;
            }
            printf(ERR_MSG_OUT_OF_BOUNDS, min, max);
        } else {
            printf(ERR_MSG_INVALID_INPUT);
            clearInputBuffer();
        }
    }
}