#include <bits/stdc++.h>
const int maxn=1e6+6;
using namespace std;

typedef long long LL;

int x[maxn];
struct cmp{
	bool operator()(int a,int b)const{
		return 1ll*a*(x[a]-1)<1ll*b*(x[b]-1);
	}
};

namespace Heap {
	LL pool[1000005]; int tot = 0;
	
	void push(LL x) {
		pool[++tot] = x;
		push_heap(pool + 1, pool + tot + 1,cmp());
	}
	
	void pop() {
		pop_heap(pool + 1, pool + tot + 1,cmp());
		--tot;
	}
	
	LL top() {
		return pool[1];
	}
	
	bool empty() {
		return tot == 0;
	}
	
	int size() {
		return tot;
	}
}
int ansk,ansx[maxn];

LL sumx=0;
LL calc(LL k,LL det=0){
	return 1ll*k*(x[k]+det)*(x[k]+det-1);
}
vector<int>oper;
int main(){
	oper.reserve(int(2e6));
	int n;LL t;
	cin>>n>>t;
	LL ans=1ll*n*(n+1)/2;
	LL res=ans;
	
	x[1]=n;
	Heap::push(1);
	
	
	ansk=1;
	int anscur=0;
	
	for(int k=2;k<=n;k++){
		x[k]=0;
		//cerr<<"k="<<k<<endl;
		//cerr<<"before res="<<res<<endl;
		res+=t;
		while(1){
			int id=Heap::top();
			
			LL delta1=calc(id,-1)-calc(id);
			LL delta2=calc(k,1)-calc(k);
			
		//	cerr<<id<<" "<<delta1<<" "<<delta2<<endl;
			if(x[id]>0&&delta1+delta2<0){
				Heap::pop();
				
				res=res+(delta1+delta2)/2;
				oper.push_back(-id);
				oper.push_back(k);
				x[k]++;
				x[id]--;
				Heap::push(id);
			}else break;
		}
		/*cerr<<"res="<<res<<endl;
		cerr<<"x is "<<endl;
		for(int i=1;i<=k;i++)
			cerr<<x[i]<<" ";cerr<<endl;*/
		Heap::push(k);
		if(res<ans){
			ans=res;
			ansk=k;
			anscur=oper.size();		
		}
	}
	
	x[1]=n;
	for(int k=2;k<=n;k++)x[k]=0;
	
	
	
	for(int i=0;i<anscur;i++){
		if(oper[i]<0){
			x[-oper[i]]--;
		}else{
			x[oper[i]]++;
		}
		
	}
	cout<<ans<<endl;
	cout<<ansk-1<<endl;

	
	LL sum=0;
	for(int i=1;i<ansk;i++){
		sum+=x[i];
		printf("%lld%c",sum," \n"[i+1==ansk]);
	}
	return 0;
}
