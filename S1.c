#include <stdio.h>
#include <string.h>

// 1. Khai báo struct Student
struct Student {
    int id;
    char name[50];
    int age;
    float gpa;
};

int main() {
    // 2. Khởi tạo sẵn một mảng gồm 3 sinh viên mẫu
    struct Student students[3] = {
        {1, "Nguyen Van A", 20, 3.5},
        {2, "Tran Thi B", 21, 3.2},
        {3, "Le Van C", 22, 3.8}
    };

    // 3. In danh sách sinh viên này ra màn hình dưới dạng bảng
    printf("+----+--------------------+-----+-------+\n");
    printf("| ID |        Name        | Age |  GPA  |\n");
    printf("+----+--------------------+-----+-------+\n");

    for (int i = 0; i < 3; i++) {
        printf("| %-2d | %-18s | %-3d | %-5.2f |\n",
               students[i].id, students[i].name, students[i].age, students[i].gpa);
    }

    printf("+----+--------------------+-----+-------+\n");

    return 0;
}

