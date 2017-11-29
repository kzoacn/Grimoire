#include<bits/stdc++.h>
using namespace std;

const int maxn=233;

typedef long double LD;
const LD eps=1e-15;
LD A[maxn][maxn];


void print(int n){
	for(int i=1;i<=n;i++){
		for(int j=0;j<=n;j++)
			printf("%.3Lf ",A[i][j]);
		puts("");
	}
	puts("");	
}


int id[maxn],pos[maxn];

void Gauss(int n){
	
	//print(n);


	
	int now=1;
	for(int i=1;i<=n;i++){
		int r=now;
		for(int j=now;j<=n;j++){
			if(fabs(A[r][i])<fabs(A[j][i])){
				r=j;
			}
		}
		
		if(fabs(A[r][i])<eps)
			continue;
		
		pos[now]=i;
		swap(A[r],A[now]);
//		cerr<<i<<endl;
//		assert(fabs(A[i][i])>1e-8);
		//print(n);
		for(int j=now+1;j<=n;j++){
			LD t=A[j][i]/A[now][i];
			for(int k=0;k<=n;k++){
				A[j][k]-=A[now][k]*t;
			}
		}
		
		now++;
		//print(n);
	}
	for(int i=n;i>=1;i--){
		for(int j=pos[i]+1;j<=n;j++)if(fabs(A[i][j])>eps)
			A[i][0]-=A[i][j]*A[j][0];
		A[i][0]/=A[i][pos[i]];
		A[i][pos[i]]/=A[i][pos[i]];
	}
	//print(n);
}

LD a,b,c,d,r;
int n,m;


int main(){
	int T;cin>>T;
	while(T--){
		cin>>n>>m>>a>>b>>c>>d>>r;
		memset(A,0,sizeof A);
		for(int i=-m;i<=m;i++){
			id[i+m+1]=i+m+1;
			int nxt;
			LD t=(LD)i/m;
			if(i<=0){
				nxt=-m-2*i;
				A[i +m+1][i +m+1]+=1;
				A[i +m+1][nxt +m+1]+= - (b+r*t*t)/r;
				A[i +m+1][0]+=a/r;
			}else{
				nxt=m-2*i;
				A[i +m+1][i +m+1]+=1;
				A[i +m+1][nxt +m+1]+= - (d+r*t*t)/r;
				A[i +m+1][0]+=c/r;
			}
		}
		
		
		Gauss(2*m+1);
		
		
		int ps=0;
		for(int i=1;i<=2*m+1;i++)
			if(::pos[i]==n+m+1)
				ps=i;
		assert(ps);
		printf("%.20f\n",(double)A[ps][0]);
	}
	return 0;
}
