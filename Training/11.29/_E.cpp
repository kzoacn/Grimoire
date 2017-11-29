#pragma comment(linker, "/STACK:64000000")
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NO_DEPRECEATE
#define _USE_MATH_DEFINES
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#include <functional>
#include <set>
#include <map>
#include <cmath>
#include <queue>
#include <memory.h>
#include <sstream>
#include <cassert>
#include <ctime>
#include <complex>

using namespace std;

#define pb push_back
#define mp make_pair
#define sq(x) ((x)*(x))
#define tmin(x,y,z) (min(min((x),(y)),(z)))
typedef long long int64;
typedef unsigned long long uint64;
#define pii pair<int, int>
#define pll pair<int64, int64>
#define INF (int)(2e9+2)
#define LINF (int64)(1e16+1)
#define EPS (1e-8)
#define PI (3.1415926535897932384626433832795)
#define y1 asdf_1
#define y0 asdf_2
#define j0 jj0
#define MOD 1000000007
#ifdef _MY_DEBUG
#define HMOD 536870911
#else
#define HMOD 536870911//((long long)(1e18) + 3LL)
#endif
#define HBASE 1009
#define MAXN 100000

string s;
int nxt[MAXN + 3], prv[MAXN + 3];
double ans;
char buf[MAXN + 5];
int64 hashUp[MAXN + 5], hashDown[MAXN + 5];
int64 pw[MAXN + 5];

int64 norm(int64 a)
{
	while (a < 0LL)
	{
		a += HMOD;
	}
	while (a >= HMOD)
	{
		a -= HMOD;
	}
	return a;
}

int64 mul(int64 a, int64 b)
{
	int64 q = (long double)a * (long double)b / (long double)HMOD;
	return norm(a * b - q * HMOD);
}

void initHash()
{
	pw[0] = 1LL;
	for (int j = 1; j <= MAXN; j++)
	{
		pw[j] = mul(pw[j - 1], HBASE);
	}
}

void calcHash()
{
	for (int j = 0; j < s.size(); j++)
	{
		hashDown[j + 1] = (mul(hashDown[j], HBASE) + s[j]) % HMOD;
	}
	for (int j = s.size() - 1; j >= 0; j--)
	{
		hashUp[j + 1] = (mul(hashUp[j + 2], HBASE) + s[j]) % HMOD;
	}
}

int64 getHashUp(int l, int r)
{
	if (l > r)
	{
		return 0LL;
	}
	return norm(hashUp[l + 1] + (HMOD - mul(hashUp[r + 2], pw[r - l + 1])));
}

int64 getHashDown(int l, int r)
{
	if (l > r)
	{
		return 0LL;
	}
	return norm(hashDown[r + 1] + (HMOD - mul(hashDown[l], pw[r - l + 1])));
}

void solve()
{
	initHash();
	scanf ("%s", &buf);
	s = buf;
	calcHash();
	prv[0] = -1;
	for (int j = 1; j < s.size(); j++)
	{
		if (s[j - 1] == '?')
		{
			prv[j] = j - 1;
		}
		else
		{
			prv[j] = prv[j - 1];
		}
	}
	nxt[s.size() - 1] = s.size();
	for (int j = (int)s.size() - 2; j >= 0; j--)
	{
		if (s[j + 1] == '?')
		{
			nxt[j] = j + 1;
		}
		else
		{
			nxt[j] = nxt[j + 1];
		}
	}
	for (int pos = 0; pos < s.size(); pos++)
	{
		//printf ("pos %d\n", pos);
		double prob = 1.0;
		int delta = 0;
		for (int i = 0; i < 20 && pos - delta >= 0 && pos + delta < s.size(); i++)
		{
			int newDelta = min(pos - prv[pos - delta], nxt[pos + delta] - pos);
			//printf ("newDelta %d\n", newDelta);
			if (getHashUp(pos - newDelta + 1, pos - delta - 1) != getHashDown(pos + delta + 1, pos + newDelta - 1))
			{
				int l = 0, r = newDelta - delta - 1;
				int res = 0;
				while (l <= r)
				{
					int mid = (l + r) >> 1;
					if (getHashUp(pos - delta - mid, pos - delta - 1) != getHashDown(pos + delta + 1, pos + delta + mid))
					{
						r = mid - 1;
					}
					else
					{
						res = mid;
						l = mid + 1;
					}
				}
				//printf ("res %d\n", res);
				ans += prob * (res + 1) * 2;
				break;
			}
			ans += prob * (newDelta - delta) * 2.0;
			prob /= 26.0;
			delta = newDelta;
		}
		//printf ("%.12lf\n", ans);
	}
	printf ("%.12lf\n", ans / (double)s.size() - 1.0);
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0);


	solve();

	return 0;
}
