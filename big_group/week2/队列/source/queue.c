//
// Created by recatu on 2024/3/23.
//
#include "queue.h"

void InitLQueue(LQueue *Q){

    Q->front = NULL;   // 将队列的前端指针设为空
    Q->rear = NULL;    // 将队列的后端指针设为空
    Q->length = 0;     // 将队列长度设为0
}

void DestroyLQueue(LQueue *Q) {
    Node *temp;
    while (Q->front != NULL) {  // 遍历队列中的每个节点
        temp = Q->front;        // 保存当前节点的指针
        Q->front = Q->front->next;  // 前端指针指向下一个节点
        free(temp);             // 释放当前节点的内存空间
    }
    Q->rear = NULL;             // 将队列的尾端指针设为空
    Q->length = 0;              // 将队列长度设为0
}

Status IsEmptyLQueue(const LQueue *Q) {
    if (Q->front == NULL) {
        return TRUE;  // 队列为空
    } else {
        return FALSE; // 队列不为空
    }
}

Status GetHeadLQueue(LQueue *Q, void *e) {
    if (Q->front == NULL) {
        return FALSE;  // 队列为空，无法获取队头元素
    } else {
        *(int *)e = Q->front->data; // 将队头元素存储在e中
        return TRUE;  // 成功获取队头元素
    }
}

int LengthLQueue(LQueue *Q) {
    int length = 0;  // 初始化长度为0

    Node *current = Q->front;  // 从队列的前端开始遍历
    while (current != NULL) {
        length++;  // 遍历每个节点，增加长度计数
        current = current->next;  // 移动到下一个节点
    }
    // 其实直接返回Q->length就行，不需要再遍历,写都写了，懒得删了
    return length;  // 返回队列的长度
}

Status EnLQueue(LQueue *Q, void *data) {
    Node *newNode = (Node *)malloc(sizeof(Node));  // 为新节点分配内存空间
    if (newNode == NULL) {
        return FALSE;  // 内存分配失败，入队失败
    }

    newNode->data = *(int *)data;  // 存储入队数据

    newNode->next = NULL;  // 新节点作为最后一个节点，所以其next指针指向NULL

    if (Q->rear == NULL) {  // 如果队列为空，则将新节点设置为队头
        Q->front = newNode;
    } else {
        Q->rear->next = newNode;  // 否则，将新节点链接到队列的末尾
    }

    Q->rear = newNode;  // 更新队列的rear指针为新节点
    Q->length++;  // 增加队列的长度

    return TRUE;  // 入队成功
}

Status DeLQueue(LQueue *Q) {
    if (Q->front == NULL) {
        return FALSE;  // 队列为空，无法出队
    }

    Node *temp = Q->front;  // 保存队头节点的指针
    Q->front = Q->front->next;  // 移动队头指针到下一个节点

    // 如果出队后队列为空，则将rear指针置为NULL
    if (Q->front == NULL) {
        Q->rear = NULL;
    }

    free(temp);  // 释放原队头节点的内存空间
    Q->length--;  // 减少队列长度
    return TRUE;  // 出队成功
}

void ClearLQueue(LQueue *Q) {
    Node *current = Q->front;  // 从队列的前端开始遍历
    while (current != NULL) {
        Node *temp = current;  // 保存当前节点的指针
        current = current->next;  // 移动到下一个节点
        free(temp);  // 释放当前节点的内存空间
    }
    Q->front = NULL;  // 将队列的前端指针设为空
    Q->rear = NULL;   // 将队列的后端指针设为空
    Q->length = 0;    // 将队列长度设为0
}

// 通用函数
Status TraverseLQueue(const LQueue *Q, void (*foo)(void *q)) {
    Node *current = Q->front;  // 从队列的前端开始遍历
    while (current != NULL) {
        foo(&(current->data));  // 对每个节点的数据执行操作函数foo
        current = current->next;  // 移动到下一个节点
    }
    return TRUE;
}
void LPrint(void *q) {
    printf("%d ", *(int *)q);  // 打印指针q指向的整数数据
}

void menu() {
    printf("队列中的数据类型为int，请不要输入其他类型数据\n");
    printf("1. 入队\n");
    printf("2. 出队\n");
    printf("3. 查看队头元素\n");
    printf("4. 确定队列长度\n");
    printf("5. 打印队列\n");
    printf("6. 清空队列\n");
    printf("7. 退出\n");
    printf("请选择操作: ");
}

void PrintLQueue(const LQueue *Q) {
    printf("Queue: ");
    TraverseLQueue(Q, LPrint);
    printf("\n");
}