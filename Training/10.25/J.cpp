#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
typedef long long LL;
const int BIT=62;
vector<LL> calc_lb(LL *_a,int n){
	static LL a[2222];
	for(int i=1;i<=n;i++)a[i]=_a[i];
	vector<LL>base;
	base.resize(BIT);
	for(int i=1;i<=n;i++){
		for(int j=BIT-1;j>=0;j--)if(a[i]>>j&1){
			if(base[j]){
				a[i]^=base[j];
			}else{
				base[j]=a[i];
				break;
			}
		}
	}
	return base;
}

bool insert(vector<LL>&base,LL x){
	for(int i=BIT-1;i>=0;i--)if(x>>i&1){
		if(base[i]){
			x^=base[i];
		}else{
			base[i]=x;
			return false;
		}
	}
	return true;
}
bool test(vector<LL>base,LL x){
	for(int i=BIT-1;i>=0;i--)if(x>>i&1){
		if(base[i]){
			x^=base[i];
		}else{
			return false;
		}
	}
	return true;
}

LL size(LL *a,int n){
	vector<LL>lb=calc_lb(a,n);
	LL ans=1;
	for(auto x:lb)if(x)ans*=2;
	int zero=0;
	for(int i=1;i<=n;i++){
		static LL tmp[2222];
		int sz=0;
		for(int j=1;j<=n;j++)if(i!=j){
			tmp[++sz]=a[j];
		}
		vector<LL>base=calc_lb(tmp,sz);
		if(test(base,a[i])){
			zero=1;
			break;
		}
	}
	return ans;
}



void test(){
	int n;
	static LL a[2222];
//	int w=64;
//	for(int i=1;i<=n*2;i++)
//		a[i]=rand()%w;

	if(cin>>n){}else exit(0);
	for(int i=1;i<=2*n;i++)
		cin>>a[i];
	int dimA=0,dimB=0,dimU=0,dimI=0;

	vector<LL>A=calc_lb(a,n),U;
	vector<LL>B=calc_lb(a+n,n),I;

	U=calc_lb(a,n*2);
	I.resize(BIT);
/*
	for(int i=0;i<w;i++){
		if(test(A,i)&&test(B,i)){
			insert(I,i);
		}
	}*/
	for(auto x:A)if(x)dimA++;
	for(auto x:B)if(x)dimB++;
	for(auto x:U)if(x)dimU++;
//	for(auto x:I)if(x)dimI++;

	cout<< (1LL<<(dimA+dimB-dimU)) <<endl;
//	assert(dimA+dimB-dimU==dimI);

//	printf("dimA=%d dimB=%d dimU=%d dimI=%d\n",dimA,dimB,dimU,dimI);
}

int main(){
	srand(time(0)^getpid());
	int T=10;
	while(1)
	test();
	return 0;
	int n;
	static LL a[2222];

	while(cin>>n){
		for(int i=1;i<=n;i++)
			cin>>a[i];
		for(int i=n+1;i<=2*n;i++)
			cin>>a[i];
		LL sizU=size(a,n*2);
		LL sizA=size(a,n);
		LL sizB=size(a+n,n);

		vector<LL>lba=calc_lb(a,n);
		vector<LL>lbb=calc_lb(a+n,n);


		int cnt=0;
		for(int i=0;i<BIT;i++){
			if(lba[i]&&lbb[i]&&(lba[i]==lbb[i]))
				cnt++;
		}
		sizU=1LL<<cnt;

		cout<<sizU<<endl;
	}
	return 0;
}
