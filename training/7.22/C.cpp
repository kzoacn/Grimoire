#include<bits/stdc++.h>
using namespace std;
int val[int(1e6)+1];


int b[11];
int c[11];
int calc(int b[]){
	static int a[333];
	for(int i=1;i<=5;i++)
		a[i]=b[i];
	sort(a+1,a+1+5);
	
	int ok=1;
	for(int i=1;i<=5;i++)
		if(a[i]!=a[1])
			ok=0;
	if(ok)return 50;
	
	ok=1;
	for(int i=1;i<=4;i++){
		if(a[i]+1!=a[i+1])
			ok=0;
	}
	if(ok)return 40;
	
	
	ok=1;
	for (int i = 1; i <= 5; ++i) {
		c[i] = a[i];
	}
	int k = unique(c + 1, c + 5 + 1) - c - 1;
	if (k == 4 && c[1] + 3 == c[4]) {
		return 30;
	}
	ok=1;
	for(int i=2;i<=4;i++){
		if(a[i]+1!=a[i+1])
			ok=0;
	}
	if(ok)return 30;
	ok=1;
	for(int i=1;i<=3;i++){
		if(a[i]+1!=a[i+1])
			ok=0;
	}
	if(ok)return 30;

	map<int,int>M;
	for(int i=1;i<=5;i++)M[a[i]]++;
	int mx=0,tmp;
	for(auto x:M){
		if(x.second>mx){
			mx=max(mx,x.second);
			tmp=x.first;
		}
	}
	if(mx==4){
		return 4*tmp;
	}else if(mx==3){
		if(M.size()==2)
			return 25;
		return 3*tmp;
	}
	return 0;
}


void pre(){
	for(b[1]=1;b[1]<=6;b[1]++)
	for(b[2]=1;b[2]<=6;b[2]++)
	for(b[3]=1;b[3]<=6;b[3]++)
	for(b[4]=1;b[4]<=6;b[4]++)
	for(b[5]=1;b[5]<=6;b[5]++){
		int x=0;
		for(int i=1;i<=5;i++)	
			x=x*10+b[i];
		/*if (b[1] != 3) {
			continue;
		}
		if (b[2] != 5) {
			continue;
		}
		if (b[3] != 2) {
			continue;
		}
		if (b[4] != 4) {
			continue;
		}
		if (b[5] != 4) {
			continue;
		}*/
		val[x]=calc(b);
	}
	//cout << val[35244] << endl; exit(0);
}

/*int ty[33];
int card[33][2];
int Sval;

int vis[14];
const int dx[]={0,0,1,-1};
const int dy[]={1,-1,0,0};*/
int n=5;
int pack(int q,int w,int e,int r,int t){
	return q*10000+w*1000+e*100+r*10+t;
}
int a[15][15];
int emp=0;
int px,py;
int calcValue(){
	int ans=0;
	int cnt=0;
	for(int i=1;i<=n;i++){
		int v=val[pack(a[i][1],a[i][2],a[i][3],a[i][4],a[i][5])];
//cout << "line: " << i << " " << pack(a[i][1],a[i][2],a[i][3],a[i][4],a[i][5]) << " " << v << endl;
		if(v==50)
			cnt++;
		else 
			ans+=v;
	}
	for(int i=1;i<=n;i++){
		int v=val[pack(a[1][i],a[2][i],a[3][i],a[4][i],a[5][i])];
		if(v==50)
			cnt++;
		else 
			ans+=v;
	}
	int v=val[pack(a[1][1],a[2][2],a[3][3],a[4][4],a[5][5])];
	if(v==50)
		cnt++;
	else 
		ans+=v;
	v=val[pack(a[5][1],a[4][2],a[3][3],a[2][4],a[1][5])];
	if(v==50)
		cnt++;
	else 
		ans+=v;
	if(cnt)ans+=50+(cnt-1)*100;
	
	return ans;
}

/*int CLO=0;*/
void print(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)
			printf("%d%c",a[i][j]," \n"[j==n]);
	}
}
/*int type[44][44];
int cnt=0;
bool dfs(int x,int y){
	if(y==n+1){
		x++;
		y=1;
	}
	if(x==n&&y==n){
	
		
		return true;
	}
	if(!a[x][y]){
		for(int i=1;i<=13;i++)if(!vis[i]){
			if(ty[i]==1){
				if(x==n||a[x][y]||a[x+1][y])continue;
				a[x][y]=card[i][0];
				a[x+1][y]=card[i][1];
				vis[i]=1;
				cnt++;
				type[x][y]=1;
				if(dfs(x,y+1))return true;
				cnt--;
				vis[i]=0;				
				a[x][y]=0;
				a[x+1][y]=0;
				
			}else if(ty[i]==2){
				if(y==n||a[x][y]||a[x][y+1])continue;
				a[x][y]=card[i][0];
				a[x][y+1]=card[i][1];
				vis[i]=1;
				cnt++;
				type[x][y]=2;
				if(dfs(x,y+1))return true;
				cnt--;
				vis[i]=0;				
				a[x][y]=0;
				a[x][y+1]=0;
			}else{
				a[x][y]=Sval;
				if(dfs(x,y+1))return true;
			}
		}
	}else{
		
	}
	assert(false);
}
*/

int card[111][2];
int M[111][111];
int Sval;
int p_x[111], p_y[111];
int tp[111];
void solve(){
	memset(a, 0, sizeof(a));
	for (int i = 1; i <= 6; ++i) {
		for (int j = 1; j <= 6; ++j) {
			M[i][j] = 1;
		}
	}
	for(int i=1;i<=13;i++){
		char s[33];scanf("%s",s);
		bool flag = true;
		if(s[0]=='S'){
			tp[i] = 0;
			scanf("%d", &Sval);
			for (int x = 1; x <= 5; ++x) {
				for (int y = 1; y <= 5; ++y) {
					if (!a[x][y] && flag) {
						a[x][y] = Sval;
						flag = false;
					}
				}
			}
		}else{
			scanf("%d%d",&card[i][0],&card[i][1]);
			if (s[0] == 'V') {
				tp[i] = 1;
			} else {
				tp[i] = 2;
			}
			for (int x = 1; x <= 5; ++x) {
				for (int y = 1; y <= 5; ++y) {
					if (!flag) continue;
					if (s[0] == 'V') {
						if (x < 5 && !a[x][y] && !a[x + 1][y]) {
							flag = false;
							a[x][y] = card[i][0];
							a[x + 1][y] = card[i][1];
							p_x[i] = x;
							p_y[i] = y;
							M[card[i][0]][card[i][1]] = 0;
							M[card[i][1]][card[i][0]] = 0;
						}
					} else {
						if (y < 5 && !a[x][y] && !a[x][y + 1]) {
							flag = false;
							a[x][y] = card[i][0];
							a[x][y + 1] = card[i][1];
							p_x[i] = x;
							p_y[i] = y;
							M[card[i][0]][card[i][1]] = 0;
							M[card[i][1]][card[i][0]] = 0;
						}
					}
				}
			}
		}
		assert(!flag);
	}
	
	
	//cout << p_x[12] << " " << p_y[12] << endl;
	/*a[5][1] = 3;
	a[5][2] = 2;
	print();
	cout << calcValue() << endl;
	return;*/
	/*puts("");
	print();*/
	int ans=calcValue();
	for (int i = 1; i <= 13; ++i) {
		if (!tp[i]) {
			continue;
		}
		for (int j = 1; j <= 6; ++j) {
			for (int k = 1; k <= 6; ++k) {
				if (!M[j][k]) {
					continue;
				}
				if (tp[i] == 1) {
					a[p_x[i]][p_y[i]] = j;
					a[p_x[i] + 1][p_y[i]] = k;
					ans = max(ans, calcValue());
					a[p_x[i]][p_y[i]] = card[i][0];
					a[p_x[i] + 1][p_y[i]] = card[i][1];
				} else {
					a[p_x[i]][p_y[i]] = j;
					a[p_x[i]][p_y[i] + 1] = k;
					//assert(a[p_x[i]][p_y[i]] == card[i][0] && a[p_x[i] + 1][p_y[i]])
					ans = max(ans, calcValue());
					a[p_x[i]][p_y[i]] = card[i][0];
					a[p_x[i]][p_y[i] + 1] = card[i][1];
				}
			}
		}
	}
	
	/*puts("");
	print();*/
	printf("%d\n",ans);
}

int main(){
	pre();
	int T;cin>>T;
	for(int t=1;t<=T;t++){
		printf("Case %d: ",t);
		solve();	
	}
	
	return 0;
}

/*

6 5 5 6 6
3 5 1 2 4
1 4 3 5 6
6 0 4 3 4
1 5 2 3 4
*/
