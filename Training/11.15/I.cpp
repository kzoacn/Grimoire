#include<bits/stdc++.h>
#define L first
#define R second
using namespace std;
const int maxn=1010;
typedef pair<int,int> seg;
int n;
int xx[maxn],yy[maxn];

vector<seg> Union(seg s,vector<seg>vec){

	
	vector<seg>tmp;
	for(auto se:vec){
		seg ss=seg(max(s.L,se.L),min(s.R,se.R));
		if(ss.L<ss.R)
			tmp.push_back(ss);
	}
	vec=tmp;tmp.clear();

	sort(vec.begin(),vec.end(),[](seg a,seg b){
				if(a.L!=b.L)
					return a.L<b.L;
				return a.R>b.R;
			});

	tmp.clear();
	if(vec.empty())return tmp;
	tmp.push_back(vec.front());
	for(int i=1;i<vec.size();i++){
		if(vec[i].L>tmp.back().R)
			tmp.push_back(vec[i]);
		else{
			tmp.back().R=max(tmp.back().R,vec[i].R);
		}
	}
	return tmp;
}

vector<seg> Comp(seg s,vector<seg>vec){
	vec.push_back({s.L,s.L});
	vec.push_back({s.R,s.R});
	sort(vec.begin(),vec.end());
	vector<seg>tmp;
	for(int i=0;i+1<vec.size();i++){
		int l=vec[i].R,r=vec[i+1].L;
		if(l<r)tmp.push_back({l,r});
	}
	return tmp;
}

vector<pair<int,seg> >X,Y;

void print(vector<seg>vec){
	for(auto s:vec)
		printf("[%d,%d] ",s.L,s.R);
	puts("");puts("");
}

long long calc(vector<pair<int,seg> >X){
	for(auto &p:X)
		if(p.second.L>p.second.R)
			swap(p.second.L,p.second.R);
	sort(X.begin(),X.end());
	vector<seg>Seg,Uni;
	for(auto p:X){
		Seg.push_back(p.second);
	}
	long long ans=0;
	for(int i=0;i<Seg.size();i++){
		long long res=0;

		vector<seg>pre,nxt,uni;
		for(int j=0;j<Seg.size();j++){
			if(j<i)pre.push_back(Seg[j]);
			if(j>i)nxt.push_back(Seg[j]);
		}
		pre=Union(Seg[i],pre);
		nxt=Union(Seg[i],nxt);



		pre=Comp(Seg[i],pre);
		nxt=Comp(Seg[i],nxt);

		for(auto s:pre)uni.push_back(s);
		for(auto s:nxt)uni.push_back(s);

		uni=Union(Seg[i],uni);
		for(auto x:uni)
			res+=x.R-x.L;

		ans+=res;
		
//		pre=vector<seg>(seg.begin(),seg.begin()+i);
//		nxt=vector<seg>(seg.begin()+i+1,seg.end());
	}
	return ans;
}

int main(){
freopen("intel.in","r",stdin);
freopen("intel.out","w",stdout);
	cin>>n;
	for(int i=0;i<n;i++){
		scanf("%d%d",&xx[i],&yy[i]);
	}

	long long sum=0;
	for(int i=0;i<n;i++){
		sum+=abs(xx[(i+1)%n]-xx[i])+abs(yy[(i+1)%n]-yy[i]);
		if(xx[(i+1)%n]==xx[i]){
			Y.emplace_back(xx[i],seg(yy[i],yy[(i+1)%n]));
		}else{
			X.emplace_back(yy[i],seg(xx[i],xx[(i+1)%n]));
		}
	}
	long long ans=0;
	ans+=calc(X);
	ans+=calc(Y);

	cout<<sum-ans<<endl;
	return 0;
}

/*
 *
 *
[1,6] [2,5] [1,2] [3,5] [3,6] 

it is 0


[1,6] 

res= 5
it is 1
[2,5] 

[2,5] 

res= 0
it is 2
[1,2] 

[1,2] 

res= 0
it is 3
[3,5] 

[3,5] 

res= 0
it is 4
[3,6] 



res= 3
[1,3] [2,3] [3,4] [2,3] [1,4] 

it is 0


[1,3] 

res= 2
it is 1
[2,3] 

[2,3] 

res= 0
it is 2
[3,4] 

[3,4] 

res= 0
it is 3
[2,3] 

[2,3] 

res= 0
it is 4
[1,4] 



res= 3
9


 * */
