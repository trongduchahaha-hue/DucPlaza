#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 50

// 1. Dinh nghia cau truc Student
struct Student {
    int id;
    char name[MAX_NAME_LENGTH];
    int age;
    float gpa;
};

// 3. Trien khai ham doc sinh vien tu file
int readStudentsFromFile(const char *filename, struct Student students[]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 0; // Return 0 students read
    }

    int count = 0;
    while (count < MAX_STUDENTS &&
           fscanf(file, "%d,%49[^,],%d,%f\n",
                  &students[count].id,
                  students[count].name,
                  &students[count].age,
                  &students[count].gpa) == 4) {
        count++;
    }

    fclose(file);
    return count;
}

// 4. Trien khai ham in danh sach sinh vien
void printStudents(const struct Student students[], int num_students) {
    if (num_students == 0) {
        printf("No students to display.\n");
        return;
    }

    printf("\nDanh sach sinh vien tu file:\n");
    printf("+----+--------------------+-----+-------+\n");
    printf("| ID |        Name        | Age |  GPA  |\n");
    printf("+----+--------------------+-----+-------+\n");

    for (int i = 0; i < num_students; i++) {
        printf("| %-2d | %-18s | %-3d | %-5.2f |\n",
               students[i].id, students[i].name, students[i].age, students[i].gpa);
    }

    printf("+----+--------------------+-----+-------+\n");
}

// 5. Trien khai ham main
int main() {
    struct Student students[MAX_STUDENTS];
    int num_students = readStudentsFromFile("students.txt", students); // Changed path

    printStudents(students, num_students);

    return 0;
}
