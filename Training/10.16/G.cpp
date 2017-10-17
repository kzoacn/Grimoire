#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
struct P{
	LL x,y;
	int id;
	P(){}
	P(LL _x,LL _y):x(_x),y(_y){}
	void print(){
		printf("(%lld,%lld)\n",x,y);
	}
	void read(){
		scanf("%lld%lld",&x,&y);
	}
	
	int quad(){
		return y==0?x>0:y>0;
	}
	
}p[1010];
P operator+(P a,P b){
	return P(a.x+b.x,a.y+b.y);
}
P operator-(P a,P b){
	return P(a.x-b.x,a.y-b.y);
}
LL operator*(P a,P b){
	return a.x*b.y-a.y*b.x;
}
LL operator^(P a,P b){
	return a.x*b.x+a.y*b.y;
}
bool operator==(P a,P b){
	return a.x==b.x && a.y==b.y;
}
bool operator<(P a,P b){
	return a.x!=b.x ? a.x<b.x: a.y<b.y;
}
bool operator>(P a,P b){
	return a.x!=b.x ? a.x>b.x: a.y>b.y;
}
LL det(P a,P b,P c){
	return (b-a)*(c-a);
}

bool onLine(P p,P a,P b){
	return det(p,a,b)==0;
}
bool onSeg(P p,P a,P b){
	return onLine(p,a,b) && ((p-a)^(b-a))>=0 && ((p-b)^(a-b))>=0;
}

bool cmp(P a,P b){
	return a.quad()!=b.quad() ? a.quad()<b.quad() : a*b>0;
}

int n;
bool check(vector<P>A,vector<P>B,P O){
	vector<P>vec;
	
	if(A.size()==0)
		swap(A,B);
	
	/*cerr<<"A"<<endl;
	for(auto p:A)
		p.print();
	cerr<<"B"<<endl;
	for(auto p:B)
		p.print();
	cerr<<"O"<<endl;
	O.print();*/
	for(int i=0;i<A.size();i++){
		P p=A[i]-O;
		p.id=1;
		vec.push_back(p);
	}
	for(int i=0;i<B.size();i++){
		P p=B[i]-O;
		p.id=-1;
		vec.push_back(p);
	}
	sort(vec.begin(),vec.end(),cmp);
	
	/*cerr<<"vec"<<endl;
	for(auto p:vec)
		p.print();
	*/
	int sum=0;
	for(int i=0,j=0;i<vec.size();i++){
		if(i==j){
			sum=vec[i].id;
			j=(j+1)%vec.size();
		}
		while(vec[i]*vec[j]>0){
			sum+=vec[j].id;
			j=(j+1)%vec.size();
		}
		if(sum==A.size() || (B.size()&&-sum==B.size())){
			return true;
		}
		sum-=vec[i].id;
	}
	return false;
}

bool check(int pos){
	vector<P>les,gre;
	for(int i=0;i<n;i++){
		if(i<pos)
			les.push_back(p[i]);
		if(i>pos)
			gre.push_back(p[i]);
	}
	return check(les,gre,p[pos]);
}

int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		p[i].read();
	//check(2);
	//return 0;
	for(int i=0;i<n;i++){
		//cerr<<"check "<<i<<endl;
		if(!check(i)){
			puts("Impossible");
			return 0;
		}
	}
	puts("Possible");
	return 0;
}

/*
4
0 0
0 1
1 1
1 0

check 0
A
(0,1)
(1,1)
(1,0)
B
O
(0,0)
vec
(1,0)
(1,1)
(0,1)
check 1
A
(0,0)
B
(1,1)
(1,0)
O
(0,1)
vec
(0,-1)
(1,-1)
(1,0)
check 2
A
(0,0)
(0,1)
B
(1,0)
O
(1,1)
vec
(-1,0)
(-1,-1)
(0,-1)
check 3
A
(0,0)
(0,1)
(1,1)
B
O
(1,0)
vec
(-1,0)
(0,1)
(-1,1)
Impossible

*/
