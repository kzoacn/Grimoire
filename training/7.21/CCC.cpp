#include<bits/stdc++.h>
using namespace std;

struct Point
{
	int x,y;
}	a[50];
int r[10][10],c[10][10];
int t;
int n,m,ans;
void search1(int now)
{
	if (now==m)
	{
		if (t>=1 && t<=n)
		{
			if (!r[a[now].x][t] && !c[a[now].y][t])	ans++;
		}
		return;
	}
	if (t > n * (m - now + 1) || t < (m - now + 1))	return;
	for (int i=1;i<=n;i++)
	if (!r[a[now].x][i] && !c[a[now].y][i] && t>i)
	{
		r[a[now].x][i]=true;
		c[a[now].y][i]=true;
		t-=i;
		search1(now+1);
		t+=i;
		r[a[now].x][i]=false;
		c[a[now].y][i]=false;
	}
}
void search2(int now)
{
	if (now==m)
	{
		if (t>=1 && t<=n)
		{
			if (!r[a[now].x][t] && !c[a[now].y][t])	ans++;
		}
		return;
	}
	for (int i=1;i<=n;i++)
	if (!r[a[now].x][i] && !c[a[now].y][i] && t%i==0)
	{
		r[a[now].x][i]=true;
		c[a[now].y][i]=true;
		t/=i;
		search2(now+1);
		t*=i;
		r[a[now].x][i]=false;
		c[a[now].y][i]=false;
	}
}
int main()
{
	scanf("%d%d%d",&n,&m,&t);
	char op=getchar();
	while (op!='+' && op!='-' && 0op!='*' && op!='/')	op=getchar();
	for (int i=1;i<=m;i++)	scanf("%d%d",&a[i].x,&a[i].y);
	if (op=='+')	search1(1);
	if (op=='*')	search2(1);
	if (op=='-')
	{
		for (int i=1;i+t<=n;i++)
			ans+=2;
		printf("%d\n",ans);
		return 0;
	}
	if (op=='/')
	{
		for (int i=1;i<=n;i++)
		if (t*i<=n)
		{
			if (t==1 && (a[1].x==a[2].x || a[1].y==a[2].y))	break;
			ans+=2;
		}
		printf("%d\n",ans);
		return 0;
	}
	printf("%d\n",ans);
	return 0;
}
