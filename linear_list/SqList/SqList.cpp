#define TRUE 1
#define FALSE 0
#define OK 1
#define ERRO 0
#define INFEASIBLE -1 // 不可实行
#define OVERFLOW -2

typedef int Status;
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

/* 使用动态分配一维数组的方式来表示线性表的顺序结构 */
#define LIST_INIT_SIZE 100
#define LIST_INCREMENT 10

typedef int ElemType;
typedef struct SqList
{
    ElemType *elem;
    int length; // 当前表长
    int size;   // 当前表的容量
} SqList;

/* 操作集函数原型 */
Status InitList_Sq(SqList &);                    // 初始化顺序表，分配初始容量
Status DestoryList_Sq(SqList &);                 // 销毁顺序表，释放空间
Status GetElem_Sq(SqList, int, ElemType &);      // 获取顺序表中指定位序元素的值
Status PutElem_Sq(SqList &, int, ElemType);      // 修改顺序表中指定位序元素的值
Status LocateElem_Sq(SqList, int &, ElemType);   // 获取顺序表中指定元素的位序
int Length_Sq(SqList);                           // 获取指定顺序表的长度
Status ListInsert_Sq(SqList &, int, ElemType);   // 在顺序表的指定位置插入指定元素
Status ListDelete_Sq(SqList &, int, ElemType &); // 在顺序表的指定位置删除当前元素，并返回当前元素

int main(void)
{
    SqList la;
    int index;
    ElemType data;
    InitList_Sq(la);

    for (int i = 1; i <= 3; ++i)
    {
        scanf("%d %d", &index, &data);
        ListInsert_Sq(la, index, data);
    }
    printf("%d %d %d\n", la.elem[0], la.elem[1], la.elem[2]);
    ListDelete_Sq(la, 2, data);
    printf("%d %d\n", la.elem[0], la.elem[1]);
    ListInsert_Sq(la, 1, 625);
    printf("%d %d %d\n", la.elem[0], la.elem[1], la.elem[2]);
    DestoryList_Sq(la);
    getchar();
    getchar();

    return 0;
}

Status InitList_Sq(SqList &L)
{
    L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!L.elem)
    {
        printf("Erro: 内存空间不足！无法完成初始化！\n\n");
        exit(OVERFLOW);
    }
    L.length = 0;
    L.size = LIST_INIT_SIZE;
    printf(
        "Success: 成功初始化顺序表！\n"
        "Info: 入口地址是: %#x\n"
        "Info: 当前表长为: %d 单位\n"
        "Info: 当前表容量为: %d 单位\n\n",
        L.elem, L.length, L.size);

    return OK;
} // InitList_Sq

Status DestoryList_Sq(SqList &L)
{
    free(L.elem);
    L.elem = NULL;
    printf("Success: 顺序表已摧毁！\n\n");

    return OK;
} // DestoryList_Sq

Status GetElem_Sq(SqList L, int i, ElemType &e)
{
    if (!L.length)
    {
        printf("Warning: 顺序表为空！没有元素可以获取！\n\n");

        return ERRO;
    }
    else if (i < 1 || i > L.length)
    {
        printf("Erro: 非法位序！\n\n");

        return ERRO;
    }
    e = L.elem[i - 1];
    printf("Success: 成功获取第 %d 号元素 %d\n\n", i, e);

    return OK;
} // GetElem_Sq

Status PutElem_Sq(SqList &L, int i, ElemType e)
{
    if (!L.length)
    {
        printf("Warning: 顺序表为空！没有元素可以修改！\n\n");

        return ERRO;
    }
    else if (i < 1 || i > L.length)
    {
        printf("Erro: 非法位序！\n\n");

        return ERRO;
    }
    L.elem[i - 1] = e;
    printf("Success: 成功修改第 %d 号元素的值为 %d\n\n", i, e);

    return OK;
} // PutElem_Sq

Status LocateElem_Sq(SqList L, int &i, ElemType e)
{
    /* 最笨的实现方法，即一个一个比较，时间复杂度为线性阶 */
    if (!L.length)
    {
        printf("Warning: 顺序表为空表！没有元素可以定位！\n\n");
        return ERRO;
    }
    ElemType *p = L.elem;                // 表头指针
    ElemType *q = &L.elem[L.length - 1]; // 表尾指针
    while ((p++) <= q)
    {
        if (*p == e)
        {
            i = p - L.elem + 1;
            break;
        }
    }
    if (p > q)
    {
        i = 0;
    }
    printf("Info: 元素 %d 的位序为 %d\n\n", e, i);

    return OK;
} // LocateElem_Sq

int Length_Sq(SqList L)
{
    printf("Info: 当前表长为: %d 单位\n\n", L.length);

    return L.length;
}

Status ListInsert_Sq(SqList &L, int i, ElemType e)
{
    // 1. 判断是否有空间插入，若无，重新申请空间
    if (L.length >= L.size)
    {
        ElemType *base;
        base = (ElemType *)realloc(L.elem, (LIST_INCREMENT + L.size) * sizeof(ElemType));
        if (!base)
        {
            printf("Erro: 内存空间不足！无法申请新的空间！\n\n");
            exit(OVERFLOW);
        }
        L.elem = base;
        L.size += LIST_INCREMENT;
        printf(
            "Success: 成功申请了 %d 单位的空间\n"
            "Info: 当前表容量: %d 单位\n\n",
            LIST_INCREMENT, L.size);
    }
    // 2. 判断插入位置是否合法
    if (i < 1 || i > L.length + 1)
    {
        printf("Erro: 插入位置非法！\n\n");
        return ERRO;
    }
    // 3. 元素从后向前右移
    ElemType *cur = &(L.elem[i - 1]);
    ElemType *q = &(L.elem[L.length - 1]); // 表尾元素地址
    while (cur <= q)
    {
        *(q + 1) = *q;
        q--;
    }
    *cur = e;
    L.length++;
    printf("Success: 成功在第 %d 号位置插入元素 %d\n", i, e);
    printf("Info: 当前表长: %d 单位\n\n", L.length);

    return OK;
}

Status ListDelete_Sq(SqList &L, int i, ElemType &e)
{
    if (!L.length)
    {
        printf("Erro: 顺序表为空！没有元素可以删！\n\n");
        return ERRO;
    }
    else if (i < 1 || i > L.length)
    {
        printf("Erro: 非法删除位置！\n\n");
        return ERRO;
    }
    ElemType *p = &(L.elem[i]);
    e = *(p - 1);
    ElemType *q = &(L.elem[L.length - 1]);
    while (p <= q)
    {
        *(p - 1) = *p;
        p++;
    }
    L.length--;
    printf("Success: 成功删除第 %d 号元素 %d\n", i, e);
    printf("当前表长: %d\n\n", L.length);

    return OK;
}