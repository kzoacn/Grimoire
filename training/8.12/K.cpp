#include<bits/stdc++.h>
using namespace std;
int min3(int a,int b,int c){return min(min(a,b),c);}
void solve(){
	int A,B,C,AB,BC,AC,ABC;
	int n;
	cin>>n;
	int ans=0;
	while(n--){
		cin>>A>>B>>C>>AB>>BC>>AC>>ABC;
		int flag=1;
		
		if(AC+AB-ABC>A)flag=0;
		if(AB+BC-ABC>B)flag=0;
		if(AC+BC-ABC>C)flag=0;
		if(AB>A||AB>B||AC>A||AC>C||BC>B||BC>C)flag=0;
		if(ABC>min3(AB,BC,AC))flag=0;
		
		if(flag){
			ans=max(A+B+C-AB-BC-AC+ABC,ans);
		}else{
			
		}
	}
	cout<<ans<<endl;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;cin>>T;
	while(T--)
		solve();
	return 0;
}
