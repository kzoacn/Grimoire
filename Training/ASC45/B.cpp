#include<bits/stdc++.h>
#define x1 _sdf1
#define x2 _sdf2
#define __advance __attribute__((optimize("O3")))
using namespace std;
const int maxn=1e5+5;
struct L{
	double k,b;
	double l,r;
}l[maxn];
struct P{
	double x,y;
}p[maxn];
int n;
double a,b,alpha;

pair<double,double>seg[maxn];
int sz;
double tmpl,tmpr;
__advance __inline double leng(pair<double,double>s){
	return s.second-s.first;
}
double tot=0;
__advance __inline double intersect(pair<double,double>a,pair<double,double>b){
	double l=max(a.first,b.first);
	double r=min(a.second,b.second);
	if(l>r)return 0;
	return r-l;	
}
int C = 0;
double ttl,ttr;
__advance __inline double calc(pair<double,double>*seg,double len){
	int n=::sz;
//	deque<pair<double,double> >dq;
	int head=0,tail=0;
	static pair<double,double> dq[maxn];
	
	double ans=0;
	double sum=0;
	for(int i=1;i<=n;i++){
//		dq.push_back(seg[i]);
		dq[tail++]=seg[i];
		sum+=leng(seg[i]);
		double fr=seg[i].second-len;
		while(head > 0 && dq[head].second<=fr){
			sum-=leng(dq[head]);
			head++;
		}
		double res=sum-(head <= tail ? leng(dq[head]) : 0);
		res+=intersect(dq[head],{seg[i].second-len,seg[i].second});
		if(res>ans){
			ans=res;
			ttl=seg[i].second-len;
			ttr=seg[i].second;
		}
	}
	return ans;
}

__advance __inline double calc(double len){
	int n=::sz;
	double ans=0;
	for(int i=1;i<=n;i++){
		seg[i].first=-seg[i].first;
		seg[i].second=-seg[i].second;
		swap(seg[i].first,seg[i].second);
	}
	reverse(seg+1,seg+1+n);
	//sort(seg+1,seg+1+n);
	
	double res1=calc(seg,len);
	if(res1>=ans){
		ans=res1;
		tmpl=-ttr;
		tmpr=-ttl;
	}
	for(int i=1;i<=n;i++){
		seg[i].first=-seg[i].first;
		seg[i].second=-seg[i].second;
		swap(seg[i].first,seg[i].second);
	}
	reverse(seg+1,seg+1+n);
	double res2=calc(seg,len);
	if(res2>=ans){
		ans=res2;
		tmpl=ttl;
		tmpr=ttr;
	}
	return ans/tot;
}

__advance int main(){
//freopen("bayes.in","r",stdin);
//freopen("bayes.out","w",stdout);
	while(scanf("%d",&n)==1&&n){
		scanf("%lf%lf",&a,&b);
		scanf("%lf",&alpha);
		for(int i=0;i<=n;i++){
			scanf("%lf%lf",&p[i].x,&p[i].y);
		}
		double last=0;
		for(int i=1;i<=n;i++){
			l[i].k=(p[i].y-p[i-1].y)/(p[i].x-p[i-1].x);
			l[i].b=-l[i].k*p[i].x+p[i].y;
			l[i].l=last;
			l[i].r=p[i].x;
			last=p[i].x;
		}
		sz=0;
		tot=0;
		for(int i=1;i<=n;i++){
			double x1=(a-l[i].b)/l[i].k;
			double x2=(b-l[i].b)/l[i].k;
			if(x1>x2)swap(x1,x2);
			x1=max(x1,l[i].l);
			x2=min(x2,l[i].r);
			if(x1<x2){
				seg[++sz]=make_pair(x1,x2);
				tot+=x2-x1;
			}
		}
		sort(seg+1,seg+1+sz);
				
		/*for(int i=1;i<=sz;i++){
			fprintf(stderr,"[%.3f,%.3f] ",seg[i].first,seg[i].second);
		}
		cerr<<endl;
		*/
		
//		cerr<<calc(1)<<endl;
		
		double l=0,r=p[n].x;
		double ansl=0,ansr=p[n].x;
		while(r-l>1e-9){
			double mid=(l+r)/2;
			if(calc(mid)>=alpha){
				r=mid;
				ansl=tmpl;
				ansr=tmpr;
			}else
				l=mid;
		}/*
		double t=0;
		for(int i=1;i<=sz;i++)
			t+=intersect(seg[i],{ansl,ansr});
		fprintf(stderr,"%.15f\n",t/tot);*/
		printf("%.10f %.10f\n",ansl,ansr); //cout << C << endl;
		
	}
	return 0;
}
