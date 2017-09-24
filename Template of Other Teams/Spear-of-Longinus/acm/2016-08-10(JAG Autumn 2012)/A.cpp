#include<cstdio>
#include<queue>
#include<iostream>
#include<algorithm>
using namespace std;
char s[233];
string str[555];
int M[26][26];
int vis[26],in[26];
int T,S;
int main(){

	__int128 TTT;
	TTT=2;
	
	//cin>>TTT;
	//cout<<TTT<<endl;

	int n;
	while(scanf("%d",&n)==1){
		if(!n)break;
		for(int i=1;i<=n;i++){
			scanf("%s",s);
			str[i]=string(s);
		}
		
		for(int i=0;i<26;i++)
			in[i]=0;
		for(int i=0;i<26;i++)
		for(int j=0;j<26;j++)
			M[i][j]=0;
		int flag=1;
		for(int i=1;i<n;i++){
			int prefix=1;
			for(int j=0;j<min(str[i].length(),str[i+1].length());j++){
				int c1=str[i][j]-'a';
				int c2=str[i+1][j]-'a';
				
				if(c1==c2)continue;
				prefix=0;	
				if(M[c1][c2]==0){
					M[c1][c2]=1;
					in[c2]++;
				}
				//cerr << c1 <<"--" <<c2 <<endl;
				break;
			}
			
			if(prefix){
				flag &= str[i].length() <= str[i+1].length();
			}
			
			if(flag==0)
				break;
		}
		
		queue<int>q;
		int ans=0;
		for(int i=0;i<26;i++){
			if(!in[i])q.push(i);
		}
		
		while(!q.empty()){
			int u=q.front();
			q.pop();
			for(int i=0;i<26;i++)if(M[u][i]){
				if(!--in[i]){
					q.push(i);
					
				}
			}
		}
	
		for(int i=0;i<26;i++)if(in[i])
			flag=0;		
		
		puts(flag?"yes":"no");
	}
	return 0;
}
