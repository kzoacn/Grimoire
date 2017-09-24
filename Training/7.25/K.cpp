#include<bits/stdc++.h>
using namespace std;
bool isword(const string &s){
	for(int i=0;i<s.length();i++)
		if(!isalpha(s[i]))
			return false;
	return true;


}
vector<string>split(char *s,int len){
	string tmp;
	vector<string>ans;
	
	for(int i=0;i<len;i++){
		if(isalpha(s[i])){
			tmp+=s[i];
		}else{
			if(tmp!="")
				ans.push_back(tmp);
			tmp="";
		}
	}
	if(tmp!="")
		ans.push_back(tmp);
	
	return ans;
}
unordered_set<string>fob;
pair<string,string>pack(string a,string b){
	if(a>b)swap(a,b);
	return make_pair(a,b);
}
char s[int(1e6)];
int n,m;
map<pair<string,string>,int>M;
map<string,int>C;
string tolower(string s){
	for(int i=0;i<s.length();i++){
		if('A'<=s[i]&&s[i]<='Z')
			s[i]=s[i]-'A'+'a';	
	}
	return s;
}
int main(){
	vector<string>words,vec;
	scanf("%d\n",&n);
	for(int i=1;i<=n;i++){
		gets(s);
		int len=strlen(s);
		vector<string>t=split(s,len);
		for(auto x:t)
			vec.push_back(tolower(x));
	}
	scanf("%d",&m);
	while(m--){
		scanf("%s",s);
		string st=tolower(string(s));
		fob.insert(s);
	}
	for(int i=0;i<vec.size();i++){
		if(!fob.count(vec[i]))
			words.push_back(tolower(vec[i]));
	}
	int len=words.size();
	for(int i=0;i<words.size();i++)
		C[words[i]]++;
	for(int i=0;i+1<words.size();i++){
		M[pack(words[i],words[i+1])]++;
	}
	//for(auto x:words)
	//	cerr<<x<<" ";
	scanf("%d",&m);
	while(m--){
		string a,b;
		scanf("%s",s);a=tolower(string(s));
		scanf("%s",s);b=tolower(string(s));
		double pab=1.0*M[pack(a,b)]/(len-1);
		double pa=1.0*C[a]/len;
		double pb=1.0*C[b]/len;
		double ans=pab/pa/pb;
		printf("%.10f\n",ans);
	}
	return 0;
}
