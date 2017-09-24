#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cctype>
#include<cstring>
using namespace std;
int n,m;
struct tup{
	int x,y,z;
	bool operator<(const tup &oth)const{
		if(x!=oth.x)return x<oth.x;
		if(y!=oth.y)return y<oth.y;
		return z<oth.z;
	}
	bool operator==(const tup &oth)const{
		return x==oth.x&&y==oth.y&&z==oth.z;
	}
	int& operator[](int t){
		if(t==0)return x;
		if(t==1)return y;
		if(t==2)return z;
	}
};
tup blocks[int(1e6+5)];
char s[22222];
int main(){
	int T;scanf("%d",&T);
	while(T--){
		scanf("%d%d\n",&n,&m);
		int siz=0;
		char A,B;
		int a,b;
		while(m--){
			//A=getchar();
			//scanf("%c=%d,%c=%d",&A,&a,&B,&b);
			scanf("%s",s);
			int len=strlen(s);
			A=B=0;
			for(int i=0;i<len;i++){
				if(s[i]=='='){
					if(!A)A=s[i-1];
					else B=s[i-1];
				}	
			}
			
			
			int flag=0;
			for(int i=0;i<len;i++){
				if(s[i]=='-'){
					flag=1;break;
				}
			}
			if(flag)continue;
			
			
			
			a=0;b=0;
			int r=0;
			for(int i=2;i<len;i++){
				if(s[i]==','){
					a=r;r=0;
					continue;
				}
				if(isdigit(s[i]))
				r=r*10+s[i]-'0';
			}
			b=r;
			
//			printf("%c %d %c %d\n",A,a,B,b);
			
			if(a<1||a>n||b<1||b>n)continue;
			
			tup Bl;
			if(A=='X')Bl[0]=a;
			if(A=='Y')Bl[1]=a;
			if(A=='Z')Bl[2]=a;
			
			if(B=='X')Bl[0]=b;
			if(B=='Y')Bl[1]=b;
			if(B=='Z')Bl[2]=b;
			
			int lin=0;
			
			if('X'!=A&&'X'!=B){
				lin=0;
			}else if('Y'!=A&&'Y'!=B){
				lin=1;
			}else if('Z'!=A&&'Z'!=B){
				lin=2;
			}
			
			for(int i=1;i<=n;i++){
				Bl[lin]=i;
				blocks[++siz]=Bl;
			}
			
		}
		sort(blocks+1,blocks+1+siz);
		int ans=unique(blocks+1,blocks+1+siz)-blocks-1;
		printf("%d\n",ans);
	}
	return 0;
}
