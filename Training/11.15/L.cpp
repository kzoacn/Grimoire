#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL n;


pair<LL,LL> test(LL a,LL b){
	LL n=::n;
	vector<LL>vec;
	LL cnta=0,cntb=0;
	
	
	if(n%b)return make_pair(-1,-1);
	while(n%b==0)n/=b,cntb++;

	if(a!=b){
	
		if(n%a)return make_pair(-1,-1);
		while(n%a==0)n/=a,cnta++;
	}
	
	if(n!=1)return make_pair(-1,-1);
	
	return make_pair(cnta,cntb);
}

int main(){
freopen("little.in","r",stdin);
freopen("little.out","w",stdout);
	while(cin>>n){
	
		if((n&-n)==n){
			puts("-1");
			continue;
		}
	
		vector<vector<LL> >ans;
		
		ans.push_back({n});
		LL sqrtn=sqrt(n);
		
		int inf=0;
		
		for(LL i=2;i<=2e6;i++){
			auto par=test(i,i+1);
			if(par.second!=-1){
				vector<LL>vec;
				for(int j=0;j<par.first;j++)vec.push_back(i);
				for(int j=0;j<par.second;j++)vec.push_back(i+1);
				ans.push_back(vec);
			}
			
			par=test(i,i);
			if(par.second!=-1){
				vector<LL>vec;
				for(int j=0;j<par.first;j++)vec.push_back(i);
				for(int j=0;j<par.second;j++)vec.push_back(i);
				ans.push_back(vec);
			}
		}
		
		for(LL d=-200;d<=200;d++){
			
			LL i=sqrtn+d;
			if(i<=1)continue;
		
			auto par=test(i,i+1);
			if(par.second!=-1){
				vector<LL>vec;
				for(int j=0;j<par.first;j++)vec.push_back(i);
				for(int j=0;j<par.second;j++)vec.push_back(i+1);
				ans.push_back(vec);
			}
			par=test(i,i);
			if(par.second!=-1){
				vector<LL>vec;
				for(int j=0;j<par.first;j++)vec.push_back(i);
				for(int j=0;j<par.second;j++)vec.push_back(i);
				ans.push_back(vec);
			}
		}
		
		
		
		sort(ans.begin(),ans.end());
		ans.erase(unique(ans.begin(),ans.end()),ans.end());
		
		if(inf)
			puts("-1");
		else{
			cout<<ans.size()<<endl;
			for(auto &vec:ans){
				printf("%d",(int)vec.size());
				for(auto x:vec)
					printf(" %lld",x);
				puts("");
			}
		}
	
	}
	return 0;
}
