#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <queue>
#include <cctype>
#include <algorithm>
#include <vector>
#include <cassert>
#include <set>
#include <map>
#include <iomanip>

using namespace std;

const int N = 1005;

int n, m, Mark;
bool Finish[N];
int Dis[N], Deg[N], Time[N];
char str[N];
vector<int> Need[N], Nxt[N], G[N];
priority_queue< pair<int, int> > Q;

string Get(int x){
    
    string Ans, Tmp;
    Ans.push_back('P');
    
    for( ; x; x /= 10)
        Tmp.push_back(char(x % 10 + '0'));
    
    reverse(Tmp.begin(), Tmp.end());
    return Ans + Tmp;
}

string Work(int x){
    string Ans = "";
    
    if (!G[x].size()){
        Ans += Get(x);
        return Ans;
    }
    if (x > 0){
        Ans += Get(x);        
    }
    
    if (G[x].size() > 1) Ans += '('; 
    
    for (int i = 0; i < (int)G[x].size(); i++){
        Ans += '(';
        Ans += Work(G[x][i]);
        Ans += ')';
        
        if (i + 1 != G[x].size()) Ans += '|';
        
    }
    
    if (G[x].size() > 1) Ans += ')';
    return Ans;
}

int main(){
    
    int Case = 0;
    int n,m,o;
    while (1){
        scanf("%d%d%d", &n, &m, &o);
        if (n + m + o == 0) break;
        for(int i = 1; i <= n; ++ i) {
        Nxt[i].clear();
        G[i].clear();
    }
    G[0].clear();

    scanf("%s", Finish + 1);
    for(int i = 1; i <= m; ++ i) {
        Need[i].clear();
        Finish[i] -= '0';
        if (Finish[i]) {
            Dis[i] = 0;
        }
    }

    priority_queue< pair<int, int> > Q;
    for(int i = 1; i <= n; ++ i) {
        scanf("%d", Time + i);
        int cnt, x;
        scanf("%d", &cnt);
        Deg[i] = cnt;
        for(int j = 0; j < cnt; ++ j) {
            scanf("%d", &x);
            Need[x].push_back(i);
            if (Finish[x]) {
                Deg[i] --;
            }
        }
        if (Deg[i] == 0) {
            G[0].push_back(i);
            Q.push(make_pair(-Time[i], i));
        }

        scanf("%d", &cnt);
        for(int j = 0; j < cnt; ++ j) {
            scanf("%d", &x);
            Nxt[i].push_back(x);
        }
    }

    for( ; Q.size(); ) {
        int u = Q.top().second;
        int dis = -Q.top().first;
        Q.pop();

        for(int i = 0; i < (int)Nxt[u].size(); ++ i) {
            int cur = Nxt[u][i];
            if (! Finish[cur]) {
                Finish[cur] = true;
                Dis[cur] = dis;
                for(int j = 0; j < (int)Need[cur].size(); ++ j) {
                    int v = Need[cur][j];
                    -- Deg[v];
                    if (! Deg[v]) {
                        Q.push(make_pair(-dis - Time[v], v));
                        G[u].push_back(v);
                    }
                }
            }
        }
    }
        ++Case;
        printf("Case %d: ", Case);
        if (! Finish[Mark]) {
            cout << -1 << endl;
			puts("");
            continue;
        }
        cout << Dis[Mark] << ' ';
        cout << Work(0) << endl;
        
        printf("\n");
    }
    
    return 0;
}