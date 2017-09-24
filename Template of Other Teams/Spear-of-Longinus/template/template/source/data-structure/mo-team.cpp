struct node{
	int l, r, id;
	friend bool operator < (const node &a, const node &b){
		if (a.l / Block == b.l / Block) return a.r / Block < b.r / Block;
		return a.l / Block < b.l / Block;
	}
}q[N];
Block = int(sqrt(n));
for (int i = 1; i <= m; i++){
	scanf("%d%d", &q[i].l, &q[i].r);
	q[i].id = i;
}
sort(q + 1, q + 1 + m);	
Cur = a[1]; /// Hints: adjust by yourself
Le = Ri = 1;	
for (int i = 1; i <= m; i++){
	while (q[i].r > Ri) Ri++, ChangeRi(1, Le, Ri);
	while (q[i].l > Le) ChangeLe(-1, Le, Ri), Le++;
	while (q[i].l < Le) Le--, ChangeLe(1, Le, Ri);
	while (q[i].r < Ri) ChangeRi(-1, Le, Ri), Ri--;
	Ans[q[i].id] = Cur;
}
