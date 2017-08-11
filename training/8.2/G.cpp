#include<bits/stdc++.h>
using namespace std;

int trans[1<<12][1<<12];

int dp[1010][1010];

char s[1222];
char rule[1111];
int n;
vector<char>to[255];
vector<pair<char,char> >to2[255];
int a[22222];
int r[2222][3];
int sz=0;
int main(){
freopen("G.in","r",stdin);
	scanf("%s",s+1);
	n=strlen(s+1);
	cerr<<n<<endl;
	static int ending[2222];
	while(scanf("%s",rule+1)==1){
		ending[rule[1]]=1;
		if(strlen(rule+1)==2){
			to[rule[2]].push_back(rule[1]);
		}else{
			to2[rule[1]].push_back({rule[2],rule[3]});
			sz++;
			r[sz][0]=rule[1];
			r[sz][1]=rule[2];
			r[sz][2]=rule[3];
		}
	}

	map<char,int>M;
	int tot=0;
	for(int i=0;i<255;i++){
		if(ending[i]){
			M[i]=tot++;
		}	
	}
	
	for(int i=0;i<(1<<tot);i++)
	for(int j=0;j<(1<<tot);j++){
		for(int k=1;k<=sz;k++){
			if(!M.count(r[k][1])||!M.count(r[k][2]))continue;
			if((i&(1<<M[r[k][1]])) && (j&(1<<M[r[k][2]])))
				trans[i][j]|=(1<<M[r[k][0]]);
		}
	}
//	cerr<<tot<<endl;
	
	for(int i=1;i<=n;i++){
		for(auto x:to[s[i]]){
			a[i]|=(1<<M[x]);
		}
		dp[i][i]=a[i];
	}
	
	for(int len=2;len<=n;len++){
		for(int i=1;i+len-1<=n;i++){
			int j=i+len-1;
			for(int mid=i;mid<j;mid++){
				dp[i][j]|=trans[dp[i][mid]][dp[mid+1][j]];	
			}		
		}
	}
	if(dp[1][n]&(1<<M['S']))	
		puts("1");
	else
		puts("0");
	return 0;
}
