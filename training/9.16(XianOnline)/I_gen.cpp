#include<bits/stdc++.h>
using namespace std;
int len;
string randstr(){
	int l=rand()%len+1;
	string s;
	while(l--){
		s+=rand()%26+'a';
	}
	return s;
}

int main(){
	int T=1;
	printf("%d\n",T);
	while(T--){
		int q=30000;
		printf("%d\n",q);
		len=2e6/q/5*2;
		
		while(q--){
			int ty=rand()%2+1;
			if(ty==1){
				printf("%d %s\n",ty,randstr().c_str());
			}else{
				printf("%d %s %s %s %s\n",ty,randstr().c_str(),randstr().c_str(),randstr().c_str(),randstr().c_str());
			}
		}
		
	}

	return 0;
}
