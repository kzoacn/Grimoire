#include<bits/stdc++.h>
using namespace std;
int n;

char a[55][55],b[55][55];

string decode(){
	string s;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)if(b[i][j]=='*'){
		if(a[i][j]=='.')
			s+=' ';
		else
			s+=a[i][j];
	}
	return s;
}
void turn90(){
	static char tmp[55][55];
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
		tmp[i][j]=b[n-j+1][i];
	memcpy(b,tmp,sizeof tmp);
}

string trim(string s){
	while(s[0]==' ')s=s.substr(1,s.length()-1);
	while(s[s.length()-1]==' ')s=s.substr(0,s.length()-1);
	return s;
}

vector<string>split(string s){
	vector<string>ans;
	string tmp;
	s+=" ";
	for(int i=0;i<s.length();i++){
		if(s[i]==' '){
			if(tmp!="")
				ans.push_back(tmp);
			tmp="";
		}else{
			tmp+=s[i];
		}
	}
	return ans;
}

bool cmp(vector<string>a,vector<string>b){
	for(int i=0;i<min(a.size(),b.size());i++){
		if(a[i]!=b[i])
			return a[i]<b[i];
	}	
	return a.size()<b.size();
}

string solve(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%s",a[i]+1);
	for(int i=1;i<=n;i++)
		scanf("%s",b[i]+1);
	string str[4],s[4];
	for(int i=0;i<4;i++){
		str[i]=decode();
		turn90();
	}
	
	for(int i=0;i<4;i++){
		s[i]=str[i];
		for(int j=(i+1)%4;j!=i;j=(j+1)%4){
			s[i]+=str[j];
		}
		s[i]=trim(s[i]);
//		cerr<<s[i]<<endl;
	}
	int m;scanf("%d",&m);
	set<string>know;
	for(int i=0;i<m;i++){
		static char ss[50*50+100];scanf("%s",ss);
		know.insert(ss);
	}
	vector<vector<string> >S;
	for(int i=0;i<4;i++){
		vector<string>tmp=split(s[i]);
		int ok=1;
		for(auto x:tmp){
			if(!know.count(x)){
				ok=0;
			}
		}
		if(ok)S.push_back(tmp);
	}
	if(S.empty()){
		return string("FAIL TO DECRYPT");
	}
	sort(S.begin(),S.end(),cmp);
	string ans;
	for(auto x:S[0])
		ans=ans+x+" ";
	ans=trim(ans);
	return ans;
}

int main(){
	int T;cin>>T;
	for(int t=1;t<=T;t++){
		printf("Case #%d: %s\n",t,solve().c_str());
	}
	return 0;
}
