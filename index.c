#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_SUBJECTS 6

typedef struct {
    char name[50];
    int roll;
    float marks[MAX_SUBJECTS];
    float gpa;
} Student;

Student students[MAX_STUDENTS];
int student_count = 0;

void swap(Student *a, Student *b) {
    Student temp = *a;
    *a = *b;
    *b = temp;
}

void sort_students() {
    for (int i = 0; i < student_count - 1; i++) {
        for (int j = 0; j < student_count - i - 1; j++) {
            if (strcmp(students[j].name, students[j + 1].name) > 0) {
                swap(&students[j], &students[j + 1]);
            }
        }
    }
    for (int i = 0; i < student_count; i++) {
        students[i].roll = i + 1; // Assign roll numbers after sorting
    }
}

float calculate_gpa(float marks[]) {
    float total = 0;
    for(int i=0; i<MAX_SUBJECTS; i++) {
        if(marks[i]<24){
            return (total=0);
            exit(0);
        }
    }
        for (int i = 0; i < MAX_SUBJECTS; i++) {
            total += marks[i];
        }
        return (total /90);
    }

void rank_students() {
    for (int i = 0; i < student_count - 1; i++) {
        for (int j = 0; j < student_count - i - 1; j++) {
            if (students[j].gpa < students[j + 1].gpa) {
                swap(&students[j], &students[j + 1]);
            }
        }
    }
}

void save_to_file() {
    FILE *file = fopen("students.txt", "w");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < student_count; i++) {
        fprintf(file, "%d %s ", students[i].roll, students[i].name);
        for (int j = 0; j < MAX_SUBJECTS; j++) {
            fprintf(file, "%.2f ", students[i].marks[j]);
        }
        fprintf(file, "%.2f\n", students[i].gpa);
    }

    fclose(file);
}

void load_from_file() {
    FILE *file = fopen("students.txt", "r");
    if (!file) return;

    student_count = 0;
    while (fscanf(file, "%d %49s", &students[student_count].roll, students[student_count].name) != EOF) {
        for (int j = 0; j < MAX_SUBJECTS; j++) {
            fscanf(file, "%f", &students[student_count].marks[j]);
        }
        fscanf(file, "%f", &students[student_count].gpa);
        student_count++;
    }

    fclose(file);
}

void add_student() {
    if (student_count >= MAX_STUDENTS) {
        printf("Student limit reached!\n");
        return;
    }

    printf("Enter student name: ");
    scanf("%s", students[student_count].name);

    printf("Enter marks for %d subjects: ", MAX_SUBJECTS);
    for (int i = 0; i < MAX_SUBJECTS; i++) {
        scanf("%f", &students[student_count].marks[i]);
    }

    students[student_count].gpa = calculate_gpa(students[student_count].marks);
    student_count++;

    sort_students();
    save_to_file();
}

void display_students() {
    printf("\nRoll  Name       GPA\n");
    printf("--------------------\n");
    for (int i = 0; i < student_count; i++) {
        printf("%-4d  %-10s %.2f\n", students[i].roll, students[i].name, students[i].gpa);
    }
}

int main() {
    load_from_file();
    int choice;

    do {
        printf("\n1. Add Student\n2. Display Students\n3. Rank Students\n4. Exit\nChoice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_student();
                break;
            case 2:
                display_students();
                break;
            case 3:
                rank_students();
                display_students();
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 4);

    return 0;
}
