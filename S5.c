#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 50

// Dinh nghia cau truc sinh vien
struct Student {
    int id;
    char name[MAX_NAME_LENGTH];
    int age;
    float gpa;
};

/**
 * @brief Doc du lieu sinh vien tu mot file da chi dinh vao mot mang cau truc Student.
 *
 * @param filename Duong dan den file chua du lieu sinh vien.
 * @param students Mang cau truc Student de luu tru du lieu da doc.
 * @return So luong sinh vien da doc thanh cong tu file.
 */
int readStudentsFromFile(const char *filename, struct Student students[]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 0; // Tra ve 0 neu khong doc duoc sinh vien nao
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

/**
 * @brief In danh sach sinh vien ra bang duoc dinh dang tren console.
 *
 * @param students Mang cau truc Student se duoc in.
 * @param num_students So luong sinh vien trong mang.
 */
void printStudents(const struct Student students[], int num_students) {
    if (num_students == 0) {
        printf("No students to display.\n");
        return;
    }

    printf("\nDanh sach sinh vien:\n");
    printf("+----+--------------------+-----+-------+\n");
    printf("| ID |        Name        | Age |  GPA  |\n");
    printf("+----+--------------------+-----+-------+\n");

    for (int i = 0; i < num_students; i++) {
        printf("| %-2d | %-18s | %-3d | %-5.2f |\n",
               students[i].id, students[i].name, students[i].age, students[i].gpa);
    }

    printf("+----+--------------------+-----+-------+\n");
}

/**
 * @brief Tim kiem sinh vien theo ID trong mot mang cau truc Student.
 *
 * @param students Mang cau truc Student de tim kiem.
 * @param num_students So luong sinh vien trong mang.
 * @param id ID cua sinh vien can tim.
 * @return Con tro den cau truc Student neu tim thay, nguoc lai la NULL.
 */
struct Student* findStudentById(struct Student students[], int num_students, int id) {
    for (int i = 0; i < num_students; i++) {
        if (students[i].id == id) {
            return &students[i];
        }
    }
    return NULL;
}

int main() {
    struct Student students[MAX_STUDENTS];
    int num_students = readStudentsFromFile("session08/students.txt", students);

    printStudents(students, num_students);

    // Cac truong hop kiem thu cho ham findStudentById
    printf("\n--- Test cases for findStudentById ---\n");

    // Truong hop kiem thu 1: ID ton tai
    int search_id_exists = 2;
    struct Student *found_student = findStudentById(students, num_students, search_id_exists);
    if (found_student != NULL) {
        printf("Found student with ID %d: Name = %s, Age = %d, GPA = %.2f\n",
               found_student->id, found_student->name, found_student->age, found_student->gpa);
    } else {
        printf("Student with ID %d not found.\n", search_id_exists);
    }

    // Truong hop kiem thu 2: ID khong ton tai
    int search_id_not_exists = 99;
    found_student = findStudentById(students, num_students, search_id_not_exists);
    if (found_student != NULL) {
        printf("Found student with ID %d: Name = %s, Age = %d, GPA = %.2f\n",
               found_student->id, found_student->name, found_student->age, found_student->gpa);
    } else {
        printf("Student with ID %d not found.\n", search_id_not_exists);
    }

    // Truong hop kiem thu 3: ID am
    int search_id_negative = -1;
    found_student = findStudentById(students, num_students, search_id_negative);
    if (found_student != NULL) {
        printf("Found student with ID %d: Name = %s, Age = %d, GPA = %.2f\n",
               found_student->id, found_student->name, found_student->age, found_student->gpa);
    } else {
        printf("Student with ID %d not found.\n", search_id_negative);
    }

    return 0;
}
