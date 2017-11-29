#include <bits/stdc++.h>

typedef long long LL;

const int MAXN = (5e5 + 5);

int n, m, k;
int s[MAXN];

int mn[MAXN][19];

void get_ST_Table() {
	for (int j = 0; j < 19; ++j) {
		for (int i = 1; i <= n; ++i) {
			if (j == 0) {
				mn[i][0] = mn[i - 1][0] + s[i];
				continue;
			}
			mn[i][j] = mn[i][j - 1];
			if (i + (1 << j - 1) <= n) {
				mn[i][j] = std::min(mn[i][j], mn[i + (1 << j - 1)][j - 1]);
			}
		}
	}
}

int queryMin(int l, int r) {
	int k = std::__lg(r - l + 1);
	return std::min(mn[l][k], mn[r - (1 << k) + 1][k]);
}

std::vector<int> In[MAXN], Out[MAXN];
std::unordered_set<int> S;
int pre[MAXN], cnt[MAXN];
bool ok[MAXN];


using namespace std;
bool Check(int d) {
	for (int i = 0; i <= n; ++i) {
		cnt[i] = ok[i] = 0;
		pre[i] = 0;
		In[i].clear();
		Out[i].clear();
	}
	S.clear();
	
	/*cout << mn[1][0] << " " << mn[2][0] <<  " " << mn[3][0] << endl;
	cout << mn[2][1] << endl;
	cout << queryMin(1, 3) << endl;*/
	ok[1] = 1;
	int tmp = 0;
//int cc = 0;
	for (int i = 1; i <= n; ++i) {
	//cout << "asdf" << i << endl;
		for (int j: Out[i])
			S.erase(j);
		for (int j:	In[i])
			S.insert(j);
		
		if (!ok[i]) {
			ok[i] = (bool)(tmp += cnt[i]);
			if (!ok[i]) continue;
			pre[i] = *S.begin();
		}	
//cout << "fir: " << i << endl;	
		int nxt = n + 1, L = i, R = n;
		
		while (L <= R) { //cc++;
			int mid = (L + R) >> 1;
			if (queryMin(i, mid) <= -m - (i - 1) * k) nxt = mid, R = mid - 1;
			else L = mid + 1;
		}
//std::cerr << i << ": " << nxt << std::endl;
		if (i == 1) {
			++cnt[i + 1];
			if (nxt + 1 <= n) --cnt[nxt + 1];
			In[i + 1].push_back(i);
			if (nxt + 1 <= n) Out[nxt + 1].push_back(i);
		}
		else {
			if (i + d > n || i + d >= nxt + 1) continue;
			++cnt[i + d];
			if (nxt + 1 <= n) --cnt[nxt + 1];
			In[i + d].push_back(i);
			if (nxt + 1 <= n) Out[nxt + 1].push_back(i);
		}
	}
	//cout << cc << endl;
	//cout << ok[4] << endl;
	/*for (int i = 1; i <= n; ++i)
		fprintf(stderr, "ok[%d] = %d, pre[%d] = %d\n", i, ok[i], i, pre[i]);*/
	
	for (int i = 1; i <= n; ++i) if (ok[i]) {
		if (m + (i - 1) * k + queryMin(i, n) > 0) {
			pre[n + 1] = i;
			return 1;
		}
	}
	return 0;
}

std::vector<int> Ans;

int main() {
	while (~scanf("%d%d%d", &n, &m, &k)) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", s + i);
			s[i] = -s[i];
		}
		
		bool lose = 0;
		
		LL tmp = m;
		for (int i = 1; i <= n; ++i) {
			tmp += s[i];
			if (tmp <= 0) {
				lose = 1; break;
			}
			tmp += k;
		}
		if (lose) {
			puts("Poor Hero!");
			continue;
		}
		
		get_ST_Table();
		
//cout << Check(2) << endl;
//return 0;
		
		if (Check(n)) {
			puts("Poor JRY!");
			continue;
		}
		
		//return 0;
		
		int ans = n, L = 1, R = n - 1;
		while (L <= R) {
//cout << L << " " << R << endl;
			int mid = (L + R) >> 1;
			if (Check(mid)) ans = mid, L = mid + 1;
			else R = mid - 1;
		}
		
		Check(ans);
		
		printf("%d\n", ans);
		Ans.clear();
		int now = n + 1;
		while (pre[now] != 1) {
			Ans.push_back(pre[now] - 1);
			now = pre[now];
			//std::cerr << now << std::endl;
		}
		printf("%d\n", (int)Ans.size());
		for (int i = Ans.size() - 1; i >= 0; --i)
			printf("%d%c", Ans[i], " \n"[i == 0]);
			
		std::reverse(Ans.begin(), Ans.end());
		int tp[MAXN];
		memset(tp, 0, sizeof(tp));
		for (int i = 0; i < Ans.size(); ++i) {
			tp[Ans[i]] = 1;
			if (i) {
				//cout << endl << i << " " << Ans[i - 1] << " " << Ans[i] << endl;
				assert(Ans[i] - Ans[i - 1] >= ans);
				//cout << i << endl;
			}
		}
		for (int i = 1, c = m, h = 0; i <= n; ++i) {
			c += s[i];
			assert(c > 0);
			h += k;
			if (tp[i]) {
				c += h;
				h = 0;
			}
		}
	}
	
	return 0;
}
