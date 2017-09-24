int n,m,K;
struct DLX{
	int L[maxn],R[maxn],U[maxn],D[maxn];
	int sz,col[maxn],row[maxn],s[maxn],H[maxn];
	bool vis[233];
	int ans[maxn],cnt;
	void init(int m){
		for(int i=0;i<=m;i++){
			L[i]=i-1;R[i]=i+1;
			U[i]=D[i]=i;s[i]=0;
		}
		memset(H,-1,sizeof H);
		L[0]=m;R[m]=0;sz=m+1;
	}
	void Link(int r,int c){
		U[sz]=c;D[sz]=D[c];U[D[c]]=sz;D[c]=sz;
		if(H[r]<0)H[r]=L[sz]=R[sz]=sz;
		else{
			L[sz]=H[r];R[sz]=R[H[r]];
			L[R[H[r]]]=sz;R[H[r]]=sz;
		}
		s[c]++;col[sz]=c;row[sz]=r;sz++;
	}
	void remove(int c){
		for(int i=D[c];i!=c;i=D[i])
			L[R[i]]=L[i],R[L[i]]=R[i];
	}
	void resume(int c){
		for(int i=U[c];i!=c;i=U[i])
			L[R[i]]=R[L[i]]=i;
	}
	int A(){
		int res=0;
		memset(vis,0,sizeof vis);
		for(int i=R[0];i;i=R[i])if(!vis[i]){
			vis[i]=1;res++;
			for(int j=D[i];j!=i;j=D[j])
				for(int k=R[j];k!=j;k=R[k])
					vis[col[k]]=1;
		}
		return res;
	}
	void dfs(int d,int &ans){
		if(R[0]==0){ans=min(ans,d);return;}
		if(d+A()>=ans)return;
		int tmp=23333,c;
		for(int i=R[0];i;i=R[i])
			if(tmp>s[i])tmp=s[i],c=i;
		for(int i=D[c];i!=c;i=D[i]){
			remove(i);
			for(int j=R[i];j!=i;j=R[j])remove(j);
			dfs(d+1,ans);
			for(int j=L[i];j!=i;j=L[j])resume(j);
			resume(i);
		}
	}
	void del(int c){//exactly cover
        L[R[c]]=L[c];R[L[c]]=R[c];  
		for(int i=D[c];i!=c;i=D[i])
			for(int j=R[i];j!=i;j=R[j])
				U[D[j]]=U[j],D[U[j]]=D[j],--s[col[j]];  
    }  
    void add(int c){  //exactly cover
        R[L[c]]=L[R[c]]=c;  
		for(int i=U[c];i!=c;i=U[i])
			for(int j=L[i];j!=i;j=L[j])
				++s[col[U[D[j]]=D[U[j]]=j]];  
    }  
	bool dfs2(int k){//exactly cover
        if(!R[0]){  
            cnt=k;return 1;  
        }  
        int c=R[0];
		for(int i=R[0];i;i=R[i])
			if(s[c]>s[i])c=i;  
        del(c);  
		for(int i=D[c];i!=c;i=D[i]){  
			for(int j=R[i];j!=i;j=R[j])
				del(col[j]);  
            ans[k]=row[i];if(dfs2(k+1))return true;  
			for(int j=L[i];j!=i;j=L[j])
				add(col[j]);  
        }  
        add(c); 
		return 0;
	}
}dlx;
int main(){
	dlx.init(n);
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			if(dis(station[i],city[j])<mid-eps)
				dlx.Link(i,j);
			dlx.dfs(0,ans);
}
