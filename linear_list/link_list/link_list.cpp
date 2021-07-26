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

/* 采用单链表存储结构实现单链表(带头结点, 且用头结点存储表长) */
typedef struct Node
{
    ElemType data;
    struct Node *next;
} Node, *LinkList;

/* 操作函数原型 */
void Display(LinkList);
Status CreateList_L(LinkList &, int); // 第二个参数是初始化时要创建的结点数目
Status DestroyList_L(LinkList &);
Status InsertNode_L(LinkList &, int, ElemType); // 第二个参数是指定节点插入后其位序
Status DeleteNode_L(LinkList &, int);           // 第二个参数是要删除结点的位序
int LocateNode_L(LinkList, ElemType);           // 找出指定结点的位序
Status FindNode_L(LinkList, int, ElemType &);   // 找出指定位序的结点
Status Merge_L(LinkList &, LinkList &);         // 要合并的两个链表都必须是非递减的，第二个链表合并到第一个链表

/* 主函数 */
int main(void)
{
    LinkList foo, bar;
    ElemType elem;
    // CreateList_L(foo, 10);

    // DeleteNode_L(foo, 5);
    // InsertNode_L(foo, 5, 50);

    // printf("%d\n", LocateNode_L(foo, 9));
    // FindNode_L(foo, 7, elem);
    // printf("%d\n", elem);

    // int listLength = foo->data;
    // for (int i = 0; i < listLength; i++)
    // {
    //     DeleteNode_L(foo, foo->data);
    // }

    // DestroyList_L(foo);

    printf("Note: Make sure the next two lists are non-decrement!\n");
    CreateList_L(foo, 10);
    CreateList_L(bar, 5);
    Merge_L(foo, bar);

    DestroyList_L(foo);
    DestroyList_L(bar);

    return 0;
}

/* 操作函数的实现 */
void Display(LinkList list)
{
    for (Node *p = list; p; p = p->next)
    {
        printf("%d\t", p->data);
    }
    printf("\n");
}

Status CreateList_L(LinkList &list, int n)
{
    Node *p, *q; // q 结点是 p 结点的前驱

    // 创建头结点
    list = (Node *)malloc(sizeof(Node));
    list->data = 0; // 头结点的数据域用于存储表长
    list->next = NULL;

    q = list;
    for (int i = 0; i < n; i++)
    {
        p = (Node *)malloc(sizeof(Node));
        if (!p)
        {
            printf("Infeasible: There're not enough spaces for new node！\n");
            return INFEASIBLE;
        }
        list->data++;
        scanf("%d", &p->data);
        p->next = q->next;
        q->next = p;
        q = q->next;
    }

    Display(list);

    return OK;
}

Status DestroyList_L(LinkList &list)
{
    Node *p, *q;
    int listLength;
    p = list;
    listLength = list->data;

    for (int i = 0; i < listLength; i++)
    {
        q = p->next;
        free(p);
        p = q;
    }
    printf("INFO: Link list has been destroyed!\n");
    return OK;
}

Status InsertNode_L(LinkList &list, int i, ElemType e)
{
    Node *p, *q;
    int j; // p 指向第 j 个结点
    p = list;
    j = 0;

    while (p && j < i - 1)
    {
        p = p->next;
        j++;
    }
    if (!p || j > i - 1)
    {
        return ERRO;
    }

    q = (Node *)malloc(sizeof(Node));
    if (!q)
    {
        printf("Infeasible: There're not enough spaces for new node！\n");
        return INFEASIBLE;
    }
    q->data = e;
    q->next = p->next;
    p->next = q;
    list->data++;

    Display(list);

    return OK;
}

Status DeleteNode_L(LinkList &list, int i)
{
    Node *p, *q;
    int j; // p 指向第 j 个结点
    p = list;
    j = 0;

    while (p && j < i - 1)
    {
        p = p->next;
        j++;
    }
    if (!p || j > i - 1)
    {
        return ERRO;
    }

    q = p->next;
    p->next = q->next;
    free(q);
    list->data--;

    Display(list);

    return OK;
}

int LocateNode_L(LinkList list, ElemType e)
{
    Node *p;
    int i;
    p = list->next;
    i = 1;

    while (p)
    {
        if (p->data == e)
        {
            break;
        }
        p = p->next;
        i++;
    }

    if (!p)
    {
        return ERRO;
    }

    return i;
}

Status FindNode_L(LinkList list, int i, ElemType &e)
{
    Node *p = list->next;
    int j = 1;

    while (p && j < i)
    {
        p = p->next;
        j++;
    }
    if (!p || j > i)
    {
        return ERRO;
    }

    e = p->data;

    return OK;
}

Status Merge_L(LinkList &la, LinkList &lb)
{
    Node *p, *q, *temp, *r;
    p = la->next;
    q = lb->next;
    r = la;

    while (p && q)
    {
        if (q->data < p->data)
        {
            temp = q->next;
            q->next = r->next;
            r->next = q;
            q = temp;
            r = r->next;
        }
        else
        {
            p = p->next;
            r = r->next;
        }
    }
    r->next = p ? p : q;
    free(lb);
    Display(la);

    return OK;
}
