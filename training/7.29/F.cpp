#include<bits/stdc++.h>
using namespace std;
int n;

struct state{
	int id;
	char op;
	int val;
	state(){}
	state(int _id,char* _op,int v){
		id=_id;
		op=*_op;
		val=v;
	}
};
bool operator<(state a,state b){
	return a.id!=b.id ? a.id<b.id :(a.op!=b.op ? a.op<b.op : a.val<b.val);
}
bool operator==(state a,state b){
	return a.id==b.id && a.op==b.op && a.val==b.val;
}
map<int,vector<state> >M;
map<string,int>IDM;
const long long inf=1LL<<61;
int calc(vector<state>vec){
	sort(vec.begin(),vec.end());
	vec.erase(unique(vec.begin(),vec.end()),vec.end());
	int ans=0;
	int ok=-1,sum=0;
	for(int i=0,j;i<vec.size();i=j){
		j=i;
		while(j<vec.size()&&vec[i].id==vec[j].id)
			j++;
		long long mx=-inf,mn=inf;
		for(int k=i;k<j;k++){
			if(vec[k].op=='<'){
				mx=max(mx,1ll*vec[k].val);
			}
			if(vec[k].op=='>'){
				mn=min(mn,1ll*vec[k].val);
			}	
		}
		int cnt=0;
		set<int>has;
		for(int k=i;k<j;k++){
			if(vec[k].op=='='){
				if(vec[k].val<mx||vec[k].val>mn){
					//
				}else{
					cnt++;
					has.insert(vec[k].val);
				}
			}
		}
		if(mx!=-inf)cnt++;
		if(mn!=inf)cnt++;
		int flag=1;
		for(long long i=mx;i<=mn;i++){
			if(!has.count(i)){
				flag=0;
				break;
			}
		}
		if(flag){
			if(ok==-1||ok>cnt){
				ok=cnt;
			}
		}
		sum+=cnt;
	}
	if(ok==-1)
		return sum;
	return ok;
}

int main(){
	while(scanf("%d\n",&n)==1){
		if(!n)break;
		M.clear();
		IDM.clear();
		int tot=0;
		for(int i=1;i<=n;i++){
			int x,v,lt;
			static char op[3],var[266];
			scanf("if %s %s %d then turnOn( %d );\n",var,op,&v,&lt);
			if(!IDM[var])IDM[var]=++tot;
			M[lt].push_back(state(IDM[var],op,v));
		}
		int ans=0;
		for(auto x:M)
			ans+=calc(x.second);
		printf("%d\n",n-ans);
	}
	return 0;
}
