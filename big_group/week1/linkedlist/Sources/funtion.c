#include "funtion.h"

void menu()
{
    int option = 0;
    printf("\n\t\t\t------------------------------\n\t\t\t欢迎光临\n\t\t\t------------------------------\n");
    system("color 1F");//程序面板颜色调节
    while (1)
    {
        system("cls");//每次循环开始时刷新屏幕
        do
        {
            system("cls");
            printf("\n                 -----------------------菜单--------------------\n");
            printf("\t\t|\t          ①  存储                        |\n");
            printf("\t\t|\t          ②  查看                        |\n");
            printf("\t\t|\t          ③  查看单链表中点                |\n");
            printf("\t\t|\t          ④  奇偶对换                   |\n");
            printf("\t\t|\t          ⑤  退出                    |\n");
            printf("\t\t|\t          6  是否成环                    |\n");
            printf("\n                 -----------------------------------------------\n");
            printf("\n");
            printf("\t\t请输入选项:  [\t ]\b\b\b\b");
            scanf("%d", &option);//对option进行赋值
        } while (option > 6|| option < 1);//管理模块选项为1111
        tran(option);//中转
    }

}




void tran(int math)//中转
{
    switch(math)
    {
        case 1:
            save();
            break;
        case 2:
            look();
            break;
        case 3:
            find_mi();
            break;
        case 4:
            link_tran();
            break;
        case 5:
            printf("已退出系统\n欢迎下次使用!!!");
            exit(0);
        case 6:
            printf("%d\n",is_cycle());
            printf("1为成环，0为不成环");
            getchar();
            getchar();
            break;
    }
}

void save() //输入信息函数
{
    system("cls");
    int len = sizeof(link1);
    int n;
    printf("请输入要输入信息的学生个数:");
    scanf("%d",&n);
    system("cls");//清屏
    //创建单向链表头节点
    link1 *p = (link1*) malloc(len); //p为链表指针
    link1 *p1 = p;//p1为链表前一节点
    link1 *head = p;//记录头节点的位置
    printf("请输入学号：");
    scanf("%d",&p->student.number);
    printf("\n请输入成绩：");
    scanf("%f",&p->student.store);
    system("cls");
    for(int i=0;i<n-1;i++)
    {
        p = (link1*) malloc(len);
        printf("请输入学号：");
        scanf("%d",&p->student.number);
        printf("\n请输入成绩：");
        scanf("%f",&p->student.store);
        system("cls");
        p1->next = p;
        p1 = p;
    }
    p->next=NULL;
    save_file(head);//保存数据到文件中
}

void save_file(link1* head) //将单向链表中的数据保存在文件中
{
    FILE* fp = fopen("stu.txt","w"); //创建文件指针
    link1 *p = head;
    while (p!=NULL)
    {
        fprintf(fp,"%d %f ",p->student.number,p->student.store);
        p=p->next;
    }
    fclose(fp);
}

void look()//查看文件中的数据
{
    system("cls");
    int len = sizeof(link2);
    link2* head = (link2*)malloc(len);//创建首元节点
    head->frior=NULL;
    head->next=NULL;
    link2* p = head;//p用来遍历链表
    FILE* fp = fopen("stu.txt","r");
    while(!feof(fp)) {
        fscanf(fp,"%d %f ",&p->student.number,&p->student.store);
        p->next = (link2*)malloc(len);
        p->next->frior = p;
        p = p->next;
    }
    p->frior->next=NULL;
    free(p);//释放最后创建的节点的空间
    print(head);
}

void print(link2 *head)
{
    //打印双向链表中的数据
    link2 *p=head;

    while(p!=NULL)
    {
        printf("%d %f\n",p->student.number,p->student.store);
        p=p->next;
    }
    free(p);
    getchar();
    getchar();
}

//查找单链表中点
void find_mi()
{
    system("cls");
    int num = 0;
    link1* head = read();
    link1 *fast = head;
    link1 *slow = head;
    while(fast && fast->next)
    {
        fast = fast->next->next;
        slow = slow->next;

    }
        printf("中间结点为：\n");
        printf("%d %f ",slow->student.number,slow->student.store);
    getchar();
    getchar();
}

//读取文件，返回单链表头指针
link1* read()
{
    FILE *fp = fopen("stu.txt","r");
    link1* head = (link1*)malloc(sizeof(link1) );
    link1*p = head;
    link1*p1 = head;
    while (!feof(fp))
    {
        fscanf(fp,"%d %f ",&p->student.number,&p->student.store);
        p1 = p;
        p = (link1*)malloc(sizeof(link1) );
        p1->next = p;
    }
    p1->next = NULL;
    free(p);
    return head;
}


void link_tran()
{//单链表奇偶调换
    link1 *head = read();
    link1 *p1 = head; //p1指向1节点的位置
    link1 *p2 = head->next;   //p2指向2节点的位置
    link1 *p = NULL;
    int n = link_num(head);
    head = p2;
    p1->next = p2->next;
    p2->next = p1;

    p = p1;
    for(int a=1;a<=(n/2)-1;a++)
    {
        p1 = p->next;
        p2 = p1->next;

        p->next = p2;
        p1->next = p2->next;
        p2->next = p1;

        p = p1;


    }

    save_file(head);
    printf("已完成对换");
    Sleep(2000);
}

int link_num(link1 *head)//判断链表长度
{
    link1 *p = head;
    int num = 0;
    while (p != NULL)
    {
        p = p->next;
        num++;
    }
    return num;
}

int is_cycle()//判断链表是否成环
{
    //0为不成环，1为成环
    link1 *head = read();
    link1 *fast = head;
    link1 *slow = head;
    while(fast!=NULL)
    {
        slow = slow->next;
        fast = fast->next;

        if(fast==NULL)
        {
            return 0;
        }
        else
        {
            fast=fast->next;
        }

        if(slow==fast)
        {
            return 1;
        }
    }
    return 0;
}