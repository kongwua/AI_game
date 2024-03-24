#include "evaluate.h"

int main() {
    system("chcp 65001");//拯救中文乱码
    system("cls");
    char expression[100];
    printf("请输入一个算术表达式: ");
    fgets(expression, 100, stdin);

    // 移除末尾的换行符
    for (int i = 0; expression[i] != '\0'; i++) {
        if (expression[i] == '\n') {
            expression[i] = '\0';
            break;
        }
    }

    printf("结果: %.2f\n", evaluate(expression));
    system("pause");
    return 0;
}
