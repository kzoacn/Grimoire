#include<bits/stdc++.h>
using namespace std;

const double eps=1e-9;
int sgn(double x){return (x>eps)-(x<-eps);}

struct P{
	double x,y;
	P(){}
	P(double _x,double _y):x(_x),y(_y){}
	double len(){return sqrt(x*x+y*y);}
	
};
P operator+(P a,P b){
	return P(a.x+b.x,a.y+b.y);
}
P operator-(P a,P b){
	return P(a.x-b.x,a.y-b.y);
}
double operator^(P a,P b){
	return a.x*b.x+a.y*b.y;
}
double operator*(P a,P b){
	return a.x*b.y-a.y*b.x;
}
double det(P a,P b,P c){
	return (b-a)*(c-a);
}
struct L{
	P a,b;
};
vector<L> extan()
int main(){

	return 0;
}
