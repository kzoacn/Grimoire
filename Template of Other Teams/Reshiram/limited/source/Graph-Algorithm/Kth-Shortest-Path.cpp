#define for_each(it, v)  for (vector<Edge*>::iterator it = (v).begin(); it != (v).end(); ++it)
const int MAX_N = 10000，MAX_M = 50000,MAX_K = 10000;
const int INF = 1000000000;
struct Edge {int from, to;int weight;};
struct HeapNode {
Edge* edge;
int depth;
HeapNode* child[4];
//child[0..1] for heap G
//child[2..3] for heap out edge
};
int n, m, k, s, t;
Edge* edge[MAX_M];
int dist[MAX_N];
Edge* prev[MAX_N];
vector<Edge*> graph[MAX_N];
vector<Edge*> graphR[MAX_N];
HeapNode* nullNode;
HeapNode* heapTop[MAX_N];
HeapNode* createHeap(HeapNode* curNode, HeapNode* newNode) {
if (curNode == nullNode) return newNode;
HeapNode* rootNode = new HeapNode;
memcpy(rootNode, curNode, sizeof(HeapNode));
if (newNode->edge->weight < curNode->edge->weight) {
rootNode->edge = newNode->edge;
rootNode->child[2] = newNode->child[2];
rootNode->child[3] = newNode->child[3];
newNode->edge = curNode->edge;
newNode->child[2] = curNode->child[2];
newNode->child[3] = curNode->child[3];
}
if (rootNode->child[0]->depth < rootNode->child[1]->depth)
rootNode->child[0] = createHeap(rootNode->child[0], newNode);
else
rootNode->child[1] = createHeap(rootNode->child[1], newNode);
rootNode->depth=max(rootNode->child[0]->depth, rootNode->child[1]->depth)+1;
return rootNode;
}
bool heapNodeMoreThan(HeapNode* node1, HeapNode* node2) {return node1->edge->weight > node2->edge-
>weight;}
int main() {
scanf("%d%d%d", &n, &m, &k); scanf("%d%d", &s, &t);
s--, t--;
while (m--) {
Edge* newEdge = new Edge;
int i, j, w;
scanf("%d%d%d", &i, &j, &w);
i--, j--;
newEdge->from = i; newEdge->to = j; newEdge->weight = w;
graph[i].push_back(newEdge); graphR[j].push_back(newEdge);
}
//Dijkstra
queue<int> dfsOrder;
memset(dist, -1, sizeof(dist));
typedef pair<int, pair<int, Edge*> > DijkstraQueueItem;
priority_queue<DijkstraQueueItem, vector<DijkstraQueueItem>, greater<DijkstraQueueItem> > dq;
dq.push(make_pair(0, make_pair(t, (Edge*) NULL)));
while (!dq.empty()) {
int d = dq.top().first;
int i = dq.top().second.first;
Edge* edge = dq.top().second.second;
dq.pop();
if (dist[i] != -1) continue;
dist[i] = d; prev[i] = edge;
dfsOrder.push(i);
for_each(it, graphR[i])
dq.push(make_pair(d+(*it)->weight,make_pair((*it)->from, *it)));
}
//Create edge heap
nullNode = new HeapNode;
nullNode->depth = 0;
nullNode->edge = new Edge;
nullNode->edge->weight = INF;
fill(nullNode->child, nullNode->child + 4, nullNode);
while (!dfsOrder.empty()) {
int i = dfsOrder.front();
dfsOrder.pop();
if (prev[i] == NULL) heapTop[i] = nullNode;
else heapTop[i] = heapTop[prev[i]->to];
vector<HeapNode*> heapNodeList;
for_each(it, graph[i]) {
int j = (*it)->to;
if (dist[j] == -1) continue;
(*it)->weight += dist[j] - dist[i];
if (prev[i] != *it) {
HeapNode* curNode = new HeapNode;
fill(curNode->child, curNode->child + 4, nullNode);
curNode->depth = 1; curNode->edge = *it;
heapNodeList.push_back(curNode);
}
}
if (!heapNodeList.empty()) { //Create heap out
make_heap(heapNodeList.begin(), heapNodeList.end(), heapNodeMoreThan);
int size = heapNodeList.size();
for (int p = 0; p < size; p++) {
heapNodeList[p]->child[2] = 2 * p + 1 < size ? heapNodeList[2 * p + 1] : nullNode;
heapNodeList[p]->child[3] = 2 * p + 2 < size ? heapNodeList[2 * p + 2] : nullNode;
}
heapTop[i] = createHeap(heapTop[i], heapNodeList.front());
}
}
//Walk on DAG
typedef pair<long long, HeapNode*> DAGQueueItem;
priority_queue<DAGQueueItem, vector<DAGQueueItem>, greater<DAGQueueItem> > aq;
if (dist[s] == -1) printf("NO\n");
else {
printf("%d\n", dist[s]);
if (heapTop[s] != nullNode) aq.push(make_pair(dist[s] + heapTop[s]->edge->weight,heapTop[s]));
}
k--;
while (k--) {
if (aq.empty()) {printf("NO\n"); continue;}
long long d = aq.top().first;
HeapNode* curNode = aq.top().second; aq.pop(); printf("%I64d\n", d);
if (heapTop[curNode->edge->to] != nullNode) aq.push(make_pair(d + heapTop[curNode->edge->to]->edge->weight, heapTop[curNode->edge->to]));
for (int i = 0; i < 4; i++)
if (curNode->child[i] != nullNode) aq.push(make_pair(d - curNode->edge->weight +
curNode->child[i]->edge->weight, curNode->child[i]));
}
return 0;
}
K短路（不可重复）
int Num[10005][205],Path[10005][205],dev[10005],from[10005];
int value[10005],dist[205],Next[205],Graph[205][205];
bool forbid[205],hasNext[10005][205];
int N, M, K, s, t;
int tot, cnt;
struct cmp {
bool operator() (const int &a, const int &b) {
int *i, *j;
if(value[a] != value[b]) return value[a] > value[b];
for(i = Path[a], j = Path[b]; (*i) == (*j); i ++, j ++);
return (*i) > (*j);
}
};
void Check(int idx, int st, int *path, int &res) {
int i, j;
for(i = 0; i < N; i ++) {dist[i] = 1000000000; Next[i] = t;}
dist[t] = 0; forbid[t] = true; j = t;
while(1) {
for(i = 0; i < N; i ++)
if(!forbid[i] && (i != st || !hasNext[idx][j]) && (dist[j] + Graph[i][j] < dist[i] ||
dist[j] + Graph[i][j] == dist[i] && j < Next[i])) {
Next[i] = j; dist[i] = dist[j] + Graph[i][j];
}
j = -1;
for(i = 0; i < N; i ++) if(!forbid[i] && (j == -1 || dist[i] < dist[j])) j = i;
if(j == -1) break;
forbid[j] = 1; if(j == st) break;
}
res += dist[st];
for(i = st; i != t; i = Next[i], path ++) (*path) = i;
(*path) = i;
}
int main() {
int i, j, k, l;
while(scanf("%d%d%d%d%d", &N, &M, &K, &s, &t) && N) {
priority_queue <int, vector <int>, cmp> Q;
for(i = 0; i < N; i ++) for(j = 0; j < N; j ++) Graph[i][j] = 1000000000;
for(i = 0; i < M; i ++) {scanf("%d%d%d", &j, &k, &l);Graph[j - 1][k - 1] = l;}
s --; t --;
memset(forbid, false, sizeof(forbid));memset(hasNext[0], false, sizeof(hasNext[0]));
Check(0, s, Path[0], value[0]);
dev[0] = 0; from[0] = 0; Num[0][0] = 0; Q.push(0); cnt = 1; tot = 1;
for(i = 0; i < K; i ++) {
if(Q.empty()) break;
l = Q.top(); Q.pop();
for(j = 0; j <= dev[l]; j ++) Num[l][j] = Num[from[l]][j];
for(; Path[l][j] != t; j ++) {
memset(hasNext[tot], false, sizeof(hasNext[tot]));
Num[l][j] = tot ++;
}
for(j=0; Path[l][j]!=t;j++) hasNext[Num[l][j]][Path[l][j+1]]=true;
for(j = dev[l]; Path[l][j] != t; j ++) {
memset(forbid, false, sizeof(forbid)); value[cnt] = 0;
for(k = 0; k < j; k ++) {
forbid[Path[l][k]] = true; Path[cnt][k] = Path[l][k];
value[cnt] += Graph[ Path[l][k] ][ Path[l][k + 1] ];
}
Check(Num[l][j], Path[l][j], &Path[cnt][j], value[cnt]);
if(value[cnt] > 2000000) continue;
dev[cnt] = j; from[cnt] = l; Q.push(cnt); cnt ++;
}
}
if(i < K || value[l] > 2000000) printf("None\n");
else {
for(i = 0; Path[l][i] != t; i ++) printf("%d-", Path[l][i] + 1);
printf("%d\n", t + 1);
}
}
}
