#include<bits/stdc++.h>
using namespace std;
int n,m;

string nine(int n){
	string s;
	while(n--)s+="9";
	return s;
}
string ten(int n){
	string s;
	while(n--)s+="0";
	s+="1";
	return s;
}




double to_double(string s){
	double x=0;
	for(int i=0;i<s.length();i++)
		x=x*10+s[i]-'0';
	return x;
}
int main(){
	cin>>n>>m;
	double tmp=pow(10,n)/(pow(10,m)-1);
	vector<string>ans;
	while(n){
		string num;
		cerr<<n<<" "<<m<<endl;
		if(n<m){
			ans.push_back("0");
			ans.push_back(nine(m-n));
			ans.push_back("0");
			m=n;
		}else{
			n-=m;
			num=ten(n);
			while(n>=m){
				num[n-m]='1';
				n-=m;
			}
			ans.push_back(num);
		}
	}
	
	ans.push_back(nine(m));
	
	cout<<(int)ans.size()-1<<endl;
	for(int i=0;i<ans.size();i++){
		reverse(ans[i].begin(),ans[i].end());
		printf("%s%c",ans[i].c_str()," \n"[i+1==ans.size()]);
	}
	
	double res=0;	
	for(int i=(int)ans.size()-1;i>=1;i--){
		res=1.0/(res+to_double(ans[i]));
	}
	res+=to_double(ans[0]);
	cerr<<res<<endl;
	cerr<<tmp<<endl;
	return 0;
}
/*
3 2
1 2
1 1
5
10 0 9 0 1 9
20.1111
10.101

*/
