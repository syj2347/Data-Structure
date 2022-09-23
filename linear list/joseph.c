#include <stdio.h>
#include <stdlib.h>

//单向循环单链表
typedef int ElemType;
#define TRUE 1
#define FALSE 0
#define OK 1
#define FAIL 0
#define OVERFLOW -1

typedef struct LNode
{
    ElemType data;
    struct LNode *next;
} LNode;

int visit(ElemType *x)
{
    printf("%d\n", *x);
    return OK;
}
int equal(ElemType a, ElemType b)
{
    if (a == b)
        return TRUE;
    else
        return FALSE;
}

LNode *InitList()
{
    LNode *Lhead = (LNode *)malloc(sizeof(LNode));
    if (!Lhead)
        exit(OVERFLOW);
    Lhead->next = Lhead;
    return Lhead;
}
int ListEmpty(LNode *L)
{
    if (L->next == L)
        return TRUE;
    else
        return FALSE;
}
int ListLength(LNode *L)
{
    int len = 0;
    if (ListEmpty(L))
        return 0;
    LNode *p = L;
    while (p->next != L)
    {
        len++;
        p = p->next;
    }
    return len;
}
int ListInsert(LNode *L, int i, ElemType e)
{
    LNode *p = L;
    int j = 1;
    while (j < i)
    {
        p = p->next;
        j++;
    }
    LNode *NewNode = (LNode *)malloc(sizeof(LNode));
    if (!NewNode)
        exit(OVERFLOW);
    NewNode->next = p->next;
    p->next = NewNode;
    NewNode->data = e;
    return OK;
}
int ListDelete1(LNode *L, int i, ElemType *e) //按传入下标删除对应元素
{
    if (ListEmpty(L) || i < 1 || i > ListLength(L))
        return FAIL;
    LNode *p = L;
    int j = 1;
    for (j = 1; j < i; j++)
    {
        p = p->next;
    }
    *e = p->next->data;
    LNode *q = p->next;
    p->next = p->next->next;
    free(q);
    return OK;
}
int ListDelete2(LNode *L, LNode *r, ElemType *e) //按传入地址删除对应元素
{
    LNode *p = L;
    int i;
    int len = ListLength(L);
    for (i = 1; i <= len; i++)
    {
        if (p->next == r)
        {
            *e = p->next->data;
            p->next = r->next;
            free(r);
            return OK;
        }
        p = p->next;
    }
    return FAIL;
}
int DestroyList(LNode *L)
{
    LNode *p = L;
    while (p->next != L)
    {
        LNode *q = p;
        p = p->next;
        free(q);
    }
    free(p);
    return OK;
}
int ClearList(LNode *L)
{
    LNode *p = L;
    while (p->next != L)
    {
        p->data = 0;
        p = p->next;
    }
    return OK;
}
int GetElem(LNode *L, int i, ElemType *e)
{
    if (i > ListLength(L))
        return FAIL;
    LNode *p = L;
    int j;
    for (j = 1; j <= i; j++)
    {
        p = p->next;
    }
    *e = p->data;
    return OK;
}
int ListTraverse(LNode *L, int (*visit)(ElemType *))
{
    LNode *p = L;
    int i;
    for (i = 1; i <= ListLength(L); i++)
    {
        p = p->next;
        if (!visit(&(p->data)))
            return FAIL;
    }
    return OK;
}
int LocateElem(LNode *L, ElemType e, int (*compare)(ElemType, ElemType))
{
    LNode *p = L;
    int i;
    for (i = 1; i <= ListLength(L); i++)
    {
        p = p->next;
        if (compare(p->data, e))
            return i;
    }
    return 0;
}
int PriorElem(LNode *L, ElemType cur_e, ElemType *pre_e)
{
    int pos = LocateElem(L, cur_e, equal);
    if (pos == 0 || pos == 1)
        return FAIL;
    else
        GetElem(L, pos - 1, pre_e);
    return OK;
}
int NextElem(LNode *L, ElemType cur_e, ElemType *next_e)
{
    int pos = LocateElem(L, cur_e, equal);
    if (pos == 0 || pos == ListLength(L))
        return FAIL;
    else
        GetElem(L, pos + 1, next_e);
    return OK;
}

int main()
{
    LNode *a = InitList();
    int n, m;
    scanf("%d%d", &n, &m);
    int i;
    for (i = 1; i <= n; i++)
    {
        int x;
        scanf("%d", &x);
        ListInsert(a, i, x);
    }
    LNode *p = a;
    int cnt = 1;
    while (!ListEmpty(a))
    {
        if (p == a)
        {
            p = p->next;
            continue;
        }
        if (!(cnt % m))
        {
            int t = -1;
            LNode *q = p;
            p = p->next;
            ListDelete2(a, q, &t);
            printf("%d\n", t);
            cnt = 1;
            m = t;
            continue;
        }
        p = p->next;
        cnt++;
    }
    DestroyList(a);
    return 0;
}