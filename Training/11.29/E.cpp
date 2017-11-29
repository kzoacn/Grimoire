#include<bits/stdc++.h>
using namespace std;

const int maxn=1e5+6;
char s[maxn];
int n;
template<class T,T mo,T base>
struct Hash{
	T h[maxn],h_l[maxn];
	void init(){
		h_l[0]=1;
		for(int i=1;i<maxn;i++){
			h_l[i]=h_l[i-1]*base;
			if(mo!=0)h_l[i]%=mo;
		}
	}
	void build(int n,char *s){
		h[0]=0;
		for(int i=1;i<=n;i++){
			h[i]=h[i-1]*base+s[i];
			if(mo!=0)h[i]%=mo;
		}
	}
	T get(int l,int r){
		if(mo==0)
			return h[r]-h[l-1]*h_l[r-l+1];
		return (h[r]+mo-h[l-1]*h_l[r-l+1]%mo)%mo;
	}
};
Hash<unsigned long long,0,233>H,rH;
vector<int>ques;

bool equals(int l1,int r1,int l2,int r2){
	auto h1=H.get(l1,r1);
	auto h2=rH.get(n-r2+1,n-l2+1);
	//cerr<<h1<<" "<<h2<<endl;	
	return h1==h2;
}

int lcp(int x,int y){
	if(s[x]!=s[y])return 0;
	
	//cerr<<"lcp "<<x<<" "<<y<<endl;
	int l=1,r=min(x,n-y+1)+1;
	
	
	while(l<r){
		int mid=(l+r)>>1;
		if(equals(x-mid+1,x,y,y+mid-1))
			l=mid+1;
		else
			r=mid;
	}
	
	int q1=*lower_bound(ques.begin(),ques.end(),y)-y;
	int q2=x-*(upper_bound(ques.begin(),ques.end(),x)-1);
	
	int ans=min(q1,q2);
	ans=min(ans,l-1);
	
	return ans;
}

/*
double calc(int c){
	double p=1;
	double ans=1;
	
	int l=1;
	
	int lastlen=0;
	
	while(1){
		if(c+l>n||c-l<1){
			cerr<<lastlen<<endl;
			ans+=p*2;
			break;
		}
		int LCP=lcp(c-l,c+l);
		cerr<<c<<" "<<l<<" "<<LCP<<endl;
		double res=0;
		cerr<<p<<" "<<(l+LCP)<<endl;
		if(c+l+LCP<=n&&c-l-LCP>=1&&(s[c+l+LCP]=='?'||s[c-l-LCP]=='?')){
			res=p*(2*(LCP));
			lastlen=LCP-1;
			ans+=res;
			p*=(1.0/26);
			if(res<1e-12){break;}
			l+=LCP+1;
		}else{
			ans+=p*(2*(LCP));
			break;
		}
	}
	
	return ans;
}
*/
double calc(int c){
	long double p=1;
	double ans=1;
	
	int l=1;
	
	int lastlen=0;
	
	
	while(1){
		//cerr<<c<<" "<<l<<endl;
		if(c+l>n||c-l<1){
			break;
		}
		int LCP=lcp(c-l,c+l);
		//cerr<<LCP<<endl;
		double res=0;
		if(c+l+LCP<=n&&c-l-LCP>=1&&(s[c+l+LCP]=='?'||s[c-l-LCP]=='?')){
			res=p*(2*(LCP))+p/26*2;
			ans+=res;
			p*=(1.0/26);
			if(p<1e-18){break;}
			l+=LCP+1;
		}else{
			ans+=p*(2*(LCP));
			break;
		}
	}
	
	return ans;
}

int main(){
//freopen("palindromes.in","r",stdin);
//freopen("palindromes.out","w",stdout);
	H.init();
	rH.init();
	scanf("%s",s+1);
	n=strlen(s+1);
	H.build(n,s);
	reverse(s+1,s+1+n);
	rH.build(n,s);
	reverse(s+1,s+1+n);
	
	ques.push_back(0);	
	for(int i=1;i<=n;i++){
		if(s[i]=='?')
			ques.push_back(i);	
	}
	ques.push_back(n+1);	
//	cerr<<calc(2)<<endl;
//		return 0;

	double ans=0;
	for(int i=1;i<=n;i++){
		double res=calc(i);
		ans+=res;
		//cerr<<i<<" "<<res<<endl;
	}
	
	printf("%.10f\n",ans/n);
	return 0;
}
