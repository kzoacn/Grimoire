#include<bits/stdc++.h>
using namespace std;

const int maxn=1510;

int n,k;
bitset<maxn>bs[maxn];
bitset<maxn>v[maxn];


int Gauss(int m,int n){
	int now=0;
	for(int i=0;i<n;i++){
		int r=-1;
		for(int j=now;j<m;j++){
			if(bs[j][i]){
				r=j;
				break;
			}
		}
		if(r==-1){
			continue;
		}
		swap(bs[r],bs[now]);
		for(int j=now+1;j<m;j++){
			if(bs[j][i])
				bs[j]^=bs[now];
		}
		now++;
	}
	for(int i=now;i<m;i++){
		if(bs[i][n])
			return 0;
	}
	return 1;
}

int main(){
	while(scanf("%d%d",&n,&k)==2){
		for(int i=0;i<n;i++){
			v[i].reset();
			for(int j=0;j<k;j++){
				int x;scanf("%d",&x);
				if(x%2)v[i][j]=1;
				else v[i][j]=0;
			}
		}
		
		
		int sz=0;
		
		for(int j=0;j<k;j++){
			for(int i=0;i<n;i++)
				bs[sz][i]=v[i][j];
			bs[sz][n]=0;
			sz++;
		}
		
		for(int i=0;i<=n;i++)
			bs[sz][i]=1;
		sz++;
		
		int ans=Gauss(sz,n);
		
		puts(ans?"No":"Yes");
	}

	return 0;
}
