#include <cstdio>
#include <cstring>
#include <string>

int n, mx, mxlen;
char s[100005];
char *ss[100005];

namespace SAM {
	int to[100005 << 1][26], parent[100005 << 1], step[100005 << 1], tot;
	int sam_len, root, np;
	
	int newnode(int STEP) {
		++tot;
		memset(to[tot], 0, sizeof to[tot]);
		parent[tot] = 0;
		step[tot] = STEP;
		return tot;
	}
	
	void init() {
		tot = 0;
		root = np = newnode(sam_len = 0);
	}
	
	void extend(char ch) {
		int x = ch - 'a';
		int last = np; np = newnode(++sam_len);
		for (; last && !to[last][x]; last = parent[last])
			to[last][x] = np;
		if (!last) parent[np] = root;
		else {
			int q = to[last][x];
			if (step[q] == step[last] + 1) parent[np] = q;
			else {
				int nq = newnode(step[last] + 1);
				memcpy(to[nq], to[q], sizeof to[q]);
				parent[nq] = parent[q];
				parent[q] = parent[np] = nq;
				for (; last && to[last][x] == q; last = parent[last])
					to[last][x] = nq;
			}
		}
	}
	
	bool run_in_sam(int id) {
		int k = root;
		for (char *c = ss[id]; *c; ++c) {
			int x = *c - 'a';
			if (!to[k][x]) return 0;
			k = to[k][x];
		}
		return 1;
	}
}

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		mx = 0; mxlen = 0;
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%s", s);
			int len = strlen(s);
			ss[i] = new char[len + 1];
			for (int j = 0; j < len; ++j)
				ss[i][j] = s[j];
			ss[i][len] = '\0';
			if (len > mxlen) {
				mx = i;
				mxlen = len;
			}
		}
		
//		std::cerr << mxlen << std::endl;
		
		SAM::init();
		for (int i = 0; i < mxlen; ++i) SAM::extend(ss[mx][i]);
		
		bool flag = 1;
		for (int i = 1; i <= n; ++i) if (i != mx) {
			if (!SAM::run_in_sam(i)) {
//				std::cerr << ss[i] << " is not a substring of " << ss[mx] << std::endl;
				flag = 0;
				break;
			}
		}
		if (flag) puts(ss[mx]);
		else puts("No");
		
		for (int i = 1; i <= n; ++i)
			delete ss[i];
	}
	
	return 0;
}
