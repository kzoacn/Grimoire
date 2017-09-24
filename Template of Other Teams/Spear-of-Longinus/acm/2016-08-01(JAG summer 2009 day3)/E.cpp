#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<map>
#include<set>
using namespace std;
map<string,int>M;
char s[9][233];
int a[9],b[9];
set<int>S;
int hash(){
	int ans=0;
	for(int i=1;i<=8;i++)
		ans=ans*10+b[i];
	return ans;
}
void rot1(){
	static int tmp[9];
	for(int i=1;i<=8;i++)
		tmp[i]=b[i];
	b[1]=tmp[2];
	b[2]=tmp[3];
	b[3]=tmp[4];
	b[4]=tmp[1];
	b[5]=tmp[6];
	b[6]=tmp[7];
	b[7]=tmp[8];
	b[8]=tmp[5];
}
void rot2(){
	static int tmp[9];
	for(int i=1;i<=8;i++)
		tmp[i]=b[i];
	b[1]=tmp[4];
	b[2]=tmp[3];
	b[3]=tmp[7];
	b[4]=tmp[8];
	b[5]=tmp[1];
	b[6]=tmp[2];
	b[7]=tmp[6];
	b[8]=tmp[5];
}
void rot3(){
	static int tmp[9];
	for(int i=1;i<=8;i++)
		tmp[i]=b[i];
	b[1]=tmp[5];
	b[2]=tmp[1];
	b[3]=tmp[4];
	b[4]=tmp[8];
	b[5]=tmp[6];
	b[6]=tmp[2];
	b[7]=tmp[3];
	b[8]=tmp[7];
}
int main(){
	while(scanf("%s%s%s%s%s%s%s%s",s[1],s[2],s[3],s[4],s[5],s[6],s[7],s[8])!=-1){
		M.clear();
		int tot=0;
		for(int i=1;i<=8;i++){
			if(!M[string(s[i])])M[string(s[i])]=++tot;
			a[i]=M[string(s[i])];
			
			//printf("%d%c",a[i]," \n"[i==8]);
			
		}
		
		
		
		sort(a+1,a+1+8);
		S.clear();
		int ans=0;
		do{
			int ok=1;
			for(int i=1;i<=8;i++)
				b[i]=a[i];
			
			if(!S.count(hash())){
				ans++;
				for(int i=1;i<=4;i++){
					rot1();
					for(int j=1;j<=4;j++){
						rot2();
						for(int k=1;k<=4;k++){
							rot3();
							S.insert(hash());
						}
					}
				}
			}
		}while(next_permutation(a+1,a+1+8));
		printf("%d\n",ans);
	}
	return 0;
}
