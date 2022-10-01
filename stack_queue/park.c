#include <stdio.h>
#include <stdlib.h>

//停车场问题
typedef struct
{
    int id;
    int a;
    int d;
} Car;
#define STACK_INIT_SIZE 1010
#define STACKINCREMENT 10
typedef Car SElemType;
typedef Car QElemType;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1

typedef struct
{
    SElemType *base;
    SElemType *top;
    int stacksize;
} SqStack;

int visit(SElemType *e)
{
    printf("%d %d %d\n", e->id, e->a, e->d);
    return OK;
}
int compareid(Car x, Car y) //专用于查询Car结构体作为数据成员时位置的比较函数
{
    if (x.id == y.id)
        return 1;
    return 0;
}

SqStack *InitStack()
{
    SqStack *s = (SqStack *)malloc(sizeof(SqStack));
    s->base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if (!s->base)
        exit(OVERFLOW);
    s->top = s->base;
    s->stacksize = STACK_INIT_SIZE;
    return s;
}
int GetTop(SqStack *s, SElemType *e)
{
    if (s->top == s->base)
        return ERROR;
    (*e) = *(s->top - 1);
    return OK;
}
int Push(SqStack *s, SElemType e)
{
    if (s->top - s->base >= s->stacksize)
    {
        s->base = (SElemType *)realloc(s->base, (s->stacksize + STACKINCREMENT) * sizeof(SElemType));
        if (!(s->base))
            exit(OVERFLOW);
        s->top = s->base + s->stacksize;
        s->stacksize += STACKINCREMENT;
    }
    *((s->top)++) = e;
    return OK;
}
int Pop(SqStack *s, SElemType *e)
{
    if (s->top == s->base)
        return ERROR;
    (*e) = *(--(s->top));
    return OK;
}
int StackTraverse(SqStack *s, int (*visit)(SElemType *))
{
    if (s->base == s->top)
        return ERROR;
    SElemType *p = s->base;
    for (; p != s->top; p++)
    {
        if (!(visit(p)))
            return ERROR;
    }
    return OK;
}
int DestroyStack(SqStack *s)
{
    free(s->base);
    free(s);
    return OK;
}
int StackLength(SqStack *s)
{
    return (s->top) - (s->base);
}
int StackElemPos(SqStack *s, SElemType e, int (*compare)(SElemType, SElemType)) //返回与compare函数匹配的成员位置
{
    int i = 1;
    int len = StackLength(s);
    for (i = 1; i <= len; i++)
    {
        if (compare(*((s->base) + i - 1), e))
            return i;
    }
    return 0;
}

typedef struct QNode
{
    QElemType data;
    struct QNode *next;
} QNode, *QueuePtr;

typedef struct
{
    QueuePtr front;
    QueuePtr rear;
} LinkQueue;

LinkQueue *InitQueue()
{
    LinkQueue *q = (LinkQueue *)malloc(sizeof(LinkQueue));
    q->front = q->rear = (QueuePtr)malloc(sizeof(QNode));
    if (!(q->front))
        exit(OVERFLOW);
    q->front->next = NULL;
    return q;
}
int DestroyQueue(LinkQueue *q)
{
    while (q->front)
    {
        q->rear = q->front->next;
        free(q->front);
        q->front = q->rear;
    }
    return OK;
}
int Enqueue(LinkQueue *q, QElemType e)
{
    QNode *p = (QueuePtr)malloc(sizeof(QNode));
    if (!p)
        exit(OVERFLOW);
    p->data = e;
    p->next = NULL;
    q->rear->next = p;
    q->rear = p;
    return OK;
}
int DeQueue(LinkQueue *q, QElemType *e)
{
    if (q->front == q->rear)
        return ERROR;
    QueuePtr p = q->front->next;
    (*e) = p->data;
    q->front->next = p->next;
    if (q->rear == p)
        q->rear = q->front;
    free(p);
    return OK;
}
int QueueElemPos(LinkQueue *q, QElemType e, int (*compare)(QElemType, QElemType)) //返回与compare函数匹配的成员位置
{
    int i = 1;
    QNode *p = q->front->next;
    while (1)
    {
        if (compare(p->data, e))
            return i;
        if (p == q->rear)
            break;
        p = p->next;
        i++;
    }
    return 0;
}

//输入数据
/*2
('A',1,5),('A',2,10),('D',1,15),('A',3,20),('A',4,25),('A',5,30),('D',2,35),('D',4,40),('E',0,0)*/
int main()
{
    int n;
    scanf("%d", &n);
    getchar(); //读取换行符
    SqStack *park = InitStack();
    LinkQueue *channel = InitQueue();
    SqStack *out = InitStack();
    char x;
    int t, ttime;
    while (scanf("('%c',%d,%d)", &x, &t, &ttime))
    {
        getchar(); //读取逗号(最后一个循环读取换行符)
        Car cc;
        cc.id = t;
        if (x == 'A')
        {
            cc.a = ttime;
            if (StackLength(park) < n)
            {
                Push(park, cc);
                printf("park:%d\n", StackElemPos(park, cc, compareid)); //根据id返回对应位置
            }
            else
            {
                Enqueue(channel, cc);
                printf("channel:%d\n", QueueElemPos(channel, cc, compareid));
            }
        }
        else if (x == 'D')
        {
            int pos = StackElemPos(park, cc, compareid);
            printf("time:%d\n", ttime - ((park->base + pos - 1)->a));
            int i = StackLength(park);
            while (i >= pos)
            {
                Car temp1;
                Pop(park, &temp1);
                if (i != pos)
                    Push(out, temp1);
                i--;
            }
            i = StackLength(out);
            while (i--)
            {
                Car temp1;
                Pop(out, &temp1);
                Push(park, temp1);
            }
            if (channel->front != channel->rear)
            {
                Car temp2;
                DeQueue(channel, &temp2);
                temp2.a = ttime;
                Push(park, temp2);
            }
        }
        else
            break;
    }
    DestroyStack(park);
    DestroyStack(out);
    DestroyQueue(channel);
    return 0;
}
