#include<bits/stdc++.h>
using namespace std;
int T;
string sp;
int n,g;
string rk[22][22];

bool is_adv(int x,int y){
	set<string>S;
	for(int j=1;j<=20;j++){
		for(int i=1;i<=5;i++){
			if(S.count(rk[i][j]))continue;
			S.insert(rk[i][j]);
			if(!--x)goto EC;
		}
	}
	EC:
	if(y)for(int i=1;i<=20;i++){
		if(S.count(rk[6][i]))continue;
		S.insert(rk[6][i]);
		if(!--y)break;
	}
	return S.count(sp);
}

int main(){
	cin>>T;
	while(T--){
		cin>>g>>sp;
		for(int i=1;i<=5;i++){
			for(int j=1;j<=20;j++)
				cin>>rk[i][j];
		}
		
		for(int j=1;j<=20;j++)
			cin>>rk[6][j];
		
		
		int ymin=100;
		for(int x=0;x<=g;x++){
			int y=g-x;
			if(is_adv(x,y)){
				
			}else{
				ymin=min(y,ymin);
			}
		}
		static int tt=0;
		if(ymin==100)
			printf("Case #%d: ADVANCED!\n",++tt);
		else
			printf("Case #%d: %d\n",++tt,ymin);
	}
	return 0;
}
