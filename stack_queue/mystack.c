#include <stdio.h>
#include <stdlib.h>

//Ë³ÐòÕ»µÄ¿âÊµÏÖ
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef int SElemType;
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
    printf("%d\n", *e);
    return OK;
}
int compare1(SElemType a, SElemType b)
{
    if (a == b)
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
int StackElemPos(SqStack *s, SElemType e, int (*compare)(SElemType, SElemType))
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

int main()
{
    SqStack *a = InitStack();
    int i;
    for (i = 1; i <= 5; i++)
        Push(a, i);
    StackTraverse(a, visit);
    printf("len:%d\n", StackLength(a));
    int ans = -1;
    Pop(a, &ans);
    printf("%d\n", ans);
    printf("len:%d\n", StackLength(a));
    GetTop(a, &ans);
    printf("%d\n", ans);
    printf("pos3:%d\n", StackElemPos(a, 3, compare1));
    DestroyStack(a);
    return 0;
}