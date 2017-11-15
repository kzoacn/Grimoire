#include<bits/stdc++.h>
#define x1 _sdf1
#define x2 _sdf2
#define __advance //__attribute__((optimize("O3")))
using namespace std;
const int maxn=1e5+5 + 1e5;
struct L{
	long double k,b;
	long double l,r;
}l[maxn];
struct P{
	long double x,y;
}p[maxn];
int n;
long double a,b,alpha;

pair<long double,long double>seg[maxn];
int sz;
long double tmpl,tmpr;
__advance __inline long double leng(pair<long double,long double>s){
	return s.second-s.first;
}
long double tot=0;
__advance __inline long double intersect(pair<long double,long double>a,pair<long double,long double>b){
	long double l=max(a.first,b.first);
	long double r=min(a.second,b.second);
	if(l>r)return 0;
	return r-l;	
}
int C = 0;
long double ttl,ttr;
__advance __inline long double calc(pair<long double,long double>*seg,long double len){
	int n=::sz;
//	deque<pair<long double,long double> >dq;
	int head=0,tail=0;
	static pair<long double,long double> dq[maxn];
	
	long double ans=0;
	long double sum=0;
	for(int i=1;i<=n;i++){
//		dq.push_back(seg[i]);
		dq[tail++]=seg[i];
		sum+=leng(seg[i]);
		long double fr=seg[i].first-len;
		while(head +1 < tail && dq[head].second<=fr){
			sum-=leng(dq[head]);
			head++;
		}
		long double res=sum-leng(dq[head]);
		res+=intersect(dq[head],{seg[i].second-len,seg[i].second});
		if(res>ans){
			ans=res;
			ttl=seg[i].second-len;
			ttr=seg[i].second;
		}
	}
	return ans;
}

__advance __inline long double calc(long double len){
	int n=::sz;
	long double ans=0;
	for(int i=1;i<=n;i++){
		seg[i].first=-seg[i].first;
		seg[i].second=-seg[i].second;
		swap(seg[i].first,seg[i].second);
	}
	reverse(seg+1,seg+1+n);
	//sort(seg+1,seg+1+n);
	
	long double res1=calc(seg,len);
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
	long double res2=calc(seg,len);
	if(res2>=ans){
		ans=res2;
		tmpl=ttl;
		tmpr=ttr;
	}
	return ans/tot;
}

int main(){
freopen("bayes.in","r",stdin);
freopen("bayes.out","w",stdout);
	while(scanf("%d",&n)==1&&n){
	double ta, tb, aa;
		scanf("%lf%lf",&ta,&tb);
		scanf("%lf",&aa);
		a = ta;
		b = tb;
		alpha = aa;
		for(int i=0;i<=n;i++){
			double xx, yy;
			scanf("%lf%lf", &xx, &yy);
			p[i].x = xx;
			p[i].y = yy;
		}
		long double last=0;
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
			long double x1=(a-l[i].b)/l[i].k;
			long double x2=(b-l[i].b)/l[i].k;
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
		
		long double l=0,r=p[n].x;
		long double ansl=0,ansr=p[n].x;
		while(r-l>1e-13){
			long double mid=(l+r)/2;
			if(calc(mid)>=alpha){
				r=mid;
				ansl=tmpl;
				ansr=tmpr;
			}else
				l=mid;
		}
		printf("%.10f %.10f\n",(double)ansl,(double)ansr); //cout << C << endl;
		
	}
	return 0;
}
