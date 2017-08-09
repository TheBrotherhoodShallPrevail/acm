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

const int maxn=1e5+10;
const ll mod=1e9+7;

int C[10][10];
int n,m;
ll a[maxn];

ll s[maxn][10];

struct Node{
	int set;
	ll sum[7];
}node[maxn<<2];

ll quick_pow(ll a,ll n){
	ll ans=1;
	while (n){
		if (n&1)
			ans=ans*a%mod;
		a=a*a%mod;
		n>>=1;
	}
	return ans;
}

void init(){
	for (int i=0;i<=5;i++){ // 组合数
		C[i][0]=1;
		for (int j=1;j<=i;j++){
			C[i][j]=C[i-1][j-1]+C[i-1][j];
		}
	}
	for (int i=0;i<100005;i++){
		s[i][0]=0;
		for (int j=0;j<=5;j++){
			if (i>=1)
				s[i][j]=(s[i-1][j]+quick_pow(i,j))%mod;
		}
	}
}

void PushUp(int root){
	for (int i=0;i<=5;i++){
		node[root].sum[i]=(node[root<<1].sum[i]+node[root<<1|1].sum[i])%mod;
	}
}

void PushDown(int root,int l,int r){
	if (~node[root].set){
		int mid=(l+r)>>1;
		node[root<<1].set=node[root].set;
		node[root<<1|1].set=node[root].set;
		for (int i=0;i<=5;i++){
			node[root<<1].sum[i]=(s[mid][i]-s[l-1][i]+mod)%mod*node[root<<1].set%mod;
			node[root<<1|1].sum[i]=(s[r][i]-s[mid][i]+mod)%mod*node[root<<1|1].set%mod;
		}
		node[root].set=-1;
	}
}

void Build(int root,int l,int r){
	node[root].set=-1;
	if (l==r){
		for (int i=0;i<=5;i++){
			node[root].sum[i]=a[l]*quick_pow(l,i)%mod;
		}
		return;
	}
	int mid=(l+r)>>1;
	Build(root<<1,l,mid);
	Build(root<<1|1,mid+1,r);
	PushUp(root);
}

void Update(int root,int l,int r,int xl,int xr,int x){
	if (xl<=l&&xr>=r){
		node[root].set=x;
		for (int i=0;i<=5;i++){
			node[root].sum[i]=(s[r][i]-s[l-1][i]+mod)%mod*x%mod;
		}
		return;
	}
	PushDown(root,l,r);
	int mid=(l+r)>>1;
	if (xl<=mid)
		Update(root<<1,l,mid,xl,xr,x);
	if (xr>mid)
		Update(root<<1|1,mid+1,r,xl,xr,x);
	PushUp(root);
}

ll Query(int root,int l,int r,int k,int xl,int xr){
	if (xl<=l&&xr>=r){
		ll ans=0,tmp=1;
		for (int i=k;i>=0;i--){
			ans=(ans+node[root].sum[i]*C[k][i]%mod*tmp%mod+mod)%mod;
			tmp=tmp*(1-xl)%mod;
		}
		return ans;
	}
	PushDown(root,l,r);
	int mid=(l+r)>>1;
	ll ans=0;
	if (xl<=mid)
		ans=(ans+Query(root<<1,l,mid,k,xl,xr)%mod+mod)%mod;
	if (xr>mid)
		ans=(ans+Query(root<<1|1,mid+1,r,k,xl,xr)%mod+mod)%mod;
	return ans;
}

int main(){
	// freopen("1.txt","r",stdin);
	init();
	scanf("%d %d",&n,&m);
	for (int i=1;i<=n;i++){
		scanf("%I64d",&a[i]);
	}
	Build(1,1,n);
	while (m--){
		char ch;
		ll k;
		int l,r;
		scanf(" %c %d %d %I64d",&ch,&l,&r,&k);
		if (ch=='=')
			Update(1,1,n,l,r,k);
		else if (ch=='?'){
			ll ans=Query(1,1,n,k,l,r);
			printf("%I64d\n",ans);
		}
	}
}