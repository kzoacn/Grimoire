#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL lcm(LL a,LL b){return a/__gcd(a,b)*b;}
struct frac{
	LL p,q;
	frac(){}
	frac(LL _p,LL _q):p(_p),q(_q){}
	frac& form(){
		LL d=__gcd(llabs(p),llabs(q));
		p/=d;q/=d;
		return *this;
	}
	
	void deb(){
		printf("%lld/%lld\n",p,q);
	}
};
LL dv(LL p,LL q){
	if(q<0)p*=-1,q*=-1;
	if(p>=0){
		return p/q;
	}else{
		return (p-q+1)/q;
	}
}
void same(frac &a,frac &b){
	LL l=lcm(a.q,b.q);
	a.p*=l/a.q;a.q=l;
	b.p*=l/b.q;b.q=l;
}
frac operator+(frac a,frac b){
	same(a,b);
	frac c;
	c=frac(a.p+b.p,a.q);
	return c.form();
}
frac operator-(frac a,frac b){
	same(a,b);
	frac c;
	c=frac(a.p-b.p,a.q);
	return c.form();
}
frac operator*(frac a,frac b){
	frac c;
	c.p=a.p*b.p;
	c.q=a.q*b.q;
	return c.form();
}
frac operator/(frac a,frac b){
	swap(b.p,b.q);
	if(b.q<0)b.p*=-1,b.q*=-1;
	return a*b;
}
frac ONE(1,1);
vector<LL>ans;


void _print(frac f){
	f.form();
	LL x=dv(f.p,f.q);
	ans.push_back(x);
	if(f.q!=1)
		_print(ONE/(f-frac(x,1)));
}
void print(frac f){
	ans.clear();
	_print(f);
	for(int i=0;i<ans.size();i++)
		printf("%lld%c",ans[i]," \n"[i+1==ans.size()]);
}
LL a[2222];
int main(){
	frac r1,r2;
	int n1,n2;
	int T=0;
	while(1){
		T++;
		scanf("%d%d",&n1,&n2);
		if(!n1&&!n2)break;
		for(int i=1;i<=n1;i++)
			scanf("%lld",&a[i]);
		r1=frac(a[n1],1);
		for(int i=n1-1;i>=1;i--){
			r1=frac(a[i],1)+ONE/r1;
		}
			
		for(int i=1;i<=n2;i++)
			scanf("%lld",&a[i]);
		
		r2=frac(a[n2],1);
		for(int i=n2-1;i>=1;i--){
			r2=frac(a[i],1)+ONE/r2;
		}
		
		
		printf("Case %d:\n",T);
		print(r1+r2);
		print(r1-r2);
		print(r1*r2);
		print(r1/r2);
	}
	return 0;
}
