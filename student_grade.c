#include <stdio.h>

#define MAX_STUDENTS 100
#define MAX_SUBJECTS 10

typedef struct {
    char name[20];
    int scores[MAX_SUBJECTS];
    char grades[MAX_SUBJECTS];
    double average;
    char averageGrade;
} Student;

char calculateGrade(double score);
void clearInputBuffer(void);
int getSafeInt(int min, int max);

int main() {
    char subjects[MAX_SUBJECTS][20];
    int subjectCount;
    int studentCount;

    printf("과목 수 입력 (최대 %d): ", MAX_SUBJECTS);
    subjectCount = getSafeInt(1, MAX_SUBJECTS);

    for (int i = 0; i < subjectCount; i++) {
        printf("%d번째 과목명 입력: ", i + 1);
        scanf("%19s", subjects[i]);
        clearInputBuffer();
    }
    printf("\n");
    
    printf("학생 수 입력 (최대 %d): ", MAX_STUDENTS);
    studentCount = getSafeInt(1, MAX_STUDENTS);
    printf("\n");

    Student list[MAX_STUDENTS];

    // 1. 학생 정보 입력 및 계산 부분에 포인터 적용
    for (int i = 0; i < studentCount; i++) {
        Student *s = &list[i]; // 현재 학생의 주소를 포인터에 저장
        
        printf("[%d번째 학생]\n", i + 1);
        printf("이름: ");
        scanf("%19s", s->name); // '.' 대신 '->' 사용
        clearInputBuffer();
        
        int sum = 0;
        for (int j = 0; j < subjectCount; j++) {
            printf("%s 점수 입력: ", subjects[j]);
            s->scores[j] = getSafeInt(0, 100);
            s->grades[j] = calculateGrade((double)s->scores[j]);
            sum += s->scores[j];
        }
        s->average = (double)sum / subjectCount;
        s->averageGrade = calculateGrade(s->average);
        printf("\n");
    }

    printf("--- 결과 ---\n");
    printf("%-10s", "이름");
    for (int j = 0; j < subjectCount; j++) {
        printf(" | %-10s", subjects[j]);
    }
    printf(" | %-10s\n", "평균");
   
    // 2. 결과 출력 부분에 포인터 적용
    for (int i = 0; i < studentCount; i++) {
        Student *s = &list[i]; // 출력할 학생의 주소를 포인터에 저장
        
        printf("%-10s", s->name);
        for (int j = 0; j < subjectCount; j++) {
            printf(" | %3d점 (%c)", s->scores[j], s->grades[j]);
        }
        printf(" | %5.1f점 (%c)\n", s->average, s->averageGrade);
    }

    return 0;
}

char calculateGrade(double score) {
    if (score >= 90.0) return 'A';
    if (score >= 80.0) return 'B';
    if (score >= 70.0) return 'C';
    if (score >= 60.0) return 'D';
    return 'E';
}

void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int getSafeInt(int min, int max) {
    int value;
    while (1) {
        if (scanf("%d", &value) == 1) {
            if (value >= min && value <= max) {
                clearInputBuffer();
                return value;
            }
            printf("[오류] 입력값은 %d에서 %d 사이의 정수여야 합니다. 다시 입력해 주세요: ", min, max);
        } else {
            printf("[오류] 올바른 숫자를 입력해 주세요: ");
            clearInputBuffer();
        }
    }
}