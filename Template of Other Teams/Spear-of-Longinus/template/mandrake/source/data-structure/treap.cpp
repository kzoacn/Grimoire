class Node {
public:
    Node *child[2];
    int key;
    int size, priority;

    Node(Node *left, Node *right, int key) : key(key), size(1), priority(rand()) {
        child[0] = left;
        child[1] = right;
    }

    void update() {
        size = child[0]->size + 1 + child[1]->size;
    }
};

Node *null;

void rotate(Node *&x, int dir) {
    Node *y = x->child[dir];
    x->child[dir] = y->child[dir ^ 1];
    y->child[dir ^ 1] = x;
    x->update();
    y->update();
    x = y;
}

void insert(Node *&x, int key) {
    if (x == null) {
        x = new Node(null, null, key);
    } else {
        insert(x->child[key > x->key], key);
        if (x->child[key > x->key]->priority < x->priority) {
            rotate(x, key > x->key);
        }
        x->update();
    }
}

void remove(Node *&x, int key) {
    if (x->key != key) {
        remove(x->child[key > x->key], key);
    } else if (x->child[0] == null && x->child[1] == null) {
        x = null;
        return;
    } else {
        int dir = x->child[0]->priority > x->child[1]->priority;
        rotate(x, dir);
        remove(x->child[dir ^ 1], key);
    }
    x->update();
}

void build() {
    null = new Node(NULL, NULL, 0);
    null->child[0] = null->child[1] = null;
    null->size = 0;
    null->priority = RAND_MAX;
}