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
    Node(int sum) : sum(sum) {}
    Node() : sum(0) {}
};

Node merge(Node a,Node b) {
    return Node(a.sum + b.sum);
}

void build(int idx,int l,int r,vector<int> &a) {
    if(l==r) {
        tree[idx] = {a[l]};
        return;
    }
    int mid = (l+r)/2;
    build(2*idx,l,mid,a);
    build(2*idx + 1,mid + 1,r,a);
    tree[idx] = merge(tree[2*idx],tree[(2*idx)+ 1]);
}

Node query(int idx,int tl,int th,int ql,int qh) {
    if(ql>th || qh<tl) {
        return Node();
    }
    if(ql<=tl && th<=qh) {
        return tree[idx];
    }
    int mid = (tl+th)/2;
    return merge(query(2*idx,tl,mid,ql,qh),query(2*idx + 1,mid + 1,th,ql,qh));
}

    if(tl>pos || th<pos) {
        return;
    }
    if(tl==th) {
        tree[idx] = {val};
        return;
    }
    int mid = (tl+th)/2;
    update(2*idx,tl,mid,pos,val);
    update(2*idx + 1,mid + 1,th,pos,val);
    tree[idx] = merge(tree[2*idx],tree[2*idx + 1]);
}

// you can change the struct to whatever you want
tree.resize(4*N);
build(1,1,N,a);
update(1,1,N,pos,x);
query(1,1,N,l,r).sum;

