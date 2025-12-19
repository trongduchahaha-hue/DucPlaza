#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_STUDENTS_PER_CLASS 50
#define MAX_NAME_LENGTH 50
#define MAX_FILENAME_LENGTH 100

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
 * @brief Doc du lieu sinh vien tu mot file da chi dinh vao mot mang cau truc Student.
 *
 * @param filename Duong dan den file chua du lieu sinh vien.
 * @param students Mang cau truc Student de luu tru du lieu da doc.
 * @return So luong sinh vien da doc thanh cong tu file.
 */
int readStudentsFromFile(const char *filename, struct Student students[]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Loi khi mo file");
        return 0; // Tra ve 0 neu khong doc duoc sinh vien nao
    }

    int count = 0;
    while (count < MAX_STUDENTS_PER_CLASS &&
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
 * @brief Tao du lieu sinh vien gia lap cho mot lop va ghi vao mot file.
 *
 * @param filename Duong dan den file de ghi du lieu lop hoc.
 * @param num_students_to_generate So luong sinh vien can tao.
 * @param start_id ID bat dau cho cac sinh vien duoc tao.
 */
void generateClassData(const char *filename, int num_students_to_generate, int start_id) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Loi khi tao file lop hoc");
        return;
    }

    srand(time(NULL) + start_id); // Khoi tao bo sinh so ngau nhien voi mot gia tri duy nhat

    for (int i = 0; i < num_students_to_generate; i++) {
        int id = start_id + i;
        char name[MAX_NAME_LENGTH];
        sprintf(name, "Sinh Vien %d", id);
        int age = 18 + (rand() % 5); // Tuoi tu 18 den 22
        float gpa = (float)(rand() % 401) / 100.0f; // GPA tu 0.00 den 4.00
        fprintf(file, "%d,%s,%d,%.2f\n", id, name, age, gpa);
    }

    fclose(file);
    printf("Da tao du lieu gia lap cho %s thanh cong.\n", filename);
}

/**
 * @brief Them mot sinh vien moi vao mang.
 *
 * @param students Mang cau truc Student.
 * @param num_students Con tro den so luong sinh vien hien tai trong mang.
 * @param new_student Cau truc Student cua sinh vien moi can them.
 * @return 1 neu them thanh cong, 0 neu mang day hoac ID trung lap.
 */
int addStudent(struct Student students[], int *num_students, const struct Student new_student) {
    if (*num_students >= MAX_STUDENTS_PER_CLASS) {
        printf("Loi: Mang sinh vien da day, khong the them sinh vien moi.\n");
        return 0; // Mang day
    }

    for (int i = 0; i < *num_students; i++) {
        if (students[i].id == new_student.id) {
            printf("Loi: ID sinh vien %d da ton tai. Khong the them sinh vien moi.\n", new_student.id);
            return 0; // ID trung lap
        }
    }

    students[*num_students] = new_student;
    (*num_students)++;
    printf("Da them sinh vien %s (ID: %d) thanh cong.\n", new_student.name, new_student.id);
    return 1; // Them thanh cong
}

/**
 * @brief Xoa mot sinh vien khoi mang dua tren ID.
 *
 * @param students Mang cau truc Student.
 * @param num_students Con tro den so luong sinh vien hien tai trong mang.
 * @param id_to_delete ID cua sinh vien can xoa.
 * @return 1 neu xoa thanh cong, 0 neu khong tim thay sinh vien.
 */
int deleteStudentById(struct Student students[], int *num_students, int id_to_delete) {
    int found_index = -1;
    for (int i = 0; i < *num_students; i++) {
        if (students[i].id == id_to_delete) {
            found_index = i;
            break;
        }
    }

    if (found_index == -1) {
        printf("Loi: Khong tim thay sinh vien voi ID %d de xoa.\n", id_to_delete);
        return 0; // Khong tim thay sinh vien
    }

    // Dich chuyen cac phan tu con lai de lap day khoang trong
    for (int i = found_index; i < *num_students - 1; i++) {
        students[i] = students[i+1];
    }
    (*num_students)--;
    printf("Da xoa sinh vien voi ID %d thanh cong.\n", id_to_delete);
    return 1; // Xoa thanh cong
}

int main() {
    // Buoc 1: Tao du lieu gia lap cho cac lop hoc
    printf("\n--- Tao du lieu gia lap cho cac lop hoc ---\n");
    generateClassData("session08/classA.txt", 3, 1001); // 3 sinh vien ban dau

    // Buoc 2: Doc du lieu tu file classA.txt de khoi tao danh sach ban dau
    struct Student students[MAX_STUDENTS_PER_CLASS];
    int num_students = readStudentsFromFile("session08/classA.txt", students);
    printf("\n--- Danh sach sinh vien ban dau tu classA.txt ---\n");
    printStudents(students, num_students);

    // Buoc 3: Test ham them sinh vien moi
    printf("\n--- Kiem thu chuc nang Them Sinh Vien ---\n");

    // Test case 1.1: Them sinh vien moi thanh cong
    struct Student new_s1 = {1004, "Nguyen E", 19, 3.1};
    addStudent(students, &num_students, new_s1);
    printStudents(students, num_students);

    // Test case 1.2: Them sinh vien voi ID trung lap
    struct Student new_s2 = {1001, "Tran F", 20, 3.0}; // ID 1001 da ton tai
    addStudent(students, &num_students, new_s2);
    printStudents(students, num_students);

    // Buoc 4: Test ham xoa sinh vien theo ID
    printf("\n--- Kiem thu chuc nang Xoa Sinh Vien ---\n");

    // Test case 2.1: Xoa sinh vien ton tai
    deleteStudentById(students, &num_students, 1002);
    printStudents(students, num_students);

    // Test case 2.2: Xoa sinh vien khong ton tai
    deleteStudentById(students, &num_students, 9999);
    printStudents(students, num_students);

    return 0;
}
