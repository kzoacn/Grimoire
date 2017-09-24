class Node {
public:
    Node *child[256], *parent;
    int length;
    
    Node(int length = 0) : parent(NULL), length(length) {
        memset(child, NULL, sizeof(child));
    }
    
    Node* extend(Node *start, int token) {
        Node *p = this;
        Node *np = new Node(length + 1);
        for (; p && !p->child[token]; p = p->parent) {
            p->child[token] = np;
        }
        if (!p) {
            np->parent = start;
        } else {
            Node *q = p->child[token];
            if (p->length + 1 == q->length) {
                np->parent = q;
            } else {
                Node *nq = new Node(p->length + 1);
                memcpy(nq->child, q->child, sizeof(q->child));
                nq->parent = q->parent;
                np->parent = q->parent = nq;
                for (; p && p->child[token] == q; p = p->parent) {
                    p->child[token] = nq;
                }
            }
        }
        return np;
    }
};
