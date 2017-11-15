#include<bits/stdc++.h>
using namespace std;
int h,w,n;

char mp[222][222];

void print(int x,int y){
	
	for(int i=1;i<=h;i++)
	for(int j=1;j<=w;j++)
		mp[i][j]='.';

	for(int i=1;i<=x;i++){
		for(int j=1;j<=w;j++)
			mp[(i-1)*2+2][j]='#';
	}
	
	for(int j=1;j<=y;j++){
		for(int i=1;i<=h;i++){
			mp[i][(j-1)*2+2]='#';
		}
	}
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++)
			putchar(mp[i][j]);
		puts("");
	}
}

int main(){
freopen("kotlin.in","r",stdin);
freopen("kotlin.out","w",stdout);
	while(cin>>h>>w>>n){	
		for(int i=0;i<=(h-1)/2;i++){
			for(int j=0;j<=(w-1)/2;j++){
				if((i+1)*(j+1)==n){
					print(i,j);		
					goto END;
				}
			}
		}
		puts("Impossible");
		END:;
	}	
	return 0;
}
