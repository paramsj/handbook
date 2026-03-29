/**
 * Author: Simon Lindholm
 * Date: 2015-03-15
 * License: CC0
 * Source: own work
 * Description: 
 * Suffix Automaton
 * Status: stress-tested
 * 
 * 
 * 
 * 
 */

struct state{
    int len,link;
    int next[26];
    // bool is_clone; // occurence counting
    // int first_pos; // finding first position
};

const int MAXN = 1e5;
state st[2*MAXN];
int sz,last;

void sa_init() {
    st[0].len = 0;
    st[0].link = -1;
    memset(st[0].next,-1,sizeof(st[0].next));
    sz = 1;
    last = 0;
}

void sa_extend(char c) {
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    // st[cur].is_clone = false;
    // st[cur].first_pos = st[cur].len - 1;
    memset(st[cur].next,-1,sizeof(st[cur].next));

    int p = last;
    int code = c - 'a';
    while(p!=-1 && st[p].next[code]==-1) {
        st[p].next[code] = cur;
        p = st[p].link;
    }
    if (p == -1) {
        st[cur].link = 0;
    } else {
        int q = st[p].next[code];
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        } else {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            st[clone].link = st[q].link;
            memcpy(st[clone].next, st[q].next, sizeof(st[q].next));
            // st[clone].is_clone = true;
            // st[clone].first_pos = st[q].first_pos;
            while (p != -1 && st[p].next[code] == q) {
                st[p].next[code] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}


