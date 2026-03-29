/**
 * Author: Lukas Polacek
 * Date: 2009-10-30
 * License: CC0
 * Source: folklore/TopCoder
 * Description: XOR Basis for Max Subset Xor and Number of Subsets 
 * Time: Both operations are $O(\log N)$.
 * Status: Stress-tested
 */


void solve() {
    int n;
    cin>>n;
    vector<int> a(n);
    for(int i=0;i<n;i++) {
        cin>>a[i];
    }
    sort(a.begin(),a.end());
    int index = 0;
    for(int i=32;i>=0;i--) {
        int temp = -1;
        for(int j=index;j<n;j++) {
            if(a[j]&(1LL<<i)) {
                temp = j;
                break;
            }
        }
        if(temp==-1) {
            continue;
        }
        swap(a[index],a[temp]);
        for(int j=0;j<n;j++) {
            if(a[j]&(1LL<<i) && j!=index) {
                a[j] = a[j]^a[index];
            }
        }
        index++;
    }
    int ans = 0;
    for(int i=0;i<n;i++) {
        ans = max(ans,ans^a[i]);
    }
    cout<<ans<<endl;
}
