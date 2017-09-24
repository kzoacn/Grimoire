#include<bits/stdc++.h>
using namespace std;
map<string,int>M;
int main(){

M["Baltimore Bullets"]=1;
M["Boston Celtics"]=17;
M["Chicago Bulls"]=6;
M["Cleveland Cavaliers"]=1;
M["Dallas Mavericks"]=1;
M["Detroit Pistons"]=3;
M["Golden State Warriors"]=2;
M["Houston Rockets"]=2;
M["L.A. Lakers"]=11;
M["Miami Heat"]=3;
M["Milwaukee Bucks"]=1;
M["Minneapolis Lakers"]=5;
M["New York Knicks"]=2;
M["Philadelphia 76ers"]=2;
M["Philadelphia Warriors"]=2;
M["Portland Trail Blazers"]=1;
M["Rochester Royals"]=1;
M["San Antonio Spurs"]=5;
M["Seattle Sonics"]=1;
M["St. Louis Hawks"]=1;
M["Syracuse Nats"]=1;
M["Washington Bullets"]=1;

	string s;
	getline(cin,s);
	int t=0;
	while(getline(cin,s)){
		printf("Case #%d: %d\n",++t,M[s]);
	}
	return 0;
}
