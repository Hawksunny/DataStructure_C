#include <stdio.h>
#include <malloc.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERRO 0
#define INFEASIBLE -1 // 不可实行
#define OVERFLOW -2

typedef int Status;
typedef int ElemType;

/* 采用单链表存储结构实现单链表(带头结点) */
typedef struct Node
{
    ElemType data;
    struct Node *next;
} Node, *LinkList;

/* 操作函数原型 */
Status CreateList_L(LinkList &, int); // 第二个参数是初始化时要创建的结点数目
Status DestroyList_L(LinkList &);
Status InsertNode_L(LinkList &, int, ElemType); // 第二个参数是指定节点插入后其位序
Status DeleteNode_L(LinkList &, int);           // 第二个参数是要删除结点的位序
int LocateNode_L(ElemType);                     // 找出指定结点的位序
Status FindNode_L(int);                         // 找出指定位序的结点
int Length_L(LinkList);
Status isEmpty_L(LinkList);
Status Merge_L(LinkList &, LinkList); // 要合并的两个链表都必须是非递减的，第二个链表合并到第一个链表

int main(void)
{
    LinkList foo, bar;
    CreateList_L(foo, 10);

    Length_L(foo);
    DeleteNode_L(foo, 5);
    InsertNode_L(foo, 5, 5);
    InsertNode_L(foo, 10, 10);
    Length_L(foo);

    LocateNode_L(5);
    FindNode_L(7);

    isEmpty_L(foo);
    for (int i = 0; i < Length_L(foo); i++)
    {
        DeleteNode_L(foo, i + 1);
    }
    isEmpty_L(foo);

    DestroyList_L(foo);

    printf("请确保接下来的两个链表是非递减的！\n");
    CreateList_L(foo, 10);
    CreateList_L(bar, 5);
    Merge_L(foo, bar);

    DestroyList_L(foo);
    DestroyList_L(bar);

    return 0;
}

/* 操作函数的实现 */
Status CreateList_L(LinkList &list, int n)
{
    Node *p;

    // 创建头结点
    list = (Node *)malloc(sizeof(Node));
    list->data = 0; // 头结点的数据域用于存储表长
    list->next = NULL;

    for (int i = 0; i < n; i++)
    {
        p = (Node *)malloc(sizeof(Node));
        if (!p)
        {
            printf("INFEASIBLE: 没有足够的存储空间用于创建新结点了！\n");
            return INFEASIBLE;
        }
        scanf("%d", &p->data);
        p->next = list->next;
        list->next = p;
    }

    return OK;
}