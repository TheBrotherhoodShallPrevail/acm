#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#define ll long long

// 功能：扩展BSGS算法求解离散对数：A ^ x = B (mod C), 已知A, B, C求x, C是不是质数都可以
// 接口：int BabyStep(int A, int B, int C)
// 输入：A, B, C
// 输出：x

struct Node
{
	int idx;
	int val;
} baby[1000000];

bool cmp(Node n1, Node n2)
{
	return n1.val != n2.val ? n1.val < n2.val : n1.idx < n2.idx;
}

int gcd(int a, int b)
{
	return b == 0 ? a : gcd(b, a % b);
}

int extend_gcd(int a, int b, int &x, int &y)
{
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	int gcd = extend_gcd(b, a % b, x, y);
	int t = x;
	x = y;
	y = t - a / b * y;
	return gcd;
}

int inval(int a, int b, int n)
{
	int e, x, y;
	extend_gcd(a, n, x, y);
	e = ((ll)x * b) % n;
	return e < 0 ? e + n : e;
}

int PowMod(int a, int b, int MOD)
{
	ll ret = 1 % MOD, t = a % MOD;
	while (b)
	{
		if (b & 1)
			ret = ((ll)ret * t) % MOD;
		t = ((ll)t * t) % MOD;
		b >>= 1;
	}
	return (int)ret;
}

int BinSearch(int num, int m)
{
	int low = 0, high = m - 1, mid;
	while (low <= high)
	{
		mid = (low + high) >> 1;
		if (baby[mid].val == num)	return baby[mid].idx;
		if (baby[mid].val < num)	low = mid + 1;
		else	high = mid - 1;
	}
	return -1;
}

//A ^ x = B (mod C)
int BabyStep(int A, int B, int C)
{
	ll tmp, D = 1 % C;
	int temp;
	for (int i = 0, tmp = 1 % C; i < 100; i++, tmp = ((ll)tmp * A) % C)
	{
		if (tmp == B)
			return i;
	}
	int d = 0;
	while ((temp = gcd(A, C)) != 1)
	{
		if (B % temp) return -1;
		d++;
		C /= temp;
		B /= temp;
		D = ((A / temp) * D) % C;
	}
	int m = (int)ceil(sqrt((double)C));
	for (int i = 0, tmp = 1 % C; i <= m; i++, tmp = ((ll)tmp * A) % C)
	{
		baby[i].idx = i;
		baby[i].val = tmp;
	}
	sort(baby, baby + m + 1, cmp);
	int cnt = 1;
	for (int i = 1; i <= m; i++)
	{
		if (baby[i].val != baby[cnt - 1].val)
			baby[cnt++] = baby[i];
	}
	int am = PowMod(A, m, C);
	for (int i = 0; i <= m; i++, D = ((ll)(D * am)) % C)
	{
		int tmp = inval(D, B, C);
		if (tmp >= 0)
		{
			int pos = BinSearch(tmp, cnt);
			if (pos != -1)
				return i * m + pos + d;
		}
	}
	return -1;
}

//POJ 2417
int main()
{
	int P, B, N;
	while (scanf("%d %d %d", &P, &B, &N) != EOF)
	{
		// if (!P && !B && !N)	break;
		// B ^ ans = N (mod P)
		B %= P;
		N %= P;
		int ans = BabyStep(B, N, P);
		if (ans < 0)	printf("no solution\n");
		else	printf("%d\n", ans);
	}
	return 0;
}