#include "funtion.h"

void menu()
{
    int option = 0;
    printf("\n\t\t\t------------------------------\n\t\t\t��ӭ����\n\t\t\t------------------------------\n");
    system("color 1F");//���������ɫ����
    while (1)
    {
        system("cls");//ÿ��ѭ����ʼʱˢ����Ļ
        do
        {
            system("cls");
            printf("\n                 -----------------------�˵�--------------------\n");
            printf("\t\t|\t          ��  �洢                        |\n");
            printf("\t\t|\t          ��  �鿴                        |\n");
            printf("\t\t|\t          ��  �鿴�������е�                |\n");
            printf("\t\t|\t          ��  ��ż�Ի�                   |\n");
            printf("\t\t|\t          ��  �˳�                    |\n");
            printf("\t\t|\t          6  �Ƿ�ɻ�                    |\n");
            printf("\n                 -----------------------------------------------\n");
            printf("\n");
            printf("\t\t������ѡ��:  [\t ]\b\b\b\b");
            scanf("%d", &option);//��option���и�ֵ
        } while (option > 6|| option < 1);//����ģ��ѡ��Ϊ1111
        tran(option);//��ת
    }

}




void tran(int math)//��ת
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
            printf("���˳�ϵͳ\n��ӭ�´�ʹ��!!!");
            exit(0);
        case 6:
            printf("%d\n",is_cycle());
            printf("1Ϊ�ɻ���0Ϊ���ɻ�");
            getchar();
            getchar();
            break;
    }
}

void save() //������Ϣ����
{
    system("cls");
    int len = sizeof(link1);
    int n;
    printf("������Ҫ������Ϣ��ѧ������:");
    scanf("%d",&n);
    system("cls");//����
    //������������ͷ�ڵ�
    link1 *p = (link1*) malloc(len); //pΪ����ָ��
    link1 *p1 = p;//p1Ϊ����ǰһ�ڵ�
    link1 *head = p;//��¼ͷ�ڵ��λ��
    printf("������ѧ�ţ�");
    scanf("%d",&p->student.number);
    printf("\n������ɼ���");
    scanf("%f",&p->student.store);
    system("cls");
    for(int i=0;i<n-1;i++)
    {
        p = (link1*) malloc(len);
        printf("������ѧ�ţ�");
        scanf("%d",&p->student.number);
        printf("\n������ɼ���");
        scanf("%f",&p->student.store);
        system("cls");
        p1->next = p;
        p1 = p;
    }
    p->next=NULL;
    save_file(head);//�������ݵ��ļ���
}

void save_file(link1* head) //�����������е����ݱ������ļ���
{
    FILE* fp = fopen("stu.txt","w"); //�����ļ�ָ��
    link1 *p = head;
    while (p!=NULL)
    {
        fprintf(fp,"%d %f ",p->student.number,p->student.store);
        p=p->next;
    }
    fclose(fp);
}

void look()//�鿴�ļ��е�����
{
    system("cls");
    int len = sizeof(link2);
    link2* head = (link2*)malloc(len);//������Ԫ�ڵ�
    head->frior=NULL;
    head->next=NULL;
    link2* p = head;//p������������
    FILE* fp = fopen("stu.txt","r");
    while(!feof(fp)) {
        fscanf(fp,"%d %f ",&p->student.number,&p->student.store);
        p->next = (link2*)malloc(len);
        p->next->frior = p;
        p = p->next;
    }
    p->frior->next=NULL;
    free(p);//�ͷ���󴴽��Ľڵ�Ŀռ�
    print(head);
}

void print(link2 *head)
{
    //��ӡ˫�������е�����
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

//���ҵ������е�
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
        printf("�м���Ϊ��\n");
        printf("%d %f ",slow->student.number,slow->student.store);
    getchar();
    getchar();
}

//��ȡ�ļ������ص�����ͷָ��
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
{//��������ż����
    link1 *head = read();
    link1 *p1 = head; //p1ָ��1�ڵ��λ��
    link1 *p2 = head->next;   //p2ָ��2�ڵ��λ��
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
    printf("����ɶԻ�");
    Sleep(2000);
}

int link_num(link1 *head)//�ж�������
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

int is_cycle()//�ж������Ƿ�ɻ�
{
    //0Ϊ���ɻ���1Ϊ�ɻ�
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