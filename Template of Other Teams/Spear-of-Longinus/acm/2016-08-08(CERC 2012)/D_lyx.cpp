#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 200005;

int a[N], b[N], heap[N], Le[N], Ri[N];
int tot;
int n;

struct node{
	int val;
	int time;
	int le, ri;
}Q[N * 4];

struct node1{
	int min;
	int add;
}tree[N * 4];

bool cmp(node a, node b){
	return a.time < b.time;
}

inline void Add(int x1, int x2, int y1, int y2){
	
	if (x1 > x2) swap(x1, x2);
	if (y1 > y2) swap(y1, y2);

	++tot;
	Q[tot].val = 1;
	Q[tot].le = y1;
	Q[tot].ri = y2;
	Q[tot].time = x1;
	
	++tot;
	Q[tot].val = -1;
	Q[tot].le = y1;
	Q[tot].ri = y2;
	Q[tot].time = x2 + 1;
}

inline void build(int s, int x, int y){
	tree[s].min = 0;
	tree[s].add = 0;
	
	if (x == y) return;
	
	int t = s + s, mid = (x + y) >> 1;
	build(t, x, mid);
	build(t + 1, mid + 1, y); 
}

inline void push_down(int s){
	if (tree[s].add == 0) return;
	
	int t = s + s;
	tree[t].min += tree[s].add;
	tree[t].add += tree[s].add;
	
	tree[t + 1].min += tree[s].add;
	tree[t + 1].add += tree[s].add;
	
	tree[s].add = 0;
}

inline void Change(int s, int x, int y, int l, int r, int val){
	if (x == l && y == r){
		tree[s].min += val;
		tree[s].add += val;
		return;
	}
	
	if (x != y) push_down(s);
	
	int t = s + s, mid = (x + y) >> 1;
	
	if (r <= mid) Change(t, x, mid, l, r, val);
	else
	if (l > mid) Change(t + 1, mid + 1, y, l, r, val);
	else {
		Change(t, x, mid, l, mid, val);
		Change(t + 1, mid + 1, y, mid + 1, r, val);
	}
	
	tree[s].min = min(tree[t].min, tree[t + 1].min);
}

inline int Find(int s, int x, int y, int l, int r){
	if (x == l && y == r){
		return tree[s].min;
	}
	
	if (x != y) push_down(s);
	
	int t = s + s, mid = (x + y) >> 1;
	
	int Ret;
	if (r <= mid) Ret = Find(t, x, mid, l, r);
	else
	if (l > mid) Ret = Find(t + 1, mid + 1, y, l, r);
	else {
		Ret = min(Find(t, x, mid, l, mid),Find(t + 1, mid + 1, y, mid + 1, r));
	}
	
	tree[s].min = min(tree[t].min, tree[t + 1].min);
	return Ret;
}

int main(){
	
	int Case;
	scanf("%d", &Case);
	
	for (int ii = 1; ii <= Case; ii++){
	
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		
		for (int i = 1; i <= n; i++) b[i] = a[i];
		
		sort(b + 1, b + 1 + n);
		
		int m = unique(b + 1, b + 1 + n) - b - 1;
		
		for (int i = 1; i <= n; i++)
			a[i] = lower_bound(b + 1, b + 1 + m, a[i]) - b;
		
		for (int i = 1; i <= m; i++) heap[i] = 0;
		
		for (int i = 1; i <= n; i++){
			Le[i] = heap[a[i]];
			heap[a[i]] = i;
		}
		
		for (int i = 1; i <= m; i++) heap[i] = n + 1;
		
		for (int i = n; i >= 1; i--){
			Ri[i] = heap[a[i]];
			heap[a[i]] = i;
		}
		
		tot = 0;
		for (int i = 1; i <= n; i++){
			Add(Le[i] + 1, i, i, Ri[i] - 1);
			//Add(i, Ri[i] - 1, i, Le[i] + 1);
		}
		
		build(1, 1, n);
		
		sort(Q + 1, Q + 1 + tot, cmp);
		
		bool flag = 1;
		
		
		int j;
		for (int i = 1; i <= tot; i = j + 1){
			
			Change(1, 1, n, Q[i].le, Q[i].ri, Q[i].val);
			
			j = i;
			while (j + 1 <= tot && Q[j + 1].time == Q[i].time){
				j++;
				Change(1, 1, n, Q[j].le, Q[j].ri, Q[j].val);
			}
			
			
			if (Q[j].time > n) continue;
			
			if (Find(1, 1, n, Q[j].time, n) == 0){
				flag = 0;
				break;
			}
		}
		
		if (flag) puts("non-boring");
		else puts("boring");
		
	}
	
	return 0;
}
