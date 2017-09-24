class Node {
public:
    Node *left, *right;
    int value;

    Node(Node *left, Node *right, int value) : left(left), right(right), value(value) {}

    Node* modify(int l, int r, int ql, int qr, int delta);
    int query(int l, int r, int qx);
};

Node* null;

Node* Node::modify(int l, int r, int ql, int qr, int delta) {
    if (qr < l || r < ql) {
        return this;
    }
    if (ql <= l && r <= qr) {
        return new Node(this->left, this->right, this->value + delta);
    }
    int mid = l + r >> 1;
    return new Node(this->left->modify(l, mid, ql, qr, delta),
                    this->right->modify(mid + 1, r, ql, qr, delta),
                    this->value);
}

int Node::query(int l, int r, int qx) {
    if (qx < l || r < qx) {
        return 0;
    }
    if (qx <= l && r <= qx) {
        return this->value;
    }
    int mid = l + r >> 1;
    return this->left->query(l, mid, qx)
         + this->right->query(mid + 1, r, qx)
         + this->value;
}

void build() {
    null = new Node(NULL, NULL, 0);
    null->left = null->right = null;
}