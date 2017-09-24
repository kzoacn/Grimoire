#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
#include<cctype>
#include<ctime>
#define output(x) cerr<< #x << "=" << x <<endl;
using namespace std;
const int maxn=1e5+5;
int getn() {
    int r=0;
    char c=getchar();
    while(!isdigit(c))c=getchar();
    while(isdigit(c))r=r*10+c-'0',c=getchar();
    return r;
}
int a, b ;
int last;
int n,m;
int A[maxn],B[maxn];
int rnd(int last) {
    static int C = ~(1<<31), M = (1<<16)-1;
    a = (36969 + (last >> 3)) * (a & M) + (a >> 16);
    b = (18000 + (last >> 3)) * (b & M) + (b >> 16);
    return (C & ((a << 16) + b)) % 1000000000;
}

struct node {
    int ans,lazy;
    vector<int>pl,pr;
    node(){lazy=-1;}
} t[maxn<<2];
#define ls i<<1
#define rs i<<1|1
#define mid ((l+r)>>1)
#define lson i<<1,l,mid
#define rson i<<1|1,mid+1,r

inline void pd(const int &i,const int &l,const int &r) { 
    if(t[i].lazy!=-1) {
        bool bound=(t[i].lazy!=r-l+1);
        t[ls].lazy=t[ls].ans=bound?t[i].pl[t[i].lazy]:(mid-l+1);
        t[rs].lazy=t[rs].ans=bound?t[i].pr[t[i].lazy]:(r-mid);
        t[i].lazy=-1;
    }
}
void build(const int &i,const int &l,const int &r) { 
    if(l==r) {
        t[i].ans=A[l]>=B[l];
        t[i].lazy=-1;
        t[i].pl.clear();
        t[i].pr.clear();
        return;
    }
    build(lson);
    build(rson);

    t[i].pl.clear();
    t[i].pr.clear();
    t[i].lazy=-1;

    vector<pair<int,int> >L,R,M;
    for(int j=l; j<=mid; j++)
        L.push_back(make_pair(B[j],0));
    sort(L.begin(),L.end());
    for(int j=0; j<L.size(); j++)
        L[j].second=j+1;
    for(int j=mid+1; j<=r; j++)
        R.push_back(make_pair(B[j],0));
    sort(R.begin(),R.end());
    for(int j=0; j<R.size(); j++)
        R[j].second=-(j+1);
    for(int j=0; j<L.size(); j++)M.push_back(L[j]);
    for(int j=0; j<R.size(); j++)M.push_back(R[j]);
    sort(M.begin(),M.end());
    //[0,p)
    int llast=0,rlast=0;
    for(int j=0; j<M.size(); j++) {
        t[i].pl.push_back(llast);
        t[i].pr.push_back(rlast);
        if(M[j].second>0)llast++;
        else rlast++;
    }
    t[i].ans=t[ls].ans+t[rs].ans;
}
inline int Q(const int &i,const int &l,const int &r,const int &l0,const int &r0) {
//    printf("%d %d %d %d %d %d\n",i,l,r,l0,r0,t[i].ans);
    if(l0<=l&&r0>=r)return t[i].ans;
    pd(i,l,r);
    int ans=0;
    if(l0<=mid)ans+=Q(lson,l0,r0);
    if(r0>mid)ans+=Q(rson,l0,r0);
    t[i].ans=t[ls].ans+t[rs].ans;
    return ans;
}
inline void C(const int &i,const int &l,const int &r,const int &l0,const int &r0,const int &p) {

//    printf("%d %d %d %d %d %d\n",i,l,r,l0,r0,p);

    if(l0<=l&&r0>=r) { //Waiting
        t[i].lazy=p;
        t[i].ans=p;
        return ;
    }
    pd(i,l,r);
    if(l0<=mid)C(lson,l0,r0,p==(r-l+1)?(mid-l+1):t[i].pl[p]);
    if(r0>mid)C(rson,l0,r0,p==(r-l+1)?(r-mid):t[i].pr[p]);
    t[i].ans=t[ls].ans+t[rs].ans;
}
void solve() {
    n=getn();
    m=getn();
    a=getn();
    b=getn();
    last=0;
    for(int i=1; i<=n; i++)A[i]=getn();
    for(int i=1; i<=n; i++)B[i]=getn();

//    n=1e5;
//    m=3e6;
//    a=233;
//    b=2333;
//    for(int i=1;i<=n;i++)A[i]=rand(),B[i]=rand();    

    build(1,1,n);
    
    //cerr<<clock()/double(CLOCKS_PER_SEC)<<endl;
    
    /*for(int i=1;i<=2*n;i++){
        printf("ID=%d\n",i);
        t[i].print();
    }*/
    
    sort(B+1,B+1+n);
    int ans=0;
    const int mo=1e9+7;
    for(int i=1; i<=m; i++) {
        
        /*if(i==3){
            for(int i=1;i<=2*n;i++){
                printf("ID=%d\n",i);
                t[i].print();
            }
        
        }*/
    
    
        int z=0;
        int l=rnd(last)%n+1,r=rnd(last)%n+1,x=rnd(last)+1;
        if(l>r)swap(l,r);
        
        //printf("%c %d\n",((l+r+x)&1)?'C':'Q',i);
        //output(l);
        //output(r);
        //output(x);
    
        if((l+r+x)&1) {
            int p;//Waiting
            p=upper_bound(B+1,B+1+n,x)-B-1;
            //output(p);
            C(1,1,n,l,r,p);
        } else {
            z=Q(1,1,n,l,r);
            //printf("%d\n",z);    
            last=z;
        }
        if(z)ans=(ans+(long long)i*z%mo)%mo;
    }
    printf("%d\n",ans);
}
int main() {
    int T;
    scanf("%d",&T);
    while(T--)
        solve();
    return 0;
}
