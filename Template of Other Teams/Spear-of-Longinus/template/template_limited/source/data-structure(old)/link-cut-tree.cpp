class Node {
public:
    T data, sum;
    Node *father, *vfather;
    Node *child[2];
    int index;
    bool reverse;
    
    Node() {}
    
    Node(int index, const T &data) : index(index), data(data) {
        sum = data;
        father = NULL;
        vfather = NULL;
        child[0] = NULL;
        child[1] = NULL;
    }
    
    void update() {
        if (child[0]) {
            child[0]->release();
        }
        if (child[1]) {
            child[1]->release();
        }
        sum = (child[0] ? child[0]->sum : T()) + data + (child[1] ? child[1]->sum : T());
    }
    
    void release() {
        if (reverse) {
            if (child[0]) {
                child[0]->reverse ^= 1;
            }
            if (child[1]) {
                child[1]->reverse ^= 1;
            }
            std::swap(child[0], child[1]);
            reverse = false;
        }
    }
};

void rotate(Node *x, bool dir){
    Node *y = x->father;
    if (y->father) {
        y->father->child[y->father->child[1] == y] = x;
    }
    x->father = y->father;
    x->vfather = y->vfather;
    y->vfather = NULL;
    if (x->child[dir ^ 1]) {
        x->child[dir ^ 1]->father = y;
    }
    y->child[dir] = x->child[dir ^ 1];
    x->child[dir ^ 1] = y;
    y->father = x;
    y->update();
}

void splay(Node *x, Node *target = NULL){
    for (x->release(); x->father != target; ) {
        Node *y = x->father;
        if (y->father == target){
            y->release();
            x->release();
            bool dir = (y->child[1] == x);
            rotate(x, dir);
        } else {
            y->father->release();
            y->release();
            x->release();
            bool dir = (y->child[1] == x);
            if ((y->father->child[1] == y) == dir) {
                rotate(y, dir);
                rotate(x, dir);
            } else {
                rotate(x, dir);
                rotate(x, dir ^ 1);
            }
        }
    }
    x->update();
}

Node* access(Node *x){
    splay(x);
    if (x->child[0]) {
        x->release();
        x->child[0]->vfather = x;
        x->child[0]->father = NULL;
        x->child[0] = NULL;
        x->update();
    }
    Node *y = x;
    if (x->vfather) {
        y = access(x->vfather);
        x->vfather->child[0] = x;
        x->father = x->vfather;
        x->vfather->update();
    }
    splay(x);
    return y;
}

void addEdge(Node *x, Node *y) {
    access(x);
    Node *w = access(y);
    splay(x);
    if (x->vfather == w || x == w) {
        throw "Circle exists";
    }
    x->reverse ^= 1;
    access(y);
    y->child[0] = x;
    x->father = y;
    y->update();
}

void eraseEdge(Node *x, Node *y) {
    if (x == y) {
        throw "Not connected";
    }
    access(x);
    if (access(y) == x){
        splay(x, y);
        if (x->child[0]) {
            throw "Not connected";
        }
        y->release();
        y->child[1]->father = NULL;
        y->child[1]->vfather = NULL;
        y->child[1] = NULL;
        y->update();
    } else {
        splay(x);
        if (x->vfather != y || x->child[1]) {
            throw "Not connected";
        }
        access(x);
        x->release();
        x->child[1]->father = NULL;
        x->child[1]->vfather = NULL;
        x->child[1] = NULL;
        x->update();
    }
}

void modify(Node *x, const T &v) {
    access(x);
    x->data = v;
    x->update();
}

T query(Node *x, Node *y) {
    access(x);
    Node *u = access(y);
    T sum = u->data;
    splay(u);
    if (u->child[0]) {
        sum = sum + u->child[0]->sum;
    }
    access(x);
    splay(u);
    if (u->child[0]) {
        sum = sum + u->child[0]->sum;
    }
    return sum;
}

Node* lca(Node *x, Node *y) {
    access(x);
    return access(y);
}

Node* root(Node *x) {
    access(x);
    for (; ; x = x->child[1]) {
        x->release();
        if (!x->child[1]) {
            break;
        }
    }
    return x;
}

void evert(Node *x) {
    access(x);
    x->reverse ^= 1;
}

int n;
std::vector<Node> node;

void build(const std::vector<std::pair<int, int> > &edge, const std::vector<T> &weight) {
    node.clear();
    for (int i = 0; i < n; ++i) {
        node.push_back(Node(i, weight[i]));
    }
    for (int i = 0; i < (int)edge.size(); ++i) {
        int x = edge[i].first, y = edge[i].second;
        if (root(x) == root(y)) {
            throw "Circle exists";
        }
        addEdge(x, y);
    }
}