#include<bits/stdc++.h>
using namespace std;
const int maxn=(1<<17)+20;
int k,q;
int n;
int id(int l,int r){
	return l+r|l!=r;
}
int a[maxn];
struct node{
	int mx1,mx2,mn1,mn2;
}t[maxn*2];
node merge(node ls,node rs){
	node t;
	
	t=ls;
	
	
	if(rs.mx1>=t.mx1){
		t.mx2=t.mx1;
		t.mx1=rs.mx1;
	}else{
		t.mx2=max(t.mx2,rs.mx1);
	}
	
	if(rs.mx2>=t.mx1){
		t.mx2=t.mx1;
		t.mx1=rs.mx2;
	}else{
		t.mx2=max(t.mx2,rs.mx2);
	}
	
	
	
	if(rs.mn1<=t.mn1){
		t.mn2=t.mn1;
		t.mn1=rs.mn1;
	}else{
		t.mn2=min(t.mn2,rs.mn1);
	}
	
	
	if(rs.mn2<=t.mn1){
		t.mn2=t.mn1;
		t.mn1=rs.mn2;
	}else{
		t.mn2=min(t.mn2,rs.mn2);
	}
	/*
	static int a[8];
	a[0]=ls.mx1;
	a[1]=ls.mx2;
	a[2]=ls.mn1;
	a[3]=ls.mn2;
	
	a[4]=rs.mx1;
	a[5]=rs.mx2;
	a[6]=rs.mn1;
	a[7]=rs.mn2;
	
	sort(a,a+8);
	t.mx1=a[7];
	t.mx2=a[6];
	t.mn1=a[0];
	t.mn2=a[1];*/
	return t;
}

void build(int l,int r){
	int x=id(l,r);
	if(l==r){
		t[x].mn1=t[x].mn2=t[x].mx1=t[x].mx2=a[l];
		return ;
	}
	int mid=(l+r)>>1;
	build(l,mid);
	build(mid+1,r);
	t[x]=merge(t[id(l,mid)],t[id(mid+1,r)]);
}
void C(int l,int r,int pos,int y){
	int x=id(l,r);
	if(l==r){
		t[x].mn1=t[x].mn2=t[x].mx1=t[x].mx2=y;
		return ;
	}
	int mid=(l+r)>>1;
	if(pos<=mid)
		C(l,mid,pos,y);
	else
		C(mid+1,r,pos,y);
	t[x]=merge(t[id(l,mid)],t[id(mid+1,r)]);
}
node Q(int l,int r,int l0,int r0){
	if(l0<=l&&r0>=r)
		return t[id(l,r)];
	int mid=(l+r)>>1;
	if(l0<=mid&&r0>mid)
		return merge(Q(l,mid,l0,r0),Q(mid+1,r,l0,r0));
	if(l0<=mid)
		return Q(l,mid,l0,r0);
	if(r0>mid)
		return Q(mid+1,r,l0,r0);
}

void solve(){
	scanf("%d",&k);
	n=(1<<k);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}	
	build(1,n);
	scanf("%d",&q);
	while(q--){
		int ty,x,y;
		scanf("%d%d%d",&ty,&x,&y);
		if(ty==2){
			x++;
			C(1,n,x,y);
		}else{
			x++;y++;
			node t=Q(1,n,x,y);
			static long long a[4];
			a[0]=t.mn1;
			a[1]=t.mn2;
			a[2]=t.mx1;
			a[3]=t.mx2;
			
			long long ans=(1LL<<61);
			for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
				ans=min(ans,a[i]*a[j]);
			printf("%lld\n",ans);
		}
	}
}

int main(){
	int T;cin>>T;
	while(T--)
		solve();
	return 0;
}
