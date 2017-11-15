#include<bits/stdc++.h>
using namespace std;
int n,m,k;

struct score{
	int sol,pen,la;
	string name;
	bool operator>(const score &oth)const{
		if(sol!=oth.sol)return sol>oth.sol;
		if(pen!=oth.pen)return pen<oth.pen;
		if(la!=oth.la)return la<oth.la;
		return name<oth.name;
	}
	bool operator<(const score &oth)const{
		return oth>*this;
	}
	void clear(){
		name="";
		sol=pen=la=0;
	}
};

struct team{
	string name;
	char c[30];
	int a[30];
	int t[30];
	
	score best,worst;
	
	void read(){
		static char str[40];
		scanf("%s",str);
		name=str;
		for(int i=0;i<n;i++){
			scanf("%s",str);
			c[i]=str[0];
			scanf("%d%d",&a[i],&t[i]);
		}
	}
	
	void calc(){
		worst.clear();
		worst.name=name;
		for(int i=0;i<n;i++){
			worst.sol+=(c[i]=='+');
			if(c[i]=='+'){
				worst.pen+=t[i]+20*(a[i]-1);
				worst.la=max(worst.la,t[i]);
			}
		}
		
		best.clear();
		best.name=name;
		best.sol=n;
		for(int i=0;i<n;i++){
		
			if(c[i]=='+'){
				best.pen+=t[i]+20*(a[i]-1);
				best.la=max(best.la,t[i]);
			}
		
			if(c[i]=='.'){
				best.pen+=240;
				best.la=max(best.la,t[i]);
			}
			if(c[i]=='-'){
				if(t[i]<240){
					best.pen+=240+20*a[i];
					best.la=max(best.la,240);
				}else{
					best.pen+=t[i]+20*a[i];
					best.la=max(best.la,t[i]);
				}
			}
		}
	}
	
}frz[1111],unfrz[1111];

int main(){
	while(scanf("%d%d%d",&n,&m,&k)==3){
		set<string>vis;
		for(int i=1;i<=m;i++){
			frz[i].read();
			frz[i].calc();
		}
		for(int i=1;i<=k;i++){
			unfrz[i].read();
			unfrz[i].calc();
			vis.insert(unfrz[i].name);
		}
	
		int ok=1;
	
		for(int i=1;i<k;i++){
			if(unfrz[i].worst>unfrz[i+1].worst){
		
			}else{
				ok=0;
			}
		}
		for(int i=1;i<=m;i++){
			//cerr<<i<<endl;
			if(vis.count(frz[i].name))continue;
			if(frz[i].best>unfrz[1].worst || frz[i].worst<unfrz[k].worst){
		
			}else{
				ok=0;
			}
		}
	
		puts(ok?"Leaked":"Fake");	
		
	}
	return 0;
}
