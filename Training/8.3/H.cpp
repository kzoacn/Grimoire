#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=2e5+5;
int in(){
    int r=0;char c=getchar();
    while(!isdigit(c))c=getchar();
    while(isdigit(c))r=r*10+c-'0',c=getchar();
    return r;
}
int n;
struct point{
    int x,y,id;
    int& operator[](const int s){return s==0?x:y;}
}p[maxn];
struct rec{
    int x[2],y[2];
    rec(){}
    rec(point p){x[0]=x[1]=p.x;y[0]=y[1]=p.y;}
};
bool operator==(const point &A,const point &B){
    return A.x==B.x&&A.y==B.y;
}
inline rec operator+(const rec &ls,const rec &rs){
    static rec R;R=ls;
    R.x[0]=min(R.x[0],rs.x[0]);
    R.x[1]=max(R.x[1],rs.x[1]);
    R.y[0]=min(R.y[0],rs.y[0]);
    R.y[1]=max(R.y[1],rs.y[1]);
    return R;
}
inline bool operator*(const point &p,const rec &R){
    return R.x[0]<=p.x&&p.x<=R.x[1]&&R.y[0]<=p.y&&p.y<=R.y[1];
}
inline bool In(const rec &A,const rec &B){
    return B.x[0]<=A.x[0]&&A.x[1]<=B.x[1]&&B.y[0]<=A.y[0]&&A.y[1]<=B.y[1];
}
inline bool Out(const rec &A,const rec &B){
    return B.x[0]>A.x[1]||A.x[0]>B.x[1]||B.y[0]>A.y[1]||A.y[0]>B.y[1];
}
struct node{
    rec R;point p;
    int sum,siz;
    node *c[2];
    node *rz(){
        sum=p.id;R=rec(p);siz=1;
        if(c[0])sum+=c[0]->sum,R=R+c[0]->R,siz+=c[0]->siz;
        if(c[1])sum+=c[1]->sum,R=R+c[1]->R,siz+=c[1]->siz;
        return this;
    }
    node(){sum=0;siz=1;c[0]=c[1]=0;}
}*root,*re,pool[maxn],*cur=pool;
node *sta[maxn];
int D,si;
bool cmp(const point &A,const point &B){
    if(D)return A.x<B.x||(A.x==B.x&&A.y<B.y);
    return A.y<B.y||(A.y==B.y&&A.x<B.x);
}
int top;
node *newnode(){
    if(si)return sta[si--];
    return cur++;
}
node* build(int l,int r,int d){
    int mid=(l+r)>>1;D=d;
    nth_element(p+l,p+mid,p+r+1,cmp);
    node *t=newnode();t->p=p[mid];
    if(l<=mid-1)t->c[0]=build(l,mid-1,d^1);
    if(mid+1<=r)t->c[1]=build(mid+1,r,d^1);
    return t->rz();
}
void dfs(node *&t){
    if(t->c[0])dfs(t->c[0]);
    p[++top]=t->p;
    if(t->c[1])dfs(t->c[1]);
    sta[++si]=t;*t=node();
    //delete t;
}
node* rebuild(node *&t){
    if(!t)return 0;
    top=0;dfs(t);
    return build(1,top,0);
}
#define siz(x) (x?x->siz:0)
void Add(node *&t,point p){
    D^=1;
    if(!t){t=newnode(),t->p=p;t->rz();return;}
    if(t->p==p){t->p.id+=p.id;t->rz();return;}
    if(p[D]<t->p[D])Add(t->c[0],p);
    else Add(t->c[1],p);t->rz();
    if(max(siz(t->c[0]),siz(t->c[1]))>0.618*t->siz)
        re=t;
}
vector<int>ans;
void Q(const node *t,const rec &R){
    if(Out(t->R,R))return ;
    if(t->p*R){
    	//ans+=t->p.id;
    	ans.push_back(t->p.id);
    }
    if(t->c[0])Q(t->c[0],R);
    if(t->c[1])Q(t->c[1],R);
}


int n,Q;
int W,H;



__advance void solve(){
//	scanf("%d%d%d%d",&n,&Q,&W,&H);
	cur=pool;
	root=0;
	
	cin>>n>>Q>>W>>H;
	for(int i=1;i<=n;i++){
        Add(root,(point){x,y,i});
        if(re)re=rebuild(re);
	}
	
	while(Q--){
		P p;p.read();
		LL E,a,b,c,d,e,f;
		cin>>E>>a>>b>>c>>d>>e>>f;
//		scanf("%lld%lld%lld%lld%lld%lld%lld",&E,&a,&b,&c,&d,&e,&f);	
		int sz=0;
		static P tmp[N];
		ans.clear();
				
		for(int i=1;i<=sz;i++){
			LL tmpx=tmp[i].x,tmpy=tmp[i].y;
			int id=tmp[i].id;
			pt[id].x=(tmpx*a+tmpy*b+id*c)%W;
			pt[id].y=(tmpx*d+tmpy*e+id*f)%H;
			insert(1,pt[id]);
		}
	}
	for(int i=1;i<=n;i++){
		cout<<pt[i].x<<" "<<pt[i].y<<"\n";
//		printf("%lld %lld\n",pt[i].x,pt[i].y);
	}
}
__advance int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;cin>>T;
	for(int t=1;t<=T;t++){
		cout<<"Case #"<<t<<":"<<"\n";
		solve();
	}
	return 0;
}
