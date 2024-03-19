
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
//导入头文件
#ifndef FUNTION_H
#define FUNTION_H

typedef struct student_data //存储学生数据
    {
        int number; //存储学号
        float store; //存储成绩
    }data;

typedef struct link_one //单向链表结点
{
    data student;//学生信息
    struct link_one* next;//尾指针
}link1;

typedef struct link_two
{
    struct link_two* frior;//前指针
    data student;//学生信息
    struct link_two* next;//尾指针
}link2;

void menu();//菜单函数
void tran(int math);//中转函数
void save(); //采用单链表输入信息
void save_file(link1* head);//将链表中的信息保存到文件中
void look();//查看文件中的数据
void print(link2 *head);//打印链表数据
void find_mi();//查找单链表中点
link1* read();//读取文件数据，构建单链表
int link_num(link1 *head);//计算链表长度,返回int
void link_tran();//单链表奇偶调换
int is_cycle();//判断链表是否成环
#endif 
