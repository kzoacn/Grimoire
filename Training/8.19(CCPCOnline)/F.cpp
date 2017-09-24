#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL mo=1e9+7;
const int maxn=1e5+5;
struct tup{
	LL A,B,C;
	tup(){}
	tup(LL _A,LL _B,LL _C):A(_A),B(_B),C(_C){}
	void print(){
		printf("(%lld,%lld,%lld)\n",A,B,C);
	}
};
int n,q;
char s[maxn];
struct node{
	int flip,rev;
	tup x,y;
	void makerev(){
		flip^=1;rev^=1;
		swap(x,y);
		swap(x.A,x.B);
		swap(y.A,y.B);
	}
}t[maxn*2];
int id(int l,int r){
	return l+r|l!=r;
}
tup in(tup t,tup x,tup y){
	tup nt;
	
	nt.A=(t.A*x.A+t.B*y.A)%mo;
	nt.B=(t.A*x.B+t.B*y.B)%mo;
	nt.C=(t.C+t.A*x.C+t.B*y.C)%mo;
	
	return nt;
}

void merge(node &t,node ls,node rs){
	t.x=in(rs.x,ls.x,ls.y);
	t.y=in(rs.y,ls.x,ls.y);
}

void rz(int l,int r){
	int x=id(l,r),mid=(l+r)/2;
	int ls=id(l,mid),rs=id(mid+1,r);
	merge(t[x],t[ls],t[rs]);
}

void pd(int l,int r){
	int x=id(l,r),mid=(l+r)/2;
	int ls=id(l,mid),rs=id(mid+1,r);
	
	if(t[x].flip){
		
		t[ls].makerev();
		t[rs].makerev();
		
		
		
		t[x].flip=0;
	}
	
}

void build(int l,int r){
	int x=id(l,r);
	t[x].flip=0;
	t[x].rev=0;
	if(l==r){
		if(s[l]=='0'){
			t[x].x=tup(1,1,1);
			t[x].y=tup(0,1,0);
		}else{
			t[x].x=tup(1,0,0);
			t[x].y=tup(1,1,1);
		}
		return ;
	}
	int mid=(l+r)>>1;
	build(l,mid);
	build(mid+1,r);
	rz(l,r);
}

void P(int l,int r){
	int x=id(l,r);	
	printf("[%d,%d]\n",l,r);
	t[x].x.print();
	t[x].y.print();
	if(l==r)return ;
	int mid=(l+r)>>1;
	P(l,mid);
	P(mid+1,r);
}
void F(int l,int r,int l0,int r0){
	if(l0<=l&&r0>=r){
		t[id(l,r)].makerev();
		return ;
	}
	pd(l,r);
	int mid=(l+r)>>1;
	if(l0<=mid)F(l,mid,l0,r0);
	if(r0>mid)F(mid+1,r,l0,r0);
	rz(l,r);
}
int sz;
node tmp[maxn];
void Q(int l,int r,int l0,int r0){
	if(l0<=l&&r0>=r){
		tmp[++sz]=t[id(l,r)];
		return ;
	}
	pd(l,r);
	int mid=(l+r)>>1;
	if(l0<=mid)Q(l,mid,l0,r0);
	if(r0>mid)Q(mid+1,r,l0,r0);
}
void solve(){
	scanf("%d%d",&n,&q);
	scanf("%s",s+1);
	build(1,n);
//	P(1,n);
//	return ;
	while(q--){
		int ty,l,r;
		scanf("%d%d%d",&ty,&l,&r);
		if(ty==1){
			F(1,n,l,r);			
		}else{
			sz=0;
			Q(1,n,l,r);
			
			for(int i=1;i<sz;i++){
				merge(tmp[i+1],tmp[i],tmp[i+1]);
			}
			printf("%lld\n",(tmp[sz].x.C+tmp[sz].y.C)%mo);
		}
	}
}


int main(){
	int T;cin>>T;
	while(T--)
		solve();
	return 0;
}
