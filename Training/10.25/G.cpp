#include<bits/stdc++.h>
using namespace std;
const int maxn=2e6+6;
int g=5,n,r;
int a[maxn];
bitset<2016>bs;
int rmp[3333];

bool check(int g){
	int e=1;
	set<int>S;
	for(int i=1;i<2017;i++){
		e=e*g%2017;
		if(S.count(e))return false;
		S.insert(e);
	}
	return true;
}

int main(){
	/*for(int i=2;;i++)if(check(i)){
		cout<<i<<endl;
		return 0;
	}*/
	int e=1;
	for(int i=0;i+1<2017;i++){
		rmp[e]=i;
		e=e*g%2017;
	}

	while(scanf("%d%d",&n,&r)==2){
		r=rmp[r];
		bs.reset();
		bs[0]=1;
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			a[i]=rmp[a[i]];
		}

		for(int i=1;i<=n;i++){
			bs=bs^(bs<<a[i])^(bs>>(2016-a[i]));	
		}
		printf("%d\n",(int)bs[r]);
	}
	return 0;
}
