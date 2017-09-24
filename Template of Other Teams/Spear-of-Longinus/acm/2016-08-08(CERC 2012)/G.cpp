#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int N = 200005;

struct node {
	int x, y, c;
} a[N];


struct node1 {
	int L, R, Lson, Rson, Sum;
} tree[N * 40];

int xx[N], yy[N], n, k, tot;

vector<node> C[N];
int root[N];

int Make(int L, int R) {
	++tot;
	tree[tot].L = L;
	tree[tot].R = R;
	tree[tot].Lson = tree[tot].Rson = tree[tot].Sum = 0;
	return tot;
}

int Same(int x) {
	++tot;
	tree[tot] = tree[x];
	return tot;
}

int build(int L, int R) {
	++tot;
	tree[tot].L = L;
	tree[tot].R = R;
	tree[tot].Lson = tree[tot].Rson = tree[tot].Sum = 0;
	
	if (L == R) return tot;
	
	int s = tot;
	int mid = (L + R) >> 1;
	tree[s].Lson = build(L, mid);
	tree[s].Rson = build(mid + 1, R);
	return s;
}


int Ask(int Lst, int Cur, int L, int R, int x, int y) {
	if (R < x || L > y) return 0;
	if (x <= L && R <= y) return tree[Cur].Sum - tree[Lst].Sum;
	int Tmp = Ask(tree[Lst].Lson, tree[Cur].Lson, L, L + R >> 1, x, y);
	Tmp += Ask(tree[Lst].Rson, tree[Cur].Rson, (L + R >> 1) + 1, R, x, y);
	return Tmp;
}


int Add(int Lst, int pos) {
	int root = Same(Lst);
	
	tree[root].Sum++;
	if (tree[root].L == tree[root].R) return root;
	
	int mid = (tree[root].L + tree[root].R) >> 1;
	if (pos <= mid) tree[root].Lson = Add(tree[root].Lson, pos);
	else tree[root].Rson = Add(tree[root].Rson, pos);
	
	return root;
}

bool cmp(node a, node b){
	if (a.x != b.x) return a.x < b.x;
	return a.y < b.y;
}

int Pre[N], Suf[N];
int stack[N], Heap[N];

int main() {
	int Case;
	scanf("%d", &Case);
	
	while (Case --) {
		scanf("%d%d", &n, &k);
		
		int mx = 0, my = 0;
		for (int i = 1; i <= n; i++){
			scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].c);
		}
		for (int i = 1; i <= n; i++){
			xx[++mx] = a[i].x;
			yy[++my] = a[i].y;
		}
	
		
		for (int i = 1; i <= k; i ++) C[i].clear();
	
		sort(xx + 1, xx + n + 1);
		mx = unique(xx + 1, xx + n + 1) - xx - 1;
		
		sort(yy + 1, yy + n + 1);
		my = unique(yy + 1, yy + n + 1) - yy - 1;
		
		for (int i = 1; i <= n; i++){
			a[i].x = lower_bound(xx + 1, xx + mx + 1, a[i].x) - xx;
			a[i].y = lower_bound(yy + 1, yy + my + 1, a[i].y) - yy;
		}
		
		
		for (int i = 1; i <= n; i++)
			C[a[i].c].push_back(a[i]);
		for (int i = 1; i <= k; i++)
			sort(C[i].begin(), C[i].end(), cmp);
		
		sort(a + 1, a + n + 1, cmp);
	
		tot = 0;
		root[0] = build(1, my);
		
		a[0].x = 0;
		for (int i = 1; i <= n; i++){
			root[a[i].x] = Add(root[a[i - 1].x], a[i].y);
		}	
	
		int Ans = 0;
		for (int i = 1; i <= k; i++){
			for (int j = 0; j < C[i].size(); j++){
				Pre[j] = 1;
				Suf[j] = mx;
			}
			// Learn
			Heap[0] = 0;
			int top = 0;
			for (int j = 0; j < C[i].size(); j++){
				Pre[j] = Heap[upper_bound(stack + 1, stack + top + 1, C[i][j].y - 1) - stack - 1] + 1;
				
				while (top && stack[top] >= C[i][j].y) top--;
				stack[++top] = C[i][j].y;
				Heap[top] = C[i][j].x;
			}
	
			Heap[0] = mx + 1;
			top = 0;
			for (int j = (int)C[i].size() - 1; j >= 0; j--){
				Suf[j] = Heap[upper_bound(stack + 1, stack + top + 1, C[i][j].y - 1) -stack - 1] - 1;
				
				while (top && stack[top] >= C[i][j].y) top--;
				stack[++top] = C[i][j].y;
				Heap[top] = C[i][j].x;
			}
			
			
			if (C[i][0].x > 1) Ans = max(Ans, Ask(root[0], root[C[i][0].x - 1], 1, my, 1, my));
			if (C[i].back().x < mx) Ans = max(Ans, Ask(root[C[i].back().x], root[mx], 1, my, 1, my));
			
			for (int j = 0; j < (int)C[i].size(); j++){
				if (j > 0 && C[i][j].x == C[i][j - 1].x) continue;
				
				
				
				int L = Pre[j], R = Suf[j];
				
				Ans = max(Ans, Ask(root[L - 1], root[R], 1, my, 1, C[i][j].y - 1));
				
				
				if (j > 0){
					Ans = max(Ans, Ask(root[C[i][j - 1].x], root[C[i][j].x - 1], 1, my, 1, my));
				}
				
			}
		}
		printf("%d\n", Ans);
	}
	
	return 0;
}
