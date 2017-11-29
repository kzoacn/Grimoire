#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
typedef long long LL;
const int MAGIC=200;
LL p;
int q;
LL g;
LL pw(LL x,LL k,LL p=::p){
	LL ans=1;
	for(;k;k>>=1){
		if(k&1)ans=ans*x%p;
		x=x*x%p;
	}
	return ans%p;
}


bool is_prime(LL p){
	for(int i=2;i*i<=p;i++)if(p%i==0)return false;
	return true;
}

int main(){
	srand(time(0)^getpid());
	p=rand()%200+2;
	while(!is_prime(p))p++;
	
	int q=50;
	cout<<p<<" "<<q<<endl;
	while(q--){
		LL x=rand()%p,z=rand()%p;
		cout<<x<<" "<<pw(x,z,p)<<endl;
	}
	
	return 0;
}
