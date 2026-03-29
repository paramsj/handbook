#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // for PBDS
#include <ext/pb_ds/tree_policy.hpp> // for PBDS
using namespace __gnu_pbds; // for PBDS
using namespace std;
#define int long long int
const int MOD = 1000000007;

template<typename T>
using ordered_set = tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;
// less_equal will make it multiset
// less makes it set
void solve() {

}

signed main() {
ios_base::sync_with_stdio(false);
cin.tie(NULL);
ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // orz
cin.exceptions(cin.failbit); // orz
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
