#include<bits/stdc++.h>
using namespace std;

int mp[255];
string eraseNum(string s){
	string ans;
	bool flag = false;
	for(int i=0;i<s.length();i++)
		if('0'<=s[i]&&s[i]<='9'){
			flag = true;
		}else{
			ans+=s[i];
		}
	if (!flag) {
		return string("");
	}
	return ans;
}

bool oppo(string a,string b){
	if(a.length()!=b.length())
		return false;
	for(int i=0;i<a.length();i++){
		if(isalpha(a[i])^isalpha(b[i]))
			return false;
		if(!isalpha(a[i])) {
			if (a[i] != b[i]) {
				return false;
			}
			continue;
		}
		if(mp[a[i]]!=b[i])
			return false;
	}
	return true;
}

int main(){

	for(int i=0;i<26;i++){
		mp['a'+i]='A'+i;
		mp['A'+i]='a'+i;
	}

	int T;cin>>T;
	for(int t=1;t<=T;t++){
		string s1,s2;
		cin>>s1>>s2;
		if(s1==s2){
			printf("Case %d: Login successful.\n",t);
			continue;
		}
		if(eraseNum(s1)==s2){
			printf("Case %d: Wrong password. Please, check your num lock key.\n",t);
			continue;
		}
		if(oppo(s1,s2)){
			printf("Case %d: Wrong password. Please, check your caps lock key.\n",t);
			continue;
		}
		if(oppo(eraseNum(s1),s2)){
			printf("Case %d: Wrong password. Please, check your caps lock and num lock keys.\n",t);
			continue;
		}
		printf("Case %d: Wrong password.\n",t);
	}
	return 0;
}

