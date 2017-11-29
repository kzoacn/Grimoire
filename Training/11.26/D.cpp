#include<bits/stdc++.h>
#define X first
#define Y second
using namespace std;
typedef pair<int,int> Pos;
Pos nxt[20][20][6];
//L R LL LR UL UR 
//0 1 2  3  4  5

int bitrev[1<<15][15];
int n;

int mp[22][22];
int len[22];
int col[22][22],match[10];

bool inside(Pos p){
	if(p.X<1||p.X>17)return false;
	return p.Y<=len[p.X]&&p.Y>=1;
}

void init(){
	match[1]=2;
	match[2]=1;
	
	match[3]=4;
	match[4]=3;
	
	match[5]=6;
	match[6]=5;
	
	memset(mp,0,sizeof mp);
	memset(col,0,sizeof col);
	for(int i=1;i<=4;i++)
		len[i]=len[17-i+1]=i;
	for(int i=5;i<=8;i++)
		len[i]=len[17-i+1]=13-(i-5);
	len[9]=9;	
	
	for(int i=1;i<=4;i++)
		for(int j=1;j<=len[i];j++)
			col[i][j]=1;
			
	for(int i=14;i<=17;i++)
		for(int j=1;j<=len[i];j++)
			col[i][j]=2;

	for(int i=10;i<=13;i++)
		for(int j=1;j<=i-9;j++)
			col[i][j]=3;
			
	for(int i=5;i<=8;i++)
		for(int j=1;j<=9-i;j++)
			col[i][len[i]-j+1]=4;
			
	for(int i=10;i<=13;i++)
		for(int j=1;j<=i-9;j++)
			col[i][len[i]-j+1]=5;

	for(int i=5;i<=8;i++)
		for(int j=1;j<=9-i;j++)
			col[i][j]=6;

	memcpy(mp,col,sizeof col);
	
	
	for(int i=1;i<=17;i++){
		for(int j=1;j<=len[i];j++){
			nxt[i][j][0]=Pos(i,j-1);
			nxt[i][j][1]=Pos(i,j+1);
		}
	}
	
	for(int i=1;i<=17;i++){
		for(int j=1;j<=len[i];j++){
			if(i<=3){
				nxt[i][j][2]=Pos(i+1,j+0);
				nxt[i][j][3]=Pos(i+1,j+1);
			}else
			if(i==4){
				nxt[i][j][2]=Pos(i+1,j+4);
				nxt[i][j][3]=Pos(i+1,j+5);
			}else
			if(i<=8){
				nxt[i][j][2]=Pos(i+1,j-1);
				nxt[i][j][3]=Pos(i+1,j+0);
			}else
			if(i<=12){
				nxt[i][j][2]=Pos(i+1,j+0);
				nxt[i][j][3]=Pos(i+1,j+1);
			}else
			if(i==13){
				nxt[i][j][2]=Pos(i+1,j-5);
				nxt[i][j][3]=Pos(i+1,j-4);
			}else
			if(i<=17){
				nxt[i][j][2]=Pos(i+1,j-1);
				nxt[i][j][3]=Pos(i+1,j+0);
			}
		}
	}
	
	
	for(int i=1;i<=17;i++){
		for(int j=1;j<=len[i];j++){
			if(inside(nxt[i][j][2])){
				nxt[nxt[i][j][2].X][nxt[i][j][2].Y][5]=Pos(i,j);
			}
			if(inside(nxt[i][j][3])){
				nxt[nxt[i][j][3].X][nxt[i][j][3].Y][4]=Pos(i,j);
			}
		}
	}
}
void move(int x,int y,int d,int player){
	int bit=0,len=0;
	int c=mp[x][y];
	if(!c || c!=player)return;
	Pos pos=Pos(x,y);
	int tmpx=x,tmpy=y;
	//cerr<<col[x][y]<<" "<<mp[x][y]<<endl;
//	cerr<<mp[5][5]<<endl;
//	cerr<<x<<" "<<y<<endl;
	
//	cerr<<inside(Pos(9,1))<<endl;
	
	while(inside(Pos(x,y))&&(col[x][y]==0||match[col[x][y]]==c||col[x][y]==c)){
		
		bit=(bit<<1)|(!!mp[x][y]);
		len++;
		if(len==1)bit=0;
		
		if(len==2&&__builtin_popcount(bit)==0){
			pos=Pos(x,y);
		}
		if(len>=3&&__builtin_popcount(bit)>=1){
			if(bitrev[bit][len]==bit)
				pos=Pos(x,y);
		}
		
		int tx,ty;
		tx=nxt[x][y][d].X;
		ty=nxt[x][y][d].Y;
		x=tx;y=ty;
	//	cerr<<tx<<" "<<ty<<" "<<mp[tx][ty]<<" "<<col[tx][ty]<<endl;
	}
	//fprintf(stderr,"from (%d,%d) to (%d,%d)\n",tmpx,tmpy,pos.X,pos.Y);
	swap(mp[tmpx][tmpy],mp[pos.X][pos.Y]);
}

int main(){
	for(int i=1;i<15;i++){
		for(int S=0;S<(1<<i);S++){
			int bit=0;
			for(int j=0;j<i;j++)
				bit|=(S>>j&1)<<(i-1-j);
			bitrev[S][i]=bit;
		}
	}
	
	while(scanf("%d",&n)==1&&n){
		init();	
		
		/*for(int i=1;i<=17;i++)
		for(int j=1;j<=len[i];j++)
		for(int k=0;k<6;k++)
			printf("nxt[%d][%d][%d]=(%d,%d)\n",i,j,k,nxt[i][j][k].X,nxt[i][j][k].Y);
		*/
		map<string,int>M;
		M["L"]=0;
		M["R"]=1;
		M["LL"]=2;
		M["LR"]=3;
		M["UL"]=4;
		M["UR"]=5;
		int player=1;
		while(n--){
			int x,y;char s[5];
			scanf("%d%d%s",&x,&y,s);
			move(x,y,M[s],player);
			player=player%6+1;
		}
		vector<pair<int,int> >vec[7];
		for(int i=1;i<=17;i++)
		for(int j=1;j<=len[i];j++)
			vec[mp[i][j]].push_back({i,j});
		for(int i=1;i<=6;i++){
			sort(vec[i].begin(),vec[i].end());
			for(int j=0;j<10;j++)
				printf("%d %d%c",vec[i][j].X,vec[i][j].Y," \n"[j==9]);
		}
	}

	return 0;
}
