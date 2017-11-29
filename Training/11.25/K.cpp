#include<bits/stdc++.h>
using namespace std;
int n;

char mp[20][20];


int ok;


bool check(int *a,int pre,int nxt){
	int ans1=0,ans2=0;
	int c1=0,c2=0;
	for(int i=1;i<=n;i++){
		if(a[i]>c1){
			c1=a[i];
			ans1++;
		}
	}
	
	for(int i=n;i>=1;i--){
		if(a[i]>c2){
			c2=a[i];
			ans2++;
		}
	}
	int ok=1;
	if(1<=pre&&pre<=n)ok&=(ans1==pre);
	if(1<=nxt&&nxt<=n)ok&=(ans2==nxt);
	return ok;
}
bool check_row(int r){
	int tmp[10];
	for(int i=1;i<=n;i++)
		tmp[i]=mp[r][i]-'0';
	return check(tmp,mp[r][0]-'0',mp[r][n+1]-'0');
}
bool check_col(int c){
	int tmp[10];
	for(int i=1;i<=n;i++)
		tmp[i]=mp[i][c]-'0';
	return check(tmp,mp[0][c]-'0',mp[n+1][c]-'0');
}
bool checkall(){
	for(int i=1;i<=n;i++)
		if(!check_row(i))
			return false;
	for(int i=1;i<=n;i++)
		if(!check_col(i))
			return false;
	return true;
}

bool check_single(int x,int y){
	for(int i=1;i<=n;i++){
		if(i!=y&&mp[x][i]==mp[x][y])
			return false;
		if(i!=x&&mp[i][y]==mp[x][y])
			return false;
	}
	return true;
}


void print(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)
			putchar(mp[i][j]);
		puts("");
	}
}

void dfs(int x,int y){
	if(ok)return ;
	//cerr<<x<<" "<<y<<endl;
	//print();
	if(y==n+1){
		if(!check_row(x))
			return ;
		x++;
		y=1;
	}
	
	if(x==n+1){
		if(checkall()){
			ok=1;
			print();
		}
		return ;
	}
	if(isdigit(mp[x][y])){
		if(check_single(x,y))
			dfs(x,y+1);
	}else{
		for(int i=1;i<=n;i++){
			mp[x][y]='0'+i;
			if(check_single(x,y))
				dfs(x,y+1);
			mp[x][y]='-';
		}
	}
	
}

void solve(){
	cin>>n;
	for(int i=0;i<=n+1;i++)
		cin>>mp[i];
	ok=0;
	dfs(1,1);
	
	if(ok){
		//print();
	}else{
		puts("no");
	}
	puts("");
}

int main(){
	int T;cin>>T;
	while(T--)
		solve();
	return 0;
}
