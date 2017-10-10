#include<bits/stdc++.h>
using namespace std;
const int maxn=10101;
double L,W;
int n,m;
double a[maxn],w[maxn];

pair<double,double>seg[maxn];
const double eps=1e-9;
int sgn(double x){return (x>eps)-(x<-eps);}
double solve(){
	scanf("%lf%lf",&L,&W);
	double sx,sy,dx,dy,k,b;
	scanf("%lf%lf%lf%lf",&sx,&sy,&dx,&dy);	
	k=dy/dx;
	b=sy;
	
	scanf("%d",&m);
	double ans=1;
	if(sgn(k*L+b)<0||sgn(k*L+b-W)>0)
		ans=0;
//	cerr<<ans<<endl;
	while(m--){
		double x,sum=0;
		scanf("%lf%d",&x,&n);
		for(int i=1;i<=n;i++){
			scanf("%lf",&a[i]);
			sum+=a[i];
		}
		for(int i=1;i<n;i++){
			scanf("%lf",&w[i]);
			sum+=w[i];
		}
		double last=0;
		for(int i=1;i<=n;i++){
			seg[i]=make_pair(last,last+a[i]);
			last+=a[i]+w[i];
		}
		pair<double,double>s(k*x+b-(W-sum),k*x+b);
		double prob=0;
		//cerr<<s.first<<" "<<s.second<<endl;
		for(int i=1;i<=n;i++){
			double l,r;
			l=max(seg[i].first,s.first);
			r=min(seg[i].second,s.second);
			//cerr<<seg[i].first<<" "<<seg[i].second<<endl;
			if(sgn(l-r)<=0){
				prob+=r-l;
			}
		}
		prob/=W-sum;
		ans=ans*(1-prob);
	}
	return ans;
}

int main(){
	int T;
	cin>>T;
	for(int t=1;t<=T;t++){
		printf("Case #%d: %.5f\n",t,solve());
	}
	return 0;
}
