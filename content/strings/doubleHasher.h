/**
 * Author: Simon Lindholm
 * Date: 2015-03-15
 * License: CC0
 * Source: own work
 * Description: Various self-explanatory methods for string hashing.
 * Use on Codeforces, which lacks 64-bit support and where solutions can be hacked.
 * Status: stress-tested
 */

struct hasher {
    int base;
    int mod;
    vector<int> hash;
    vector<int> basepow;
    vector<int> rHash;

    hasher() {}

    hasher(string s, int _base = 37, int _mod = 1e9 + 7) {
        base = _base;
        mod = _mod;
        int n = s.size();
        s = "#" + s + "#"; 
        
        hash.resize(n + 2);
        basepow.resize(n + 2);
        rHash.resize(n + 2);

        hash[0] = 0;
        basepow[0] = 1;

        for (int i = 1; i <= n; i++) {
            hash[i] = (hash[i - 1] * base + (s[i] - 'a' + 1)) % mod;
            basepow[i] = (basepow[i - 1] * base) % mod;
        }

        rHash[n + 1] = 0;
        for (int i = n; i >= 1; i--) {
            rHash[i] = (rHash[i + 1] * base + (s[i] - 'a' + 1)) % mod;
        }
    }

    int getHash(int l, int r) {
        int res = hash[r];
        res -= (basepow[r - l + 1] * hash[l - 1]) % mod;
        res = (res % mod + mod) % mod;
        return res;
    }
    int getRevHash(int l, int r) {
        int res = rHash[l];
        res -= (basepow[r - l + 1] * rHash[r + 1]) % mod;
        res = (res % mod + mod) % mod;
        return res;
    }

    bool isPalindrome(int l, int r) {
        return getHash(l, r) == getRevHash(l, r);
    }
};

struct doubleHasher{
    hasher hash1,hash2;
    
    doubleHasher() {
        
    }
    
    doubleHasher(string s) {
        hash1 = hasher(s, 53, 1000000007); 
        hash2 = hasher(s, 53, 9999999937);
    }
    
    int getHash(int l,int r) {
        return (1LL<<32)*hash1.getHash(l,r) + hash2.getHash(l,r);
    }
};
