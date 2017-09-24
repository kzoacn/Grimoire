void Rotate(int x, int c){
	int y = T[x].c[c];
	int z = T[y].c[1 - c];
	
	if (T[x].fa){
		if (T[T[x].fa].c[0] == x) T[T[x].fa].c[0] = y;
		else T[T[x].fa].c[1] = y;
	}
	
	T[z].fa = x; T[x].c[c] = z;
	T[y].fa = T[x].fa; T[x].fa = y; T[y].c[1 - c] = x;
	
	Update(x);
	Update(y);
}

int stack[M], fx[M];

void Splay(int x, int fa){
	int top = 0;
	for (int  u = x; u != fa; u = T[u].fa)
		stack[++top] = u;
	for (int i = 2; i <= top; i++)
		if (T[stack[i]].c[0] == stack[i - 1]) fx[i] = 0;
		else fx[i] = 1;
	
	for (int i = 2; i <= top; i += 2){
		if (i == top) Rotate(stack[i], fx[i]);
		else {
			if (fx[i] == fx[i + 1]){
				Rotate(stack[i + 1], fx[i + 1]);
				Rotate(stack[i], fx[i]);
			} else {
				Rotate(stack[i], fx[i]);
				Rotate(stack[i + 1], fx[i + 1]);
			}
		}
	}
	
	if (fa == 0) Root = x;
}
