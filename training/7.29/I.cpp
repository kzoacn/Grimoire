#include<bits/stdc++.h>
using namespace std;
#define __advance __attribute__((optimize("O3")))
const int maxn=1010;
int n,m;
char s[maxn];
char mp[maxn][maxn];

int to[maxn][maxn][2];
int sgn(int x){
	if(x>0)return 1;
	if(x==0)return 0;
	return -1;
}
struct Robot{
	int x,y;
	int ty;
}rob[maxn*maxn],nrob[maxn*maxn];
int sz=0;
int jam[maxn][maxn];
int ans=0;
int ok;
int herox,heroy;
int T=0;
int tab[maxn][maxn];
const int inf=1e9;

void print(){
	static char nmp[maxn][maxn];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			nmp[i][j]='.';
			if(jam[i][j])
				nmp[i][j]='*';
		}
	}
	nmp[herox][heroy]='@';
	for(int i=1;i<=sz;i++){
		nmp[rob[i].x][rob[i].y]=rob[i].ty==1?'+':'#';
	}
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			putchar(nmp[i][j]);
		}
		puts("");
	}puts("");
}

__advance void move(int fob){
	T++;
	for(register int i=1;i<=sz;i++){
		nrob[i]=rob[i];
		if(rob[i].ty==2||!fob){
			nrob[i].x=rob[i].x+to[rob[i].x][rob[i].y][0];
			nrob[i].y=rob[i].y+to[rob[i].x][rob[i].y][1];
		}else{
			nrob[i].x=rob[i].x;
			nrob[i].y=rob[i].y;
		}
		if(tab[nrob[i].x][nrob[i].y]!=T)
			tab[nrob[i].x][nrob[i].y]=T;
		else{
			jam[nrob[i].x][nrob[i].y]=1;
		}
	}
	register int nsz=0;
	for(register int i=1;i<=sz;i++){
		if(nrob[i].x==herox&&nrob[i].y==heroy){
			ans++;
			continue;
		}
		if(jam[nrob[i].x][nrob[i].y]){
			continue;
		}else{
			++nsz;
			rob[nsz]=nrob[i];
			ok=1;
		}
	}
	sz=nsz;
	
}

__advance void run(){
	
	sz=0;
	for(register int i=1;i<=n;i++){
		for(register int j=1;j<=m;j++){
			if(mp[i][j]=='@'){
				herox=i;
				heroy=j;
			}
			if(mp[i][j]=='*')
				jam[i][j]=1;
			else jam[i][j]=0;
			if(mp[i][j]=='+'){
				sz++;
				rob[sz].x=i;rob[sz].y=j;
				rob[sz].ty=1;
			}
			
			if(mp[i][j]=='#'){
				sz++;
				rob[sz].x=i;rob[sz].y=j;
				rob[sz].ty=2;
			}
				
		}
	}
//	print();
//	exit(0);
	for(register int i=1;i<=n;i++){
		for(register int j=1;j<=m;j++){
			to[i][j][0]=sgn(herox-i);
			to[i][j][1]=sgn(heroy-j);
		}
	}
	ans=0;
	int step=0;
	while(1){
		ok=0;
		//cerr<<"be "<<sz<<endl;
		move(step);	
		//cerr<<"af "<<sz<<endl;	
		step^=1;
		//print();
		if(!ok)break;
	}
	printf("%d\n",ans);
}

__advance int main(){
	while(gets(s+1)){
		if(s[1]=='$'){
			run();
			n=0;
			continue;
		}
		m=strlen(s+1);
		n++;
		strcpy(mp[n]+1,s+1);
	}
	return 0;
}
