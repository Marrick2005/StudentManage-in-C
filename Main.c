#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 科目数量常量
#define SUBJECTS 3
#define MAX_STUDENTS 100
#define FILENAME "students.dat"

// 学生结构体
typedef struct {
    char id[12];        // 学号
    char name[20];      // 姓名
    float scores[SUBJECTS]; // 三科成绩
    float total;        // 总成绩
} Student;

// 全局变量
Student students[MAX_STUDENTS];
int student_count = 0;

// 函数声明
void add_student();
void display_all();
void search_student();
void modify_student();
void delete_student();
void save_to_file();
void load_from_file();
void show_menu();

int main() {
    load_from_file();
    int choice;
    
    do {
        show_menu();
        printf("请输入您的选择: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: add_student(); break;
            case 2: display_all(); break;
            case 3: search_student(); break;
            case 4: modify_student(); break;
            case 5: delete_student(); break;
            case 6: save_to_file(); break;
            case 0: printf("感谢使用！\n"); break;
            default: printf("无效的选项！\n");
        }
    } while(choice != 0);
    
    return 0;
}

// 菜单显示
void show_menu() {
    printf("\n===== 学生管理系统 =====\n");
    printf("1. 添加学生\n");
    printf("2. 显示所有学生\n");
    printf("3. 查找学生\n");
    printf("4. 修改信息\n");
    printf("5. 删除学生\n");
    printf("6. 保存数据\n");
    printf("0. 退出系统\n");
    printf("========================\n");
}

// 添加学生
void add_student() {
    if(student_count >= MAX_STUDENTS) {
        printf("学生数量已达上限！\n");
        return;
    }
    
    Student s;
    printf("\n请输入学号: ");
    scanf("%s", s.id);
    
    // 检查学号是否重复
    for(int i = 0; i < student_count; i++) {
        if(strcmp(students[i].id, s.id) == 0) {
            printf("学号已存在！\n");
            return;
        }
    }
    
    printf("请输入姓名: ");
    scanf("%s", s.name);
    
    printf("请输入三科成绩（数学 语文 英语）: ");
    s.total = 0;
    for(int i = 0; i < SUBJECTS; i++) {
        scanf("%f", &s.scores[i]);
        s.total += s.scores[i];
    }
    
    students[student_count++] = s;
    printf("添加成功！\n");
}

// 显示所有学生
void display_all() {
    if(student_count == 0) {
        printf("没有学生记录！\n");
        return;
    }
    
    printf("\n学号\t姓名\t数学\t语文\t英语\t总分\n");
    for(int i = 0; i < student_count; i++) {
        printf("%s\t%s\t", students[i].id, students[i].name);
        for(int j = 0; j < SUBJECTS; j++) {
            printf("%.1f\t", students[i].scores[j]);
        }
        printf("%.1f\n", students[i].total);
    }
}

// 查找学生
void search_student() {
    char id[12];
    printf("请输入要查找的学号: ");
    scanf("%s", id);
    
    for(int i = 0; i < student_count; i++) {
        if(strcmp(students[i].id, id) == 0) {
            printf("\n学号: %s\n姓名: %s\n", students[i].id, students[i].name);
            printf("成绩: 数学=%.1f 语文=%.1f 英语=%.1f\n", 
                   students[i].scores[0], students[i].scores[1], students[i].scores[2]);
            printf("总分: %.1f\n", students[i].total);
            return;
        }
    }
    printf("未找到该学生！\n");
}

// 文件保存/加载
void save_to_file() {
    FILE *fp = fopen(FILENAME, "wb");
    if(fp == NULL) {
        printf("文件保存失败！\n");
        return;
    }
    
    fwrite(&student_count, sizeof(int), 1, fp);
    fwrite(students, sizeof(Student), student_count, fp);
    fclose(fp);
    printf("数据已保存！\n");
}

void load_from_file() {
    FILE *fp = fopen(FILENAME, "rb");
    if(fp == NULL) return;
    
    fread(&student_count, sizeof(int), 1, fp);
    fread(students, sizeof(Student), student_count, fp);
    fclose(fp);
    printf("数据已加载！\n");
}

// 修改学生信息
void modify_student() {
    char id[12];
    printf("请输入要修改的学号: ");
    scanf("%s", id);
    
    for(int i = 0; i < student_count; i++) {
        if(strcmp(students[i].id, id) == 0) {
            printf("输入新姓名（当前：%s）: ", students[i].name);
            scanf("%s", students[i].name);
            
            printf("输入新成绩（数学 语文 英语）: ");
            students[i].total = 0;
            for(int j = 0; j < SUBJECTS; j++) {
                scanf("%f", &students[i].scores[j]);
                students[i].total += students[i].scores[j];
            }
            printf("修改成功！\n");
            return;
        }
    }
    printf("未找到该学生！\n");
}

// 删除学生
void delete_student() {
    char id[12];
    printf("请输入要删除的学号: ");
    scanf("%s", id);
    
    for(int i = 0; i < student_count; i++) {
        if(strcmp(students[i].id, id) == 0) {
            // 将最后一个元素移到当前位置
            students[i] = students[student_count-1];
            student_count--;
            printf("删除成功！\n");
            return;
        }
    }
    printf("未找到该学生！\n");
}
