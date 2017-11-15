#include<bits/stdc++.h>
using namespace std;
typedef __int128 LL;
LL a[1111];
LL r[1111];

LL calcR(int n){
	set<LL>S;
	for(int i=1;i<=n;i++)
	for(int j=1;j<i;j++)
		S.insert(a[i]-a[j]);
	for(int i=1;;i++){
		if(!S.count(i))
			return i;
	}
	return -1;
}
LL sum[1111];
int n=600;
int main(){
	a[1]=1;
	a[2]=2;
	r[1]=calcR(1);
	r[2]=calcR(2);
	sum[1]=a[1];
	sum[2]=a[1]+a[2];
	for(int i=3;i<=n;i++){
		if(i%2==0){
			a[i]=a[i-1]+r[i-1];
		}else{
			a[i]=a[i-1]*2;
		}
		r[i]=calcR(i);
		sum[i]=sum[i-1]+a[i];
//	for(int i=2;i<=n;i++)if(r[i]-r[i-1]==2)
	printf("i=%d a=%lld r=%lld sum=%lld\n",i,(long long)a[i],(long long)r[i],(long long)sum[i]);
	}
//		printf("i=%d r[i]=%lld r[i-1]=%lld\n",i,r[i],r[i-1]);
//	for(int i=1;i<=n;i++)
//		printf("i=%d a=%lld r=%lld sum=%lld\n",i,(long long)a[i],(long long)r[i],(long long)sum[i]);
	return 0;
}
