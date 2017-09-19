#include<bits/stdc++.h>

#define X first
#define Y second
#define m_p make_pair
using namespace std;
int n=8,m=9;
//int cnt=0;
struct Map{
	int mp[9][10];
	void print(){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++)
				printf("%d%c",mp[i][j]," \n"[j==m]);
		}
	}
	int* operator[](int x){return mp[x];}
	void clear(){memset(mp,0,sizeof mp);}
}now;
struct perm{
	pair<int,int> mp[9][10];
	pair<int,int>* operator[](int x){
		return mp[x];
	}
	void build(){
		for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if(mp[i][j].X==0){
				mp[i][j]=m_p(i,j);
			}
		}
	}
}p1,p2,M;

struct view{
	int mp[10];
	int& operator[](int x){return mp[x];}
}v1,v2;

Map operator*(Map mp,perm p){
	static Map nmp;
	nmp.clear();
	/*for(register int i=1;i<=n;i++){
		for(register int j=1;j<=m;j++){
			for(int k=1;k<=n;k++)
			for(int l=1;l<=m;l++){
				if(p[i][j]==p[k][l]&&(i!=k||j!=l)){
					cerr<<i<<" "<<j<<" "<<k<<" "<<l<<endl;
				}
			}	
		}
			//printf("(%d,%d)%c",p[i][j].X,p[i][j].Y, " \n"[j==m]);
	}
	*/
	
	for(register int i=1;i<=n;i++){
		for(register int j=1;j<=m;j++){
		//++cnt;
			nmp[p[i][j].X][p[i][j].Y]=mp[i][j];
		}
	}
	return nmp;
}

Map operator*(Map mp,view v){
	static Map nmp;
	for(register int i=1;i<=n;i++){
		for(register int j=1;j<=m;j++) {
			nmp[v[i]][j]=mp[i][j];
		//++cnt;
		}
//		memcpy(nmp[v[i]],mp[i],sizeof mp[i]);
	}
	return nmp;
}

void pre(){
#define P1(a,b,c,d) p1[a][b]=m_p(c,d)
#define PPP1(a,b,c,d,e,f) P1(a,b,c,d);P1(c,d,e,f);P1(e,f,a,b);



	PPP1(1,1,5,9,7,5);
	PPP1(2,1,8,5,4,9);
	PPP1(2,3,8,6,4,8);
	PPP1(2,2,8,7,4,4);
	PPP1(2,6,8,8,4,3);
	PPP1(2,5,8,9,4,1);
	p1.build();
#define P2(a,b,c,d) p2[a][b]=m_p(c,d);
#define PPP2(a,b,c,d,e,f) P2(a,b,c,d);P2(c,d,e,f);P2(e,f,a,b);
	
	PPP2(1,4,5,7,7,2);
	PPP2(1,3,5,8,7,6);
	PPP2(1,2,5,4,7,7);
	PPP2(2,4,8,2,4,7);
	PPP2(2,8,8,3,4,6);
	PPP2(2,7,8,4,4,2);
	p2.build();
	
	pair<int,int>tmp[90];
	int sz=0;
#define MM(a,b) tmp[++sz]=m_p(a,b);
	
	MM(1,5);MM(1,7);MM(1,6);MM(1,2);MM(1,9);MM(1,8);MM(1,4);MM(1,3);MM(1,1);
	MM(2,9);MM(2,4);MM(2,8);MM(2,7);MM(2,1);MM(2,3);MM(2,2);MM(2,6);MM(2,5);
	MM(5,5);MM(5,7);MM(5,6);MM(5,2);MM(5,9);MM(5,8);MM(5,4);MM(5,3);MM(5,1);
	MM(6,9);MM(6,4);MM(6,8);MM(6,7);MM(6,1);MM(6,3);MM(6,2);MM(6,6);MM(6,5);
	MM(4,9);MM(4,4);MM(4,8);MM(4,7);MM(4,1);MM(4,3);MM(4,2);MM(4,6);MM(4,5);
	MM(3,5);MM(3,7);MM(3,6);MM(3,2);MM(3,9);MM(3,8);MM(3,4);MM(3,3);MM(3,1);
	MM(8,9);MM(8,4);MM(8,8);MM(8,7);MM(8,1);MM(8,3);MM(8,2);MM(8,6);MM(8,5);
	MM(7,5);MM(7,7);MM(7,6);MM(7,2);MM(7,9);MM(7,8);MM(7,4);MM(7,3);MM(7,1);

	sz=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			M[i][j]=tmp[++sz];
		}
	}	

#define V1(a,b) v1[a]=b;
	V1(1,2);V1(2,3);V1(3,4);V1(4,1);
	V1(6,5);V1(5,8);V1(8,7);V1(7,6);

#define V2(a,b) v2[a]=b;
	
	V2(1,5);V2(5,1);
	V2(2,6);V2(6,2);
	V2(4,8);V2(8,4);
	V2(3,7);V2(7,3);
}
int flag;
bool check(){
	//cnt++;
	for(register int i=1;i<=n;i++){
		for(register int j=1;j<=m;j++){
			if(now[M[i][j].X][M[i][j].Y]!=now[M[i][1].X][M[i][1].Y])
				return false;
		}
	}
	return true;
}

void dfs(int dep){
	
	if(check()){
		flag=1;
	//	now.print();
		return ;
	}
	if(dep>3||flag)return ;
	
	for(int i=0;i<4;i++){
		for(int j=0;j<2;j++){
			
			Map back;
			
			back=now;
			now=now*p1;
			dfs(dep+1);
			if(flag)return ;
			now=back;
			
			
			back=now;
			now=now*p1*p1;
			dfs(dep+1);
			if(flag)return ;
			now=back;
		
			back=now;
			now=now*p2;
			dfs(dep+1);
			if(flag)return ;
			now=back;
			
			
			back=now;
			now=now*p2*p2;
			dfs(dep+1);
			if(flag)return ;
			now=back;
			
			
			now=now*v2;
		}
		now=now*v1;
	}
}


int main(){
	pre();
	int T;cin>>T;
	while(T--){
		flag=0;
		
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				int x;scanf("%d",&x);
				now[M[i][j].X][M[i][j].Y]=x;
			}
		}
//		return 0;

//		now.print();
		
		
		/*for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				now[i][j]=i;
			}
		}*/
		
		//now.print();
		//puts("");
				
//		now=now*p2*v2*p2*v1*p1*v2*p2;
		
		//now.print();
		
		dfs(1);
		//cerr<<cnt<<endl;
		puts(flag?"YES":"NO");
	}
	return 0;
}
