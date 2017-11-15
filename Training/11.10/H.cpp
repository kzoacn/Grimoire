#include<bits/stdc++.h>
using namespace std;
int n,m;
int c[20][20];
int d[20][20];
int cov[22][(1<<10) +10];

int dp[22][(1<<10) +11];

bool subset(vector<int>S,vector<int>SS){
	for(auto x:SS)
		if(!binary_search(S.begin(),S.end(),x))
			return false;
	return true;
}


bool test(int x,int S){
	for(int i=1;i<=*cov[x];i++){
		if((cov[x][i]&S)==cov[x][i])
			return false;
	}
	return true;
}

int main(){
	int T;cin>>T;
	for(int t=1;t<=T;t++){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++){
			scanf("%d",&c[i][0]);
			for(int j=1;j<=c[i][0];j++)
				scanf("%d",&c[i][j]);
			sort(c[i]+1,c[i]+1+*c[i]);
			*c[i]=unique(c[i]+1,c[i]+1+*c[i])-c[i]-1;
		}
		for(int i=1;i<=m;i++){
			scanf("%d",&d[i][0]);
			for(int j=1;j<=d[i][0];j++)
				scanf("%d",&d[i][j]);
		}
		
		for(int i=1;i<=n;i++){
			
			cov[i][0]=0;
			
			int fob=0;
			for(int j=1;j<=m;j++){
				vector<int>vec;
				for(int o=1;o<=d[j][0];o++)vec.push_back(d[j][o]);
				
				sort(vec.begin(),vec.end());
				vec.erase(unique(vec.begin(),vec.end()),vec.end());
				if(subset(vec,vector<int>(c[i]+1,c[i]+1+*c[i]))){
					if(test(i,1<<(j-1)))
						cov[i][++*cov[i]]=1<<(j-1);
					//fob|=1<<(j-1);
				}
			}
			
			for(int j=1;j<=m;j++)if(!(fob>>(j-1)&1))
			for(int k=j+1;k<=m;k++)if(!(fob>>(k-1)&1)){
				vector<int>vec;
				for(int o=1;o<=d[j][0];o++)vec.push_back(d[j][o]);
				for(int o=1;o<=d[k][0];o++)vec.push_back(d[k][o]);
				
				sort(vec.begin(),vec.end());
				vec.erase(unique(vec.begin(),vec.end()),vec.end());
				if(subset(vec,vector<int>(c[i]+1,c[i]+1+*c[i]))){
					if(test(i,(1<<(j-1)) | (1<<(k-1)) ))
						cov[i][++*cov[i]]=(1<<(j-1)) | (1<<(k-1));
					//fob|= (1<<(j-1)) | (1<<(k-1));
				}
			}
			
			
			for(int j=1;j<=m;j++)if(!(fob>>(j-1)&1))
			for(int k=j+1;k<=m;k++)if(!(fob>>(k-1)&1))
			for(int l=k+1;l<=m;l++)if(!(fob>>(l-1)&1)){
				vector<int>vec;
				for(int o=1;o<=d[j][0];o++)vec.push_back(d[j][o]);
				for(int o=1;o<=d[k][0];o++)vec.push_back(d[k][o]);
				for(int o=1;o<=d[l][0];o++)vec.push_back(d[l][o]);
				
				sort(vec.begin(),vec.end());
				vec.erase(unique(vec.begin(),vec.end()),vec.end());
				if(subset(vec,vector<int>(c[i]+1,c[i]+1+*c[i]))){
					if(test(i,(1<<(j-1)) | (1<<(k-1)) |(1<<(l-1))  ))
						cov[i][++*cov[i]]=(1<<(j-1)) | (1<<(k-1)) |(1<<(l-1));
					//fob|= (1<<(j-1)) | (1<<(k-1)) |(1<<(l-1));
				}
			}
		}
		/*
		for(int i=1;i<=n;i++){
			cerr<<i<<" "<<cov[i][0]<<endl;
			for(int j=1;j<=cov[i][0];j++)
				cerr<<cov[i][j]<<" ";
			cerr<<endl;
		}*/
	
		for(int i=1;i<=n;i++){
			for(int j=0;j<(1<<m);j++){
				dp[i][j]=dp[i-1][j];
				for(int k=1;k<=*cov[i];k++){
					int bit=cov[i][k];
					if((j&bit)==bit)
						dp[i][j]=max(dp[i][j],dp[i-1][j^bit]+1);
				}
			}
		}
		
		int ans=0;
		for(int j=0;j<(1<<m);j++)
			ans=max(ans,dp[n][j]);
		printf("Case #%d: %d\n",t,ans);
	}
	return 0; 
}
