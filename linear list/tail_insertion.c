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
} LNode, *LinkList;

int visit(ElemType *x) //用于作为函数参数
{
    printf("%d\n", *x);
    return OK;
}
int equal(ElemType a, ElemType b) //同用于作为函数参数
{
    if (a == b)
        return TRUE;
    else
        return FALSE;
}

LNode *InitList()
{
    //头节点数据域为空
    LNode *Lhead = (LNode *)malloc(sizeof(LNode));
    if (!Lhead)
        exit(OVERFLOW);
    Lhead->next = Lhead;
    return Lhead;
}
int ListEmpty(LNode *L) //判空
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
int DestroyList(LNode *L) //删除链表
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
int ClearList(LNode *L) //清空链表
{
    LNode *p = L;
    while (p->next != L)
    {
        p->data = 0;
        p = p->next;
    }
    return OK;
}
int GetElem(LNode *L, int i, ElemType *e) //得到第i位元素
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
int ListTraverse(LNode *L, int (*visit)(ElemType *)) //遍历对每个元素进行visit操作
{
    LNode *p = L;
    int i;
    int len = ListLength(L);
    for (i = 1; i <= len; i++)
    {
        p = p->next;
        if (!visit(&(p->data)))
            return FAIL;
    }
    return OK;
}
int LocateElem(LNode *L, ElemType e, int (*compare)(ElemType, ElemType)) //找到第一个符合与e满足compare条件的元素
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
int PriorElem(LNode *L, ElemType cur_e, ElemType *pre_e) //返回前一个元素
{
    int pos = LocateElem(L, cur_e, equal);
    if (pos == 0 || pos == 1)
        return FAIL;
    else
        GetElem(L, pos - 1, pre_e);
    return OK;
}
int NextElem(LNode *L, ElemType cur_e, ElemType *next_e) //返回后一个元素
{
    int pos = LocateElem(L, cur_e, equal);
    if (pos == 0 || pos == ListLength(L))
        return FAIL;
    else
        GetElem(L, pos + 1, next_e);
    return OK;
}
LinkList MergeList(LNode *a, LNode *b) //对有序(非递减)链表做合并
{
    LNode *pa = a->next;
    LNode *pb = b->next;
    int i = 1;
    int len = ListLength(a) + ListLength(b);
    while (i <= len && (!ListEmpty(b)))
    {
        if (pa->data <= pb->data)
        {
            pa = pa->next;
        }
        else
        {
            ListInsert(a, i, pb->data);
            LNode *t = pb;
            pb = pb->next;
            ElemType tt = -1;
            ListDelete2(b, t, &tt);
        }
        i++;
    }
    free(b);
    return a;
}
void ReverseList(LinkList a) //就地逆置循环单链表
{
    if (ListEmpty(a))
        return;
    LinkList past = a;
    LNode *p = a->next;
    int i = 1;
    int len = ListLength(a);
    for (i = 1; i <= len + 1; i++)
    {
        LNode *nxt = p->next;
        p->next = past;
        past = p;
        p = nxt;
    }
}

//用尾插法正序建立单链表，n为元素个数，且需要输入对应个数的元素
LinkList CreateList(int n)
{
    LinkList a = InitList();
    LNode *tail = a;
    int i = 1;
    for (i = 1; i <= n; i++)
    {
        ElemType dt;
        scanf("%d", &dt);
        LNode *NewNode = (LNode *)malloc(sizeof(LNode));
        tail->next = NewNode;
        NewNode->next = a;
        NewNode->data = dt;
        tail = tail->next;
    }
    return a;
}
int main()
{
    LinkList a = CreateList(4);
    ListTraverse(a, visit);
    DestroyList(a);
    return 0;
}
