int father[N], height[N], size[N], son[N], top[N], pos[N], data[N];

void build(int root) {
    std::vector<int> queue;
    father[root] = -1;
    height[root] = 0;
    queue.push_back(root);
    for (int head = 0; head < (int)queue.size(); ++head) {
        int x = queue[head];
        for (int i = 0; i < (int)edge[x].size(); ++i) {
            int y = edge[x][i];
            if (y != father[x]) {
                father[y] = x;
                height[y] = height[x] + 1;
                queue.push_back(y);
            }
        }
    }
    for (int index = n - 1; index >= 0; --index) {
        int x = queue[index];
        size[x] = 1;
        son[x] = -1;
        for (int i = 0; i < (int)edge[x].size(); ++i) {
            int y = edge[x][i];
            if (y != father[x]) {
                size[x] += size[y];
                if (son[x] == -1 || size[son[x]] < size[y]) {
                    son[x] = y;
                }
            }
        }
    }
    std::fill(top, top + n, 0);
    int counter = 0;
    for (int index = 0; index < n; ++index) {
        int x = queue[index];
        if (top[x] == 0) {
            for (int y = x; y != -1; y = son[y]) {
                top[y] = x;
                pos[y] = ++counter;
                data[counter] = value[y];
            }
        }
    }
    build(1, 1, n);
}

void solve(int x, int y) {
    while (true) {
        if (top[x] == top[y]) {
            if (x == y) {
                solve(1, 1, n, pos[x], pos[x]);
            } else {
                if (height[x] < height[y]) {
                    solve(1, 1, n, pos[x], pos[y]);
                } else {
                    solve(1, 1, n, pos[y], pos[x]);
                }
            }
            break;
        }
        if (height[top[x]] > height[top[y]]) {
            solve(1, 1, n, pos[top[x]], pos[x]);
            x = father[top[x]];
        } else {
            solve(1, 1, n, pos[top[y]], pos[y]);
            y = father[top[y]];
        }
    }
}