#include<bits/stdc++.h>
using namespace std;
const int maxn=1111;
int a[maxn];

bool cmp(int x,int y){
	cout<<1<<" "<<x<<" "<<y<<endl;
	string ans;
	cin>>ans;
	if(ans[0]=='Y')
		return true;
	return false; 
}
void sort(int l,int r){
	if(l>=r)return ;
	
	int mid=(l+r)>>1;
	sort(l,mid);
	sort(mid+1,r);
	static int tmp[maxn];
	int cur=0;
	int cur1=l,cur2=mid+1;
	while(cur1<=mid&&cur2<=r){
		if(cmp(a[cur1],a[cur2])){
			tmp[++cur]=a[cur1];	
			cur1++;
		}else{
			tmp[++cur]=a[cur2];
			cur2++;
		}
	}
	while(cur1<=mid)tmp[++cur]=a[cur1++];
	while(cur2<=r)tmp[++cur]=a[cur2++];
	for(int i=l;i<=r;i++)
		a[i]=tmp[i-l+1];
}
int n;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		a[i]=i;
	sort(1,n);
	
	int flag=1;
	for(int i=1;i<n;i++)
		if(!cmp(a[i],a[i+1]))
			flag=0;
	cout<<0;
	static int b[maxn];
	if(flag){
		for(int i=1;i<=n;i++)
			cout<<" "<<a[i];
		cout<<endl;
	}else{
		for(int i=1;i<=n;i++)
			cout<<" "<<0;
		cout<<endl;
	}
	return 0;
}
