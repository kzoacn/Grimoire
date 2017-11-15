#include<bits/stdc++.h>
using namespace std;

bool check(vector<int>A,vector<int>B){
	multiset<int>A2,B2;
	for(auto x:A)for(auto y:A)if(x!=y)
		A2.insert(x+y);
	for(auto x:B)for(auto y:B)if(x!=y)
		B2.insert(x+y);
	if(A2!=B2){
		for(auto a:A2)
			cerr<<a<<" ";cerr<<endl;
		for(auto b:B2)
			cerr<<b<<" ";cerr<<endl;
		
	}
	return A2==B2;
}

int main(){
//freopen("analogous.in","r",stdin);
//freopen("analogous.out","w",stdout);
	
	int n;
	while(scanf("%d",&n)==1&&n){

		if(n%2){
			puts("No");
			continue;
		}

		vector<int>A,B;
		for(int i=1;i<=n*2;i++){

			int t=(i%4==0||i%4==1);
//			if(((i-1)/4)&1)
//				t^=1;

			if(t)
				A.push_back(i);
			else
				B.push_back(i);
		}


		puts("Yes");
		for(auto x:A)
			printf("%d ",x);
		puts("");
		for(auto x:B)
			printf("%d ",x);
		puts("");
		assert(check(A,B));
	}

	return 0;
}
