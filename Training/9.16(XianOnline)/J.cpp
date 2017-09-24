#include<bits/stdc++.h>
#define sz(x) (x?x->siz:0)
#define deb(x,c) cerr<<#x" = "<<x<<c;
using namespace std;
typedef long long LL;
const int maxn=1e6+5;
int rnd(){
	static int x=1;
	return x=(x*23333+233);
}
int rnd(int n){
	int x=rnd();
	if(x<0)x=-x;
	return x%n+1;
}

struct node{
	int siz,key;
	int val;
	node *mn;
	node *c[2];
	node *rz(){
		mn=this;siz=1;
		if(c[0]){
			siz+=c[0]->siz;
			if(mn->val>c[0]->mn->val)
				mn=c[0]->mn;
		}
		if(c[1]){
			siz+=c[1]->siz;
			if(mn->val>c[1]->mn->val)
				mn=c[1]->mn;
		}
		return this;
	}
	node(){}
	node(int v){
		val=v;mn=this;
		siz=1;key=rnd();
		c[0]=c[1]=0;
	}
}pool[maxn*50/4],*root[maxn],*cur=pool;

node *newnode(int v=0){
	*cur=node(v);
	return cur++;
}


node* old_merge(node *p,node *q){
	if(!p&&!q)return 0;
	node *u=0;
	if(!p||!q)return u=p?p->rz():(q?q->rz():0);
	if(rnd(sz(p)+sz(q))<sz(p)){
		u=p;
		u->c[1]=old_merge(u->c[1],q);
	}else{
		u=q;
		u->c[0]=old_merge(p,u->c[0]);
	}
	return u->rz();
}


node* merge(node *p,node *q){
	if(!p&&!q)return 0;
	node *u=newnode();
	if(!p||!q)return u=p?p->rz():(q?q->rz():0);
	if(rnd(sz(p)+sz(q))<sz(p)){
		*u=*p;
		u->c[1]=merge(u->c[1],q);
	}else{
		*u=*q;
		u->c[0]=merge(p,u->c[0]);
	}
	return u->rz();
}
node *split(node *u,int l,int r){
	if(l>r||!u)return 0;
	//cerr<<"spl "<<l<<" "<<r<<endl;
	node *x=0;
	if(l==1&&r==sz(u)){
		x=newnode();
		*x=*u;
		return x->rz();
	}
	int lsz=sz(u->c[0]);
	if(r<=lsz)
		return split(u->c[0],l,r);
	if(l>lsz+1)
		return split(u->c[1],l-lsz-1,r-lsz-1);
	x=newnode();
	*x=*u;
	x->c[0]=split(u->c[0],l,lsz);
	x->c[1]=split(u->c[1],1,r-lsz-1);
	return x->rz();
}

int get_pos(node *u,node *mn){
//	cerr<<u->val<<endl;
	if(u==mn)
		return sz(u->c[0]);
	if(u->c[0]&&u->c[0]->mn==mn)
		return get_pos(u->c[0],mn);
	return get_pos(u->c[1],mn)+sz(u->c[0])+1;
}

pair<int,int> Qmin(node *u,int l,int r){
	if(l>r)return make_pair(-1,-1);
	node *v=split(u,l,r);
	
//	cerr<<"Qmin "<<l<<" "<<r<<" "<<v->mn->val<<endl; 
	 
	auto mp= make_pair(v->mn->val,get_pos(v,v->mn)+l);
//	cerr<<"sdf"<<endl;
	return mp;
}
int get(node *u,int x){
	node *v=split(u,x,x);
	return v->val;
}
int q,n;

struct sta{
	int lef,len;
	LL val;
	bool operator<(const sta &oth)const{
		return val>oth.val;
	}
};

void Q(int rt,int k){
	int n=sz(root[rt]);
	node *u=root[rt];
	set<int>S;
	
	
	/*cerr<<"debug seq"<<endl;
	
	
	for(int i=1;i<=n;i++){
		deb(get(u,i),' ');
	}cerr<<endl;
*/
	S.insert(0);
	S.insert(n+1);
	
	priority_queue<sta>q;
	
	pair<int,int>tmp=Qmin(u,1,n);
	
	q.push((sta){tmp.second,1,tmp.first});
	//cerr<<tmp.first<<" "<<tmp.second<<endl;
	
	while(k--){
		auto tp=q.top();q.pop();
		printf("%lld\n",tp.val);
		
		if(tp.len==1){
			S.insert(tp.lef);
			auto it=S.find(tp.lef);
			int pre,nxt;
			it--;pre=*it;
			it++;it++;nxt=*it;
			
			
			pair<int,int>ls,rs;
			ls=Qmin(u,pre+1,tp.lef-1);
			rs=Qmin(u,tp.lef+1,nxt-1);
			if(ls.second!=-1)
				q.push((sta){ls.second,1,ls.first});
			
			if(rs.second!=-1)
				q.push((sta){rs.second,1,rs.first});
		}
		if(tp.lef+tp.len<=n){
			q.push((sta){tp.lef,tp.len+1,tp.val+get(u,tp.lef+tp.len)});
		}
		
	}
	
}

void solve(){
	cur=pool;
	scanf("%d",&q);
	n=0;
	while(q--){
		int ty;
		scanf("%d",&ty);
		if(ty==1){
			n++;
			int m;scanf("%d",&m);
			root[n]=0;
			for(int i=1;i<=m;i++){
				int x;scanf("%d",&x);
				root[n]=old_merge(root[n],newnode(x));
			}
		}else
		if(ty==2){
			n++;
			root[n]=0;
			int x,l1,r1,y,l2,r2;
			scanf("%d%d%d%d%d%d",&x,&l1,&r1,&y,&l2,&r2);
			node *ls,*rs;
			ls=split(root[x],l1,r1);
			rs=split(root[y],l2,r2);
			root[n]=merge(ls,rs);
		}else{
			int x,k;
			scanf("%d%d",&x,&k);
			Q(x,k);
		}
	}
}

int main(){
	int T;scanf("%d",&T);
	while(T--){
		solve();
	}
	return 0;
}
