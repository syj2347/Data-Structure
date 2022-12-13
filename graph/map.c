//设计并实现一个校园导游程序，为来访的客人提供各种信息查询服务

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 0x3f3f3f3f
typedef struct site
{
    int id;
    char name[20];
    char description[250];
} Site;
int path[100][100];
double dis[100][100];
double d[100][100];
void print(int a, int b)
{
    if (path[a][b] == -1)
        return;
    printf("%d-->", path[a][b]);
    print(path[a][b], b);
}
int main()
{
    // initialize
    int n;
    printf("Please input the number of the sites in school:\n");
    scanf("%d", &n);
    getchar();
    Site *base = (Site *)malloc((n + 1) * sizeof(Site));
    int i;
    for (i = 1; i <= n; i++)
    {
        base[i].id = i;
        printf("Please input the name of the site %d:\n", i);
        gets(base[i].name);
        printf("Please input the description of the site %d:\n", i);
        gets(base[i].description);
    }
    memset(dis, INF, sizeof(dis));
    memset(d, INF, sizeof(d));
    memset(path, -1, sizeof(path));
    int j;
    printf("If there exits no way between sites, please input -1.\n");
    printf("Please input the distance between two sites.\n");
    for (i = 1; i <= n; i++)
    {
        dis[i][i] = 0;
        d[i][i] = 0;
        for (int j = i + 1; j <= n; j++)
        {
            printf("site %d and %d:\n", i, j);
            double r;
            scanf("%lf", &r);
            if (r != -1)
            {
                dis[i][j] = r;
                dis[j][i] = r;
                d[i][j] = r;
                d[j][i] = r;
            }
        }
    }
    // Floyd
    int k;
    for (k = 1; k <= n; k++)
        for (i = 1; i <= n; i++)
            for (j = 1; j <= n; j++)
                if (d[i][j] > d[i][k] + d[k][j])
                {
                    d[i][j] = d[i][k] + d[k][j];
                    path[i][j] = k;
                }

    // inquire
    printf("Please input the site id you want to inquire:(-1 to exit)\n");
    while (1)
    {
        int id;
        scanf("%d", &id);
        if (id == -1)
            break;
        if (id > n || id < 1)
        {
            printf("No such site.\n");
            continue;
        }
        printf("name:%s\n", base[id].name);
        printf("description:%s\n", base[id].description);
    }
    int st = -1, ed = -1;
    printf("Please input the site id of the start and the end(input 0 0 to stop):\n");
    while (1)
    {
        scanf("%d %d", &st, &ed);
        if (st == 0 && ed == 0)
            break;
        if (st > n || st < 1 || ed > n || ed < 1)
        {
            printf("No such site.\n");
            continue;
        }
        if (d[st][ed] == INF)
        {
            printf("There is no way between such two sites\n");
        }
        else if (d[st][ed] == 0)
        {
            printf("The shortest distance is 0.\n");
            printf("The path is:%d->%d\n", st, ed);
        }
        else
        {
            printf("The shortest distance is %lf.\n", d[st][ed]);
            printf("The path is:");
            printf("%d-->", st);
            print(st, ed);
            printf("%d\n", ed);
        }
    }
    return 0;
}