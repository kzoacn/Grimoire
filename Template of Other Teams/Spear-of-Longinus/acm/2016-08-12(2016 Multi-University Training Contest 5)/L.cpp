
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn=50010;
int d[maxn];
int n,a[maxn];
void add(int x,int y){
	if(x==0)return;
	while(x<=n){
		d[x]+=y;
		x+=x&-x;
	}
}
int get(int x){
	int ans=0;
	while(x){
		ans+=d[x];
		x-=x&-x;
	}return ans;
}
int num[maxn],siz;
int big[maxn],small[maxn];
int big2[maxn],small2[maxn];
int main(){
	while(scanf("%d",&n)==1){
	
		siz=0;
	
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			num[++siz]=a[i];
		}
		sort(num+1,num+1+siz);
		siz=unique(num+1,num+1+siz)-num-1;
		for(int i=1;i<=n;i++)
			a[i]=lower_bound(num+1,num+1+siz,a[i])-num;
		
		for(int i=1;i<=n;i++)	
			d[i]=0;
		
		for(int i=n;i>=1;i--){
			big[i]=get((siz-a[i]+1)-1);
			add(siz-a[i]+1,1);
		}	
		for(int i=1;i<=n;i++)	
			d[i]=0;
		
		for(int i=n;i>=1;i--){
			small[i]=get(a[i]-1);
			add(a[i],1);
		}
		
		
		long long ans=0;
		
		long long res1=0,res2=0;
		
		
		//for(int i=1;i<=n;i++)
		//	cerr << big[i] <<" \n"[i==n];
		//for(int i=1;i<=n;i++)
		//	cerr << small[i] <<" \n"[i==n];
		
		for(int i=1;i<=n;i++)
			res1+=big[i];
		for(int i=1;i<=n;i++)
			res2+=small[i];
		
		ans+=res1*res2;
		
		//cerr << res1*res2 << endl;
		//Case 1
		long long tmp=0;
		for(int i=1;i<=n;i++){
			tmp+=(long long)big[i]*small[i];
		}
		//cerr<< tmp <<endl;
		ans-=tmp;
		//Case 2
		for(int i=1;i<=n;i++)	
			d[i]=0;
		
		for(int i=1;i<=n;i++){
			big[i]=get((siz-a[i]+1)-1);
			add(siz-a[i]+1,1);
		}	
		for(int i=1;i<=n;i++)	
			d[i]=0;
		
		for(int i=1;i<=n;i++){
			small[i]=get(a[i]-1);
			add(a[i],1);
		}
		
		for(int i=1;i<=n;i++){
			ans-=(long long)big[i]*small[i];
		}
		
		
		//Case 3
		
		for(int i=1;i<=n;i++)	
			d[i]=0;
		
		for(int i=1;i<=n;i++){
			big[i]=get((siz-a[i]+1)-1);
			add(siz-a[i]+1,1);
		}	
		for(int i=1;i<=n;i++)	
			d[i]=0;
		
		for(int i=n;i>=1;i--){
			big2[i]=get((siz-a[i]+1)-1);
			add(siz-a[i]+1,1);
		}
		
		for(int i=1;i<=n;i++){
			ans-=(long long)big[i]*big2[i];
		}
		
		
		//Case 4


		for(int i=1;i<=n;i++)	
			d[i]=0;
		
		for(int i=n;i>=1;i--){
			small2[i]=get(a[i]-1);
			add(a[i],1);
		}
		for(int i=1;i<=n;i++)	
			d[i]=0;
		
		for(int i=1;i<=n;i++){
			small[i]=get(a[i]-1);
			add(a[i],1);
		}
		
		for(int i=1;i<=n;i++){
			ans-=(long long)small[i]*small2[i];
		}
		
		cout<< ans <<endl;
	}
	return 0;
}/*
2 0 1 0
1 2 0 0
9
2
5
3 2 1 0
0 0 0 0
0
0
0
*/
