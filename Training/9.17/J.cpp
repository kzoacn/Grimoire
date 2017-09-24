#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int n;
int a[maxn];
int pre[maxn],die[maxn*2],nxt[maxn],alive[maxn],alivesz;
struct sta{

	int id,pre;
	int val;

	bool operator<(const sta &oth)const{
		return val>oth.val;
	}
};

int main(){
	__int128 temp;
	int T;cin>>T;
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
		}
		
		//set<int>S;
		priority_queue<sta>q;
		alivesz=n;
		nxt[0]=1;
		for(int i=1;i<=n;i++){
			alive[i]=1;
			pre[i]=i-1;
			nxt[i]=i+1;
			q.push((sta){i,pre[i],a[i]-a[pre[i]]});
		}
		
		int sz=0;
		
		while(1){
			bool got=0;
			sz=0;
			while(q.size()&&q.top().val<0){
				
				auto tp=q.top();
				q.pop();got=1;
				if(pre[tp.id]!=tp.pre)continue;
				die[++sz]=tp.id;
				die[++sz]=tp.pre;
			}
			if(!got)break;
			for(int i=1;i<=sz;i++){
				int x=die[i];
				if(!alive[x])continue;
				alive[x]=0;alivesz--;
				if(alive[nxt[x]]){
					pre[nxt[x]]=pre[x];
					nxt[pre[x]]=nxt[x];
					
					q.push((sta){nxt[x],pre[nxt[x]],a[nxt[x]]-a[pre[nxt[x]]]});
				}
				pre[x]=-1;
				nxt[x]=-1;
			}
			
		}
		cout<<alivesz<<endl;
		for(int i=1;i<=n;i++)if(alive[i])
			printf("%d ",a[i]);
		puts("");
	}
	return 0;
}
