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
// 接口：vector <ll> n_residue(ll N, ll a, ll p)
// 输入：N, p, a, 其中p为素数
// 输出：vector表示x的所有可能情况
// 备注：N次剩余备用模板，能不用这个就不用这个

ll ex_gcd(ll a, ll b, ll &x, ll &y) {
    if (0 == b) {
        x = 1;
        y = 0;
        return a;
    } else {
        int r = ex_gcd(b, a % b, y, x);
        y -= x * (a / b);
        return r;
    }
}

ll pow_mod(ll x, ll k, ll m) {
    ll r = 1 % m;
    while (k) {
        if (1 & k)r = ((r * x) % m + m) % m;
        x = ((x * x) % m + m) % m;
        k >>= 1;
    }
    return r;
}

int g_test(ll g, ll p, vector<ll> &v) {
    ll sz = v.size();
    for (ll i = 0; i < sz; i++)
        if (1 == pow_mod(g, (p - 1) / v[i], p))
            return 0;
    return 1;
}

ll primitive_rt(ll p) {
    ll t = p - 1;
    std::vector<ll> v;
    for (ll i = 2; i <= t / i; i++)
        if (0 == t % i) {
            v.push_back(i);
            while (0 == t % i)
                t /= i;
        }
    if (1 != t)
        v.push_back(t);
    ll g = 1;
    while (true) {
        if (g_test(g, p, v))
            return g;
        g++;
    }
}

ll discrete_log(ll x, ll n, ll m) {
    // x^y = n (mod m)
    map< ll, ll > rec;
    ll s = (ll)sqrt((double)m);
    while (s * s <= m)s++;
    ll cur = 1;
    for (ll i = 0; i < s; i++) {
        rec[cur] = i;
        cur = ((cur * x) % m + m) % m;
    }
    ll mul = cur;
    cur = 1;
    for (ll i = 0; i < s; i++) {
        ll more = (n * pow_mod(cur, m - 2, m) % m + m) % m;
        if (rec.count(more))
            return i * s + rec[more];
        cur = ((cur * mul) % m + m) % m;
    }
    return -1;
}

// x ^ N = a (mod p)
vector <ll> n_residue(ll N, ll a, ll p) {
    vector<ll> res;
    ll g = primitive_rt(p);
    ll m = discrete_log(g, a, p);
    if (a == 0) {
        res.push_back(0);
        return res;
    }
    if (m == -1) {
        return res;
    }
    ll A = N, B = p - 1, C = m, x, y;
    ll d = ex_gcd(A, B, x, y);
    if (C % d != 0) {
        return res;
    }
    x = x * (C / d) % B;
    ll delta = B / d;
    for (ll i = 0; i < d; i++) {
        x = ((x + delta) % B + B) % B;
        res.push_back(pow_mod(g, x, p));
    }
    sort(res.begin(), res.end());
    res.erase(unique(res.begin(), res.end()), res.end());
    return res;
}

// HDU 3930 Wrong Answer
int main() {
    ll N, a, p;
    while (scanf("%lld %lld %lld", &N, &p, &a) != EOF) {
        vector <ll> ans = n_residue(N, a, p);
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
