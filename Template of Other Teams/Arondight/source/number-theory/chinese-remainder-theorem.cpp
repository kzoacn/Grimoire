// 返回 (ans, M)，其中ans是模M意义下的解
std::pair<long long, long long> CRT(const std::vector<long long>& m, const std::vector<long long>& a) {
	long long M = 1, ans = 0;
	int n = m.size();
	for (int i = 0; i < n; i++) M *= m[i];
	for (int i = 0; i < n; i++) {
		ans = (ans + (M / m[i]) * a[i] % M * inv(M / m[i], m[i])) % M;  // 可能需要大整数相乘取模
	}
	return std::make_pair(ans, M);
}
// 模数不互质的情况
bool solve(int n, std::pair<long long, long long> input[],
                  std::pair<long long, long long> &output) {
	output = std::make_pair(1, 1);
	for (int i = 0; i < n; ++i) {
		long long number, useless;
		// euclid(a, b, x, y)
		euclid(output.second, input[i].second, number, useless);
		long long divisor = std::__gcd(output.second, input[i].second);
		if ((input[i].first - output.first) % divisor) return false;
		number *= (input[i].first - output.first) / divisor;
		fix(number, input[i].second);	// fix 成正的
		output.first += output.second * number;
		output.second *= input[i].second / divisor;
		fix(output.first, output.second);
	}
	return true;
}
