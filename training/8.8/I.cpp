#include<bits/stdc++.h>
using namespace std;
const int maxn=4e4+5;
typedef long long LL;
int rnd(){
	return ((LL)rand()<<32)^((LL)rand()<<16)^rand();
}
struct node{
	int key;
	LL val;
	int siz,s;
	node *c[2];
	node(LL v=0){
		val=v;
		key=rnd();
		siz=1;s=1;
		c[0]=c[1]=0;
	}
	void rz(){
		siz=s;
		if(c[0]){
			siz+=c[0]->siz;
		}
		if(c[1]){
			siz+=c[1]->siz;
		}
	}
}pool[int(4e4*20+233)],*cur;
node *newnode(LL val){
	*cur=node(val);
	return cur++;
}
struct Treap{
	node *root;
	Treap(){root=0;}
	void clear(){root=0;}
	void rot(node *&t,int d){
		if(!t->c[d])t=t->c[!d];
		else{
			node *p=t->c[d];t->c[d]=p->c[!d];
			p->c[!d]=t;t->rz();p->rz();t=p;
		}
	}
	void insert(node *&t,LL x){
		if(!t){
			t=newnode(x);
			return ;
		}
		if(t->val==x){
			t->s++;t->siz++;
			return ;
		}
		insert(t->c[x>t->val],x);
		if(t->key<t->c[x>t->val]->key)
			rot(t,x>t->val);
		else t->rz();
	}
	
	#define sz(x) (x?x->siz:0)
	int geq(node *t,LL x){
		if(!t)return 0;
		if(t->val>=x){
			return sz(t->c[1])+geq(t->c[0],x)+t->s;
		}else	return geq(t->c[1],x);
	}
	void insert(LL x){
		insert(root,x);
	}
	
	int geq(LL x){
		return geq(root,x);
	}
};
Treap d[maxn];
int lim;
void add(LL x,LL y){
//fprintf(stderr,"add (%lld,%lld)\n",x,y);
	while(x<=lim){
		d[x].insert(y);
//		cerr<<x<<" put "<<y<<endl;
		x+=x&-x;
	}
}
int get(LL x,LL y){
//fprintf(stderr,"get (%lld,%lld)\n",x,y);
	int ans=0;
	while(x){
		ans+=d[x].geq(y);
//		cerr<<x<<" get "<<y<<" is "<<d[x].geq(y)<<endl;
		x-=x&-x;
	}
//fprintf(stderr,"ans=%lld\n",ans);
	return ans;
}

int n,m;

struct P{LL x,y;}p[maxn];


struct sta{
	LL l1,r1,l2,r2,m,x,y,z;
	LL boundml;
	int ty,id;
	
	sta(){}
	sta(LL _l1,LL _r1,LL _l2,LL _r2,int _id){
		l1=_l1;
		r1=_r1;
		l2=_l2;
		r2=_r2;
		id=_id;
	}

	inline LL X()const{
		if(ty==0)
			return x;
		return r1;
	}
	bool operator<(const sta &oth)const{
		return X()<oth.X();
	}
	
}tri1[maxn],tri2[maxn],qes[maxn*2];
LL ans[maxn];
int sz1=0,sz2=0;

void solve(sta *tri,int trisz){
//cerr<<"clear"<<endl;
	cur=pool;
	lim=n+m+1;
	for(int i=1;i<=lim;i++)	
		d[i].clear();
	//TODO clear
	int sz=0;
	static LL b[maxn];b[0]=0;
	for(int i=1;i<=n;i++)
		b[++b[0]]=p[i].y-p[i].x;
	for(int i=1;i<=trisz;i++){
		tri[i].m=(tri[i].l2+tri[i].r2)/2;
		tri[i].boundml=tri[i].m-tri[i].l1;
		b[++b[0]]=tri[i].boundml;
	}
	sort(b+1,b+1+b[0]);
	b[0]=unique(b+1,b+1+b[0])-b-1;
	
	for(int i=1;i<=n;i++){
		sz++;
		qes[sz].ty=0;
		qes[sz].x=p[i].x;
		qes[sz].y=lower_bound(b+1,b+1+b[0],p[i].y-p[i].x)-b;
		qes[sz].z=p[i].x+p[i].y;
	}
	for(int i=1;i<=trisz;i++){
		sz++;
		qes[sz]=tri[i];
		qes[sz].boundml=lower_bound(b+1,b+1+b[0],tri[i].boundml)-b;
		qes[sz].ty=1;
	}
	sort(qes+1,qes+1+sz);
	
	for(int i=1,j=1;i<=sz;i=j){
		while(j<=sz&&qes[i].X()==qes[j].X())j++;
		for(int k=i;k<j;k++){
			if(qes[k].ty==0){
				add(qes[k].y,qes[k].z);
			}
		}
		for(int k=i;k<j;k++){
			if(qes[k].ty==1){
				int tmp=get(qes[k].boundml,qes[k].m+qes[k].l1);
				ans[qes[k].id]+=tmp;
			}
		}
	}
}
void solve(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&p[i].x,&p[i].y);
	}
	sz1=sz2=0;
	for(int i=1;i<=m;i++){
		LL x,y,d,w;scanf("%lld%lld%lld%lld",&x,&y,&d,&w);
		if(w>d)continue;
		if(w==0){
			if(d){
				sz1++;
				tri1[sz1]=sta(x-d/2,x-1,y-d/2+1,y+d/2-1,i);
			}
			sz2++;
			tri2[sz2]=sta(x,x+d/2,y-d/2,y+d/2,i);
		}else{
			sz1++;
			tri1[sz1]=sta(x-d/2,x-w/2,y-d/2+w/2,y+d/2-w/2,i);
			sz2++;
			tri2[sz2]=sta(x+w/2,x+d/2,y-d/2+w/2,y+d/2-w/2,i);
		}
	}
	
	for(int i=1;i<=m;i++)
		ans[i]=0;
	solve(tri1,sz1);
	
	for(int i=1;i<=n;i++)
		p[i].x*=-1;
	for(int i=1;i<=sz2;i++){
		tri2[i].l1*=-1;
		tri2[i].r1*=-1;
		swap(tri2[i].l1,tri2[i].r1);
	}
	solve(tri2,sz2);
	for(int i=1;i<=m;i++)
		printf("%lld\n",ans[i]);
}

int main(){
	int T;cin>>T;
	for(int t=1;t<=T;t++){
		printf("Case #%d:\n",t);
		solve();
	}
	return 0;
}
