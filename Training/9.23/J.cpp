#include<bits/stdc++.h>
#define __advance __attribute__((optimize("O3"))) __inline
using namespace std;
typedef pair<int,int> par;
const int inf=1e9;
const int base=8;
char s1[10],s2[10];
int k;


int d[16777216+1];
char vis[16777216+1];
int clo=0;

__advance int& at(int x){
	if(vis[x]!=clo){
		vis[x]=clo;
		d[x]=0;
	}
	return d[x];
}

__advance int pack(char *s1,int k){
	int s=0;
	for(int i=0;i<7;i++){
		s=s*base;
		if(s1[i]==0)
			s1[i]='a'-1;
		s+=s1[i]-'a'+1;
	}
	s=s*base+k;
	return s;
}
__advance void unpack(int u,char *s,int &k){
	k=u%8;
	u/=8;
	for(int i=6;i>=0;i--){
		s[i]=u%8+'a'-1;
		u/=8;
	}
}


__advance void del(char *to,char *from,int k){
	memcpy(to,from,sizeof(char)*10);
	for(int i=k;i+1<7;i++){
		to[i]=from[i+1];
	}
	to[6]='a'-1;
}
__advance void ins(char *to,char *from,int k,char c){
	memcpy(to,from,sizeof(char)*10);
	to[k]=c;
	for(int i=k+1;i<7;i++){
		to[i]=from[i-1];
	}
}
__advance int ins(int u,int k,int c){
	int v;
	int nk=u>>3;
	int rig=(nk&((1<<3*(7-k))-1));
	int lef=(nk^rig);
	
	rig<<=3;
	lef<<=3;
	
	v=lef|((c-'a'+1)<<3*(7-k))|(rig>>3)|k;
	return v;
}

__advance void output(int u){
	char s[10];
	int k;
	unpack(u,s,k);
	
	cerr<<"it is "<<u<<endl;
	cerr<<k<<endl;
	for(int i=0;i<7;i++)putchar(s[i]);
	puts("");
	
}

namespace Heap {
	par hp[10000005];
	int tot;
	
	__advance void init() {
		tot = 0;
	}
	
	__advance void push(const par &rhs) {
		hp[++tot] = rhs;
		std::push_heap(hp + 1, hp + tot + 1,greater<par>());
	}
	
	__advance void pop() {
		if (tot == 0) return;
		std::pop_heap(hp + 1, hp + tot + 1,greater<par>());
		--tot;
	}
	
	__advance par top() {
		return hp[1];
	}
	
	__advance bool empty() {
		return tot == 0;
	}
}

__advance void solve(){
	
	clo++;
	int s=pack(s1,k);
	/*
	
	output(s);
	output(ins(s,2,'g'));
	
	
	return ;*/
	//priority_queue<par,vector<par>,greater<par> >q;
	Heap::init();
	int cnt=0;
	Heap::push({at(s)=1,s});
	while(!Heap::empty()){
		
		int u=Heap::top().second;
		if(at(u)!=Heap::top().first){
			Heap::pop();
			continue;
		}
		Heap::pop();
		static char s[10],s2[10];
		int k;
		memset(s,0,sizeof s);
		memset(s2,0,sizeof s2);
		unpack(u,s,k);
	/*
		cerr<<"it is "<<u<<endl;
		cerr<<k<<endl;
		for(int i=0;i<7;i++)putchar(s[i]);
		puts("");
	
	
		if(++cnt>10)exit(0);*/
		
		if(k!=7&&s[k]!='a'-1){
			int v=u+1;
			if(!at(v)||at(v)>at(u)+1){
				at(v)=at(u)+1;
				Heap::push({at(v),v});
			}
		}
		if(k!=0){
			int v=u-1;
			if(!at(v)||at(v)>at(u)+1){
				at(v)=at(u)+1;
				Heap::push({at(v),v});
			}
		}
		if(k!=7){		
			del(s2,s,k);
			int v=pack(s2,k);
			if(!at(v)||at(v)>at(u)+2){
				at(v)=at(u)+2;
				Heap::push({at(v),v});
			}
		}
		
		if(k!=0){		
			del(s2,s,k-1);
			int v=pack(s2,k-1);
			if(!at(v)||at(v)>at(u)+2){
				at(v)=at(u)+2;
				Heap::push({at(v),v});
			}
		}
		if(k!=7&&s[6]=='a'-1){
			static bool h[8];
			memset(h,0,sizeof h);
			for(int i=0;i<7;i++)
				h[s[i]-'a'+1]=1;
			for(char c='a';c<='g';c++)if(!h[c-'a'+1]){
			
				int v=ins(u,k,c);
				
				v++;
			/*
				ins(s2,s,k,c);
				
				int v=pack(s2,k+1);*/
				if(!at(v)||at(v)>at(u)+2){
					at(v)=at(u)+2;
					Heap::push({at(v),v});
				}
			}
		}
	}
	
	
	int ans=inf;
	for(int i=0;i<7;i++){
		int t=pack(s2,i);
		//cerr<<at(t)<<" ";
		if(at(t)&&at(t)<ans){
			ans=at(t);
		}
	}
	//cerr<<endl;
	if(ans==inf)puts("-1");
	else{
		printf("%.1f\n",(ans-1)/2.0);
	}
}

int main(){
	while(scanf("%s%d%s",s1,&k,s2)==3){
		solve();
		memset(s1,0,sizeof s1);
		memset(s2,0,sizeof s2);
	}
	return 0;
}
