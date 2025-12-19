#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_STUDENTS 100
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
    while (count < MAX_STUDENTS &&
           fscanf(file, "%d,%49[^,],%d,%f\n",
                  &students[count].id,
                  students[count].name,
                  &students[count].age,
                  &students[count].gpa) == 4) {
        count++;
    }

    fclose(file);
    printf("Da doc %d sinh vien tu file %s.\n", count, filename);
    return count;
}

/**
 * @brief Ghi du lieu sinh vien tu mot mang cau truc Student vao mot file.
 *
 * @param filename Duong dan den file de ghi du lieu sinh vien.
 * @param students Mang cau truc Student chua du lieu sinh vien.
 * @param num_students So luong sinh vien trong mang.
 * @return 1 neu ghi thanh cong, 0 neu co loi.
 */
int saveStudentsToFile(const char *filename, const struct Student students[], int num_students) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Loi khi mo file de ghi");
        return 0; // Loi khi mo file
    }

    for (int i = 0; i < num_students; i++) {
        fprintf(file, "%d,%s,%d,%.2f\n", students[i].id, students[i].name, students[i].age, students[i].gpa);
    }

    fclose(file);
    printf("Da ghi %d sinh vien vao file %s thanh cong.\n", num_students, filename);
    return 1; // Ghi thanh cong
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

/**
 * @brief Them mot sinh vien moi vao mang.
 *
 * @param students Mang cau truc Student.
 * @param num_students Con tro den so luong sinh vien hien tai trong mang.
 * @param new_student Cau truc Student cua sinh vien moi can them.
 * @return 1 neu them thanh cong, 0 neu mang day hoac ID trung lap.
 */
int addStudent(struct Student students[], int *num_students, const struct Student new_student) {
    if (*num_students >= MAX_STUDENTS) {
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

/**
 * @brief Cho phep nguoi dung nhap thong tin mot sinh vien tu ban phim.
 *
 * @return Mot cau truc Student chua thong tin da nhap.
 */
struct Student inputStudentManual() {
    struct Student s;
    printf("Nhap ID: ");
    scanf("%d", &s.id);
    printf("Nhap Ten: ");
    scanf(" %49[^\n]s", s.name);
    printf("Nhap Tuoi: ");
    scanf("%d", &s.age);
    printf("Nhap GPA: ");
    scanf("%f", &s.gpa);
    return s;
}

// Ham hien thi menu
void displayMenu() {
    printf("\n===== Student Manager =====\n");
    printf("1. Nhap sinh vien\n");
    printf("2. In danh sach\n");
    printf("3. Ghi file\n");
    printf("4. Doc file\n");
    printf("5. Tim kiem\n");
    printf("6. Sap xep\n");
    printf("7. Them sinh vien\n");
    printf("8. Xoa sinh vien\n");
    printf("0. Thoat\n");
    printf("===========================\n");
    printf("Chon chuc nang: ");
}

int main() {
    struct Student students[MAX_STUDENTS];
    int num_students = 0;
    int choice;
    char filename[MAX_FILENAME_LENGTH];

    // Sinh 10 sinh vien gia lap de test
    num_students = generateStudents(students, 10, 1);
    printf("Da tao 10 sinh vien gia lap de test.\n");
    printStudents(students, num_students);

    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Nhap sinh vien
                {   // Nguoi dung nhap thong tin sinh vien moi tu ban phim
                    printf("\n--- Nhap Sinh Vien ---\n");
                    struct Student new_s = inputStudentManual();
                    addStudent(students, &num_students, new_s);
                }
                break;
            case 2: // In danh sach
                // Hien thi tat ca sinh vien hien co trong danh sach
                printf("\n--- In Danh Sach Sinh Vien ---\n");
                printStudents(students, num_students);
                break;
            case 3: // Ghi file
                // Ghi toan bo danh sach sinh vien hien tai vao mot file
                printf("\n--- Ghi File ---\n");
                printf("Nhap ten file de ghi (vi du: data.txt): ");
                scanf("%s", filename);
                saveStudentsToFile(filename, students, num_students);
                break;
            case 4: // Doc file
                // Doc danh sach sinh vien tu mot file va cap nhat danh sach hien tai
                printf("\n--- Doc File ---\n");
                printf("Nhap ten file de doc (vi du: data.txt): ");
                scanf("%s", filename);
                num_students = readStudentsFromFile(filename, students);
                printStudents(students, num_students);
                break;
            case 5: // Tim kiem
                {   // Tim kiem mot sinh vien theo ID do nguoi dung nhap
                    printf("\n--- Tim Kiem Sinh Vien ---\n");
                    int search_id;
                    printf("Nhap ID sinh vien can tim: ");
                    scanf("%d", &search_id);
                    struct Student *found_s = findStudentById(students, num_students, search_id);
                    if (found_s != NULL) {
                        printf("Tim thay sinh vien: ID = %d, Ten = %s, Tuoi = %d, GPA = %.2f\n",
                               found_s->id, found_s->name, found_s->age, found_s->gpa);
                    } else {
                        printf("Khong tim thay sinh vien voi ID %d.\n", search_id);
                    }
                }
                break;
            case 6: // Sap xep
                // Sap xep danh sach sinh vien theo GPA giam dan
                printf("\n--- Sap Xep Sinh Vien Theo GPA ---\n");
                sortStudentsByGpa(students, num_students);
                printf("Danh sach sinh vien sau khi sap xep (theo GPA giam dan):\n");
                printStudents(students, num_students);
                break;
            case 7: // Them sinh vien
                {   // Them mot sinh vien moi vao danh sach (co the trung ID)
                    printf("\n--- Them Sinh Vien ---\n");
                    struct Student new_s = inputStudentManual();
                    addStudent(students, &num_students, new_s);
                }
                break;
            case 8: // Xoa sinh vien
                // Xoa mot sinh vien khoi danh sach dua tren ID do nguoi dung nhap
                printf("\n--- Xoa Sinh Vien ---\n");
                int delete_id;
                printf("Nhap ID sinh vien can xoa: ");
                scanf("%d", &delete_id);
                deleteStudentById(students, &num_students, delete_id);
                break;
            case 0: // Thoat
                // Ket thuc chuong trinh
                printf("\nThoat chuong trinh. Tam biet!\n");
                break;
            default:
                printf("Chuc nang khong hop le. Vui long chon lai.\n");
                break;
        }
    } while (choice != 0);

    return 0;
}

