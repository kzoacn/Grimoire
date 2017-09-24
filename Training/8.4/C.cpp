#include<bits/stdc++.h>
#define deb(x) cerr<< #x << " = " << x <<endl
using namespace std;
const int maxn=1e6+6;
typedef unsigned long long UL;

int n;
int bel[2][maxn];
int tmp[maxn*2];
int sz[2][maxn];
pair<int,int> a[2][maxn];

int blc[2];
void solve(){
	scanf("%d",&n);
	for(int i=0;i<=n;i++)
		sz[0][i]=sz[1][i]=0;
	
	for(int i=1;i<=n;i++)
		scanf("%d%d",&bel[0][i],&bel[1][i]);
	
	for(int j=0;j<2;j++){
		tmp[0]=0;
		for(int i=1;i<=n;i++)
			tmp[++tmp[0]]=bel[j][i];
		sort(tmp+1,tmp+1+tmp[0]);
		tmp[0]=unique(tmp+1,tmp+1+tmp[0])-tmp-1;
		blc[j]=tmp[0];
		for(int i=1;i<=n;i++){
			bel[j][i]=lower_bound(tmp+1,tmp+1+tmp[0],bel[j][i])-tmp;
			sz[j][bel[j][i]]++;
			a[j][i]=make_pair(bel[j][i],i);
		}
		sort(a[j]+1,a[j]+1+n);
	}
	
	
	int ans[3];
	memset(ans,0,sizeof ans);
	for(int j=0;j<2;j++){
		for(int i=1,k;i<=n;i=k){
			k=i;
			tmp[0]=0;
			while(k<=n&&a[j][i].first==a[j][k].first)k++;
			for(int l=i;l<k;l++){
				tmp[++tmp[0]]=bel[j^1][a[j][l].second];
			}
			sort(tmp+1,tmp+1+tmp[0]);
			
			tmp[0]=unique(tmp+1,tmp+1+tmp[0])-tmp-1;
			int s=0;
			for(int l=1;l<=tmp[0];l++){
				
				s+=sz[j^1][tmp[l]];
			}
			if(s==sz[j][a[j][i].first]){
				if(tmp[0]==1)ans[2]++;
				else ans[j]++;
			}
		}
	}
	
	printf("%d %d %d\n",ans[0],ans[1],ans[2]/2);
}

int main(){
	srand(10086);

	int T;cin>>T;
	for(int t=1;t<=T;t++){
		printf("Case #%d: ",t);
		solve();
	}
	return 0;
}
