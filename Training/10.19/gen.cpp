#include<bits/stdc++.h>
using namespace std;
int main(){
	srand(time(0));
	int m=1e6;
	int n=1<<29;
	
	long long s,k;
	
	s=rand()%n;
	k=rand()%(n-1)+1;
	
	cerr<<s<<" "<<k<<endl;
	cout<<n<<" "<<m<<endl;
	for(int i=0;i<m;i++){
		cout<<(((s+i*k))%n)*(1<<15)%n<<" ";
	}cout<<endl;
	return 0;
}
