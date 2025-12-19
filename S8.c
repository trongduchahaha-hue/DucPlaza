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

int main() {
    // Buoc 1: Tao du lieu gia lap cho 3 lop (classA.txt, classB.txt, classC.txt)
    // Moi lop se co mot file rieng de luu tru du lieu sinh vien.
    printf("\n--- Tao du lieu gia lap cho cac lop hoc ---\n");
    generateClassData("session08/classA.txt", 5, 1001);
    generateClassData("session08/classB.txt", 7, 2001);
    generateClassData("session08/classC.txt", 6, 3001);

    // Buoc 2: Nguoi dung nhap ten file lop hoc de doc du lieu
    // Chuong trinh se yeu cau nguoi dung cung cap ten file chua du lieu sinh vien.
    char filename[MAX_FILENAME_LENGTH];
    printf("\nNhap ten file lop hoc (vi du: session08/classA.txt): ");
    scanf("%s", filename);

    // Buoc 3: Doc du lieu tu file da nhap
    // Su dung ham readStudentsFromFile de doc tat ca sinh vien tu file duoc chi dinh.
    struct Student students[MAX_STUDENTS_PER_CLASS];
    int num_students = readStudentsFromFile(filename, students);

    // Buoc 4: In danh sach sinh vien ra man hinh
    // Hien thi du lieu sinh vien da doc duoi dang bang tren console.
    if (num_students > 0) {
        printf("\n--- Danh sach sinh vien tu file %s ---\n", filename);
        printStudents(students, num_students);
    } else {
        printf("Khong co du lieu sinh vien hoac file khong ton tai: %s\n", filename);
    }

    return 0;
}
