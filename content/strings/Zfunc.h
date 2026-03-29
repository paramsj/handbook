/**
 * Author: chilli
 * License: CC0
 * Description: z[i] computes the length of the longest common prefix of s[i:] and s,
 * except z[0] = 0. (abacaba -> 0010301)
 * Time: O(n)
 * Status: stress-tested
 */
#pragma once

vi z_function(string s) {
    int n = ssize(s);
    vi z(n, 0);
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r) z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[i + z[i]] == s[z[i]]) z[i]++;
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    // z[0] = n; // add if you need z[0]=n
    return z;
}

int z_algorithm(string text, string pat) { // Find occurrences of pat in text
    auto z = z_function(pat + '\0' + text);
    int res = 0;
    for (int i = 0; i < ssize(text) - ssize(pat) + 1; i++)
        if (z[i + ssize(pat) + 1] == ssize(pat))
            res++; // occurrence starting at text[i] found
    return res;
}