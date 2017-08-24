#include<bits/stdc++.h>
using namespace std;
const int maxn=1000*100*20+233;


int n;
char output[maxn];
class sentence:public vector<string>{
public:
	sentence(){
	
	}
	sentence(const string &s){
		push_back(s);
	}
	sentence subsen(int l,int siz){
		sentence s;
		for(int i=l;i<l+siz;i++)
			s.push_back(at(i));
		return s;
	}
	const char* c_str(){
		char *cur=output;
		for(int i=0;i<size();i++){
			string s=at(i);
			for(int j=0;j<s.length();j++){
				*cur=s[j];
				cur++;
			}
			if(i+1!=size()){
				*cur=' ';
				cur++;
			}
		}
		*cur='\0';
		return output;
	}
};

sentence split2(string s){
	sentence ans;
	string tmp;
	s+=' ';
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

vector<sentence>split(string s){
	vector<sentence>ans;
	string tmp;
	s+='.';
	for(int i=0;i<s.length();i++){
		if(s[i]=='.'||s[i]==','||s[i]==':'||s[i]==';'||s[i]=='?'||s[i]=='!'){
			sentence t=split2(tmp);
			if(!t.empty())
				ans.push_back(t);
			tmp="";
		}else{
			tmp+=s[i];
		}
	}
	return ans;
}

set<sentence>know;
string format(const string &s){
	string str=s;
	for(int i=0;i<s.length();i++)
		if('A'<=s[i]&&s[i]<='Z')
			str[i]=s[i]-'A'+'a';
		else str[i]=s[i];
	return str;
}
sentence format(const sentence &sen){
	sentence ans;
	for(auto str:sen)
		ans.push_back(format(str));
	return ans;
}
int main(){
	while(scanf("%d\n",&n)==1){
		string text;
		know.clear();
		static char s[maxn];
		while(gets(s)){
			if(s[0]=='*')break;
			text+=' ';
			text+=s;
		}
		know.insert(format(sentence("Joe")));
		vector<sentence>speak=split(text);
		for(auto sen:speak){
			for(int j=1;j<=n;j++)
				for(int i=0;i+j-1<sen.size();i++){
					know.insert(format(sen.subsen(i,j)));
					//fprintf(stderr,"#I know \"%s\" \n",sen.subsen(i,j).c_str());
				}
		}
		static int Case=0;
		if(Case)puts("");
		printf("Learning case %d\n",++Case);
		text="";
		while(gets(s)){
			if(s[0]=='#'){
				break;
			}
			text+=' ';
			text+=s;
		}
		speak=split(text);
		for(auto sen:speak){
			int ok=1;
			for(auto s:sen){
				if(!know.count(format(sentence(s)))){
					printf("What does the word \"%s\" mean?\n",s.c_str());
					know.insert(format(sentence(s)));
				}
			}
			
			for(int j=2;j<=n;j++)
				for(int i=0;i+j-1<sen.size();i++){
					sentence st=sen.subsen(i,j);	
					if(!know.count(format(st))){
						//fprintf(stderr,"#I dont know sentence \"%s\" \n",sen.c_str());
						//fprintf(stderr,"#because of \"%s\" \n",st.c_str());
						
						ok=0;
						break;
					}
				}
			if(!ok)
				printf("What does the sentence \"%s\" mean?\n",sen.c_str());
			
			for(int j=1;j<=n;j++)
				for(int i=0;i+j-1<sen.size();i++){
					sentence st=sen.subsen(i,j);	
					know.insert(format(st));
				}
			
		}
	}
	return 0;
}
