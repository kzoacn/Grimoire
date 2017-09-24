#include<bits/stdc++.h>
using namespace std;
const int maxn=33;
int A[903][903];
int inv(int i){return i;}
void Gauss(int n){
	int r,k;
	for(int i=0;i<n;i++){
		r=i;
		for(int j=i+1;j<n;j++)
			if(A[j][i]>A[r][i])r=j;
		if(r!=i)
			for(int j=0;j<=n;j++)
				swap(A[i][j],A[r][j]);
		for(int k=i+1;k<n;k++){
			int f=A[k][i]*inv(A[i][i])%3;
			if(f)
				for(int j=i;j<=n;j++)
					A[k][j]=(A[k][j]+3-f*A[i][j]%3)%3;
		}				
	}
	for(int i=n-1;i>=0;i--){
		for(int j=i+1;j<n;j++)
			A[i][n]=(A[i][n]+3-A[j][n]*A[i][j]%3)%3;
		A[i][n]=A[i][n]*inv(A[i][i])%3;
	}
}
int mp[maxn][maxn];
pair<int,int> rmp[maxn*maxn];
int a[maxn][maxn];
int n,m,tot;
const int dx[4]={0,0,1,-1};
const int dy[4]={1,-1,0,0};
int main(){
	int T;scanf("%d",&T);	
	while(T--){
		tot=0;
		scanf("%d%d",&n,&m);
		for(int i=0;i<n;i++)
		for(int j=0;j<m;j++){
			scanf("%d",&a[i][j]);
			mp[i][j]=tot;
			rmp[tot]=make_pair(i,j);
			tot++;
		}
		for(int i=0;i<=n*m;i++)
		for(int j=0;j<=n*m;j++)
			A[i][j]=0;
		for(int i=0;i<n;i++)
		for(int j=0;j<m;j++){
			A[mp[i][j]][mp[i][j]]=2;
			A[mp[i][j]][n*m]=3-a[i][j]%3;
			for(int k=0;k<4;k++){
				int x=i+dx[k];
				int y=j+dy[k];
				if(x<0||x>=n||y<0||y>=m)continue;
				A[mp[i][j]][mp[x][y]]=1;
			}
		}
		Gauss(n*m);
		vector<pair<int,int> >ans;
		
		for(int i=0;i<n*m;i++){
			int x=A[i][n*m];
			while(x--)
				ans.push_back(rmp[i]);
			
		}
		
		printf("%d\n",(int)ans.size());
		for(int i=0;i<ans.size();i++)
			printf("%d %d\n",ans[i].first+1,ans[i].second+1);
	}
	return 0;
}

