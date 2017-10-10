#include<bits/stdc++.h>
using namespace std;
int n;
int a[22];
int b[22][3],sz[5];
int m;
double calc(){	
	double ans=0;
	for(int i=0;i<m;i++){
		double p=(b[i][0]+b[i][1]+b[i][2])/2.0;
		double s=p;
		s*=p-b[i][0];
		s*=p-b[i][1];
		s*=p-b[i][2];
		if(s>0){
			s=sqrt(s);
			ans+=s;
		}
	}
	return ans;
}
int main(){
	while(scanf("%d",&n)==1&&n){
		static int id[22];		
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			id[i]=(i-1)/3;
		}
		m=(n/3)*3;
		double ans=0;
		do{
			memset(sz,0,sizeof sz);
			for(int i=1;i<=n;i++){
				b[id[i]][sz[id[i]]++]=a[i];
			}
			ans=max(ans,calc());
		}while(next_permutation(id+1,id+1+n));
		printf("%.2f\n",ans);
	}
	return 0;
}
