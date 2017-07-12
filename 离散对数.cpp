#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#define ll long long

const int MOD = 76543;

// 功能：BSGS算法求解离散对数：a^x = b (mod n),已知a,b,n求x
// 接口：int BSGS(int a, int b, int n)
// 输入：a,b,n
// 输出：x

int hs[MOD], head[MOD], next[MOD], id[MOD], top;

void insert(int x, int y)
{
	int k = x % MOD;
	hs[top] = x, id[top] = y, next[top] = head[k], head[k] = top++;
}

int find(int x)
{
	int k = x % MOD;
	for (int i = head[k]; i != -1; i = next[i])
	{
		if (hs[i] == x)
			return id[i];
	}
	return -1;
}

// a^x = b (mod n)
int BSGS(int a, int b, int n)
{
	memset(head, -1, sizeof(head));
	top = 1;
	if (b == 1)	return 0;
	int m = (int)sqrt(n * 1.0), j;
	ll x = 1, p = 1;
	for (int i = 0; i < m; i++, p = p * a % n)	insert(p * b % n, i);
	for (ll i = m;; i += m)
	{
		if ((j = find(x = x * p % n)) != -1)	return i - j;
		if (i > n)	break;
	}
	return -1;
}

//POJ 3243
int main()
{
	int x, z, k;
	while (scanf("%d %d %d", &x, &z, &k) != EOF)
	{
		if (!x && !z && !k)	break;
		// x^y = k (mod z)
		int ans = BSGS(x, k, z);
		if (ans == -1)	printf("No Solution\n");
		else	printf("%d\n", ans);
	}
}