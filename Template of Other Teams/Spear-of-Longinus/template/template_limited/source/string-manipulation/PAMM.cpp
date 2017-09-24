
const int N = 400005;

char s[N];
int Len;

struct Palindromic_Tree {
    int next[N][27];
    int fail[N];    
    int cnt[N];
    int num[N];     
    int len[N];     
    char S[N];      
    int last;       
    int n;          
    int p;          
	
    int newnode(int l)     
    {
        for(int i = 1; i <= 26; i++) next[p][i] = 0;
        cnt[p] = 0;
        num[p] = 0;
        len[p] = l;
		fail[p] = 0;
        return p++;
    }
    void init()  
    {
        p = 0;
        newnode(0);
        newnode(-1);
        last = 0;
        n = 0;
        S[n] = -1;
        fail[0] = 1;
    }
    int get_fail(int x)  
    {
        while (S[n - len[x] - 1] != S[n]) x = fail[x];
        return x;
    }
    void add(char c, int pos)
    {
        c = c - 'a' + 1;
        S[++ n] = c ;
        int cur = get_fail(last);
        if (!next[cur][c])     
        {
            int now = newnode(len[cur] + 2);
            fail[now] = next[get_fail(fail[cur])][c];
            next[cur][c] = now;
            num[now] = num[fail[now]] + 1;
        }
		last = next[cur][c] ;
        cnt[last]++;
    }
    void count()
    {
        for (int i = p - 1 ; i >= 0 ; -- i) cnt[fail[i]] += cnt[i] ;
    }
}T;

Len = strlen(s + 1);
		
T.init();
for (int i = 1; i <= Len; i++)
	T.add(s[i], i);
T.count();

