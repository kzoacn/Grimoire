struct Sa{
	int heap[N],s[N],sa[N],r[N],tr[N],sec[N],m,cnt;
	int h[19][N];
	void Prep(){
		for (int i=1; i<=m; i++) heap[i]=0;
		for (int i=1; i<=n; i++) heap[s[i]]++;
		for (int i=2; i<=m; i++) heap[i]+=heap[i-1];
		for (int i=n; i>=1; i--) sa[heap[s[i]]--]=i;
		r[sa[1]]=1; cnt=1;
		for (int i=2; i<=n; i++){
			if (s[sa[i]]!=s[sa[i-1]]) cnt++;
			r[sa[i]]=cnt;
		}
		m=cnt;
	}
	void Suffix(){
		int j=1;
		while (cnt<n){
			cnt=0;
			for (int i=n-j+1; i<=n; i++) sec[++cnt]=i;
			for (int i=1; i<=n; i++) if (sa[i]>j)sec[++cnt]=sa[i]-j;
			for (int i=1; i<=n; i++) tr[i]=r[sec[i]];
			for (int i=1; i<=m; i++) heap[i]=0;
			for (int i=1; i<=n; i++) heap[tr[i]]++;
			for (int i=2; i<=m; i++) heap[i]+=heap[i-1];
			for (int i=n; i>=1; i--) sa[heap[tr[i]]--]=sec[i];
			tr[sa[1]]=1; cnt=1;
			for (int i=2; i<=n; i++){
				if ((r[sa[i]]!=r[sa[i-1]]) || (r[sa[i]+j]!=r[sa[i-1]+j])) cnt++;
				tr[sa[i]]=cnt;
			}
			for (int i=1; i<=n; i++) r[i]=tr[i];
			m=cnt; j=j+j;
		}
	}
	void Calc(){
		int k=0;
		for (int i=1; i<=n; i++){
			if (r[i]==1) continue;
			int j=sa[r[i]-1];
			while ((i+k<=n) && (j+k<=n) && (s[i+k]==s[j+k])) k++;
			h[0][r[i]]=k;
			if (k) k--;
		}
		for (int i=1; i<19; i++)
			for (int j=1; j+(1 << i)-1<=n; j++)
				h[i][j]=min(h[i-1][j],h[i-1][j + (1 << (i - 1)) + 1]);
	}
	int Query(int L,int R){
		L=r[L], R=r[R];
		if (L>R) swap(L,R);
		L++;
		int l0 = Lg[R-L+1];
		return min(h[l0][L],h[l0][R-(1 << l0)+1]);
	}
	void Work(){
		Prep(); Suffix(); Calc();
	}
}P,S;/// Hints : 1 - Base
