#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -1
typedef char TElemType;

typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

BiTree CreateBiTree()
{
    char ch;
    scanf("%c", &ch);
    // input '*' means this node is NULL
    if (ch == '*')
        return NULL;
    else
    {
        BiTNode *p = (BiTNode *)malloc(sizeof(BiTNode));
        p->data = ch;
        p->lchild = CreateBiTree();
        p->rchild = CreateBiTree();
        return p;
    }
}

int PrintElement(TElemType e)
{
    printf("%c ", e);
    return OK;
}

int PreOrderTraverse(BiTree T, int (*visit)(TElemType e))
{
    if (T)
    {
        if (visit(T->data))
            if (PreOrderTraverse(T->lchild, visit))
                if (PreOrderTraverse(T->rchild, visit))
                    return OK;
        return ERROR;
    }
    else
        return OK;
}

typedef enum PointerTag
{
    Link,
    Thread
} PointerTag;
// Link:0,Thread:1
typedef struct BiThrNode
{
    TElemType data;
    struct BiThrNode *lchild, *rchild;
    PointerTag LTag, RTag;
} BiThrNode, *BiThrTree;
BiThrTree pre;

int InOrderTraverse_Thr(BiThrTree T, int (*visit)(TElemType e))
{
    BiThrTree p = T->lchild;
    while (p != T)
    {
        while (p->LTag == Link)
            p = p->lchild;
        if (!visit(p->data))
            return ERROR;
        while (p->RTag == Thread && p->rchild != T)
        {
            p = p->rchild;
            visit(p->data);
        }
        p = p->rchild;
    }
    return OK;
}

BiThrTree InThreading(BiTree p)
{
    if (p == 0)
        return NULL;
    BiThrTree T = (BiThrTree)malloc(sizeof(BiThrNode));
    T->data = p->data;
    T->LTag = Link;
    T->RTag = Link;
    T->lchild = InThreading(p->lchild);
    if (p->lchild == NULL)
    {
        T->LTag = Thread;
        T->lchild = pre;
    }
    if (pre->rchild == NULL)
    {
        pre->RTag = Thread;
        pre->rchild = T;
    }
    pre = T;
    T->rchild = InThreading(p->rchild);
    return T;
}

BiThrTree InOrderThreading(BiTree T)
{
    BiThrTree Thrt = (BiThrTree)malloc(sizeof(BiThrNode));
    if (Thrt == 0)
        exit(OVERFLOW);
    Thrt->LTag = Link;
    Thrt->RTag = Thread;
    Thrt->rchild = Thrt;
    if (!T)
        Thrt->lchild = Thrt;
    else
    {
        pre = Thrt;
        Thrt->lchild = InThreading(T);
        pre->rchild = Thrt;
        pre->RTag = Thread;
        Thrt->rchild = pre;
    }
    return Thrt;
}
// levelordertraverse_queue
int Depth_Count(BiTree T)
{
    BiTree p = T;
    BiTree q[1000];
    int front = -1, rear = -1;
    int level = 0, last = 0;
    q[++rear] = p;
    while (front < rear)
    {
        p = q[++front];
        if (p->lchild != NULL)
        {
            q[++rear] = p->lchild;
        }
        if (p->rchild != NULL)
        {
            q[++rear] = p->rchild;
        }
        if (front == last)
        {
            level++;
            last = rear;
        }
    }
    return level;
}
// preordertraverse_stack
int Leaves_Count(BiTree T)
{
    int count = 0;
    int top = -1;
    BiTNode s[1000];
    while (T != NULL || top != -1)
    {
        while (T != NULL)
        {
            if (T->lchild == NULL && T->rchild == NULL)
                count++;
            top++;
            s[top] = *T;
            T = T->lchild;
        }
        if (top != -1)
        {
            T = &s[top];
            top--;
            T = T->rchild;
        }
    }
    return count;
}

void DestroyTree(BiTree T)
{
    if (T == NULL)
        return;
    DestroyTree(T->lchild);
    DestroyTree(T->rchild);
    free(T);
    T = NULL;
    return;
}

void DestroyThrTree(BiThrTree T)
{
    if (T == NULL)
        return;
    if (T->LTag == Link)
        DestroyThrTree(T->lchild);
    if (T->RTag == Link)
        DestroyThrTree(T->rchild);
    free(T);
    T = NULL;
    return;
}

int main()
{
    BiTree a = CreateBiTree();
    printf("depth:%d\nleaves:%d\n", Depth_Count(a), Leaves_Count(a));
    BiThrTree b = InOrderThreading(a);
    InOrderTraverse_Thr(b, PrintElement);
    DestroyTree(a);
    DestroyThrTree(b);
    return 0;
}