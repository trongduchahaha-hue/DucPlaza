#include <stdio.h>
#include <string.h>

// 1. Khai bao struct Student
struct Student {
    int id;
    char name[50];
    int age;
    float gpa;
};

void saveToFile(struct Student list[], int n) {
    FILE *f = fopen("students.txt", "w");
    if (f == NULL) {
        printf("Loi: Khong the mo file de ghi!\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        fprintf(f, "%d,%s,%d,%.2f\n", list[i].id, list[i].name, list[i].age, list[i].gpa);
    }
    fclose(f);
    printf("Luu thanh cong\n");
}

int main() {
    
    // 2. Khoi tao san mot mang gom 3 sinh vien mau
    struct Student students[3] = {
        {1, "Nguyen Van A", 20, 3.5},
        {2, "Tran Thi B", 21, 3.2},
        {3, "Le Van C", 22, 3.8}
    };

    // 3. In danh sach sinh vien nay ra man hinh duoi dang bang
    printf("+----+--------------------+-----+-------+\n");
    printf("| ID |        Name        | Age |  GPA  |\n");
    printf("+----+--------------------+-----+-------+\n");

    for (int i = 0; i < 3; i++) {
        printf("| %-2d | %-18s | %-3d | %-5.2f |\n",
               students[i].id, students[i].name, students[i].age, students[i].gpa);
    }

    printf("+----+--------------------+-----+-------+\n");

    saveToFile(students, 3);
    printf("Da luu thanh cong\n");
    return 0;
}
