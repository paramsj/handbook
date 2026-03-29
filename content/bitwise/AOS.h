/**
 * Author: Lukas Polacek
 * Date: 2009-10-30
 * License: CC0
 * Source: folklore/TopCoder
 * Description: Addition and Subtraction Over Subsets
 * Time: Both operations are $O(\log N)$.
 * Status: Stress-tested
 */
// MLOG represents number of bits, MAXN is total masks (2^MLOG)
const lli MLOG = 20;
const lli MAXN = (1LL << MLOG);

// Forward 1: Subset Sum (SOS DP). Adds value of each element to all its supersets.
void forward1(lli dp[]) {
    for (int bit = 0; bit < MLOG; bit++) {
        for (int i = 0; i < MAXN; i++) {
            // Check if the specific bit is set in the current mask i
            if (i & (1 << bit)) {
                // dp[mask] = sum of dp[submask], moving from smaller to larger masks
                dp[i] += dp[i ^ (1 << bit)];
            }
        }
    }
}

// Backward 1: Inverse Subset Sum. Subtracts submask values to restore original array.
void backward1(lli dp[]) {
    for (int bit = 0; bit < MLOG; bit++) {
        // Iterate backward to reverse the prefix sum accumulation correctly
        for (int i = MAXN - 1; i >= 0; i--) {
            if (i & (1 << bit)) {
                // Subtract the contribution of the submask (where bit is 0)
                dp[i] -= dp[i ^ (1 << bit)];
            }
        }
    }
}

// Forward 2: Superset Sum. Adds value of each element to all its subsets.
void forward2(lli dp[]) {
    for (int bit = 0; bit < MLOG; bit++) {
        for (int i = MAXN - 1; i >= 0; i--) {
            // Check if the specific bit is set in the current mask i
            if (i & (1 << bit)) {
                // Add the value of the supermask to the submask (flipping bit from 1 to 0)
                dp[i ^ (1 << bit)] += dp[i];
            }
        }
    }
}

// Backward 2: Inverse Superset Sum. The inverse operation of forward2.
void backward2(lli dp[]) {
    for (int bit = 0; bit < MLOG; bit++) {
        // Iterate forward to reverse the superset accumulation correctly
        for (int i = 0; i < MAXN; i++) {
            if (i & (1 << bit)) {
                // Remove the contribution of the supermask from the submask
                dp[i ^ (1 << bit)] -= dp[i];
            }
        }
    }
}