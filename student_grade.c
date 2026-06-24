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

int main() {
    char subjects[MAX_SUBJECTS][20];
    int subjectCount;
    int studentCount;

    printf("과목 수 입력 (최대 %d): ", MAX_SUBJECTS);
    scanf("%d", &subjectCount);
    if (subjectCount > MAX_SUBJECTS) {
        subjectCount = MAX_SUBJECTS;
    }
    if (subjectCount <= 0) {
        printf("잘못된 과목 수입니다.\n");
        return 1;
    }

    for (int i = 0; i < subjectCount; i++) {
        printf("%d번째 과목명 입력: ", i + 1);
        scanf("%19s", subjects[i]);
        clearInputBuffer();
    }
    printf("\n");
    
    printf("학생 수 입력 (최대 %d): ", MAX_STUDENTS);
    scanf("%d", &studentCount);
    if (studentCount > MAX_STUDENTS) {
        studentCount = MAX_STUDENTS;
    }
    if (studentCount <= 0) {
        printf("잘못된 학생 수입니다.\n");
        return 1;
    }
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
            while (1) {
                printf("%s 점수 입력: ", subjects[j]);
                scanf("%d", &s->scores[j]);
                if (s->scores[j] >= 0 && s->scores[j] <= 100) {
                    break;
                }
                printf("[오류] 점수는 0점 이상 100점 이하여야 합니다. 다시 입력해 주세요.\n");
            }
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