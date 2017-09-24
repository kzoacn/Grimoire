void Manacher(){
	R[1] = 1;
	for (int i = 2, j = 1; i <= length; i++){
		if (j + R[j] <= i){
			R[i] = 0;
		} else {
			R[i] = min(R[j * 2 - i], j + R[j] - i);
		}
		while (i - R[i] >= 1 && i + R[i] <= length 
			&& text[i - R[i]] == text[i + R[i]]){
			R[i]++;
		}
		if (i + R[i] > j + R[j]){
			j = i;
		}
	}
}
	length = 0;
	int n = strlen(s + 1);
	for (int i = 1; i <= n; i++){
		text[++length] = '*';
		text[++length] = s[i];
	}
	text[++length] = '*';
/// Hints: 1 - Base
