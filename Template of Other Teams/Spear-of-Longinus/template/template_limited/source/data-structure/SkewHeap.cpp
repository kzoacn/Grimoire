struct node;
node *Null,*root[maxn];
struct node{
	node* c[2];
	int val,ind;
	node(int _val=0,int _ind=0){
		val=_val;c[0]=c[1]=Null;ind=_ind;
	}
};
node* merge(node *p,node *q){
	if(p==Null)return q;
	if(q==Null)return p;
	if(p->val>q->val)swap(p,q);
	p->c[1]=merge(p->c[1],q);
	swap(p->c[0],p->c[1]);
	return p;
}

Null=new node(0);
Null->c[0]=Null->c[1]=Null;

