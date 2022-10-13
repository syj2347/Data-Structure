#include <stdio.h>
#include <stdlib.h>

typedef int QElemType;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1

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

int compareid(QElemType x, QElemType y)
{
    if (x == y)
        return 1;
    return 0;
}

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
int QueueElemPos(LinkQueue *q, QElemType e, int (*compare)(QElemType, QElemType))
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

int main()
{
    LinkQueue *a = InitQueue();
    int i;
    for (i = 1; i <= 5; i++)
        Enqueue(a, i);
    printf("pos5:%d\n", QueueElemPos(a, 5, compareid));
    int ans = -1;
    DeQueue(a, &ans);
    printf("%d\n", ans);
    DeQueue(a, &ans);
    printf("%d\n", ans);
    DeQueue(a, &ans);
    printf("%d\n", ans);
    DestroyQueue(a);
    return 0;
}
