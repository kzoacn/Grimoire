#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
const int N=1e5+5;
const int C=26;
struct Node{
	Node *nxt[C],*fail;
	int count,len,vis,in;
	long long dp[2];
	void clear(){
		for(int i=0;i<C;i++)
			nxt[i]=0;
		len=count=0;
		dp[0]=dp[1]=0;
		fail=0;vis=0;
		in=0;
	}
};
Node *tail,*q[N*2],pool[N*2],*head;
int vis[N*2];
char str[N];
char X,st[4];
int used=0;
Node *newNode(){
	pool[used++].clear();
	return &pool[used-1];
}
void add(int x){
	Node *np=newNode(),*p=tail;
	tail=np;
	np->len=p->len+1;
	for(;p&&!p->nxt[x];p=p->fail)
		p->nxt[x]=np;
	if(!p)
		np->fail=head;
	else if(p->len+1==p->nxt[x]->len)
		np->fail=p->nxt[x];
	else{
		Node *q=p->nxt[x],*nq=newNode();
		*nq=*q;
		nq->len=p->len+1;
		q->fail=np->fail=nq;
		for(;p&&p->nxt[x]==q;p=p->fail)
			p->nxt[x]=nq;
	}
}
int ans=0;
queue<Node*>Q;
int Tm;
void bfs(){
	
	Q.push(head);
	head->dp[0]=1;
	head->dp[1]=0;
	while(!Q.empty()){
		Node *u=Q.front();Q.pop();
		for(int i=0;i<26;i++){
			Node *v=u->nxt[i];
			if(!v)continue;
			
			if(i==X-'a'){
				v->dp[1]+=u->dp[1]+u->dp[0];
			}else{
				v->dp[0]+=u->dp[0];
				v->dp[1]+=u->dp[1];
			}
			
			v->in--;
			if(!v->in){
				Q.push(v);
			}
		}
	}
}


int buc[N*2];
int main(){
	int T;scanf("%d",&T);
	for(int t=1;t<=T;t++){
		Tm++;
		scanf("%s",st);
		X=st[0];
		scanf("%s",str+1);
		int len=strlen(str+1);
		used=0;
		head=tail=newNode();
		for(int i=1;i<=len;i++)
			add(str[i]-'a');
		
		
		for(int i=0;i<used;i++){
			Node *u=&pool[i];
			for(int j=0;j<26;j++){
				Node *v=u->nxt[j];
				if(v){
					v->in++;
				}
			}
		}
			
		
		long long ans=0;
		bfs();
		for(int i=0;i<used;i++)
			ans+=pool[i].dp[1];
		
		/*for(int i=0;i<used;i++){
			printf("%d %d %d\n",i,pool[i].dp[0],pool[i].dp[1]);
			Node *u=&pool[i];
			for(int j=0;j<26;j++){
				if(u->nxt[j]){
					printf("%d--%c-->%d\n",i,j+'a',u->nxt[j]-pool);
				}
			}
		}*/
		
		printf("Case #%d: %I64d\n",t,ans);
	}
	return 0;
}
