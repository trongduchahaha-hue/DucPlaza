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
        printf("Khong co sinh vien nao de hien thi.\n");
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
 * @brief Tao ra mot so luong ban ghi sinh vien gia lap da chi dinh.
 *
 * @param students Mang cau truc Student de luu tru du lieu duoc tao.
 * @param count So luong sinh vien can tao.
 * @param start_id ID bat dau cho cac sinh vien duoc tao.
 * @param gpa_type Kieu GPA de tao: 0 cho ngau nhien, 1 cho bang nhau, 2 cho da sap xep (tang dan).
 * @return So luong sinh vien da tao.
 */
int generateStudents(struct Student students[], int count, int start_id, int gpa_type) {
    srand(time(NULL)); // Khoi tao bo sinh so ngau nhien

    for (int i = 0; i < count; i++) {
        students[i].id = start_id + i;
        sprintf(students[i].name, "Sinh Vien %d", students[i].id);
        students[i].age = 18 + (rand() % 5); // Tuoi tu 18 den 22

        if (gpa_type == 1) { // GPA bang nhau
            students[i].gpa = 3.0f;
        } else if (gpa_type == 2) { // GPA da sap xep (tang dan)
            students[i].gpa = 1.0f + (float)i * 0.2f;
        } else { // GPA ngau nhien
            students[i].gpa = (float)(rand() % 401) / 100.0f; // GPA tu 0.00 den 4.00
        }
    }
    return count;
}

/**
 * @brief Sap xep mot mang cau truc Student theo GPA giam dan bang thuat toan Bubble Sort.
 *
 * Logic: Bubble Sort lap lai cac buoc trong danh sach, so sanh cac phan tu lien ke
 * va hoan doi chung neu chung sai thu tu. Viec duyet qua danh sach duoc
 * lap lai cho den khi khong can hoan doi, dieu nay cho thay danh sach da duoc sap xep.
 * Trien khai nay sap xep theo thu tu giam dan, nghia la sinh vien co GPA cao hon
 * se xuat hien som hon trong danh sach.
 *
 * @param students Mang cau truc Student se duoc sap xep.
 * @param num_students So luong sinh vien trong mang.
 */
void sortStudentsByGpa(struct Student students[], int num_students) {
    for (int i = 0; i < num_students - 1; i++) {
        for (int j = 0; j < num_students - i - 1; j++) {
            if (students[j].gpa < students[j+1].gpa) { // Sap xep theo thu tu giam dan
                // Hoan doi students[j] va students[j+1]
                struct Student temp = students[j];
                students[j] = students[j+1];
                students[j+1] = temp;
            }
        }
    }
}

int main() {
    // Truong hop kiem thu 1: GPA ngau nhien
    printf("--- Truong hop kiem thu 1: GPA ngau nhien ---\n");
    struct Student random_students[MAX_STUDENTS];
    int num_random_students = generateStudents(random_students, 5, 1, 0);
    printf("Truoc khi sap xep:\n");
    printStudents(random_students, num_random_students);
    sortStudentsByGpa(random_students, num_random_students);
    printf("Sau khi sap xep theo GPA (giam dan):\n");
    printStudents(random_students, num_random_students);

    // Truong hop kiem thu 2: GPA bang nhau
    printf("\n--- Truong hop kiem thu 2: GPA bang nhau ---\n");
    struct Student equal_gpa_students[MAX_STUDENTS];
    int num_equal_gpa_students = generateStudents(equal_gpa_students, 5, 6, 1);
    printf("Truoc khi sap xep:\n");
    printStudents(equal_gpa_students, num_equal_gpa_students);
    sortStudentsByGpa(equal_gpa_students, num_equal_gpa_students);
    printf("Sau khi sap xep theo GPA (giam dan):\n");
    printStudents(equal_gpa_students, num_equal_gpa_students);

    // Truong hop kiem thu 3: GPA da sap xep (tang dan, se duoc sap xep thanh giam dan)
    printf("\n--- Truong hop kiem thu 3: GPA da sap xep (tang dan) ---\n");
    struct Student sorted_gpa_students[MAX_STUDENTS];
    int num_sorted_gpa_students = generateStudents(sorted_gpa_students, 5, 11, 2);
    printf("Truoc khi sap xep:\n");
    printStudents(sorted_gpa_students, num_sorted_gpa_students);
    sortStudentsByGpa(sorted_gpa_students, num_sorted_gpa_students);
    printf("Sau khi sap xep theo GPA (giam dan):\n");
    printStudents(sorted_gpa_students, num_sorted_gpa_students);

    return 0;
}
