#include <bits/stdc++.h>

using namespace std;
double p[7], ans;

int cnt[7];


int cost[333][15];
double prob[333];
int num[322];
int calc(int a[],int id){
	int ans=0;
	if(id<=6){
		for(int i=1;i<=5;i++)
			if(a[i]==id)ans+=id;
		return ans;
	}
	
	int sum = 0;
	memset(cnt, 0, sizeof cnt);
	for (int i = 1; i <= 5; ++i) {
		++cnt[a[i]];
		sum += a[i];
	}
	
	switch (id) {
		case 7:
			for (int i = 1; i <= 6; ++i)
				for (int j = i + 1; j <= 6; ++j)
					if (cnt[i] >= 2 && cnt[j] >= 2)
						return sum;
			return 0;
		case 8:
			for (int i = 1; i <= 6; ++i)
				if (cnt[i] >= 3)
					return sum;
			return 0;
		case 9:
			for (int i = 1; i <= 6; ++i)
				if (cnt[i] >= 4)
					return sum;
			return 0;
		case 10:
			for (int i = 1; i <= 6; ++i)
				for (int j = 1; j <= 6; ++j)
					if (i != j && cnt[i] >= 3 && cnt[j] >= 2)
						return 25;
			return 0;
		case 11:
			for (int i = 1; i <= 3; ++i)
				if (cnt[i] && cnt[i + 1] && cnt[i + 2] && cnt[i + 3])
					return 30;
			return 0;
		case 12:
			for (int i = 1; i <= 2; ++i)
				if (cnt[i] && cnt[i + 1] && cnt[i + 2] && cnt[i + 3] && cnt[i + 4])
					return 40;
			return 0;
		case 13:
			for (int i = 1; i <= 6; ++i)
				if (cnt[i] >= 5)
					return 50;
			return 0;
		case 14:
			return sum;
	}
	assert(0);
	return -1;
}
/*
void DFS(int now, double prob) {
	if (now == 6) {
		ans += calc() * prob;
		return;
	}
	for (int i = 1; i <= 6; ++i) {
		++cnt[i];
		DFS(now + 1, prob * p[i]);
		--cnt[i];
	}
}
*/
map<vector<int>,int>M;
bool cmp(int x,int y){
	return __builtin_popcount(x)<__builtin_popcount(y);
}
int main() {

	vector<int>vecS;
	for(int i=1;i<(1<<14);i++)
		vecS.push_back(i);
	sort(vecS.begin(),vecS.end());
	static int a[10];

	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		for (int i = 1; i <= 6; ++i)
			scanf("%lf", p + i);
		
		memset(cost,0,sizeof cost);
		memset(prob,0,sizeof prob);
		memset(num,0,sizeof num);
		int tot=0;
		M.clear();
		for(a[1]=1;a[1]<=6;a[1]++)
		for(a[2]=1;a[2]<=6;a[2]++)
		for(a[3]=1;a[3]<=6;a[3]++)
		for(a[4]=1;a[4]<=6;a[4]++)
		for(a[5]=1;a[5]<=6;a[5]++){
			double pb=1;
			for(int i=1;i<=5;i++)pb*=p[a[i]];
			vector<int>tmp(a+1,a+1+5);
			sort(tmp.begin(),tmp.end());
			if(!M.count(tmp))M[tmp]=++tot;
			int id=M[tmp];
			prob[id]+=pb;
			num[id]++;
			for(int i=1;i<=14;i++)
				cost[id][i]=calc(a,i);
		}/*
		for(int i=1;i<=252;i++){
			for(int j=1;j<=14;j++)
				cerr<<cost[i][j]<<" ";
			cerr<<endl; 
		}*/
		
		static double dp[(1<<14)+10];
		
		for(int s=0;s<vecS.size();s++){
			int S=vecS[s];
			dp[S]=0;
			
			for(int j=1;j<=tot;j++){
				double mx=0;
				for(int i=0;i<14;i++)if(S>>i&1){
					mx=max(mx,dp[S^(1<<i)]+cost[j][i+1]);
				}
				dp[S]+=prob[j]*mx;
			}
		}
		
		printf("Case #%d: %.6f\n", kase, dp[(1<<14)-1]);
	}
	
	return 0;
}
