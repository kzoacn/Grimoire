#include<bits/stdc++.h>
using namespace std;


long long x=1;
int main(){
	for(int i=1;i<=20;i++)
		x=x*2;
	for(int i=(long long)1e15/x;;i++){
		long long t=x*i+1;
		if(system(("./is_prime "+to_string(t)).c_str() )){
			cout<<t<<endl;
			return 0;
		}
	}
	return 0;
}
