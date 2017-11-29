#include<bits/stdc++.h>
using namespace std;

int n,m,x,y;

bool check(int len){
	if(2*len<n){
		if(x<=len||x>=n-len+1)
			return 2*len>=m;
		else{
			if(2*len+1==n){
				return len>=max(y-1,m-y);
			}else{
				return len>=max(y-1,m-y) && len*2>=m;
			}
		}
	}else {//2*len>=n
		int lef=min(len+1,x+1);
		int rig=max(n-len-1,x-1);
		if(lef<=rig)
			return y<=len || y>=m-len+1;
		else
			return true;
	}
}

int fx(int x){return n-x+1;}
int fy(int y){return m-y+1;}
int min3(int a,int b,int c){return min(min(a,b),c);}
int main(){
	while(scanf("%d%d%d%d",&n,&m,&x,&y)==4){
		if (n == 1 || m == 1) {
			puts("1");
			continue;
		}
		
		int ans=min((n+1)/2,(m+1)/2);
		if(n%2==1&&m%2==1){
			if((n+1)/2==x && (m+1)/2==y)
				ans=0;
		}
		
		ans=max(ans,min3(x-1,y,fy(y)));
		ans=max(ans,min3(fx(x+1),y,fy(y)));
		ans=max(ans,min3(y-1,x,fx(x)));
		ans=max(ans,min3(fy(y+1),x,fx(x)));
		
		printf("%d\n",ans);
	}	
	return 0;
}
