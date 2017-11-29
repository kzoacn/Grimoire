#include<bits/stdc++.h>
using namespace std;



vector<tuple<int,char,int> >OO;
void check(int n){
	static int a[int(2e5+5)];
	for(int i=1;i<=n;i++)
		a[i]=n;
	int tot=n;
	set<int>S;
	for(int i=1;i<n;i++){
		int x=get<0>(OO[i]);
		char op=get<1>(OO[i]);
		int y=get<2>(OO[i]);
		assert(!S.count(x));
		assert(!S.count(y));
		S.insert(x);
		S.insert(y);
		if(op=='+'){
			a[++tot]=a[x]+a[y];
		}else
		if(op=='-'){
			a[++tot]=a[x]-a[y];
		}else
		if(op=='*'){
			a[++tot]=a[x]*a[y];
		}else
		if(op=='/'){
			a[++tot]=a[x]/a[y];
		}
		
	}
	assert(OO.size()==n-1);
	assert(a[2*n-1]==24);
}



vector<char> DP(int n){
	static int _dp[50][5000],*dp[50];
	static int _pre[50][5000],*pre[50];
	
	int lim=500;
	for(int i=0;i<50;i++){
		dp[i]=_dp[i]+lim*2;
		pre[i]=_pre[i]+lim*2;
	}
	memset(_dp,0,sizeof _dp);
	dp[1][n]=1;
	for(int i=1;i<n;i++){
		for(int j=0;j<=lim;j++){
			if(dp[i][j]){
				for(auto nxt:{j+n,j-n,j*n}){
					if(-lim<=nxt&&nxt<=lim){
						dp[i+1][nxt]=1;
						pre[i+1][nxt]=j;
					}
				}
				if(j%n==0){
					int nxt=j/n;
					if(-lim<=nxt&&nxt<=lim){
						dp[i+1][nxt]=1;
						pre[i+1][nxt]=j;
					}
				}
				/*if(j&&n%j==0){
					int nxt=n/j;
					if(-lim<=nxt&&nxt<=lim){
						dp[i+1][nxt]=1;
						pre[i+1][nxt]=j;
					}
				}*/
				
			}
		}
	}
	
	
	vector<char>oper;
	
	int w=24;
	for(int i=n;i>=2;i--){
		//cout<<pre[i][w]<<endl;
		
		if(pre[i][w]+n==w){
			oper.push_back('+');
		}else 
		if(pre[i][w]-n==w){
			oper.push_back('-');
		}else 
		if(pre[i][w]*n==w){
			oper.push_back('*');
		}else 
		if(pre[i][w]/n==w){
			oper.push_back('/');
		}else assert(0);
		
		w=pre[i][w];
	}
	reverse(oper.begin(),oper.end());
	
	return oper;
}
int a[int(2e5+5)];

void small(int n){
	if(n<=3){
		puts("-1");
		return ;
	}
	vector<char>op=DP(n);
	int cur=1;
	for(int i=1;i<n;i++){
		printf("%d %c %d\n",cur,op[i-1],i+1);
		if(op[i-1]=='+'){
			a[n+i]=a[cur]+n;
		}else
		if(op[i-1]=='-'){
			a[n+i]=a[cur]-n;
		}else
		if(op[i-1]=='*'){
			a[n+i]=a[cur]*n;
		}else
		if(op[i-1]=='/'){
			a[n+i]=a[cur]/n;
		}
		cur=n+i;
	}
}

int tot;
int OP(int x,char op,int y){
	printf("%d %c %d\n",x,op,y);
	if(op=='+'){
		a[++tot]=a[x]+a[y];
	}else
	if(op=='-'){
		a[++tot]=a[x]-a[y];
	}else
	if(op=='*'){
		a[++tot]=a[x]*a[y];
	}else
	if(op=='/'){
		a[++tot]=a[x]/a[y];
	}
	return tot;
}

void huge(int n){
	tot=n;
	for(int i=1;i<=18;i+=2){
		OP(i,'/',i+1);
	}
	int two,three,four,zero;
	//n+1 .. n+9 is 1
	two=OP(n+1,'+',n+2);
	
	three=OP(n+3,'+',n+4);
	three=OP(three,'+',n+5);
	
	four=OP(n+6,'+',n+7);
	four=OP(four,'+',n+8);
	four=OP(four,'+',n+9);
	
	zero=OP(19,'-',20);
	
	for(int i=21;i<=n;i++){
		zero=OP(zero,'*',i);
	}
	
	two=OP(two,'+',zero);
	int six=OP(two,'*',three);
	OP(six,'*',four);
	assert(tot==2*n-1);
	assert(a[tot]==24);
	
}

int main(){
	
	//cout<<DP(19)<<endl;;
	int n;
	while(cin>>n){
	
		for(int i=1;i<=n;i++)
			a[i]=n;
	
		OO.clear();
		if(n<=20){
			small(n);
		}else{
			huge(n);
		}
		
		//check(n);
	}
	return 0;
}
