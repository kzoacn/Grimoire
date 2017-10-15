#include<bits/stdc++.h>
using namespace std;
string s;

int d[6]={3,2,-1,-3,-2,1};
//1 is white 0 is black
string op1(string s){
	string t=s;
	for(int i=0;i<s.length();i++){
		int cnt=0;
		for(int k=0;k<6;k++){
			int x=i+d[k];
			if(x<0||x>=s.length())continue;
			cnt+=s[i]-'0';
		}
		if(cnt==6){
			t[i]='1';
		}else t[i]=s[i];
	}
	return t;
}
string op2(string s){
	string t=s;
	for(int i=0;i<s.length();i++){
		int cnt=0;
		for(int k=0;k<6;k++){
			int x=i+d[k];
			if(x<0||x>=s.length())continue;
			cnt+=s[i]-'0';
		}
		if(cnt==0){
			t[i]='1';
		}else t[i]=s[i];
	}
	return t;
}
string op3(string s){
	string t=s;
	for(int i=0;i<s.length();i++){
		int cnt=0;
		for(int k=0;k<6;k++){
			int x=i+d[k];
			if(x<0||x>=s.length())continue;
			cnt+=s[i]-'0';
		}
		if(cnt==0){
			t[i]='1';
		}else t[i]=s[i];
	}
	return t;
}

int main(){
	while(cin>>s){
		if(s=="#")break;
		bool ok=false;
		
		if(op1(s)==op1(op1(s)) && op2(s)==op2(op2(s)))
			ok=true;
		
		puts(ok?"yes":"no");
	}
	return 0;
}
