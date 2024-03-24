#include "queue.h"

int main() {
    system("chcp 65001");//拯救中文乱码

    LQueue Q;
    InitLQueue(&Q);

    int choice;
    int data;//保存数据的值

    do {
        system("cls");
        menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("请输入要入队的数据: ");
                scanf("%d", &data);
                EnLQueue(&Q, &data);
                system("pause");
                break;
            case 2:
                if (DeLQueue(&Q))
                    printf("成功出队！\n");
                else
                    printf("队列为空，无法出队！\n");
                system("pause");
                break;
            case 3:
                if (GetHeadLQueue(&Q, &data))
                    printf("队头元素为: %d\n", data);
                else
                    printf("队列为空！\n");
                system("pause");
                break;
            case 4:
                printf("队列长度为: %d\n", LengthLQueue(&Q));
                system("pause");
                break;
            case 5:
                PrintLQueue(&Q);
                system("pause");
                break;
            case 6:
                ClearLQueue(&Q);
                printf("队列已清空！\n");
                system("pause");
                break;
            case 7:
                printf("程序退出！\n");
                DestroyLQueue(&Q);
                system("pause");
                break;
            default:
                printf("无效的选择！\n");
                system("pause");
                break;
        }
    } while (choice != 7);

    return 0;

}


