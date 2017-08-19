#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// 功能：扩展Lucas定理求C(n,m)%mod，mod可以为任何数
// 接口：ll ex_Lucas(ll n,ll m,ll mod)
// 输入：n，m，mod
// 输出：C(n,m)%mod

ll n,m,mod;

ll quick_pow(ll a,ll n,ll mod){
    ll ans=1;
    while (n){
        if (n&1)    ans=ans*a%mod;
        a=a*a%mod;
        n>>=1;
    }
    return ans;
}
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if (!b){
        x=1,y=0;
    }
    else{ 
        exgcd(b,a%b,y,x);
        y-=a/b*x;
    }
}
ll inv(ll n,ll mod)
{
    if (!n) 
        return 0;
    ll a=n,b=mod,x=0,y=0;
    exgcd(a,b,x,y);
    x=((x%b)+b)%b;
    if (!x) 
        x+=b;
    return x;
}
ll Mul(ll n,ll pi,ll pk){
    if (!n) 
        return 1;
    ll ans=1;
    if (n/pk){
        for (ll i=2;i<=pk;i++){
            if (i%pi){
                ans=ans*i%pk;
            }
        }
        ans=quick_pow(ans,n/pk,pk);
    }
    for (ll i=2;i<=n%pk;i++){
        if (i%pi){
            ans=ans*i%pk;
        }
    }
    return ans*Mul(n/pi,pi,pk)%pk;
}

ll C(ll n,ll m,ll mod,ll pi,ll pk){
    if (m>n) 
        return 0;
    ll a=Mul(n,pi,pk),b=Mul(m,pi,pk),c=Mul(n-m,pi,pk);
    ll k=0,ans;
    for (ll i=n;i;i/=pi)    k+=i/pi;
    for (ll i=m;i;i/=pi)    k-=i/pi;
    for (ll i=n-m;i;i/=pi)  k-=i/pi;
    ans=a*inv(b,pk)%pk*inv(c,pk)%pk*quick_pow(pi,k,pk)%pk;
    return ans*(mod/pk)%mod*inv(mod/pk,pk)%mod;
}

ll ex_Lucas(ll n,ll m,ll mod){
    ll ans=0;
    for (ll x=mod,i=2;i<=mod;i++){
        if (x%i==0){
            ll pk=1;
            while (x%i==0){
                pk*=i,x/=i;
            }
            ans=(ans+C(n,m,mod,i,pk))%mod;
        }
    }
    return ans;
}
int main()
{
    scanf("%lld %lld %lld",&n,&m,&mod);
    ll ans=ex_Lucas(n,m,mod);
    printf("%lld\n",ans);
}