class Node {
public:
    Node *left, *right;
    int size;

    Node();
    std::pair<Node*, Node*> split(int size);

    Node* update() {
        size = left->size + 1 + right->size;
        return this;
    }
};

bool random(int a, int b) {
    return rand() % (a + b) < a;
}

Node *null;

Node::Node() : left(null), right(null), size(1) {}

Node* merge(Node *x, Node *y) {
    if (x == null) {
        return y;
    }
    if (y == null) {
        return x;
    }
    if (random(x->size, y->size)) {
        x->right = merge(x->right, y);
        return x->update();
    } else {
        y->left = merge(x, y->left);
        return y->update();
    }
}

std::pair<Node*, Node*> Node::split(int size) {
    if (this == null) {
        return std::make_pair(null, null);
    }
    if (size <= left->size) {
        std::pair<Node*, Node*> result = left->split(size);
        left = null;
        return std::make_pair(result.first, merge(result.second, this->update()));
    } else {
        std::pair<Node*, Node*> result = right->split(size - left->size - 1);
        right = null;
        return std::make_pair(merge(this->update(), result.first), result.second);
    }
}

void build() {
    null = new Node();
    null->size = 0;
}