#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define ll long long
typedef pair <ll, ll> pll;
const int maxn = 100000 + 5;

// 功能：中国剩余定理，求解A[i] * x = B[i] (mod M[i]), 总共n个线性方程组
// 接口：pll linear(ll *A, ll *B, ll *M, int n)
// 输入：n个线性方程组的参数，分别存放在A[0],B[0],M[0]到A[n-1],B[n-1],M[n-1]中
// 输出：满足条件的最小的x和最后的LCM

ll a[maxn], b[maxn], m[maxn];

ll gcd(ll a, ll b)
{
	return b == 0 ? a : gcd(b, a % b);
}

void ex_gcd(ll a, ll b, ll &x, ll &y, ll &d)
{
	if (b == 0)
	{
		d = a;
		x = 1;
		y = 0;
	}
	else
	{
		ex_gcd(b, a % b, y, x, d);
		y -= x * (a / b);
	}
}

ll inv(ll t, ll p)
{
	ll d, x, y;
	ex_gcd(t, p, x, y, d);
	return d == 1 ? (x % p + p) % p : -1;
}

//求解A[i] * x = B[i] (mod M[i]), 总共n个线性方程组 
pll linear(ll *A, ll *B, ll *M, int n) 
{
    ll x = 0, m = 1;
    for (int i = 0; i < n; i++) 
	{
        ll a = A[i] * m, b = B[i] - A[i] * x, d = gcd(M[i], a);
        if (b % d != 0)  
			return pll(0, -1);//答案不存在, 返回-1 
        ll t = b / d * inv(a / d, M[i] / d) % (M[i] / d);
        x = x + m * t;
        m *= M[i] / d;
    }
    x = (x % m + m) % m;
    return pll(x, m);//返回的x就是答案, m是最后的lcm值 
}

//POJ 2891
int main()
{
	int n;
	while (scanf("%d", &n) != EOF)
	{
		for (int i = 0; i < n; i++)
		{
			a[i] = 1;
			scanf("%lld %lld", &m[i], &b[i]);
		}
		pll ans = linear(a, b, m, n);
		if (ans.second == -1)	printf("-1\n");
		else	printf("%lld\n", ans.first);
	}
	return 0;
}