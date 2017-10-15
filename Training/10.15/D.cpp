#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
const double eps=1e-9;
int n;
double pw;
double vw[maxn],pf[maxn],vf[maxn],th[maxn];



struct sta{
	double k,b,x0;
	bool operator<(const sta oth)const{
		return x0<oth.x0;
	}
}a[maxn];

int main(){
	while(scanf("%d",&n)==1&&n){
		scanf("%lf",&pw);
		for(int i=1;i<=n;i++){
			scanf("%lf%lf%lf%lf",&vw[i],&pf[i],&vf[i],&th[i]);
		//	cerr<<vw[i]<<" "<<pf[i]<<" "<<vf[i]<<" "<<th[i]<<endl;
		}
		int sz=0;
		double A=pw,B=0;
		
		for(int i=1;i<=n;i++){
		
		
			if(fabs(vw[i])<eps){
				B+=max(0.0,pf[i]/vf[i]*th[i]);
				continue;
			}
			++sz;
			a[sz].k=-pf[i]/vf[i]*vw[i];
			a[sz].b=pf[i]/vf[i]*th[i];
			a[sz].x0=-a[sz].b/a[sz].k;
		}
		sort(a+1,a+1+sz);
		
		
		for(int i=1;i<=sz;i++){
	//		cerr<<a[i].k<<" "<<a[i].b<<" "<<a[i].x0<<endl;
		} 
		
		
		for(int i=1;i<=sz;i++){
			if(a[i].x0>-eps&&a[i].k<eps){
				A+=a[i].k;
				B+=a[i].b;
			}
			if(a[i].x0<eps&&a[i].k>-eps){
				A+=a[i].k;
				B+=a[i].b;
			}
		}
		
		double ans=B;
		double pre0=0;
		
		for(int i=1;i<=sz;i++){
			if(a[i].x0<-eps)continue;
//			cerr<<A<<" "<<B<<endl;

			
			ans=min(ans,A*a[i].x0+B);
//			ans=min(ans,A*pre0+B);
			if(a[i].k>0){
				A+=a[i].k;
				B+=a[i].b;
			}else{
				A-=a[i].k;
				B-=a[i].b;
			}
		}
		
		printf("%.20f\n",ans);
	}
	return 0;
}
