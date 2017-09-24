int log2[N];
std::pair<int, int> value[N][20];

void build(int length, int number[]) {
    for (int i = 2; i <= length; ++i) {
        log2[i] = log2[i >> 1] + 1;
    }
    for (int i = 1; i <= length; ++i) {
        value[i][0] = std::make_pair(number[i], i);
    }
    for (int step = 1; (1 << step) <= length; ++step) {
        for (int i = 1; i + (1 << step) - 1 <= length; ++i) {
            value[i][step] = std::min(value[i][step - 1], value[i + (1 << step - 1)][step - 1]);
        }
    }
}

std::pair<int, int> get(int left, int right) {
    int step = log2[right - left + 1];
    return std::min(value[left][step], value[right - (1 << step) + 1][step]);
}