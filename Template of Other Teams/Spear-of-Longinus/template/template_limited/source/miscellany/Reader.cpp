
namespace Reader {
	const int L = (1 << 20) + 5;
	char buffer[L], *S, *T;
	__inline bool getchar(char &ch) {
		if (S == T) {
			T = (S = buffer) + fread(buffer, 1, L, stdin);
			if (S == T) {
				ch = EOF;
				return false;
			}
		}
		ch = *S ++;
		return true;
	}
	__inline bool getint(int &x) {
		char ch;
		for (; getchar(ch) && (ch < '0' || ch > '9'); );
		if (ch == EOF) return false;
		x = ch - '0';
		for (; getchar(ch), ch >= '0' && ch <= '9'; )
			x = x * 10 + ch - '0';
		return true;
	}
}
Reader::getint(x);
Reader::getint(y);
