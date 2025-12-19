#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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
 * @brief Tinh diem GPA trung binh cua mot danh sach sinh vien.
 *
 * @param students Mang cau truc Student.
 * @param num_students So luong sinh vien trong mang.
 * @return Diem GPA trung binh, hoac 0.0 neu danh sach rong.
 */
float calculateAverageGpa(const struct Student students[], int num_students) {
    if (num_students == 0) {
        return 0.0f;
    }

    float total_gpa = 0.0f;
    for (int i = 0; i < num_students; i++) {
        total_gpa += students[i].gpa;
    }
    return total_gpa / num_students;
}

/**
 * @brief Tao ra mot so luong ban ghi sinh vien gia lap da chi dinh.
 *
 * @param students Mang cau truc Student de luu tru du lieu duoc tao.
 * @param count So luong sinh vien can tao.
 * @param start_id ID bat dau cho cac sinh vien duoc tao.
 * @return So luong sinh vien da tao.
 */
int generateStudents(struct Student students[], int count, int start_id) {
    srand(time(NULL)); // Khoi tao bo sinh so ngau nhien

    for (int i = 0; i < count; i++) {
        students[i].id = start_id + i;
        sprintf(students[i].name, "Sinh Vien %d", students[i].id);
        students[i].age = 18 + (rand() % 5); // Tuoi tu 18 den 22
        students[i].gpa = (float)(rand() % 401) / 100.0f; // GPA tu 0.00 den 4.00
    }
    return count;
}

int main() {
    // 1. 3 sinh vien mau ban dau
    struct Student students_sample[3] = {
        {1, "Nguyen Van A", 20, 3.5},
        {2, "Tran Thi B", 21, 3.2},
        {3, "Le Van C", 22, 3.8}
    };

    printStudents(students_sample, 3);

    // Kiem tra GPA trung binh cho cac sinh vien ban dau
    printf("Average GPA for initial students: %.2f\n", calculateAverageGpa(students_sample, 3));

    // 2. Tao 10 sinh vien gia lap
    struct Student simulated_students[MAX_STUDENTS];
    int num_simulated_students = generateStudents(simulated_students, 10, 100);

    printStudents(simulated_students, num_simulated_students);

    // Kiem tra GPA trung binh cho cac sinh vien gia lap
    printf("Average GPA for simulated students: %.2f\n", calculateAverageGpa(simulated_students, num_simulated_students));

    // Truong hop kiem thu: Danh sach rong
    printf("\n--- Test case: Empty list ---\n");
    struct Student empty_students[MAX_STUDENTS];
    printf("Average GPA for empty list: %.2f\n", calculateAverageGpa(empty_students, 0));

    return 0;
}
