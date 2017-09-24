struct Node{
	int len, fail;
	int To[30];
}T[N];
int Lst, Root, tot, n;
char s[N];
int Ord[N], Ans[N], Ways[N], heap[N];
void Add(int x, int l){
	int Nt = ++tot, p = Lst;
	T[Nt].len = l;
	for (;p && !T[p].To[x]; p = T[p].fail) T[p].To[x] = Nt;
	if (!p) T[Nt].fail = Root; else
	if (T[T[p].To[x]].len == T[p].len + 1) T[Nt].fail = T[p].To[x];
	else{
		int q = ++tot, qt = T[p].To[x];
		T[q] = T[qt];
		T[q].len = T[p].len + 1;
		T[qt].fail = T[Nt].fail = q;
		for (;p && T[p].To[x] == qt; p = T[p].fail) T[p].To[x] = q;
	}
	Lst = Nt;
}
bool cmp(int a, int b){
	return T[a].len < T[b].len;
}
void sort(){
	for (int i = 1; i <= tot; i++) heap[T[i].len]++;  
	for (int i = 1; i <= n; i++) heap[i] += heap[i-1];  
	for (int i = 1; i <= tot; i++) Ord[heap[T[i].len]--]=i;  
}
int main(){
	scanf("%s", s + 1);
	n = strlen(s + 1);
	Root = tot = Lst = 1;
	for (int i = 1; i <= n; i++)
		Add(s[i] - 'a' + 1, i);
	sort();
	memset(Ways , 0, sizeof(Ways));
	for (int i = 1, p = Root; i <= n; i++)
		p = T[p].To[s[i] - 'a' + 1], Ways[p] = 1;
	for (int i = tot; i >= 1; i--){
		int Cur = Ord[i];
		if (T[Cur].fail == 0) continue;
		Ways[T[Cur].fail] += Ways[Cur];
	}
	for (int i = 1; i <= tot; i++)
		Ans[T[i].len] = max(Ans[T[i].len], Ways[i]);
	for (int i = n; i >= 1; i--)
		Ans[i] = max(Ans[i + 1], Ans[i]);
	for (int i = 1; i <= n; i++)
		printf("%d\n", Ans[i]);
	return 0;
}
