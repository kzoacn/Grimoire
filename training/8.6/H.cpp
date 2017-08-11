#include<bits/stdc++.h>
using namespace std;
char mp[66][66];
int n=4;

bool check(int x,int y){
	int bit=0;

	bit|=(1<<(mp[x][y]-'0'));
	bit|=(1<<(mp[x+1][y]-'0'));
	bit|=(1<<(mp[x][y+1]-'0'));
	bit|=(1<<(mp[x+1][y+1]-'0'));

	return bit==30;
}

bool checkr(int r){
	int bit=0;
	for(int j=1;j<=n;j++){
		if(mp[r][j]=='*')return true;
		bit|=1<<(mp[r][j]-'0');
	}
	if(bit!=30)return false;
	return true;
}
bool checkc(int c){
	int bit=0;
	for(int j=1;j<=n;j++){
		if(mp[j][c]=='*')return true;
		bit|=1<<(mp[j][c]-'0');
	}
	if(bit!=30)return false;
	return true;
}

bool check(){
	for(int i=1;i<=n;i++){
		int bit=0;
		for(int j=1;j<=n;j++){
			bit|=1<<(mp[i][j]-'0');
		}
		if(bit!=30)return false;
	}

	for(int i=1;i<=n;i++){
		int bit=0;
		for(int j=1;j<=n;j++)
			bit|=1<<(mp[j][i]-'0');
		if(bit!=30)return false;
	}
	if(!check(1,1))return false;
	if(!check(1,3))return false;
	if(!check(3,1))return false;
	if(!check(3,3))return false;

	return true;
}
bool dfs(int x,int y){
	if(y==n+1){
		x++;
		y=1;
	}
	if(x==n+1){
		if(check()){
			return true;
		}
		return false;
	}
	if(mp[x][y]=='*'){
		
		for(int i=1;i<=4;i++){
			mp[x][y]=i+'0';
			if(!checkr(x)||!checkc(y))
				continue;
			if(dfs(x,y+1))
				return true;
		}

		mp[x][y]='*';
		return false;
	}else return dfs(x,y+1);
	return false;
}


void solve(){
	for(int i=1;i<=n;i++){
		scanf("%s",mp[i]+1);
//		for(int j=1;j<=n;j++)
//			mp[i][j]-='0';
	}
	dfs(1,1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)
			putchar(mp[i][j]);
		puts("");
	}
}

int main(){
	int T;cin>>T;
	for(int t=1;t<=T;t++){
		printf("Case #%d:\n",t);
		solve();
	}
	return 0;
}
