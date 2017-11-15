#include <bits/stdc++.h>

const int MAXN = 5e4 + 5, MAXM = 2e5 + 5;

int n, m;

struct Rule {
	int u;
	int nxtCnt, strCnt, kd[3]; // 0: even only, 1: odd only, 2: both ok
	
	Rule() {
		u = 0;
		nxtCnt = strCnt = kd[0] = kd[1] = kd[2] = 0;
	}
	
	int tot() {
		return kd[0] + kd[1] + kd[2];
	}
	
	int res() {
		if (kd[2]) return 2;
		return (strCnt + kd[1]) & 1;
	}
} rules[MAXM];

std::vector<Rule *> pre[MAXN];
int last[MAXN], label[MAXN]; // -1: haven't visited, 0: even only, 1: odd only, 2: both ok
int odeg[MAXN];

bool inq[MAXN];

void BFS() {
	static std::queue<int> que;
	
	for (int i = 1; i <= n; ++i) if (!odeg[i]) {
		if (label[i] == -1) label[i] = 0;
		que.push(i); inq[i] = 1;
	}
	
	while (!que.empty()) {
		int now = que.front(); que.pop(); inq[now] = 0;
		
		int x = last[now], y = label[now];
		
//		std::cerr << now << " " << label[now] << std::endl;
		
		assert(y != -1);
		
		for (auto e: pre[now]) {
			if (x != -1) --e->kd[x];
			++e->kd[y];
			
			if (e->tot() == e->nxtCnt) {
				if (label[e->u] != -1 && (e->res() | label[e->u]) == label[e->u]) continue;
				last[e->u] = label[e->u];
				if (label[e->u] == -1) label[e->u] = e->res();
				else label[e->u] = e->res();
				if (!inq[e->u]) {
					que.push(e->u); inq[e->u] = 1;
				}
			}
		}
	}
}

int main() {
	while (~scanf("%d%d", &n, &m) && (n || m)) {
		// Init
		
		for (int i = 1; i <= n; ++i) {
			pre[i].clear();
			rules[i] = Rule();
			last[i] = label[i] = -1;
			odeg[i] = 0;
		}
		
		// Solve
		
		for (int i = 1; i <= m; ++i) {
			static int cnt, x;
			static char s[15];
			static std::vector<int> List;
			
			List.clear();
			
			scanf("%d%d", &rules[i].u, &cnt);
			for (int j = 1; j <= cnt; ++j) {
				scanf("%s", s);
				if (isalpha(*s)) {
					++rules[i].strCnt;
				}
				else {
					sscanf(s, "%d", &x);
					List.push_back(x);
				}
			}
			int tmp = 0;
			std::sort(List.begin(), List.end());
			for (int j = 0; j < (int)List.size(); ++j) {
				if (j != (int)List.size() - 1 && List[j] == List[j + 1]) {
					++j; continue;
				}
				pre[List[j]].push_back(&rules[i]);
				++tmp;
			}
			rules[i].nxtCnt = tmp;
			if (!tmp) {
				switch (label[rules[i].u]) {
					case -1:
						label[rules[i].u] = rules[i].strCnt & 1;
						break;
					default:
						label[rules[i].u] |= rules[i].strCnt & 1;
				}
			}
			if (tmp) odeg[i] = 1;
		}
		
		BFS();
		
//		for (int i = 1; i <= n; ++i)
//			fprintf(stderr, "label[%d] = %d\n", i, label[i]);
		
/*		bool flag = 0;
		for (int i = 1; i <= n; ++i)
			if (label[i] == 1 || label[i] == 2) {
				flag = 1; break;
			}*/
		puts((label[1] == 1 || label[1] == 2) ? "YES" : "NO");
	}
	
	return 0;
}
