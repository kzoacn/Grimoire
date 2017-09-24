#include<bits/stdc++.h>
using namespace std;
const int maxn=61200+233;

struct Num{
	char c[6][20];
	char* operator[](int x){return c[x];}
	void read(){
		memset(c,0,sizeof c);
		for(int i=0;i<5;i++){
			gets(c[i]);
			for(int j=0;j<9;j++)if(!c[i][j])
				c[i][j]=' ';
		}
	}
	void set(int r,int shift,string x){
		for(int i=0;i<3;i++)
			c[r][i+shift]=x[i];
	}
	void out(){
		for(int i=0;i<5;i++){
			for(int j=0;j<9;j++)
				putchar(c[i][j]);
			puts("");
		}
	}
}number[1000];

void print(Num &x,int pos,int dig){
	pos*=3;
	if(dig==-1){
		x.set(0,pos," . ");
		x.set(1,pos,". .");
		x.set(2,pos," . ");
		x.set(3,pos,". .");
		x.set(4,pos," . ");
	}else
	if(dig==0){
		x.set(0,pos," - ");
		x.set(1,pos,"| |");
		x.set(2,pos," . ");
		x.set(3,pos,"| |");
		x.set(4,pos," - ");
	}else
	if(dig==1){
		x.set(0,pos," . ");
		x.set(1,pos,". |");
		x.set(2,pos," . ");
		x.set(3,pos,". |");
		x.set(4,pos," . ");
	
	}else
	if(dig==2){
		x.set(0,pos," - ");
		x.set(1,pos,". |");
		x.set(2,pos," - ");
		x.set(3,pos,"| .");
		x.set(4,pos," - ");
	
	}else
	if(dig==3){
		x.set(0,pos," - ");
		x.set(1,pos,". |");
		x.set(2,pos," - ");
		x.set(3,pos,". |");
		x.set(4,pos," - ");
	
	}else
	if(dig==4){
		x.set(0,pos," . ");
		x.set(1,pos,"| |");
		x.set(2,pos," - ");
		x.set(3,pos,". |");
		x.set(4,pos," . ");
	
	}else
	if(dig==5){
		x.set(0,pos," - ");
		x.set(1,pos,"| .");
		x.set(2,pos," - ");
		x.set(3,pos,". |");
		x.set(4,pos," - ");
	
	}else
	if(dig==6){
		x.set(0,pos," - ");
		x.set(1,pos,"| .");
		x.set(2,pos," - ");
		x.set(3,pos,"| |");
		x.set(4,pos," - ");
	
	}else
	if(dig==7){
		x.set(0,pos," - ");
		x.set(1,pos,". |");
		x.set(2,pos," . ");
		x.set(3,pos,". |");
		x.set(4,pos," . ");
	
	}else
	if(dig==8){
		x.set(0,pos," - ");
		x.set(1,pos,"| |");
		x.set(2,pos," - ");
		x.set(3,pos,"| |");
		x.set(4,pos," - ");
	
	}else
	if(dig==9){
		x.set(0,pos," - ");
		x.set(1,pos,"| |");
		x.set(2,pos," - ");
		x.set(3,pos,". |");
		x.set(4,pos," - ");
	
	}
}

bool match(Num a,Num b){
	for(int i=0;i<5;i++){
		for(int j=0;j<9;j++){
			if(b[i][j]=='*')continue;
			if(b[i][j]!=a[i][j]){
			//cerr<<i<<" "<<j<<endl;
				return false;
			}
		}
	}
	return true;
}

char s[666];
int n;
int a[maxn];
Num b[maxn];

bool check(int x){
	for(int i=1;i<=n;i++){
		int p=(x+a[i])%1000;
		if(!match(number[p],b[i]))
			return false;
	}
	return true;
}

void run(){
	int cnt=0,ans=0;
	for(int i=0;i<=999;i++){
		if(check(i)){
			ans=i;
			cnt++;
		}
	}
	
	if(cnt==0)puts("? 0");
	else if(cnt>1) printf("? %d\n",cnt);
	else if(cnt==1)printf("%d\n",ans);
}

int main(){
	for(int i=0;i<=999;i++){
		if(i<10){
			print(number[i],0,-1);
			print(number[i],1,-1);
			print(number[i],2,i%10);
		}else
		if(i<100){
			print(number[i],0,-1);
			print(number[i],1,(i/10)%10);
			print(number[i],2,i%10);
		}else{
			print(number[i],0,(i/100)%10);
			print(number[i],1,(i/10)%10);
			print(number[i],2,i%10);
		}
	}
	while(gets(s)){
		//cerr<<s<<endl;
		int bomb=0;
		if(s[0]=='$')bomb=1;
		if(s[0]=='#'||s[0]=='$'){
			run();
			n=0;
		}else{
			++n;
			sscanf(s,"%d",&a[n]);
			b[n].read();
//			number[888].out();
//			b[n].out();
//			cerr<<match(number[888],b[n])<<endl;
//			exit(0);
		}
		if(bomb)break;
	}
	return 0;
}
