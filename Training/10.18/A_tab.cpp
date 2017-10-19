#include<bits/stdc++.h>
using namespace std;



map<multiset<int>,int>M;
//1 first win
int dfs(multiset<int>S){
	if(S.size()==1){
		return (*S.begin())&1;
	}
	if(M.count(S))return M[S];
	int &ans=M[S];
	multiset<int>T;
	for(auto x:S){
		T=S;
		T.erase(T.find(x));
		if(x-1>0){
			T.insert(x-1);
		}
		if(!dfs(T))
			return ans=1;
	}
	
	for(auto it=S.begin();it!=S.end();it++){
		for(auto it2=it;it2!=S.end();it2++){
			if(it2!=it){
				T=S;
				T.erase(T.find(*it));
				T.erase(T.find(*it2));
				T.insert(*it+*it2);
				if(!dfs(T))
					return ans=1;
			}
		}
	}
	
	return ans=0;
}


int n;
int a[55];
int w=8;


int judge(int *_a){
	static int a[55];
	memcpy(a,_a,sizeof a);

	sort(a,a+n);
	int sum=accumulate(a,a+n,0);
	if(n<=2){
		if(n==1)
			return a[0]&1;
		if(n==2){
			for(int i=0;i<n;i++){
				if(a[i]>=5){
					a[i]=(a[i]-3)%2+3;
				}
			}
			sort(a,a+n);
			if(a[0]==2&&a[1]==3)return 0;
			if(a[0]==3&&a[1]==4)return 0;
			return 1;
		}
	}

	int cnt1=0;
	for(int i=0;i<n;i++)
		cnt1+=(a[i]==1);
	if(cnt1==n)
		return n%3>0;
	if(cnt1==n-1&&a[n-1]==2){
		return (n-1)%3!=0;
	}
	return ((sum+n-1)%2==0&&cnt1%2==0) ? 0 :1;
}

void dfs2(int x,int y){
	if(x==n){
		
		
		int ans1=dfs(multiset<int>(a,a+n));
		
		if(ans1==0,1){
		
			int cnt1=0;
//			cout<<cnt1<<" "<<n<<" "<<accumulate(a,a+n,0)<<endl;
		
			int cnt=0;
			for(int j=0;j<n;j++){
				cerr<<a[j]<<" ";
			}cerr<<endl;
		assert(ans1==judge(a));
	//		for(int i=0;i<n;i++)	
		//		cnt+=(a[i]==1);
			//assert(cnt%2==0);
		}
		/*
		for(int i=0;i<n;i++)if(a[i]>=4){
			for(int j=0;j<n;j++){
				cerr<<a[j]<<" ";
			}cerr<<endl;
		
			a[i]-=2;
			
			int ans2=dfs(multiset<int>(a,a+n));
			assert(ans1==ans2);
			
			a[i]+=2;
		}
		*/
		return ;
	}
	for(int i=y;i<=w;i++){
		a[x]=i;
		dfs2(x+1,a[x]);
	}
}

int main(){


	

/*

	for(int i=1;i<=w;i++)
	for(int j=i;j<=w;j++)if(!dfs({i,j})){
		cout<<i<<" "<<j<<" => "<<dfs({i,j})<<endl;
	}

	for(int i=1;i<=w;i++)
	for(int j=i;j<=w;j++)
	for(int k=j;k<=w;k++)if(!dfs({i,j,k})){
		cout<<i<<" "<<j<<" "<<k<<" => "<<dfs({i,j,k})<<endl;
	}
	
	for(int i=1;i<=w;i++)
	for(int j=i;j<=w;j++)
	for(int k=j;k<=w;k++)
	for(int l=k;l<=w;l++)if(!dfs({i,j,k,l})){
		cout<<i<<" "<<j<<" "<<k<<" "<<l<<" => "<<dfs({i,j,k,l})<<endl;
	 }

	n=5;
	dfs2(0,1);
*/
	int T;cin>>T;
	for(int t=1;t<=T;t++){
		scanf("%d",&n);
		for(int i=0;i<n;i++)scanf("%d",&a[i]);
		printf("Case #%d: %s\n",t,judge(a)?"Alice":"Bob");
	}
//	for(n=1;n<=10;n++)
//		dfs2(0,1);
	
	return 0;
}
