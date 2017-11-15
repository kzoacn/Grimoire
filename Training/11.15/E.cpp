#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+6;
int d[maxn],a[maxn],n;
int ans1[maxn],ans2[maxn];
vector<int>A,AB;
set<int>S;
int is_A[maxn];
int main(){

//freopen("equal.in","r",stdin);
//freopen("equal.out","w",stdout);

	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		d[a[i]]++;
		S.insert(a[i]);
	}

	if(*max_element(a+1,a+1+n)==*min_element(a+1,a+1+n)){
		for(int i=0;i<=n;i++)
			printf("%d%c",1," \n"[i==n]);
		return 0;
	}


	int mx=*max_element(a+1,a+1+n);

	int allA=1;
	for(int i=1;i<=n;i++)if(mx%a[i])allA=0;

	for(int i=1;i<maxn;i++){
		for(int j=i+i;j<maxn;j+=i){
			if(d[j]){
				is_A[i]=1;
			}
		}
	}
	
	for(int i=1;i<maxn;i++)if(d[i]){
		if(allA&&i==mx)continue;
		if(is_A[i]){
			A.push_back(d[i]);
		}
		AB.push_back(d[i]);
	}
	
	sort(A.begin(),A.end());
	sort(AB.begin(),AB.end());
	int cur=0;
	int sz=S.size();
	
	ans1[0]=sz;
	for(auto x:A){
		cur+=x;
		ans1[cur]=--sz;
	}
	for(int i=1;i<=n;i++)if(!ans1[i])
		ans1[i]=ans1[i-1];

	cur=AB[0];
	sz=S.size();
	ans2[0]=sz;
	ans2[AB[0]]=sz;
	for(int i=1;i<AB.size();i++){
		cur+=AB[i];
		ans2[cur]=--sz;
	}
	for(int i=1;i<=n;i++)if(!ans2[i])
		ans2[i]=ans2[i-1];

	for(int i=0;i<=n;i++)
		printf("%d%c",min(ans1[i],ans2[i])," \n"[i==n]);

	return 0;
}
