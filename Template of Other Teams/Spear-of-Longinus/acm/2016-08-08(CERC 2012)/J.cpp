#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

const int N = 100005;

int n, m, flag[N], degree[N];
int tmp[N];

vector<int> adj[N];

void build(int x, int y) {
	adj[x].push_back(y);
	return ;
}

void work() {
	scanf("%d%d", &n, &m);
	
	for(int i = 1; i <= n; i++) {
		scanf("%d", &flag[i]);
	}
	for(int i = 1; i <= n; i++) {
		degree[i] = 0;
		adj[i].clear();
	}
	
	for(int i = 1; i <= m; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		build(x, y);
		degree[y]++;
	}
	for(int i = 1; i <= n; i++) {
		tmp[i] = degree[i];
	}
	
	vector<int> queue[3];
	
	for(int i = 1; i <= 2; i++) {
		queue[i].clear();
	}

	for(int i = 1; i <= n; i++) {
		if(degree[i] == 0) {
			queue[flag[i]].push_back(i);
		}
	}
	int head[3], CC = 0;
	head[1] = head[2] = 0;
	int now = 1;
	
	int size = 0;
	while(1) {
		if(head[1] >= queue[1].size() && head[2] >= queue[2].size()) {
			break;
		}
		if(head[now] >= queue[now].size()) {
			now = 3 - now;
			CC++;
			continue;
		}
		int u = queue[now][head[now]++];
		for(int i = 0; i < adj[u].size(); i++) {
			int to = adj[u][i];
			degree[to]--;
			if(degree[to] == 0){
				queue[flag[to]].push_back(to);
			}
		}
	}
	
	for(int i = 1; i <= n; i++) {
		degree[i] = tmp[i];
	}
	
	
	int ans = CC;
	
	CC = 0;
	
	for(int i = 1; i <= 2; i++) {
		queue[i].clear();
	}
	for(int i = 1; i <= n; i++) {
		if(degree[i] == 0) {
			queue[flag[i]].push_back(i);
		}
	}
	head[1] = head[2] = 0;
	now = 2;
	while(1) {
		if(head[1] >= queue[1].size() && head[2] >= queue[2].size()) {
			break;
		}
		if(head[now] >= queue[now].size()) {
			now = 3 - now;
			CC++;
			continue;
		}
		int u = queue[now][head[now]++];
		for(int i = 0; i < adj[u].size(); i++) {
			int to = adj[u][i];
			degree[to]--;
			if(degree[to] == 0){
				queue[flag[to]].push_back(to);
			}
		}
	}
	ans = min(ans, CC);
	cout << ans << endl;
	return ;
}

int main() {
	int T;
	scanf("%d", &T);
	for(int i = 1; i <= T; i++) {
		work();
	}
	return 0;
}
