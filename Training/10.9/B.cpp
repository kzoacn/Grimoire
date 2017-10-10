#include<bits/stdc++.h>
#define __advance __attribute__((optimize("O3"))) __inline
using namespace std;
const int maxn=229;
int _b[maxn];
struct num{
	int *a,_a[maxn];
	int l,r;
	__advance void zero(){
		memset(_a,0,sizeof _a);
		a=_a+maxn/2;	
		l=r=0;
	}
	num(){}
	num(const num &oth){
		memcpy(_a,oth._a,sizeof _a);
		l=oth.l;r=oth.r;
		a=_a+maxn/2;
	}
	__advance bool push2(){
		static int *b;
		b=_b+maxn/2;
		for(int i=l-10;i<=r+10;i++)
			b[i]=0;
		int nl=l,nr=r;
		bool flag=false;
		for(register int i=l;i<=r;i++){
			if(a[i]==2){
				b[i+1]++;
				b[i-2]++;
				nl=min(nl,i-2);
				nr=max(nr,i+1);
				flag=true;
			}else b[i]+=a[i];
		}
		l=nl;r=nr;
		for(register int i=l;i<=r;i++)
			a[i]=b[i];
		norm();
		return flag;
	}
	
	__advance void mul2(){
		for(int i=l;i<=r;i++)
			a[i]*=2;
		while(push2());
		norm();
	}
	__advance void add1(){
		a[0]++;
		while(push2());
		norm();
	}
	
	__advance void add(int x){
		l=min(l,x);
		r=max(r,x);
		a[x]++;
		int nl=l,nr=r;
		for(int i=r;i>=l;i--){
			if(a[i]==2){
				a[i+1]++;
				a[i]=0;
				a[i-2]++;
				nl=min(nl,i-2);
				nr=max(nr,i+1);
			}
		}
		l=nl;r=nr;
//		if(a[x]==2)
//		while(push2());
		norm();
	}
	__advance void add(num b){
		l=min(l,b.l);
		r=max(r,b.r);
		for(int i=b.l;i<=b.r;i++)if(b.a[i])
			add(i);
	}
	
	__advance void norm(){
		
//		cerr<<"start"<<endl;
		while(1){
			int nl=l,nr=r;
			bool flag=false;
//			cerr<<"norm"<<endl;
//			print();
			for(int i=r;i>=l;i--){
				assert(a[i]<=2);
				if(a[i]==1&&a[i-1]==1){
					a[i+1]++;
					a[i]=a[i-1]=0;
					nr=max(nr,i+1);
					flag=true;
				}
			}
			l=nl;r=nr;
			if(!flag)break;
		}
		
		while(l<r&&a[l]==0)l++;
		while(l<r&&a[r]==0)r--;
	}
	__advance void print(){
		if(l==r){
			puts("1");
			return;
		}
		for(int i=r;i>=l;i--){
			printf("%d",a[i]);
			if(i==0)
				putchar('.');
		}
		puts("");
	}
}ans,one,x;

int main(){
	int k;
/*	one.zero();
	one.add1();
	num two;
	two.zero();two.add1();two.add1();


	two.print();
	
	x.zero();
	x.add(one);
	x.print();
	x.add(two);
	x.print();	
	x.add(x);
	x.print();
return 0;	*/
	while(scanf("%d",&k)==1){
		
		ans.zero();
		x.zero();
		x.add1();
		
		for(;k;k>>=1){
			if(k&1)
				ans.add(x);
			x.add(x);
		}
		
		ans.print();
	}
	return 0;
}
