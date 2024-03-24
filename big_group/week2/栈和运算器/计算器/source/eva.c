//
// Created by recatu on 2024/3/24.
//
#include "evaluate.h"

// 初始化栈
void initialize(Stack *s) {
    s->top = -1;
}

// 入栈操作
void push(Stack *s, double value) {
    if (s->top == MAX_SIZE - 1) {
        printf("栈溢出\n");
        system("pause");
        exit(EXIT_FAILURE);
    }
    s->items[++s->top] = value;
}

// 出栈操作
double pop(Stack *s) {
    if (s->top == -1) {
        printf("栈下溢\n");
        system("pause");
        exit(EXIT_FAILURE);
    }
    return s->items[s->top--];
}

// 查看栈顶元素
double peek(const Stack *s) {
    if (s->top == -1) {
        printf("栈为空\n");
        system("pause");
        exit(EXIT_FAILURE);
    }
    return s->items[s->top];
}

// 判断是否是运算符
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// 运算符优先级
int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

// 计算表达式
double evaluate(char *expression) {
    Stack operand_stack; // 操作数栈
    Stack operator_stack; // 操作符栈
    initialize(&operand_stack);
    initialize(&operator_stack);

    int i;
    for (i = 0; expression[i] != '\0'; i++) {
        if (expression[i] == ' ') {
            continue; // 跳过空格
        } else if (isdigit(expression[i])) { // 如果是数字，将数字解析并入栈
            double num = 0;
            while (isdigit(expression[i]) || expression[i] == '.') {
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            if (expression[i] == '.') {
                i++;
                double fraction = 0.1;
                while (isdigit(expression[i])) {
                    num = num + (expression[i] - '0') * fraction;
                    fraction *= 0.1;
                    i++;
                }
            }
            push(&operand_stack, num);
            i--; // 将指针移回到最后一个数字的位置
        } else if (expression[i] == '(') { // 如果是左括号，入操作符栈
            push(&operator_stack, expression[i]);
        } else if (expression[i] == ')') { // 如果是右括号，执行括号内的运算
            while (peek(&operator_stack) != '(') {
                double op2 = pop(&operand_stack);
                double op1 = pop(&operand_stack);
                char op = pop(&operator_stack);
                // 根据运算符计算结果并入栈
                if (op == '+')
                    push(&operand_stack, op1 + op2);
                else if (op == '-')
                    push(&operand_stack, op1 - op2);
                else if (op == '*')
                    push(&operand_stack, op1 * op2);
                else if (op == '/')
                    push(&operand_stack, op1 / op2);
            }
            pop(&operator_stack); // 弹出左括号
        } else if (isOperator(expression[i])) { // 如果是运算符
            // 处理优先级，将高优先级的运算符进行计算
            while (operator_stack.top != -1 && precedence(peek(&operator_stack)) >= precedence(expression[i])) {
                double op2 = pop(&operand_stack);
                double op1 = pop(&operand_stack);
                char op = pop(&operator_stack);
                // 检查除数是否为零
                if (op == '/' && op2 == 0) {
                    printf("除数不能为零\n");
                    system("pause");
                    exit(EXIT_FAILURE);
                }
                // 根据运算符计算结果并入栈
                if (op == '+')
                    push(&operand_stack, op1 + op2);
                else if (op == '-')
                    push(&operand_stack, op1 - op2);
                else if (op == '*')
                    push(&operand_stack, op1 * op2);
                else if (op == '/')
                    push(&operand_stack, op1 / op2);
            }
            // 将当前运算符入栈
            push(&operator_stack, expression[i]);
        }
    }

    // 计算剩余的运算符
    while (operator_stack.top != -1) {
        double op2 = pop(&operand_stack);
        double op1 = pop(&operand_stack);
        char op = pop(&operator_stack);
        // 检查除数是否为零
        if (op == '/' && op2 == 0) {
            printf("除数不能为零\n");
            system("pause");
            exit(EXIT_FAILURE);
        }
        // 根据运算符计算结果并入栈
        if (op == '+')
            push(&operand_stack, op1 + op2);
        else if (op == '-')
            push(&operand_stack, op1 - op2);
        else if (op == '*')
            push(&operand_stack, op1 * op2);
        else if (op == '/')
            push(&operand_stack, op1 / op2);
    }

    return pop(&operand_stack); // 返回最终计算结果
}
