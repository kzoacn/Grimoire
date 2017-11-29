#include<bits/stdc++.h>
using namespace std;
int main(int argc,char **argv){
	
	long long x;
	sscanf(argv[1],"%lld",&x);
	system((string("factor ")+to_string(x)+" > out").c_str());
	freopen("out","r",stdin);
	string s;
	getline(cin,s);
	
	int cnt=0;
	for(auto c:s)if(c==' ')
		cnt++;
	cerr<<cnt<<endl;
	if(cnt==1)
		return 1;
	return 0;
}
