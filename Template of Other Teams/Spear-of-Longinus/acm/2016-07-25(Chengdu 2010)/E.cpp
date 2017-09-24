#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
#include<vector>
#include<string>
#define F first
#define S second
using namespace std;
typedef pair<int,int> Par;
int T;
int mp[2][6][6];
char Dir[6]={"DLRU"};
//               D L R  U
const int dx[4]={1,0,0,-1};
const int dy[4]={0,-1,1,0};
int Cant[2][4][6][6];
queue<pair<pair<int,int>,pair<int,int> > >q;
queue<string>way;
Par s[2],t[2];
bool vis[6][6][6][6];
bool hole[2][6][6];
void init(){
	memset(Cant,0,sizeof Cant);
	memset(vis,0,sizeof vis);
	memset(hole,0,sizeof hole);
	for(int m=0;m<2;m++)
		for(int i=0;i<6;i++)
			for(int j=0;j<6;j++){
				if(mp[m][i][j]>>0&1)
					Cant[m][1][i][j]=1;
			
				if(mp[m][i][j]>>1&1)
					Cant[m][0][i][j]=1;
			
				if(mp[m][i][j]>>2&1)
					Cant[m][2][i][j]=1;
			
				if(mp[m][i][j]>>3&1)
					Cant[m][3][i][j]=1;
			
				if(!(mp[m][i][j]>>4&1))
					hole[m][i][j]=1;
			
				if(mp[m][i][j]>>5&1)
					s[m]=make_pair(i,j);
			
				if(mp[m][i][j]>>6&1)
					t[m]=make_pair(i,j);
			}
}
void solve(){
	while(!q.empty())q.pop();
	while(!way.empty())way.pop();
	
	q.push(make_pair(s[0],s[1]));
	vis[s[0].F][s[0].S][s[1].F][s[1].S]=1;
	way.push(string(""));
	while(!q.empty()){
		Par now[2];string W=way.front();
		now[0]=q.front().F;
		now[1]=q.front().S;
		//printf("%d %d %d %d\n",now[0].F,now[0].S,now[1].F,now[1].S);
		q.pop();way.pop();
		if(now[0]==t[0]&&now[1]==t[1]){
			printf("%s\n",W.c_str());
			return;
		}
		
		for(int k=0;k<4;k++){
			char newC=Dir[k];
			Par nS[2];
			int flag=1;
			for(int m=0;m<2;m++){
				if(Cant[m][k][now[m].F][now[m].S]){
					nS[m]=now[m];
					flag&=1;
					continue;
				}else{
					int x=now[m].F+dx[k];
					int y=now[m].S+dy[k];
					if(x<0||x>=6||y<0||y>=6||hole[m][x][y]){
						flag=0;continue;
					}
					nS[m]=make_pair(x,y);
				}
			
			}
			//cerr<<flag<<endl;
			if(flag){
				if(!vis[nS[0].F][nS[0].S][nS[1].F][nS[1].S]){
					vis[nS[0].F][nS[0].S][nS[1].F][nS[1].S]=1;
					q.push(make_pair(nS[0],nS[1]));
					way.push(W+newC);
				}
			}
			
		}
		
	}
	puts("-1");
}
int main(){
	scanf("%d",&T);
	for(int i=0;i<6;i++)
		for(int j=0;j<6;j++)
			scanf("%d",&mp[0][i][j]);
	T--;
	while(T--){
		for(int i=0;i<6;i++)
			for(int j=0;j<6;j++)
				scanf("%d",&mp[1][i][j]);
		
		init();
		
		solve();

		for(int i=0;i<6;i++)
			for(int j=0;j<6;j++)
				mp[0][i][j]=mp[1][i][j];
	}
	return 0;
}
