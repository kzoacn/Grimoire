#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long LL;
LL exgcd(LL a,LL b,LL &x,LL &y){
	if(!b){
		x=1;y=0;return a;
	}else{
		LL d=exgcd(b,a%b,x,y);
		LL t=x;
		x=y;
		y=t-a/b*y;
		return d;
	}
}
LL mul(LL x,LL k,LL p){
	LL ans=0;
	for(;k;k>>=1){
		if(k&1)ans=(ans+x)%p;
		x=(x+x)%p;
	}return ans;
}
int n;
LL p[30],a[30];
pair<LL,LL> china(LL n,LL *a,LL *m){
	LL M=1,d,x=0,y;
	for(int i=0;i<n;i++){
		M*=m[i];
	}
	
	for(int i=0;i<n;i++){
		LL w=M/m[i];
		d=exgcd(m[i],w,d,y);
		y=(y%M+M)%M;
		x=(x+mul(mul(y,w,M),a[i],M)%M+M)%M;
	}
	
	return make_pair(M,x);
}
LL China(LL U,LL mo7,LL S){
	static LL a[30],m[30];
	int n=0;
	for(int k=0;k<(::n);k++){
		if(S>>k&1){
			a[n]=::a[k];
			m[n]=::p[k];
			n++;
		}
	}
	a[n]=0;
	m[n]=7;
	n++;
	pair<LL,LL> C=china(n,a,m);
	
	//cerr<<C.first<<" "<<C.second<<endl;
	
	return (U-C.second+C.first)/C.first;
}
LL get(LL U){
	LL ans=0;
	{
		for(int j=1;j<(1<<n);j++){
			int bitcnt=0;
			for(int k=0;k<n;k++)if(j>>k&1)bitcnt++;
			ans+=(bitcnt%2?1LL:-1LL)*China(U,0,j);
		}	
	}
	ans+=(U+6)/7+(U+5)/7+(U+4)/7+(U+3)/7+(U+2)/7+(U+1)/7;
	return U+1-ans;	
}
int main(){
	int T;scanf("%d",&T);
	for(int t=1;t<=T;t++){
		LL ans=0;
		LL l,r;
		cin>>n>>l>>r;
		for(int i=0;i<n;i++)
			cin>>p[i]>>a[i];
		
		ans=get(r)-get(l-1);
		
		printf("Case #%d: ",t);
		cout<<ans<<endl;
	}
	return 0;
}/*
21 14
35 28
105 98
21 14
35 28
105 98
Case #1: 21
Case #2: 14

*/
