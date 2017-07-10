#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

const double eps = 1e-8;
const int maxn = 1010;

// 功能：Graham扫描法求凸包
// 接口：void Graham(int n)
// 输入：n个点，存放在list[0]到list[n-1]中
// 输出：凸包，Stack[0]到Stack[top-1]为凸包上的点

int sgn(double x)
{
    if (fabs(x) < eps)    return 0;
    if (x > 0)    return 1;
    if (x < 0)    return -1;
}

struct Point
{
    double x, y;
    Point() {}
    Point (double a, double b)
    {
        x = a, y = b;
    }
    Point operator + (const Point &b) const
    {
        return Point(x + b.x, y + b.y);
    }
    Point operator - (const Point &b) const
    {
        return Point(x - b.x, y - b.y);
    }
    //叉积
    double operator ^ (const Point &b) const
    {
        return x * b.y - y * b.x;
    }
    //点积
    double operator * (const Point &b) const
    {
        return x * b.x + y * b.y;
    }
    //绕原点旋转角度B（弧度值）后x,y的变化
    void transXY(double B)
    {
        double tx = x, ty = y;
        x = tx * cos(B) - ty * sin(B);
        y = tx * sin(B) + ty * cos(B);
    }
};

double dist(Point a, Point b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

Point list[maxn];
int Stack[maxn], top;

bool _cmp(Point p1, Point p2)
{
    double tmp = (p1 - list[0]) ^ (p2 - list[0]);
    if (sgn(tmp) > 0)    return true;
    else if (sgn(tmp) == 0 && sgn(dist(p1, list[0]) - dist(p2, list[0])) <= 0)
        return true;
    else    return false;
}

void Graham(int n)
{
    Point p0;
    int k = 0;
    p0 = list[0];
    for (int i = 1; i < n; i++)
    {
        if ((p0.y > list[i].y) || (p0.y == list[i].y && p0.x > list[i].x))
        {
            p0 = list[i];
            k = i;
        }
    }
    swap(list[k], list[0]);
    sort(list + 1, list + n, _cmp);
    if (n == 1)
    {
        top = 1;
        Stack[0] = 0;
        return;
    }
    if (n == 2)
    {
        top = 2;
        Stack[0] = 0;
        Stack[1] = 1;
        return;
    }
    Stack[0] = 0;
    Stack[1] = 1;
    top = 2;
    for (int i = 2; i < n; i++)
    {
        while (top > 1 && sgn((list[Stack[top - 1]] - list[Stack[top - 2]]) ^ (list[i] - list[Stack[top - 2]])) <= 0)
            top--;
        Stack[top++] = i;
    }
}

int main()
{
    int n;
    while (scanf("%d", &n) != EOF && n)
    {
        for (int i = 0; i < n; i++)
            scanf("%lf %lf", &list[i].x, &list[i].y);
        if (n==1)
        {
            printf("0.00\n");
            continue;
        }
        if (n==2)
        {
            printf("%.2f\n",dist(list[0],list[1]));
            continue;
        }
        Graham(n);
        double ans = 0;
        for (int i = 0; i < top - 1; i++)
        {
            ans += dist(list[Stack[i]], list[Stack[i + 1]]);
        }
        ans += dist(list[Stack[top - 1]], list[Stack[0]]);
        printf("%.2f\n", ans);
    }
    return 0;
}