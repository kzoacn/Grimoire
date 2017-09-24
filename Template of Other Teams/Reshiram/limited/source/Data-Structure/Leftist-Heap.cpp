class Node {
public:
	Node *left, *right;
	int key, dist;
	Node(int key) : left(NULL), right(NULL), key(key), dist(0) {}
	Node* update() {
		if (!left || (right && left->dist < right->dist)) std::swap(left, right);
		dist = right ? right->dist + 1 : 0;
		return this;
	}
};
Node* merge(Node *x, Node *y) {
	if (!x) return y;
	if (!y) return x;
	if (x->key < y->key) {
		x = new Node(*x);
		x->right = merge(x->right, y);
		return x->update();
	} else {
		y = new Node(*y);
		y->right = merge(x, y->right);
		return y->update();
	}
}
