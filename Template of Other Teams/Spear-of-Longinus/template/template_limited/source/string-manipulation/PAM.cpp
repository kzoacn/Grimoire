struct PAM{
	int tot,last,str[maxn],nxt[maxn][26],n;
	int len[maxn],suf[maxn],cnt[maxn];
	int newnode(int l){
		len[tot]=l;
		return tot++;
	}
	void init(){
		tot=0;
		newnode(0);// tree0 is node 0
		newnode(-1);// tree-1 is node 1
		str[0]=-1;
		suf[0]=1;
	}
	int find(int x){
		while(str[n-len[x]-1]!=str[n])x=suf[x];
		return x;
	}
	void add(int c){
		str[++n]=c;
		int u=find(last);
		if(!nxt[u][c]){
			int v=newnode(len[u]+2);
			suf[v]=nxt[find(suf[u])][c];
			nxt[u][c]=v;
		}last=nxt[u][c];
		cnt[last]++;
	}
	void count(){
		for(int i=tot-1;i>=0;i--)cnt[suf[i]]+=cnt[i];
	}
}P;
int main(){
	P.init();
	for(int i=0;i<n;i++)
		P.add(s[i]-'a');
	P.count();

