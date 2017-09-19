#include<bits/stdc++.h>
using namespace std;
map<string,int>M;
int main(){
//	rat, ox, tiger, rabbit, dragon, snake, horse, sheep, monkey, rooster, dog and pig.;
	M["rat"]=0;
	M["ox"]=1;
	M["tiger"]=2;
	M["rabbit"]=3;
	M["dragon"]=4;
	M["snake"]=5;
	M["horse"]=6;
	M["sheep"]=7;
	M["monkey"]=8;
	M["rooster"]=9;
	M["dog"]=10;
	M["pig"]=11;


	string s1,s2;
	cin>>s1;
	while(cin>>s1>>s2){
		int d=M[s2]-M[s1];
		if(d<=0)d+=12;
		cout<<d<<endl;
	}

	return 0;
}
