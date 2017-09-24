
void Add(int x,int l)
{
	int Nt = ++ tot,p = Lst;
	T[Nt].len = l;
	for(;p && !T[p].To[x];p = T[p].fail) T[p].To[x] = Nt;
	if (!p) T[Nt].fail = S; else
		if (T[T[p].To[x]].len == T[p].len + 1) T[Nt].fail = T[p].To[x]; else
		{
			int q = ++ tot,qt = T[p].To[x];
			T[q] = T[qt];
			T[q].len = T[p].len + 1;
			T[qt].fail = T[Nt].fail = q;
			for(;p && T[p].To[x] == qt;p = T[p].fail) T[p].To[x] = q;
		}
	Lst = Nt;
}

for(int i = 1;i <= N;i ++) Add(s[i - 1] - 'a',i);
