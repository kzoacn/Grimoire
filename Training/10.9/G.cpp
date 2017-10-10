#include<bits/stdc++.h>
using namespace std;
const int maxn=808;
const int inf=2e9;
struct node{
	int mn,mx;
	node(){mn=inf;mx=-inf;}
	node(int x){mn=mx=x;}
};
node operator+(node ls,node rs){
	node t;
	t.mn=min(ls.mn,rs.mn);
	t.mx=max(ls.mx,rs.mx);
	return t;
}
int id(int l,int r){return l+r|l!=r;}
node t[1700][1700];

int a[maxn][maxn],n;


void build2(int x,int l0,int r0,int l,int r){
	if(l==r){
		t[x][id(l,r)].mn=t[x][id(l,r)].mx=a[l0][l];
		for(int i=l0;i<=r0;i++){
			t[x][id(l,r)]=t[x][id(l,r)]+a[i][l];
		}	
		return ;
	}	
	int mid=(l+r)>>1;
	build2(x,l0,r0,l,mid);
	build2(x,l0,r0,mid+1,r);
	t[x][id(l,r)]=t[x][id(l,mid)]+t[x][id(mid+1,r)];
}

void build1(int l,int r){
	build2(id(l,r),l,r,1,n);
	if(l==r){
		return ;
	}
	int mid=(l+r)>>1;
	build1(l,mid);
	build1(mid+1,r);
}


node Qnode2(int x,int l,int r,int l0,int r0){
	if(l0<=l&&r0>=r)
		return t[x][id(l,r)];
	int mid=(l+r)>>1;
	node ans;ans.mn=inf;ans.mx=-inf;
	if(l0<=mid)
		ans=ans+Qnode2(x,l,mid,l0,r0);
	if(r0>mid)
		ans=ans+Qnode2(x,mid+1,r,l0,r0);
	return ans;
}

node Qnode1(int l,int r,int l1,int r1,int l2,int r2){
	if(l1<=l&&r1>=r)
		return Qnode2(id(l,r),1,n,l2,r2);
	int mid=(l+r)>>1;
	node ans;ans.mn=inf;ans.mx=-inf;
	if(l1<=mid)
		ans=ans+Qnode1(l,mid,l1,r1,l2,r2);
	if(r1>mid)
		ans=ans+Qnode1(mid+1,r,l1,r1,l2,r2);
	return ans;
}


void C2(int l0,int r0,int l,int r,int y){
	if(l==r){
		if(l0==r0){
			t[id(l0,r0)][id(l,r)].mn=t[id(l0,r0)][id(l,r)].mx=a[l0][l];		
		}else{
			int mid0=(l0+r0)/2;
			t[id(l0,r0)][id(l,r)]=t[id(l0,mid0)][id(l,r)]+t[id(mid0+1,r0)][id(l,r)];
		}	
		return ;
	}
	int mid=(l+r)>>1;
	if(y<=mid)
		C2(l0,r0,l,mid,y);
	else
 		C2(l0,r0,mid+1,r,y);
 	t[id(l0,r0)][id(l,r)]=t[id(l0,r0)][id(l,mid)]+t[id(l0,r0)][id(mid+1,r)];
}

void C1(int l,int r,int x,int y){
	if(l==r){
		C2(l,r,1,n,y);
		return ;
	}
	int mid=(l+r)>>1;
	if(x<=mid)
		C1(l,mid,x,y);
	else
		C1(mid+1,r,x,y);
	C2(l,r,1,n,y);
}

void print(){
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
		printf("%d%c",Qnode1(1,n,i,i,j,j)," \n"[j==n]);
	cerr<<endl;
}

int main(){
	int T;cin>>T;
	for(int t=1;t<=T;t++){
		printf("Case #%d:\n",t);
		scanf("%d",&n);
		for(int i=1;i<=n;i++)	
		for(int j=1;j<=n;j++)
			scanf("%d",&a[i][j]);
/*		for(int i=1;i<=n;i++)	
		for(int j=1;j<=n;j++)
			C1(1,n,i,j);
*/		build1(1,n);
		//print();
		int q;scanf("%d",&q);
		while(q--){
			int x,y,l;
			scanf("%d%d%d",&x,&y,&l);
			
			node inf=Qnode1(1,n,max(1,x-l/2),min(n,x+l/2),max(1,y-l/2),min(n,y+l/2));
			a[x][y]=(inf.mn+inf.mx)/2;
			C1(1,n,x,y);
			printf("%d\n",(inf.mn+inf.mx)/2);
			
		//print();
		}
	}

	return 0;
}
