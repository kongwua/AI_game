//
// Created by recatu on 2024/3/24.
//
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#ifndef WEEK2_EVALUATE_EVALUATE_H
#define WEEK2_EVALUATE_EVALUATE_H
// 定义栈结构
#define MAX_SIZE 100

typedef struct {
    int top;
    double items[MAX_SIZE];
} Stack;

void initialize(Stack *s); // 初始化栈
void push(Stack *s, double value); //入栈
double pop(Stack *s); // 出栈
double peek(const Stack *s); // 查看栈顶元素
int isOperator(char c); // 判断是否为运算符
int precedence(char op); // 运算符优先级判断
double evaluate(char *expression); // 计算表达式

#endif //WEEK2_EVALUATE_EVALUATE_H
