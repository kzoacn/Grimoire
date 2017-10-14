#include<bits/stdc++.h>
#include<random>
using namespace std;

mt19937 g;

double randp(){
	return g()%RAND_MAX/(1.0*RAND_MAX);
}
int n;
double test(){
	double mn=1;
	vector<double>vec;
	for(int i=0;i<n;i++){
		vec.push_back(randp());
	}
	vec.push_back(0);
	vec.push_back(1);
	sort(vec.begin(),vec.end());
	for(int i=1;i<vec.size();i++)
		mn=min(mn,vec[i]-vec[i-1]);
	return mn;
}

double get(int n){
	g=mt19937(time(0));
	::n=n;
	int T=1000000;
	double ans=0;
	for(int i=0;i<T;i++){
		ans+=test();
	}
	ans/=T;
	return ans;
}
int main(){
	for(int i=1;i<=10;i++){
		cerr<<i<<" "<<get(i)<<endl;
	}
	return 0;
}
