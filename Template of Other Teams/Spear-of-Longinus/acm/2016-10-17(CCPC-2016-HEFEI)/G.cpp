#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int N = 400005;

int n, m;
vector<int> G[N];
int a[N], Par[N];

struct node{
	bool Rev;
	int c[2], fa;
}T[N];


inline void Rev(int x){
	if (!x) return;
	swap(T[x].c[0], T[x].c[1]);
	T[x].Rev ^= 1;
}

inline void Lazy_Down(int x){
	if (!x) return;
	if (T[x].Rev) Rev(T[x].c[0]), Rev(T[x].c[1]), T[x].Rev = 0;
}

void Rotate(int x, int c){
	int y = T[x].c[c];
	int z = T[y].c[1 - c];
	
	if (T[x].fa){
		if (T[T[x].fa].c[0] == x) T[T[x].fa].c[0] = y;
		else T[T[x].fa].c[1] = y;
	}
	
	T[z].fa = x; T[x].c[c] = z;
	T[y].fa = T[x].fa; T[x].fa = y; T[y].c[1 - c] = x;
	
	//Update(x);
	//Update(y);
}

int stack[N], fx[N];

void Splay(int x){
	int top = 0;
	for (int  u = x; u; u = T[u].fa)
		stack[++top] = u;
	for (int i = top; i >= 1; i--)
		Lazy_Down(stack[i]);
	for (int i = 2; i <= top; i++)
		if (T[stack[i]].c[0] == stack[i - 1]) fx[i] = 0;
		else fx[i] = 1;
	
	for (int i = 2; i <= top; i += 2){
		if (i == top) Rotate(stack[i], fx[i]);
		else {
			if (fx[i] == fx[i + 1]){
				Rotate(stack[i + 1], fx[i + 1]);
				Rotate(stack[i], fx[i]);
			} else {
				Rotate(stack[i], fx[i]);
				Rotate(stack[i + 1], fx[i + 1]);
			}
		}
	}
	
	if (x != stack[top]) Par[x] = Par[stack[top]], Par[stack[top]] = 0;
}

inline int Access(int u){
	int Nxt = 0;
	while (u){
		Splay(u);
		if (T[u].c[1]){
			T[T[u].c[1]].fa = 0;
			Par[T[u].c[1]] = u;
		}
		T[u].c[1] = Nxt;
		if (Nxt){
			T[Nxt].fa = u;
			Par[Nxt] = 0;
		}
		//Update(u)
		Nxt = u;
		u = Par[u];
	}
	return Nxt;
}

inline void Root(int u){
	Access(u);
	Splay(u);
	Rev(u);
}

inline void Link(int u, int v){
	Root(u);
	Par[u] = v;
}

inline void Cut(int u, int v){
	Access(u);
	Splay(v);
	if (Par[v] != u){
		swap(u, v);
		Access(u);
		Splay(v);
	}
	Par[v] = 0;
}

inline int Find_Root(int x){
	Access(x);
	Splay(x);
	
	int y = x;
	while (T[y].c[0]){
		Lazy_Down(y);
		y = T[y].c[0];
	}
	return y;
}

int main(){
	scanf("%d%d", &n, &m);
	for (int i = 0; i <= n; i++){
		G[i].clear();
		T[i].Rev = 0;
		T[i].fa = T[i].c[0] = T[i].c[1] = 0;
		Par[i] = 0;
	}
	
	for (int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
		int x = i, y = a[i];
		if (y) {
			int t = Find_Root(y);
			if (t == x){
				G[x].push_back(y);
			} else 
				Link(x, y);
		}
	}
	
	for (int i = 1; i <= m; i++){
		int k, x, y;
		scanf("%d", &k);
		
		if (k == 1){
			scanf("%d%d", &x, &y);
			int tmp = a[x];
			a[x] = y;
			
			if (G[x].size() > 0 && G[x][0] == tmp){
				G[x].clear();
				
				if (y > 0){
					int t = Find_Root(y);
					
					if (t == x){
						G[x].push_back(y);
					} else {
						Link(x, y);
					}
				}
			} else {
				if (tmp > 0)
					Cut(x, tmp);
				
				int p = Find_Root(tmp);
				
				if (G[p].size() > 0 && Find_Root(G[p][0]) == x){
					int q = G[p][0];	
					Link(p, q);
					G[p].clear();
					
					if (!y) continue;
					int t = Find_Root(y);
					if (t == x){
						G[x].push_back(y);
					} else {
						Link(x, y);
					}
				} else {
					if (!y) continue;
					int t = Find_Root(y);		
					
					if (t == x){
						G[x].push_back(y);
					} else {
						Link(x, y);
					}
				}
			}
			
		} else {
			scanf("%d", &x);
			int t = Find_Root(x);
			
			if (G[t].size() > 0)
				puts("-1");
			else
				printf("%d\n", t);
		}
	}
	
	return 0;
}
