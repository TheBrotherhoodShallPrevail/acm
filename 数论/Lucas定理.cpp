#include <cstdio>
using namespace std;
typedef long long ll;

// 功能：Lucas定理，求组合数C(n,m) mod p的值，其中p为素数
// 输入：n,m,p
// 输出：C(n,m)%p
// 接口：int Lucas(int n,int m,int p)
// 时间复杂度：O(log(p)(n))

ll quick_mod(ll a,ll n,ll mod){
    ll res=1;
    while (n){
        if (n&1)    res=res*a%mod;
        a=a*a%mod;
        n>>=1;
    }
    return res;
}

ll Comb(ll a,ll b,ll p){
    if (a<b)    return 0;
    if (a==b)   return 1;
    if (b>a-b)  b=a-b;
    ll ans=1,ca=1,cb=1;
    for (ll i=0;i<b;i++){
        ca=(ca*(a-i))%p;
        cb=(cb*(b-i))%p;
    }
    ans=(ca*quick_mod(cb,p-2,p))%p;
    return ans;
}

ll Lucas(int n,int m,int p){
    ll ans=1;
    while (n&&m&&ans){
        ans=(ans*Comb(n%p,m%p,p))%p;
        n/=p;
        m/=p;
    }
    return ans;
}

int main(){
    int n,m,p;
    while (~scanf("%d %d %d",&n,&m,&p)){
        printf("%lld\n",Lucas(n,m,p));
    }
}