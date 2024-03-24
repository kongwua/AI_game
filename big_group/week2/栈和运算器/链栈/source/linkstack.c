//
// Created by recatu on 2024/3/24.
//
#include "Linkstack.h"

// 初始化栈
Status initLStack(LinkStack *s)
{
    s->top = NULL;  // 将栈顶指针置为空
    s->count = 0;   // 栈中元素数量置为0
    return SUCCESS; // 返回成功状态
}

// 判断栈是否为空
Status isEmptyLStack(LinkStack *s)
{
    if (s->count == 0 && s->top == NULL)  // 如果栈中元素数量为0且栈顶指针为空
        return SUCCESS;                   // 栈为空，返回成功状态
    else
        return ERROR;                     // 栈非空，返回错误状态
}

// 得到栈顶元素
Status getTopLStack(LinkStack *s, ElemType *e)
{
    if (isEmptyLStack(s) == SUCCESS)  // 如果栈为空
        return ERROR;                 // 返回错误状态

    *e = s->top->data;  // 获取栈顶元素的数据
    return SUCCESS;     // 返回成功状态
}

// 清空栈
Status clearLStack(LinkStack *s)
{
    while (s->top != NULL)  // 当栈顶指针不为空时
    {
        LinkStackPtr temp = s->top;  // 临时指针指向栈顶
        s->top = s->top->next;        // 栈顶指针指向下一个节点
        free(temp);                   // 释放当前节点内存
    }
    s->count = 0;  // 栈中元素数量置为0
    return SUCCESS; // 返回成功状态
}

// 销毁栈
// 因为在清空栈时就已经把内存free了，所以销毁函数和清空函数大同小异
Status destroyLStack(LinkStack *s)
{
    clearLStack(s);  // 调用清空栈函数
    return SUCCESS;  // 返回成功状态
}

// 检测栈长度
Status LStackLength(LinkStack *s, int *length)
{
    *length = s->count;  // 获取栈中元素数量
    return SUCCESS;      // 返回成功状态
}

// 入栈
Status pushLStack(LinkStack *s, ElemType data)
{
    LinkStackPtr newNode = (LinkStackPtr)malloc(sizeof(StackNode));  // 创建新节点
    if (newNode == NULL)  // 如果内存分配失败
        return ERROR;     // 返回错误状态

    newNode->data = data;       // 设置新节点数据
    newNode->next = s->top;     // 新节点指向原栈顶
    s->top = newNode;           // 栈顶指针指向新节点
    s->count++;                 // 栈中元素数量加1
    return SUCCESS;             // 返回成功状态
}

// 出栈
Status popLStack(LinkStack *s, ElemType *data)
{
    if (isEmptyLStack(s) == SUCCESS)  // 如果栈为空
        return ERROR;                 // 返回错误状态

    LinkStackPtr temp = s->top;  // 临时指针指向栈顶
    *data = temp->data;          // 获取栈顶元素的数据
    s->top = temp->next;         // 栈顶指针指向下一个节点
    free(temp);                  // 释放栈顶节点内存
    s->count--;                  // 栈中元素数量减1
    return SUCCESS;              // 返回成功状态
}

// 打印栈
Status print(LinkStack *s)
{
    if (isEmptyLStack(s) == SUCCESS)  // 如果栈为空
    {
        printf("栈为空.\n");  // 打印提示信息
        return ERROR;                 // 返回错误状态
    }

    printf("栈内数据(左为尾元素): ");       // 打印提示信息
    LinkStackPtr current = s->top;    // 当前指针指向栈顶
    while (current != NULL)           // 当前指针不为空时
    {
        printf("%d ", current->data); // 打印节点数据
        current = current->next;      // 移动到下一个节点
    }
    printf("\n");                     // 换行
    return SUCCESS;                   // 返回成功状态
}

void menu()
{
    LinkStack s;        // 声明链式栈变量
    ElemType topElem;   // 用于存储栈顶元素的变量
    int length;         // 用于存储栈长度的变量
    int choice;         // 用户选择菜单项的变量
    ElemType data;      // 用户输入的数据

    initLStack(&s);  // 初始化栈

    while (1)
    {
        system("cls");
        // 打印菜单选项
        printf("\n栈菜单:\n");
        printf("1. 入栈\n");
        printf("2. 出栈\n");
        printf("3. 打印栈\n");
        printf("4. 得到栈顶元素\n");
        printf("5. 检测栈长度\n");
        printf("6. 清空栈\n");
        printf("7. 销毁栈\n");
        printf("8. 退出\n");
        printf("请输入您的选择: ");
        printf("（请勿输入除数字外其他字符，否则会导致程序崩溃）\n");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("请输入要入栈的元素: ");
                scanf("%d", &data);
                pushLStack(&s, data);  // 入栈操作
                break;
            case 2:
                if (popLStack(&s, &topElem) == SUCCESS)
                    printf("出栈元素: %d\n", topElem);
                else
                    printf("栈为空，无法出栈。\n");
                system("pause");
                break;
            case 3:
                print(&s);  // 打印栈
                system("pause");
                break;
            case 4:
                if (getTopLStack(&s, &topElem) == SUCCESS)
                    printf("栈顶元素: %d\n", topElem);
                else
                    printf("栈为空，无法获取栈顶元素。\n");
                system("pause");
                break;
            case 5:
                if (LStackLength(&s, &length) == SUCCESS)
                    printf("栈长度: %d\n", length);
                else
                    printf("栈为空，长度为0。\n");
                system("pause");
                break;
            case 6:
                clearLStack(&s);  // 清空栈
                printf("栈已清空。\n");
                system("pause");
                break;
            case 7:
                destroyLStack(&s);  // 销毁栈
                printf("栈已销毁。\n");
                system("pause");
                break;
            case 8:
                printf("正在退出...\n");
                exit(0);
            default:
                printf("无效的选择，请输入1到8之间的数字。\n");
        }
    }
}
