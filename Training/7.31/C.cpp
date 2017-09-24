#include <bits/stdc++.h>
using namespace std;

const int mo = 786433;
const int MAXN = 300000;
const int MAXH = 22;
int f[MAXH][MAXN], g[MAXN], rev[MAXN], n, h;
int G = 5;

inline int pw(int x, int k) {
	int ret = 1;
	for (; k; k >>= 1) {
		if (k & 1) {
			ret = 1LL * ret * x % mo;
		}
		x = 1LL * x * x % mo;
	}
	return ret;
}

inline int get_root(int m) {
	for (int g = 5; g <= 5; g++) {
		bool flag = true;
		for (int i = 2; i * i <= m - 1; ++i) {
			if ((m - 1) % i) {
				continue;
			}
			if (pw(g, i) == 1 || pw(g, (m - 1) / i) == 1) {
if (g == 5) cout << i << endl;
				flag = false;
				//break;
			}
		}
		if (flag) {
			return g;
		}
	}
}

inline void NTT(int a[], int n, int f) {
	for (register int i = 0; i < n; ++i) {
		if (i < rev[i]) {
			swap(a[i], a[rev[i]]);
		}
	}
	for (register int i = 2; i <= n; i <<= 1) {
		static int exp[MAXN];
		exp[0] = 1;
		exp[1] = pw(G, (mo - 1) / i);
		if (f == -1) {
			exp[1] = pw(exp[1], mo - 2);
		}
		for (register int k = 2; k < (i >> 1); ++k) {
			exp[k] = 1LL * exp[k - 1] * exp[1] % mo;
		}
		for (register int j = 0; j < n; j += i) {
			for (register int k = 0; k < (i >> 1); ++k) {
				register int &pa = a[j + k], &pb = a[j + k + (i >> 1)];
				register int A = pa, B = 1LL * pb * exp[k] % mo;
				pa = (A + B) % mo;
				pb = (A - B + mo) % mo;
			}
		}
	}
	if (f == -1) {
		int rv = pw(n, mo - 2);
		for (int i = 0; i < n; ++i) {
			a[i] = 1LL * a[i] * rv % mo;
		}
	}
}

inline void mul(int m, int _a[], int _b[], int c[]) {  //twice???
	static int a[MAXN],b[MAXN];
	
	int n = 1, len = 0;
	while (n < m) n <<= 1, len++;
	for (int i = 1; i < n; ++i) {
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));
	}
	for (int i = 0; i < n; ++i){
		a[i]=_a[i];
		b[i]=_b[i];
	}
	
/*cout << n << " " << len << endl;
for (int i = 0; i < n; ++i) {
	cout << i << " " << a[i] << endl;
}
cout << endl;
for (int i = 0; i < n; ++i) {
	cout << i << " " << b[i] << endl;
}
cout << endl;*/
	NTT(a, n, 1);
	NTT(b, n, 1);
	for (int i = 0; i < n; ++i) {
		c[i] = 1LL * a[i] * b[i] % mo;
	}
	NTT(c, n, -1);
	
/*for (int i = 0; i < n; ++i) {
	cout << i << " " << c[i] << endl;
}
cout << endl;
	exit(0);*/
}
void test(){
	int m=16;
	int a[100],b[100],c[100];
	memset(a,0,sizeof a);
	memset(b,0,sizeof b);
	memset(c,0,sizeof c);
	
	a[1]=1;
	b[1]=1;
	mul(m,a,b,c);
	for(int i=0;i<m;i++)
		cerr<<c[i]<<" ";
	cerr<<endl;
	
}
int main() {
cout << get_root(mo) << endl;
return 0;

//test();

//return 0;
	cin >> n >> h;
	h++;
	f[0][0] = 1;
	f[1][1] = 1;
	for (int i = 2; i <= h; ++i) {
		memset(g, 0, sizeof(g));
		mul(n * 2 + 1, f[i - 1], f[i - 1], g);
		for (int j = 0; j < n; ++j) {
			f[i][j + 1] = g[j];
		}
		
		memset(g, 0, sizeof(g));
		mul(n * 2 + 1, f[i - 2], f[i - 1], g);
		for (int j = 0; j < n; ++j) {
			f[i][j + 1] = (f[i][j + 1] + g[j] * 2) % mo;
		}
/*for (int j = 0; j <= n; ++j) {
	cout << g[j] << " ";
}
cout << endl;
cout << i << ": " << endl;
for (int j = 0; j <= n; ++j) {
	cout << f[i][j] << " ";
}
cout << endl;*/
	}
	cout << f[h][n] << endl;
}
