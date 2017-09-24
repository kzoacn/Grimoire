int height[N], parent[N][20];

int lca(int x, int y) {
    if (height[x] < height[y]) {
        std::swap(x, y);
    }
    for (int i = 0; i < 20; ++i) {
        if (height[x] - height[y] >> i & 1) {
            x = parent[x][i];
        }
    }
    if (x == y) {
        return x;
    }
    for (int i = 19; i >= 0; --i) {
        if (parent[x][i] != parent[y][i]) {
            x = parent[x][i];
            y = parent[y][i];
        }
    }
    return parent[x][0];
}

void build(int root) {
    std::vector<int> queue;
    std::fill(height, height + n, -1);
    queue.push_back(root);
    height[root] = 0;
    for (int head = 0; head < (int)queue.size(); ++head) {
        int x = queue[head];
        for (int i = 0; i < (int)edge[x].size(); ++i) {
            int y = edge[x][i];
            if (height[y] == -1) {
                height[y] = height[x] + 1;
                parent[y][0] = x;
                queue.push_back(y);
            }
        }
    }
    for (int step = 1; step < 20; ++step) {
        for (int i = 0; i < n; ++i) {
            if (parent[i][step - 1] == -1) {
                parent[i][step] = -1;
            } else {
                parent[i][step] = parent[parent[i][step - 1]][step - 1];
            }
        }
    }
}