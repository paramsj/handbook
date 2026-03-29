/**
 * Author: Simon Lindholm
 * Date: 2016-10-08
 * License: CC0
 * Source: me
 * Description: Segment tree with ability to add or set values of large intervals, and compute max of intervals.
 * Can be changed to other things.
 * Use with a bump allocator for better performance, and SmallPtr or implicit indices to save memory.
 * Time: O(\log N).
 * Usage: Node* tr = new Node(v, 0, sz(v));
 * Status: stress-tested a bit
 */

struct Node {
    int sum;
    int lazy_add;
    int lazy_set;
    Node(int sum,int lazy_add,int lazy_set) : sum(sum),lazy_add(lazy_add),lazy_set(lazy_set) {}
    Node() : sum(0),lazy_add(0),lazy_set(-1) {}
};

Node merge(Node a,Node b) {
    return Node(a.sum+b.sum,0,-1);
}

vector<Node> tree;

void apply_add(int idx,int l,int r,int val) {
    tree[idx].sum += (r-l+1)*val;
    if(tree[idx].lazy_set!=-1) {
        tree[idx].lazy_set += val;
    } else {
        tree[idx].lazy_add += val;
    }
}

void apply_set(int idx,int l,int r,int val) {
    tree[idx].sum = (r-l+1)*val;
    tree[idx].lazy_set = val;
    tree[idx].lazy_add = 0;
}

void build(int idx,int l,int r,vector<int> &a) {
    if(l==r) {
        tree[idx] = {a[l],0,-1};
        return;
    }
    int mid = (l+r)/2;
    build(2*idx,l,mid,a);
    build(2*idx + 1,mid + 1,r,a);
    tree[idx] = merge(tree[2*idx],tree[(2*idx)+ 1]);
}

void push(int idx,int l,int r) {
    if(l==r) {
        return;
    }
    int mid = (l+r)/2;
    if(tree[idx].lazy_set!=-1) {
        apply_set(2*idx,l,mid,tree[idx].lazy_set);
        apply_set(2*idx + 1,mid + 1,r,tree[idx].lazy_set);
        tree[idx].lazy_set = -1;
    }
    if(tree[idx].lazy_add!=0) {
        apply_add(2*idx,l,mid,tree[idx].lazy_add);
        apply_add(2*idx + 1,mid + 1,r,tree[idx].lazy_add);
        tree[idx].lazy_add = 0;
    }
}

Node query(int idx,int tl,int th,int ql,int qh) {
    if(ql<=tl && th<=qh) {
        return tree[idx];
    }
    if(ql>th || qh<tl) {
        return Node();
    }
    int mid = (tl+th)/2;
    push(idx,tl,th);
    return merge(query(2*idx,tl,mid,ql,qh),query(2*idx + 1,mid+1,th,ql,qh));
}


void update(int idx,int tl,int th,int ql,int qh,int val,int type) {
    if(ql>th || qh<tl) {
        return;
    }

    if(ql<=tl && th<=qh) {
        if(type==1) {
            // assign
            apply_set(idx,tl,th,val);
        } else if(type==2) {
            apply_add(idx,tl,th,val);
            // add
        }
        return;
    }
    int mid = (tl+th)/2;
    push(idx,tl,th);
    update(2*idx,tl,mid,ql,qh,val,type);
    update(2*idx + 1,mid + 1,th,ql,qh,val,type);
    tree[idx] = merge(tree[2*idx],tree[2*idx + 1]);
}

// // Usage : 

// tree.resize(4*N);
// build(1,1,N,a);
// update(1,1,N,l,r,v,1);
// update(1,1,N,l,r,v,2);
// query(1,1,N,l,r).sum;
