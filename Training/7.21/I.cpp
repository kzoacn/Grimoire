#include<bits/stdc++.h>
using namespace std;
const int maxn=12;
char ans[maxn][maxn];
char mp[maxn][maxn];
int n,m;
char str[11111];
void rot(){
	static char na[maxn][maxn];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			na[n-j+1][i]=mp[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			mp[i][j]=na[i][j];
		}
	}
}
void print(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			putchar(ans[i][j]?ans[i][j]:' ');
		}
		puts("");
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%s",mp[i]+1);
	}
	scanf("%s",str+1);
	m=strlen(str+1);
	int cur=0,ok=1;
	int T=4;
	while(T--){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(mp[i][j]=='.'){
					if(ans[i][j])ok=0;
					ans[i][j]=str[++cur];	
				}
			}
		}
		//cerr<<"before"<<endl;
		//print();
		rot();rot();rot();
		//cerr<<"after"<<endl;
		//print();
	}
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
		if(!ans[i][j])
			ok=0;
	if(!ok){
		puts("invalid grille");
		return 0;
	}		
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
		putchar(ans[i][j]);
	puts("");
	return 0;
}
