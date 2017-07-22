#include<bits/stdc++.h>
using namespace std;
const int maxn=55;
vector<int>mem[maxn][maxn];
int board[1111111];
char s[maxn];
int n;
vector<int>ZERO;
int mp[666];
void dp(int l,int r){
	if(mem[l][r].size())
		return ;
	vector<int>&ans=mem[l][r];
	if(l>r){
		ans=ZERO;
		return ;
	}
	if(l==r){
		ans.push_back(mp[s[l]]);
		return ;
	}
	for (int i = l + 1; i <= r; ++i) {
		dp(l, i - 1);
		dp(i, r);
	}
	ans.clear();
	for(int i=l+1;i<=r;i++){
		vector<int>&lef=mem[l][i-1];
		vector<int>&rig=mem[i][r];
		for(auto x:lef){
			for(auto y:rig){
				if(x<y){
					if (!board[y - x]) {
						ans.push_back(y-x);
						board[y - x] = 1;
					}
				}else{
					if (!board[x + y]) {
						ans.push_back(x+y);
						board[x + y] = 1;
					}
				}
			}
		}
	}
	
	for (int i = 0; i < ans.size(); ++i) {
		board[ans[i]] = 0;
	}
	
}

int main(){
	mp['I']=1;
	mp['V']=5;
	mp['X']=10;
	mp['L']=50;
	mp['C']=100;
	ZERO.push_back(0);
	while(1){
		scanf("%s",s+1);
		n=strlen(s+1);
		if(s[1]=='0')break;
		for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			mem[i][j].clear();
		dp(1,n);
		vector<int>ans=mem[1][n];
		sort(ans.begin(), ans.end());
		if(ans[0]==0)ans.erase(ans.begin());
		static int T=0;
		printf("Case %d: ",++T);
		for(int i=0;i<ans.size();i++)
			printf("%d%c",ans[i]," \n"[i+1==ans.size()]);
	}
	return 0;
}
