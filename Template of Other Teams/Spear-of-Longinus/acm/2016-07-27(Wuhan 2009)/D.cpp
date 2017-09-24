#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
typedef pair<double,int> pdi;
priority_queue<pdi,vector<pdi>,greater<pdi> >q;
int T,n;
double B;
const int maxn=20010;
pair<double,double> task[maxn];
int main(){
	int t=0;
	while(scanf("%d%d%lf",&T,&n,&B)==3){
		t++;
		if(!T)break;
		for(int i=1;i<=T;i++){
			double S,P;scanf("%lf%lf",&S,&P);
			P/=100.;
			task[i]=make_pair(S,S*(1-P));
		}
		sort(task+1,task+1+T);
		double tim=0,ntim=0,delta=0;
		for(int i=1;i<=min(n,T);i++)
			q.push(make_pair(task[i].second,i));
		int cur=n+1;
		double sum = 0;
		while(!q.empty()){
//			cerr<<q.top().second<<endl;
			double x=q.top().first;
			double delta = (x - sum) / (B / q.size());
			tim += delta;
			sum += delta * (B / q.size());
			q.pop();
			if(cur<=T){
				q.push(make_pair(task[cur].second+sum,cur));
				cur++;
			}
		}
		printf("Case %d: %.2f\n\n",t,tim);
	}
	return 0;
}

/*1
!!!0.161600
2
!!!0.202000
3
!!!0.269333
4
!!!0.565600
6
!!!0.602667
5
!!!0.805000
Case 1: 0.81
1
!!!0.000000
Case 2: 0.00

*/
