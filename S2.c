#include <stdio.h>
#include <string.h>

// Khai bao struct Student
struct Student {
    int id;
    char name[50];
    int age;
    float gpa;
};

int main() {
    struct Student students[5]; // Mang chua toi da 5 sinh vien
    int num_students = 0;

    printf("\nNhap thong tin cho toi da 5 sinh vien:\n");
    for (int i = 0; i < 5; i++) {
        printf("\nNhap thong tin sinh vien thu %d:\n", i + 1);
        printf("ID: ");
        scanf("%d", &students[i].id);
        printf("Ten: ");
        scanf(" %49[^\n]s", students[i].name); // Doc chuoi co khoang trang
        printf("Tuoi: ");
        scanf("%d", &students[i].age);
        printf("GPA: ");
        scanf("%f", &students[i].gpa);
        num_students++;

        char choice;
        printf("Ban co muon nhap them sinh vien khong? (y/n): ");
        scanf(" %c", &choice);
        if (choice == 'n' || choice == 'N') {
            break;
        }
    }

    // In danh sach sinh vien ra man hinh duoi dang bang
    printf("\nDanh sach sinh vien:\n");
    printf("+----+--------------------+-----+-------+\n");
    printf("| ID |        Name        | Age |  GPA  |\n");
    printf("+----+--------------------+-----+-------+\n");

    for (int i = 0; i < num_students; i++) {
        printf("| %-2d | %-18s | %-3d | %-5.2f |\n",
               students[i].id, students[i].name, students[i].age, students[i].gpa);
    }

    printf("+----+--------------------+-----+-------+\n");

    return 0;
}
