#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=1e6+6;
LL n,m;
LL a[maxn];

LL suma,suma2;


LL S3(LL m){
	return (m*(m+1)*(2*m+1)/6)%n;
}
int cnt=0;
bool check(LL s,LL k){
	if(k==0)return false;
	LL sum=0;
	sum=m*s%n*s%n;
	sum=(sum+s*k%n*m%n*(m-1)%n)%n;
	sum=(sum+k*k%n*S3(m-1)%n)%n;
	//cerr<<sum<<" "<<suma2<<endl;
	if(sum!=suma2)return false;
	
	sum=0;
	sum=m*s%n;
	sum=(sum+(m*(m-1)/2)%n*k%n)%n;
	
	if(sum!=suma)return false;
	
	static LL b[maxn];
	for(int i=0;i<m;i++){
		b[i]=(s+1ll*i*k)%n;
		
		if(!binary_search(a,a+m,b[i]))
			return false;
	}
	sort(b,b+m);
	/*
	if(clock()>CLOCKS_PER_SEC*1.95){
		puts("-1 -1");
		exit(0);
	}
	*/
	
	for(int i=0;i<m;i++)if(b[i]!=a[i])
		return false;
	return true;
}

void find(int id){
	for(int i=0;i<m;i++){
		LL k=(a[i]-a[id]+n)%n;
		LL s=(a[id]-((m-1)/2)*k%n+n)%n;
		if(check(s,k)){
			cout<<s<<" "<<k<<endl;
			exit(0);
		}
	}
}
int st;
void find2(int id){
	for(int i=0;i<m;i++){
		
	
		LL k=((a[i]-a[id])%n+n)%n;
		LL cont=(a[id]+a[st]+n-(m-1)*k%n)%n;
		if(n%2==1){
			
			LL s=((n+1)/2)*cont%n;
			if(check(s,k)){
				cout<<s<<" "<<k<<endl;
				exit(0);
			}	
		}
		if(cont%2==1)continue;
		
		LL s1=cont/2;
		if(check(s1,k)){
			cout<<s1<<" "<<k<<endl;
			exit(0);
		}
		LL s2=(n-cont/2)%n;
		if(check(s2,k)){
			cout<<s2<<" "<<k<<endl;
			exit(0);
		}
		LL s3=(cont/2+n/2)%n;
		if(check(s3,k)){
			cout<<s2<<" "<<k<<endl;
			exit(0);
		}
		
	}
}


void BF(){

	if(m==1){
	
		cout<<a[0]<<" "<<1<<endl;
	
		return ;
	}

	for(int i=0;i<m;i++){
		for(int j=0;j<m;j++)if(i!=j){
			LL s=a[i];
			LL k=((a[j]-a[i])%n+n)%n;
			if(check(s,k)){
				cout<<s<<" "<<k<<endl;
				return;
			}
		}
	}
	puts("-1 -1");
}

int main(){
	srand(time(0));
	scanf("%lld%lld",&n,&m);
	for(int i=0;i<m;i++)
		scanf("%lld",&a[i]);
		
	
		
		
	sort(a,a+m);
	
	
	
	
	for(int i=0;i<m;i++){
		suma=(suma+a[i])%n;
		suma2=(suma2+a[i]*a[i])%n;
	}
	
	
	if(m<=400){
	
		BF();
	
		return 0;
	}
	
	if(m%2==1){
		for(int i=0;i<m;i++){
			if((m*a[i])%n==suma){
				find(i);
			}
		}
	}else{
		st=rand()%m;
		for(int i=0;i<m;i++)if(i!=st){
			if((m/2*(a[i]+a[st]))%n==suma){
				find2(i);
				cerr<<i<<endl;
			}
		}
	}
	puts("-1 -1");
	return 0;
}
