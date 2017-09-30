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

typedef long long ll;

int kase = 0;

// 功能：N次剩余，x ^ N = a (mod p), 已知N, p, a, 其中p为素数, 求x的所有可能情况
// 接口：vector <ll> residue(ll p, ll N, ll a)
// 输入：N, p, a, 其中p为素数
// 输出：vector表示x的所有可能情况

ll mul(ll a, ll b, ll m) {
    ll ret = 0;
    a %= m;
    while (b) {
        if (b & 1) ret = (ret + a) % m;
        a = (a + a) % m;
        b >>= 1;
    }
    return ret;
}
ll a_b_MOD_c(ll a, ll b, ll m) {
    ll ret = 1;
    a %= m;
    while (b) {
        if (b & 1) ret = mul(ret, a, m);
        a = mul(a, a, m);
        b >>= 1;
    }
    return ret;
}

ll ext_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) { x = 1, y = 0; return a; }
    ll ret = ext_gcd(b, a % b, y, x);
    y -= a / b * x;
    return ret;
}
vector<ll> a;
bool g_test(ll g, ll p) {
    for (ll i = 0; i < a.size(); ++i)
        if (a_b_MOD_c(g, (p - 1) / a[i], p) == 1)
            return 0;
    return 1;
}
ll pri_root(ll p) {
    a.clear();
    ll tmp = p - 1;
    for (ll i = 2; i <= tmp / i; ++i)
        if (tmp % i == 0) {
            a.push_back(i);
            while (tmp % i == 0)
                tmp /= i;
        }
    if (tmp != 1)
        a.push_back(tmp);
    ll g = 1;
    while (true) {
        if (g_test(g, p))
            return g;
        ++g;
    }
}
const int HASH_MOD = 9876543;
ll key[HASH_MOD], val[HASH_MOD];
int head[HASH_MOD], nxt[HASH_MOD];
struct Hash {
    int tot;
    void init() {
        memset(head, -1, sizeof(head));
        tot = 0;
    }
    ll insert(ll x, ll y) {
        int k = x % HASH_MOD;
        key[tot] = x;
        val[tot] = y;
        nxt[tot] = head[k];
        head[k] = tot++;
    }
    ll find(ll x) {
        int k = x % HASH_MOD;
        for (int i = head[k]; i != -1; i = nxt[i])
            if (key[i] == x)
                return val[i];
        return -1;
    }
} hs;
//求解模方程a^x=b(mod m),n为素数,无解返回-1
//注意：要求0 < a < m; 0 <= b < m; 否则按题意自己转化。
//复杂度O(sqrt(m))
ll log_mod(ll a, ll b, ll m) {
    hs.init();
    ll s = ceil(sqrt(m + 0.5));
    ll cur = 1;
    for (int i = 0; i < s; ++i) {
        if (hs.find(cur) == -1) hs.insert(cur, i); //记得先判重，在插入
        cur = cur * a % m;
    }

    ll v = a_b_MOD_c(a, (m - s - 1 + m) % m, m);
    for (int i = 0; i < s; ++i) {
        ll tmp = hs.find(b);
        if (tmp != -1)
            return s * i + tmp;
        b = b * v % m;
    }
    return -1;
}
/*n次剩余
  任务：
  给定N, a, p, 求出(x^N)%p=a 在模p意义下的所有解x。
  说明：
  令g为p的原根，因为p为素数，所以phi(p)=p-1。
  由原根的性质得：
  如果g为p的原根，则：g^i mod p != g^j mod p (p为素数), 其中i != j且i, j介於1至(p-1)之间
  所以，可以设g^y=x, g^t=a，则有：
  g^(y*N)%p=g^t
  又由原根的性质：
  g^(y*N)%p=g^t -> (y*N)%(p-1)=t (此方程可以由拓展欧几里得解)
  另外g^t=a可以由离散对数求出
 */
vector <ll> residue(ll p, ll N, ll a) {
    ll g = pri_root(p);
    g %= p;
    ll m = log_mod(g, a, p);
    vector<ll> ret;
    if (a == 0) {
        ret.push_back(0);
        return ret;
    }
    if (m == -1)
        return ret;
    ll A = N, B = p - 1, C = m, x, y;
    ll d = ext_gcd(A, B, x, y);
    if (C % d != 0) return ret;
    x = x * (C / d) % B;
    ll delta = B / d;
    for (int i = 0; i < d; ++i) {
        x = ((x + delta) % B + B) % B;
        ret.push_back(a_b_MOD_c(g, x, p));
    }
    sort(ret.begin(), ret.end());
    ret.erase(unique(ret.begin(), ret.end()), ret.end());
    return ret;
}

// HDU 3930
int main() {
    ll N, a, p;
    while (scanf("%lld %lld %lld", &N, &p, &a) != EOF) {
        vector <ll> ans = residue(p, N, a);
        printf("case%d:\n", ++kase);
        if (ans.size() == 0) {
            printf("-1\n");
            continue;
        }
        for (int i = 0; i < ans.size(); i++) {
            printf("%lld\n", ans[i]);
        }
    }
}
