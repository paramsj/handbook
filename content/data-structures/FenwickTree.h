/**
 * Author: Lukas Polacek
 * Date: 2009-10-30
 * License: CC0
 * Source: folklore/TopCoder
 * Description: Computes partial sums a[0] + a[1] + ... + a[pos - 1], and updates single elements a[i],
 * taking the difference between the old and new value.
 * Time: Both operations are $O(\log N)$.
 * Status: Stress-tested
 */

struct BIT {
    int size;
    vector<int> bit;
 
    BIT(int n) : size(n),bit(n+1){}
 
    void update(int x, int v) {
        x++;
        for (; x <= size; x += x & (-x)) { bit[x] += v; }
    }
    int query(int b) {
        b++;
        int result = 0;
        for (; b > 0; b -= b & (-b)) { result += bit[b]; }
        return result;
    }
 
};