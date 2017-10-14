#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <complex>
#include <ctime>
#include <unordered_set>
#include <unordered_map>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define mp make_pair

const int MOD = 13;
int add(int x, int y)
{
    x += y;
    if (x >= MOD) return x - MOD;
    return x;
}
int sub(int x, int y)
{
    x -= y;
    if (x < 0) return x + MOD;
    return x;
}
int mult(int x, int y)
{
    return (x * y) % MOD;
}
int rev(int x)
{
    int y = 1;
    for (int i = 2; i < MOD; i++)
        y = mult(y, x);
    return y;
}

map<pii, int> edId;
const int N = 550;
const int INF = (int)1e8;
int n, m, k;
int S, T;
int g[N][N];
int d[N];
int a[N][N];

int getId(int x, int y)
{
    if (x > y) swap(x, y);
    pii t = mp(x, y);
    if (edId.count(t) > 0) return edId[t];
    edId[t] = n;
    return n++;
}
void read()
{
    scanf("%d%d%d%d", &k, &S, &T, &m);
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &d[i]);
        int p;
        scanf("%d", &p);
        int lst;
        scanf("%d", &lst);
        for (int j = 1; j < p; j++)
        {
            int nxt;
            scanf("%d", &nxt);
            if (lst == nxt) throw;
            int w = getId(lst, nxt);
            g[i][w] = add(g[i][w], 1);
            lst = nxt;
        }
    }
    for (int i = 0; i < m; i++)
        g[i][n] = d[i];
    return;
}

void gauss()
{
    for (int i = 0; i < n; i++)
    {
        int t = -1;
        for (int j = i; j < m; j++)
        {
            if (g[j][i] == 0) continue;
            t = j;
            break;
        }
        if (t == -1) throw;
        swap(g[i], g[t]);
        int x = rev(g[i][i]);
        for (int j = i; j <= n; j++)
            g[i][j] = mult(g[i][j], x);
        for (int j = 0; j < m; j++)
        {
            if (j == i) continue;
            x = g[j][i];
            for (int h = 0; h <= n; h++)
                g[j][h] = sub(g[j][h], mult(g[i][h], x));
        }
    }
    for (int i = 0; i < n; i++)
        if (g[i][n] == 0) throw;
    return;
}

int main()
{
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);

    read();
    gauss();
    for (int i = 1; i <= k; i++)
        for (int j = 1; j <= k; j++)
            a[i][j] = (i == j ? 0 : INF);
    for (auto it : edId)
    {
        int v = it.first.first, u = it.first.second, w = g[it.second][n];
        a[v][u] = a[u][v] = w;
    }
    for (int h = 1; h <= k; h++)
        for (int i = 1; i <= k; i++)
            for (int j = 1; j <= k; j++)
                a[i][j] = min(a[i][j], a[i][h] + a[h][j]);
    printf("%d\n", a[S][T]);

    return 0;
}
