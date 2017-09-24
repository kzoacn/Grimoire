namespace LP{
	const int maxn=233;
	double a[maxn][maxn];
	int Ans[maxn],pt[maxn];
	int n,m;
	void pivot(int l,int i){
		double t;
		swap(Ans[l+n],Ans[i]);
		t=-a[l][i];
		a[l][i]=-1;
		for(int j=0;j<=n;j++)a[l][j]/=t;
		for(int j=0;j<=m;j++){ 
			if(a[j][i]&&j!=l){
				t=a[j][i];
				a[j][i]=0;
				for(int k=0;k<=n;k++)a[j][k]+=t*a[l][k];
			}
		}
	}
	vector<double> solve(vector<vector<double> >A,vector<double>B,vector<double>C){
		n=C.size();
		m=B.size();
		for(int i=0;i<C.size();i++)
			a[0][i+1]=C[i];
		for(int i=0;i<B.size();i++)
			a[i+1][0]=B[i];
		
		for(int i=0;i<m;i++)
			for(int j=0;j<n;j++)
				a[i+1][j+1]=-A[i][j];
		
		for(int i=1;i<=n;i++)Ans[i]=i;
		
		double t;
		for(;;){
			int l=0;t=-eps;
			for(int j=1;j<=m;j++)if(a[j][0]<t)t=a[l=j][0];
			if(!l)break;
			int i=0;
			for(int j=1;j<=n;j++)if(a[l][j]>eps){i=j;break;}
			if(!i){
				puts("Infeasible");
				return vector<double>();
			}
			pivot(l,i);
		}
		for(;;){
			int i=0;t=eps;
			for(int j=1;j<=n;j++)if(a[0][j]>t)t=a[0][i=j];
			if(!i)break;
			int l=0;
			t=1e30;
			for(int j=1;j<=m;j++)if(a[j][i]<-eps){
				double tmp;
				tmp=-a[j][0]/a[j][i];
				if(t>tmp)t=tmp,l=j;
			}
			if(!l){
				puts("Unbounded");
				return vector<double>();
			}
			pivot(l,i);
		}
		vector<double>x;
		for(int i=n+1;i<=n+m;i++)pt[Ans[i]]=i-n;
		for(int i=1;i<=n;i++)x.push_back(pt[i]?a[pt[i]][0]:0);
		return x;
	}
}

