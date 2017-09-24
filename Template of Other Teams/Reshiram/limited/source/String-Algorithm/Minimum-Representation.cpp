int minrep(const char *s) {
	int length = strlen(s), i = 0, j = 1, k = 0;
	while (i < length && j < length && k < length) {
		if (s[(i + k) % length] == s[(j + k) % length]) k++;
		else {
			if (s[(i + k) % length] > s[(j + k) % length]) i += k + 1;
			else j += k + 1;
			if (i == j) j++;
			k = 0;
		}
	}
	return std::min(i, j);
}
