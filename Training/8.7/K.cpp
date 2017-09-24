#include<bits/stdc++.h>
using namespace std;
char mp[10][33];
int n=7,m=21;

int calc(int x,int y){
	int cnt=0;
	for(int i=0;i<7;i++){
		for(int j=0;j<5;j++)
			cnt+=(mp[x+i][y+j]=='X');
	}
	cnt/=2;
	if(cnt==2)return 1;
	if(cnt==3)return 7;
	if(cnt==4)return 4;
	if(cnt==5){
		if(mp[x+1][y]=='X')return 5;
		if(mp[x+4][y]=='X')return 2;
		return 3;
	}
	if(cnt==6){
		if(mp[x+3][y+1]=='X'){
			if(mp[x+4][y]=='X')
				return 6;
			return 9;
		}
		return 0;
	}
	if(cnt==7)return 8;
	return -1;
}

void solve(){
	for(int i=1;i<=n;i++)
		scanf("%s",mp[i]+1);
	int a1=calc(1,1);
	int a2=calc(1,6);
	int a3=calc(1,13);
	int a4=calc(1,18);

	printf("%d%d:%d%d\n",a1,a2,a3,a4);
}

int main(){
	int T;cin>>T;
	while(T--)
		solve();
	return 0;
}
