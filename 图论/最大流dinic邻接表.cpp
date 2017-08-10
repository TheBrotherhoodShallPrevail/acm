#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>
#include <queue>
#include <set>
#include <map>
using namespace std;
#define ll long long

const int maxn = 210;
const int MAX = 1 << 26;

// 功能：最大流Dinic模板邻接表形式
// 接口：void addedge(int u,int v,int c) 加边
//      int dinic(int s, int t) 最大流
// 输入：网络流图，源点s和汇点t
// 输出：最大流

struct Edge {
    int u, v, c;
    int next;
} edge[20 * maxn];

int n, m;
int e;//边数
int p[maxn];//父亲
int d[maxn];
int s, t; //源点，汇点

void addedge(int u, int v, int c)
{
    edge[e].u = u; 
    edge[e].v = v; 
    edge[e].c = c;
    edge[e].next = p[u]; 
    p[u] = e++;

    edge[e].u = v; 
    edge[e].v = u; 
    edge[e].c = 0;
    edge[e].next = p[v]; 
    p[v] = e++;
}

int bfs()
{
    queue <int> q;
    memset(d, -1, sizeof(d));
    d[s] = 0;
    q.push(s);
    while (!q.empty())
    {
        int cur = q.front();
        q.pop();
        for (int i = p[cur]; i != -1; i = edge[i].next)
        {
            int u = edge[i].v;
            if (d[u] == -1 && edge[i].c > 0)
            {
                d[u] = d[cur] + 1;
                q.push(u);
            }
        }
    }
    return d[t] != -1;
}

int dfs(int a, int b)
{
    int r = 0;
    if (a == t)
        return b;
    for (int i = p[a]; i != -1 && r < b; i = edge[i].next)
    {
        int u = edge[i].v;
        if (edge[i].c > 0 && d[u] == d[a] + 1)
        {
            int x = min(edge[i].c, b - r);
            x = dfs(u, x);
            r += x;
            edge[i].c -= x;
            edge[i ^ 1].c += x;
        }
    }
    if (!r)
        d[a] = -2;
    return r;
}

int dinic(int s, int t)
{
    int total = 0, t;
    while (bfs())
    {
        while (t = dfs(s, MAX))
            total += t;
    }
    return total;
}

int main()
{
    int i, u, v, c;
    while (~scanf("%d%d", &m, &n))
    {
        e = 0; //初始化
        memset(p, -1, sizeof(p));
        s = 1; t = n;
        for (i = 0; i < m; i++)
        {
            scanf("%d %d %d", &u, &v, &c);
            addedge(u, v, c);
        }
        printf("%d\n", dinic(s, t));
    }
    return 0;
}