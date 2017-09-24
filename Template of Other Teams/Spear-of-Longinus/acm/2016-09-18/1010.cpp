#include<bits/stdc++.h>
using namespace std;
typedef long long LL;


//int f[70][int(1e5+5)];

struct ha{
    LL operator()(pair<LL,LL> x)const{
        return x.first*1e10+x.second;
    }
};

//unordered_;
map<pair<LL,LL>,LL>M;
const int maxn=5e6+5;
bitset<maxn> notp;
int p[maxn];
int sum[maxn];
LL dfs(LL i,LL j){
    if(i==0)return j;
    if(j==0)return 0;
    if((LL)p[i]*p[i]>j && j<maxn){
        if(j>=p[i])
            return sum[j]-i+1;
        else return 1;
    }
    LL a = dfs(i - 1, j), b = dfs(i - 1, j / p[i]);    
    return (a-b);
}
LL calc(LL n){
    LL k;
    for(k=1;(LL)p[k]*p[k]<=n;k++);
    return dfs(k,n)+k-1;
}

int main(){
    for(int i=2;i<maxn;i++){
        if(!notp[i]){
            p[++p[0]]=i;
        }
        for(int j=1;j<=p[0]&&(LL)i*p[j]<maxn;j++){
            notp[i*p[j]]=1;
            if(i%p[j]==0)break;
        }
    }
    for(int i=2;i<maxn;i++)
        sum[i]=sum[i-1]+(!notp[i]);    
    LL n;
    while(cin>>n){
        if(n==1){
            puts("0");
            continue;
        }        
        cout<<calc(n)<<endl;
    }
    return 0;
}
