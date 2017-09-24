class Rope {
private:
    class Node {
    public:
        Node *left, *right;
        int size;
        char key;
        
        Node(char key = 0, Node *left = NULL, Node *right = NULL)
               : key(key), left(left), right(right) {
            update();
        }
        
        void update() {
            size = (left ? left->size : 0) + 1 + (right ? right->size : 0);
        }
        
        std::string to_string() {
            return (left ? left->to_string() : "") + key
                 + (right ? right->to_string() : "");
        }
    };
    
    bool random(int a, int b) {
        return rand() % (a + b) < a;
    }
    
    Node* merge(Node *x, Node *y) {
        if (!x) {
            return y;
        }
        if (!y) {
            return x;
        }
        if (random(x->size, y->size)) {
            return new Node(x->key, x->left, merge(x->right, y));
        } else {
            return new Node(y->key, merge(x, y->left), y->right);
        }
    }
    
    std::pair<Node*, Node*> split(Node *x, int size) {
        if (!x) {
            return std::make_pair<Node*, Node*>(NULL, NULL);
        }
        if (size == 0) {
            return std::make_pair<Node*, Node*>(NULL, x);
        }
        if (size > x->size) {
            return std::make_pair<Node*, Node*>(x, NULL);
        }
        if (x->left && size <= x->left->size) {
            std::pair<Node*, Node*> part =
                split(x->left, size);
            return std::make_pair(part.first, new Node(x->key, part.second, x->right));
        } else {
            std::pair<Node*, Node*> part =
                split(x->right, size - (x->left ? x->left->size : 0) - 1);
            return std::make_pair(new Node(x->key, x->left, part.first), part.second);
        }
    }
    
    Node* build(const std::string &text, int left, int right) {
        if (left > right) {
            return NULL;
        }
        int mid = left + right >> 1;
        return new Node(text[mid],
                        build(text, left, mid - 1),
                        build(text, mid + 1, right));
    }

public:
    Node *root;
    
    Rope() {
        root = NULL;
    }
    
    Rope(const std::string &text) {
        root = build(text, 0, (int)text.length() - 1);
    }
    
    Rope(const Rope &other) {
        root = other.root;
    }
    
    Rope& operator = (const Rope &other) {
        if (this == &other) {
            return *this;
        }
        root = other.root;
        return *this;
    }
    
    int size() {
        return root ? root->size : 0;
    }
    
    void insert(int pos, const std::string &text) {
        if (pos < 0 || pos > size()) {
            throw "Out of range";
        }
        std::pair<Node*, Node*> part = split(root, pos);
        root = merge(merge(part.first, build(text, 0, (int)text.length() - 1)),
                     part.second);
    }

    void erase(int left, int right) {
        if (left < 0 || left >= size() ||
            right < 1 || right > size()) {
            throw "Out of range";
        }
        if (left >= right) {
            return;
        }
        std::pair<Node*, Node*> part = split(root, left);
        root = merge(part.first, split(part.second, right - left).second);
    }
    
    std::string substr(int left, int right) {
        if (left < 0 || left >= size() ||
            right < 1 || right > size()) {
            throw "Out of range";
        }
        if (left >= right) {
            return "";
        }
        return split(split(root, left).second, right - left).first->to_string();
    }
    
    void copy(int left, int right, int pos) {
        if (left < 0 || left >= size() ||
            right < 1 || right > size() ||
            pos < 0 || pos > size()) {
            throw "Out of range";
        }
        if (left >= right) {
            return;
        }
        std::pair<Node*, Node*> part = split(root, pos);
        root = merge(merge(part.first,
                           split(split(root, left).second, right - left).first),
                     part.second);
    }
};