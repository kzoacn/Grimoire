#include<bits/stdc++.h>
using namespace std;
typedef __int128 LL;
const LL BASE[12]={2,3,5,7,11,13,17,19,23,29,31,37};
LL get(){
	LL x=0;
	char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return x;
}
void putLL(LL x){
	if(x<10)putchar(x+'0');
	else{
		putLL(x/10);
		putchar(x%10+'0');
	}
}
LL mul(LL x,LL y,LL p){
	LL ans=0;
	for(;y;y>>=1){
		if(y&1)ans=(ans+x)%p;
		x=(x+x)%p;
	}
	return ans%p;
}
LL pw(LL x,LL k,LL p){
	LL ans=1%p;
	for(;k;k>>=1){
		if(k&1)ans=mul(ans,x,p);
		x=mul(x,x,p);
	}
	return ans;
}
LL gcd(LL a,LL b){
	if(!b)return a;
	return gcd(b,a%b);
}
bool check(LL n,int base){
	LL n2=n-1,res;
	int s=0;
	while(n%2==0)n2>>=1,s++;
	res=pw(base,n2,n);
	if(res==1||res==n-1)return 1;
	while(s--){
		res=mul(res,res,n);
		if(res==n-1)return 1;
	}
	return 0;
}
bool isprime(LL n){
	if(n==2)
		return true;
	if(n<2||n%2==0)
		return false;
	for(int i=0;i<12&&BASE[i]<n;i++){
		if(!check(n,BASE[i]))
			return false;
	}
	return true;
}
LL rnd(){
	LL x=((LL)rand()<<32)|((LL)rand()<<16) | rand();	
	if(x<0)x=-x;
	return x;
}
LL prho(LL n,LL c){
	LL i=1,k=2,x=rnd()%(n-1)+1,y=x;
	while(1){
		i++;x=(mul(x,x,n)+c)%n;
		LL d=gcd((y-x+n)%n,n);
		if(d>1&&d<n)return d;
		if(y==x)return n;
		if(i==k)y=x,k<<=1;
	}
}
void _factor(LL n,vector<LL>&fat){
	if(n==1)return ;
	if(isprime(n)){
		fat.push_back(n);
		return ;
	}
	LL p=n;
	while(p>=n)p=prho(p,rnd()%(n-1)+1);
	_factor(p,fat);
	_factor(n/p,fat);
}
int p[int(2e5+5)];
bool notp[int(2e5+5)];
void sieve(){
	for(int i=2;i<2e5;i++){
		if(!notp[i]){
			p[++p[0]]=i;
			for(int j=i+i;j<2e5;j+=i)
				notp[j]=1;			
		}
	}
}
void factor(LL n,vector<LL>&fat){
//cerr<<"factoring ";putLL(n);cerr<<endl;
	for(int i=1;i<=p[0];i++){
		while(n%p[i]==0){
			fat.push_back(p[i]);
		//	cerr<<"push "<<p[i]<<endl;
			n/=p[i];
		}
	}
	/*cerr<<"testing "<<" ";
	putLL(n);cerr<<endl;
	
	cerr<<"checking "<<isprime(n)<<endl;*/
	_factor(n,fat);
}

long long solve(LL k){
	if(k==1)return 0;
	vector<LL>fat;
	factor(k,fat);
	map<LL,int>M;
	for(auto x:fat)
		M[x]++;
	long long ans=1;
	for(auto x:M)
		ans=ans*x.second;
	return ans;
}

void add(vector<LL>&vec1,vector<LL>&vec2){
	for(auto x:vec2)
		vec1.push_back(x);
}
LL calc(vector<LL>fat){
	map<LL,int>M;
	for(auto x:fat)
		M[x]++;
	long long ans=1;
	for(auto x:M)
		ans*=x.second;
	return ans;
}
int main(){
	sieve();/*
	for(int i=1;i<=10;i++)
		cerr<<p[i]<<endl;
	return 0;*/
	srand(23);
	
	/*LL lim=1e24;
	for(LL i=lim;i>=lim-2000;i--){
		putLL(i);putchar(' ');
		cout<<solve(i)<<endl;
	}
	return 0;*/
	int T;cin>>T;
	while(T--){
		LL k1,k2;
		k1=get();
		k2=get();
		
		
		if(k1==1||k2==1){
			cout<<solve(k1)<<" "<<solve(k2)<<endl;
		}else{
			LL common=gcd(k1,k2);
			k1/=common;
			k2/=common;
			//cerr<<"common ";putLL(common);puts("");
			vector<LL>com;
			factor(common,com);
			vector<LL>vec1,vec2;
			//putLL(k1);puts("");
			factor(k1,vec1);
			factor(k2,vec2);
			/*
			for(auto x:vec1)
				putLL(x),putchar(' ');
			puts("");*/
			add(vec1,com);
			add(vec2,com);
			/*for(auto x:vec1)
				putLL(x),putchar(' ');
			puts("");*/
			
			long long ans1=calc(vec1);
			long long ans2=calc(vec2);
			cout<<ans1<<" "<<ans2<<endl;
		}
	}
	return 0;
}
