class Node {
public:
    Node *child[2], *father;
    int size;
    int key;

    Node(int key = 0);

    int side() {
        return father->child[1] == this;
    }

    void set(Node *son, int dir) {
        child[dir] = son;
        son->father = this;
    }

    void modify();

    void update() {
        size = child[0]->size + 1 + child[1]->size;
    }

    void release();
};

Node *null, *root;

Node::Node(int key) : size(1), key(key) {
    child[0] = child[1] = father = null;
}

void Node::modify() {
    if (this == null) {
        return;
    }
}

void rotate(Node *x) {
    int dir = x->side();
    Node *p = x->father;
    p->release();
    x->release();
    p->set(x->child[dir ^ 1], dir);
    p->father->set(x, p->side());
    x->set(p, dir ^ 1);
    if (p == root) {
        root = x;
    }
    p->update();
    x->update();
}

void splay(Node *x, Node *target = null) {
    for (x->release(); x->father != target; ) {
        if (x->father->father == target) {
            rotate(x);
        } else {
            x->side() == x->father->side() 
            ? (rotate(x->father), rotate(x))
            : (rotate(x), rotate(x));
        }
    }
    x->update();
}

Node* kth(int size) {
    Node *x = root;
    for (; x->child[0]->size + 1 != size; ) {
        x->release();
        if (x->child[0]->size + 1 > size) {
            x = x->child[0];
        } else {
            size -= x->child[0]->size + 1;
            x = x->child[1];
        }
    }
    return x;
}

void select(int left, int right) {
    splay(kth(right + 2));
    splay(kth(left), root);
}

void insert(int pos, int n, int key[]) {
    select(pos, pos - 1);
    Node *x = root->child[0];
    for (int i = 0; i < n; ++i) {
        Node *now = new Node(key[i]);
        x->set(now, 1);
        x = now;
    }
    splay(x);
}

void solve(int left, int right) {
    select(left, right);
    root->child[0]->child[1]->solve();
    root->child[0]->update();
    root->update();
}

void build() {
    null = new Node();
    null->size = 0;
    root = new Node();
    Node *blank = new Node();
    root->set(blank, 1);
    splay(blank);
}