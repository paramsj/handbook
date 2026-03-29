/**
 * Author: Simon Lindholm
 * Date: 2017-05-11
 * License: CC0
 * Source: folklore
 * Description: Computes sums a[i,j] for all i<I, j<J, and increases single elements a[i,j].
 *  Requires that the elements to be updated are known in advance (call fakeUpdate() before init()).
 * Time: $O(\log^2 N)$. (Use persistent segment trees for $O(\log N)$.)
 * Status: stress-tested
 */

struct BIT {
    int n,m;
    vector<vector<int>> bit;
 
    BIT(int n,int m) : n(n),m(m),bit(n+1,vector<int> (m+1)){}
 
    void update(int r, int c,int v) {
        r++;
        c++;
        for (; r <= n; r += r & -r) {
            for (int i = c; i <= m; i += i & -i) { bit[r][i] += v; }
        }
    }
 
    int query(int r,int c) {
        r++;
        c++;
        int sum = 0;
        for (; r > 0; r -= r & -r) {
            for (int i = c; i > 0; i -= i & -i) { sum += bit[r][i]; }
        }
        return sum;
    }
};
