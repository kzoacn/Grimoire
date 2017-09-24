#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int n;
int cnt[maxn],a[maxn];
int p[maxn],notp[maxn],u[maxn];
long long sum[maxn];
vector<int>fac[maxn];
const int mo=1e9+7;
int main(){
	
	for(int i=1;i<maxn;i++){
		for(int j=i;j<maxn;j+=i)
			fac[j].push_back(i);
	}
	u[1]=1;
	for(int i=2;i<maxn;i++){
		if(!notp[i]){
			u[i]=-1;
			p[++p[0]]=i;
		}
		for(int j=1;j<=p[0]&&(long long)i*p[j]<maxn;j++){
			notp[i*p[j]]=1;
			if(i%p[j]==0){
				u[i*p[j]]=0;
				break;
			}else{
				u[i*p[j]]=-u[i];
			}
		}
	}
	int T;
	scanf("%d",&T);
	while(T--){
		memset(cnt,0,sizeof cnt);
		memset(sum,0,sizeof sum);
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			int x;scanf("%d",&x);
			a[i]=x;
			cnt[x]++;
		}
		
		for(int i=1;i<maxn;i++){
			for(int j=i;j<maxn;j+=i)
				sum[i]+=cnt[j];
		}
		
		long long ans=0;
		
	//	for(int i=1;i<=10;i++)
	//		printf("%d%c",u[i]," \n"[i==10]);
	//	for(int i=1;i<=10;i++)
	//		printf("%d%c",sum[i]," \n"[i==10]);
		
		for(int i=1;i<=n;i++){
			long long res=0;
			for(int j=0;j<fac[a[i]].size();j++){
				int d=fac[a[i]][j];
				res+=(long long)u[d]*sum[d];
			}
			
			long long cop=res-(a[i]==1);
			long long ncop=(n-res)-(a[i]!=1);
			
			//cerr << cop <<" "<< ncop <<endl;
			
			ans=ans+cop*ncop;
		}
		
		ans=(long long)n*(n-1)*(n-2)/6 - ans/2;
		//ans=(ans+mo)%mo;
		cout<< ans <<endl;
	}	
	return 0;
}
