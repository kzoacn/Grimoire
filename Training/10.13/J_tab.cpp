#include<bits/stdc++.h>
using namespace std;

double p[111];
int n,m;

int cnt[22];
typedef	map<vector<int>,double> poly;
poly prob;


poly win[22];
poly allwin;

poly newp(int i){
	poly p;
	vector<int>vec;
	vec.resize(m);
	vec[i-1]=1;
	p[vec]=1;
	return p;
}

poly operator+(poly a,poly b){
	poly c=a;
	for(auto p:b){
		c[p.first]+=p.second;
	}
	return c;
}
poly operator*(poly a,poly b){
	poly c;
	for(auto p1:a){
		for(auto p2:b){
			double cof=p1.second*p2.second;
			auto vec=p1.first;
			for(int i=0;i<p2.first.size();i++)
				vec[i]+=p2.first[i];
			c[vec]+=cof;
		}
	}
	return c;
}

void dfs(int x){
	if(x==n+1){
		for(int i=1;i<=m;i++)if(cnt[i]==1){
			allwin=allwin+prob;
			win[i]=win[i]+prob;
			break;
		}
		return ;
	}
	for(int i=1;i<=m;i++){
		cnt[i]++;
		poly tmp=prob;
		
		prob=prob*newp(i);
		
		dfs(x+1);
		prob=tmp;
		cnt[i]--;
	}
}

double in(poly p){
	double ans=0;
	for(auto pr:p){
		vector<int>vec=pr.first;
		double res=1;
		for(int i=0;i<vec.size();i++)
			res*=pow(::p[i+1],vec[i]);
		ans+=res*pr.second;
	}
	return ans;
}


vector<double> find(int n,int m){
if (m == 1) {
	return {1.0};
}
//	swap(n,m);
	
	::n=n;
	::m=m;
	
	for(int i=1;i<=m;i++)
		p[i]=1.0/m;
	prob.clear();
	prob[vector<int>(m,0)]=1;;
	
	
	allwin.clear();
	for(int i=1;i<=m;i++)
		win[i].clear();
	dfs(1);
	int T=0;	
	int TAT=1000;
	while(TAT--){		
		static double win[222],allwin,op[222];
		for(int i=1;i<=m;i++){
			win[i]=in(::win[i]);
			op[i]=p[i];
		}
		allwin=in(::allwin);
		for(int i=1;i<=m;i++){
		
			p[i]+=win[i]/allwin;
		}
		double s = 0.0;
		for (int i = 1; i <= m; ++i) {
			s += p[i];
		}
		for (int i = 1; i <= m; ++i) {
			p[i] /= s;
		}
		bool flag=true;
		for (int i = 1; i <= m; ++i) {
			if(fabs(op[i]-p[i])>1e-5)
				flag=false;
		}
		T++;
		
		/*
		for(int i=1;i<=m;i++){
			cerr<<p[i]<<" ";
		}
		cerr<<endl;*/
	}
	

	return vector<double>(p+1,p+m+1);
}

void solve(){
double ans[20][20][20];

ans[1][1][0]=1.00000;
ans[1][2][0]=0.50000;
ans[1][2][1]=0.50000;
ans[2][1][0]=1.00000;
ans[2][2][0]=1.00000;
ans[2][2][1]=0.00000;
ans[2][3][0]=1.00000;
ans[2][3][1]=0.00000;
ans[2][3][2]=0.00000;
ans[3][1][0]=1.00000;
ans[3][2][0]=0.50000;
ans[3][2][1]=0.50000;
ans[3][3][0]=0.46410;
ans[3][3][1]=0.26795;
ans[3][3][2]=0.26795;
ans[3][4][0]=0.45778;
ans[3][4][1]=0.25164;
ans[3][4][2]=0.14529;
ans[3][4][3]=0.14529;
ans[4][1][0]=1.00000;
ans[4][2][0]=0.50000;
ans[4][2][1]=0.50000;
ans[4][3][0]=0.44852;
ans[4][3][1]=0.42633;
ans[4][3][2]=0.12515;
ans[4][4][0]=0.44773;
ans[4][4][1]=0.42487;
ans[4][4][2]=0.12566;
ans[4][4][3]=0.00174;
ans[4][5][0]=0.44767;
ans[4][5][1]=0.42474;
ans[4][5][2]=0.12570;
ans[4][5][3]=0.00175;
ans[4][5][4]=0.00014;
ans[5][1][0]=1.00000;
ans[5][2][0]=0.50000;
ans[5][2][1]=0.50000;
ans[5][3][0]=0.38165;
ans[5][3][1]=0.35368;
ans[5][3][2]=0.26466;
ans[5][4][0]=0.36157;
ans[5][4][1]=0.32120;
ans[5][4][2]=0.19955;
ans[5][4][3]=0.11767;
ans[5][5][0]=0.35819;
ans[5][5][1]=0.31559;
ans[5][5][2]=0.19182;
ans[5][5][3]=0.09677;
ans[5][5][4]=0.03763;
ans[5][6][0]=0.35785;
ans[5][6][1]=0.31502;
ans[5][6][2]=0.19107;
ans[5][6][3]=0.09511;
ans[5][6][4]=0.03515;
ans[5][6][5]=0.00580;


ans[6][1][0]=1.00000;
ans[6][2][0]=0.50000;
ans[6][2][1]=0.50000;
ans[6][3][0]=0.35576;
ans[6][3][1]=0.33869;
ans[6][3][2]=0.30555;
ans[6][4][0]=0.33009;
ans[6][4][1]=0.30261;
ans[6][4][2]=0.24022;
ans[6][4][3]=0.12708;
ans[6][5][0]=0.32664;
ans[6][5][1]=0.29758;
ans[6][5][2]=0.23155;
ans[6][5][3]=0.12260;
ans[6][5][4]=0.02163;
ans[6][6][0]=0.32654;
ans[6][6][1]=0.29744;
ans[6][6][2]=0.23130;
ans[6][6][3]=0.12246;
ans[6][6][4]=0.02165;
ans[6][6][5]=0.00061;
ans[6][7][0]=0.32653;
ans[6][7][1]=0.29741;
ans[6][7][2]=0.23126;
ans[6][7][3]=0.12244;
ans[6][7][4]=0.02165;
ans[6][7][5]=0.00061;
ans[6][7][6]=0.00010;

ans[7][1][0]=1.00000;
ans[7][2][0]=0.50000;
ans[7][2][1]=0.50000;
ans[7][3][0]=0.34415;
ans[7][3][1]=0.33481;
ans[7][3][2]=0.32103;
ans[7][4][0]=0.30454;
ans[7][4][1]=0.28404;
ans[7][4][2]=0.24595;
ans[7][4][3]=0.16547;
ans[7][5][0]=0.29575;
ans[7][5][1]=0.27210;
ans[7][5][2]=0.22727;
ans[7][5][3]=0.14347;
ans[7][5][4]=0.06141;
ans[7][6][0]=0.29458;
ans[7][6][1]=0.27049;
ans[7][6][2]=0.22476;
ans[7][6][3]=0.14074;
ans[7][6][4]=0.05808;
ans[7][6][5]=0.01134;

ans[7][7][0]=0.2945746500;
ans[7][7][1]=0.2704791600;
ans[7][7][2]=0.2247506100;
ans[7][7][3]=0.1407314300;
ans[7][7][4]=0.0580875400;
ans[7][7][5]=0.0109795700;
ans[7][7][6]=0.0003970400;
ans[7][8][0]=0.2945744000;
ans[7][8][1]=0.2704800000;
ans[7][8][2]=0.2247496000;
ans[7][8][3]=0.1407328000;
ans[7][8][4]=0.0580888000;
ans[7][8][5]=0.0109800000;
ans[7][8][6]=0.0003960000;
ans[7][8][7]=-0.0000016000;

	int n,m;
	cin>>n>>m;
	for(int i=0;i<m;i++)
		printf("%.5f\n",ans[n][m][i]);
	exit(0);
}

int main(){

//find(7,7);
//solve();
//return 0;
//


for(int i=7;i<=7;i++)
for(int j=1;j<=i+1;j++){
cerr<<i<<" "<<j<<endl;
	vector<double>p=find(i,j);
	for(int k=0;k<j;k++)
		printf("ans[%d][%d][%d]=%.5f;\n",i,j,k,p[k]);
}

return 0;
	int n,m;
	cin>>n>>m;
	vector<double>tmp=find(n,m);
	for(auto x:tmp)
		printf("%.5f\n",x);
	return 0;
}
