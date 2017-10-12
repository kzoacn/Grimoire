#include<bits/stdc++.h>
using namespace std;
typedef long double LD;
const LD eps=1e-10;
const LD d=300;
int sgn(LD x){return (x>eps)-(x<-eps);}

LD sqr(LD x){return x*x;}
LD mysqrt(LD x){
	if(x<0)return 0;
	return sqrtl(x);
}

	LD T,v1,v2;
pair<LD,LD>sol(LD a,LD b,LD c){
	LD delta=b*b-4*a*c;
	if(delta<-eps)return make_pair(-1,-1);
	LD x1=(-b-sqrt(delta))/2/a;
	LD x2=(-b+sqrt(delta))/2/a;
	return make_pair(x1,x2);
}

bool check2(LD x){
	if(x<-eps||x>300+eps)return false;
	LD t1,t2;
	t1=(mysqrt(sqr(d)+sqr(x))+d+x)/v1;
	t2=(d*2)/v2;
	
	int cnt=0;
	cerr<<"check2"<<endl;
	cerr<<(double)x<<endl;
	cerr<<(double)t1<<" "<<(double)t2<<endl;
	
	if(sgn(t1-(t2+T))<=0)//get 3
		cnt++;
	if(sgn((t1+d/v1)-(t2+T+d/v2))<=0)// get 4
		cnt++;
	if(sgn((t1+2*d/v1)-(t2+T+2*d/v2))<=0)// get 1
		cnt++;
	cerr<<cnt<<endl;
	return cnt>=3;
}
bool check3(LD x){
	if(x<-eps||x>300+eps)return false;
	
	LD t1,t2;
	
	t1=(sqrt(sqr(d)+sqr(d-x))+x+d+d+d)/v1;
	t2=(3*d)/v2;
	int cnt=0;
	//cerr<<"check3"<<endl;
	//cerr<<(double)t1<<" "<<(double)t2<<endl;
	
	
	if(sgn(t1-(t2+T))<=0)// get 4
		cnt++;
	if(sgn((t1+d/v1)-(t2+T+d/v2))<=0)// get 1
		cnt++;
	
	//cerr<<cnt<<endl;
	return cnt>=3;
}


void solve(){
	double tT,tv1,tv2;
	cin>>tT>>tv1>>tv2;
	T=tT;
	v1=tv1;
	v2=tv2;
	if(sgn(v1)==0){
		puts("No");
		return ;
	}
	
	if(sgn(v1-v2)==0){
		puts("Yes");
		return ;
	}
	
	vector<LD>test;
	
	double a,b,c;
	
	a=sqr(v1/v2)-1;
	b=sqr(v1/v2)*2*d;
	c=(sqr(v1/v2)-1)*d*d;
	
	//cerr<<a<<" "<<b<<" "<<c<<endl;
	auto par=sol(a,b,c);
	test.push_back(par.first);
	test.push_back(par.second);
	//test.push_back(0);
	//test.push_back(d);
	//test.push_back(d/2);
	
	sort(test.begin(),test.end());
	for(int i=0;i<test.size();i++){
		if(check2(test[i])){
			puts("Yes");
			return ;
		}
		if(i+1<test.size()&&check2((test[i]+test[i+1])/2)){
			puts("Yes");
			return ;
		}
	}


	a=sqr(v1/v2)-1;
	b=sqr(v1/v2)*4*d+2*d;
	c=4*d*d*sqr(v1/v2)+2*d*d;
	par=sol(a,b,c);
	test.push_back(par.first);
	test.push_back(par.second);
	//test.push_back(0);
	//test.push_back(d);
	//test.push_back(d/2);
	
	sort(test.begin(),test.end());
	for(int i=0;i<test.size();i++){
		if(check3(test[i])){
			puts("Yes");
			return ;
		}
		if(i+1<test.size()&&check3((test[i]+test[i+1])/2)){
			puts("Yes");
			return ;
		}
	}

		
	puts("No");
}

int main(){
	int T;cin>>T;
	for(int t=1;t<=T;t++){
		printf("Case #%d: ",t);
		solve();
	}
	return 0;
}
