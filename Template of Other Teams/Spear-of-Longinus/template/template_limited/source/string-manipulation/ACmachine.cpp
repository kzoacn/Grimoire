
struct Node{
	int Next[30], fail, mark;
}Tree[N];

void Init(){
	memset(Tree, 0, sizeof Tree);
	cnt = 1;
	
	for (int i = 1; i <= n; i++){
		char c;
		int now = 1;
		scanf("%s", s + 1);
		int Length = strlen(s + 1);
		for (int j = 1; j <= Length; j++){
			c = s[j];
			if (Tree[now].Next[c - 'a']) now = Tree[now].Next[c - 'a']; else
				Tree[now].Next[c - 'a'] = ++ cnt, now = cnt;
		}
	}
}

void Build_Ac(){
	int en = 0;
	Q[0] = 1;
	for (int fi = 0; fi <= en; fi++){
		int now = Q[fi];
		for (int next = 0; next < 26; next++)
			if (Tree[now].Next[next])
			{
				int k = Tree[now].Next[next];
				if (now == 1) Tree[k].fail = 1; else
				{
					int h = Tree[now].fail;
					while (h && !Tree[h].Next[next]) h = Tree[h].fail;
					if (!h) Tree[k].fail = 1; 
					else Tree[k].fail = Tree[h].Next[next];
				}
				Q[++ en] = k;
			}
	}
}

/// Hints : when not match , fail = 1
