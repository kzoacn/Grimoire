int manacher(char *text, int length, int *palindrome) {
	static char buffer[MAXN];
	for (int i = 1; i <= length; i++) {
		buffer[2 * i - 1] = text[i];
		if (i != 0) buffer[2 * i] = '#';
	}
	
	palindrome[1] = 1;
	for (int i = 2, j = 0; i <= 2 * length - 1; ++i) {
		if (j + palindrome[j] <= i) {
			palindrome[i] = 0;
		} else {
			palindrome[i] = std::min(palindrome[(j << 1) - i], j + palindrome[j] - i);
		}
		while (i - palindrome[i] >= 1 && i + palindrome[i] <= 2 * length - 1
			&& buffer[i - palindrome[i]] == buffer[i + palindrome[i]]) {
			palindrome[i]++;
		}
		if (i + palindrome[i] > j + palindrome[j]) {
			j = i;
		}
	}
	
	int answer = 0;
	for (int i = 1; i < 2 * length; i++) {
		if (i & 1) answer = std::max(answer, 2 * (palindrome[i] - 1 >> 1) + 1);
		else answer = std::max(answer, 2 * (palindrome[i] >> 1));
	}
	return answer;
}
