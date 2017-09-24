// 精确覆盖
const int MAXD = 1120;
const int MAXN = 1000200;

int n, m, t, size;
int U[MAXN], D[MAXN], L[MAXN], R[MAXN], C[MAXN], Row[MAXN];
int H[MAXD], S[MAXD];

void init(int n, int m) {
	for(int i = 0; i <= m; ++i) {
		S[i] = 0, D[i] = U[i] = i;
		L[i+1] = i, R[i] = i + 1;
	}
	R[m] = 0, size = m;
	for(int i = 1; i <= n; ++i)
		H[i] = -1;
}
void link(int r, int c) {
	++S[C[++size] = c];
	Row[size] = r;
	D[size] = D[c], U[D[c]] = size;
	U[size] = c, D[c] = size;
	if(H[r] < 0) H[r] = L[size] = R[size] = size;
	else {
		R[size] = R[H[r]], L[R[size]] = size;
		L[size] = H[r];
		R[H[r]] = size;
	}
}
void remove(int c) {
	R[L[c]] = R[c], L[R[c]] = L[c];
	for(int i = D[c]; i != c; i = D[i])
		for(int j = R[i]; j != i; j = R[j])
			U[D[j]] = U[j], D[U[j]] = D[j], -- S[C[j]];
}
void resume(int c) {
	R[L[c]] = L[R[c]] = c;
	for(int i = U[c]; i != c; i = U[i])
		for(int j = L[i]; j != i; j = L[j])
			U[D[j]] = D[U[j]] = j, ++S[C[j]];
}
int ans[MAXD], cnt;
bool dance(int k) {
	int i, j, tmp, c;
	if( !R[0] ) return 1;
	for(tmp = MAXD, i = R[0]; i; i = R[i])
		if(S[i] < tmp) tmp = S[c = i];
	remove(c);
	for(i = D[c]; i != c; i = D[i]) {
		ans[cnt++] = Row[i]; //用栈记录解
		for(j = R[i]; j != i; j = R[j]) remove(C[j]);
		if(dance(k + 1)) return 1;
		--cnt;
		for(j = L[i]; j != i; j = L[j]) resume(C[j]);
	}
	resume(c);
	return 0;
}

// 可重复覆盖
const int mxm = 15 * 15 + 10;
const int MAXD = 15 * 15 + 10;
const int MAXDode = MAXD * mxm;
const int INF = 0x3f3f3f3f;
//能不加的行尽量不加， 减少搜索时间
int size;
int U[MAXDode], D[MAXDode], R[MAXDode], L[MAXDode], Row[MAXDode],  Col[MAXDode];
int H[MAXD], S[mxm];
int ansd;
void init(int n, int m) {
	int i;
	for(i = 0; i <= m; ++i) {
		S[i] = 0, U[i] = D[i] = i;
		L[i] = i - 1, R[i] = i + 1;
	}
	R[m] = 0, L[0] = m, size = m;
	for(i = 1; i <= n; ++i) H[i] = -1;
}
void link(int r, int c) {
	++S[Col[++size] = c];
	Row[size] = r; D[size] = D[c]; U[D[c]] = size; U[size] = c; D[c] = size;
	if(H[r] < 0) H[r] = L[size] = R[size] = size;
	else {
		R[size] = R[H[r]];
		L[R[H[r]]] = size;
		L[size] = H[r];
		R[H[r]] = size;
	}
}
void remove(int c) {
	for(int i = D[c]; i != c; i = D[i])
		L[R[i]] = L[i], R[L[i]] = R[i];
}
void resume(int c) {
	for(int i = U[c]; i != c; i = U[i])
		L[R[i]] = R[L[i]] = i;
}
bool vv[mxm];
int f() {
	int ret = 0, c, i, j;
	for(c = R[0]; c != 0; c = R[c]) vv[c] = 1;
	for(c = R[0]; c != 0; c = R[c])
		if(vv[c]) {
			++ret, vv[c] = 0;
			for(i = D[c]; i != c; i = D[i])
				for(j = R[i]; j != i; j = R[j])
					vv[Col[j]] = 0;
		}
	return ret;
}
void dance(int d) {
	if(d + f() >= ansd) return;
	if(R[0] == 0) {
		if(d < ansd) ansd = d;
		return;
	}
	int c = R[0], i, j;
	for(i = R[0]; i; i = R[i])
		if(S[i] < S[c]) c = i;
	for(i = D[c]; i != c; i = D[i]) {
		remove(i);
		for(j = R[i]; j != i; j = R[j]) remove(j);
		dance(d + 1);
		for(j = L[i]; j != i; j = L[j]) resume(j);
		resume(i);
	}
}
