class Node {
public:
    Node *child[256], *fail;
    int counter;

    Node() : fail(NULL), counter(0) {
        memset(child, NULL, sizeof(child));
    }
};

void insert(Node *x, char *text) {
    int length = (int)strlen(text);
    for (int i = 0; i < length; ++i) {
        int token = (int)text[i];
        if (!x->child[token]) {
            x->child[token] = new Node();
        }
        x = x->child[token];
    }
    x->counter++;
}

void build() {
    std::vector<Node*> queue;
    queue.push_back(root->fail = root);
    for (int head = 0; head < (int)queue.size(); ++head) {
        Node *x = queue[head];
        for (int token = 0; token < 256; ++token) {
            if (x->child[token]) {
                x->child[token]->fail = (x == root) ? root : x->fail->child[token];
                x->child[token]->counter += x->child[token]->fail->counter;
                queue.push_back(x->child[token]);
            } else {
                x->child[token] = (x == root) ? root : x->fail->child[token];
            }
        }
    }
}
