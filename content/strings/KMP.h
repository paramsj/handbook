/**
 * Author: Johan Sannemo
 * Date: 2016-12-15
 * License: CC0
 * Description: pi[x] computes the length of the longest prefix of s that ends at x,
 * other than s[0...x] itself (abacaba -> 0010123).
 * Can be used to find all occurrences of a string.
 * Time: O(n)
 * Status: Tested on kattis:stringmatching
 */
#pragma once

vi pi_function(string s) {
    int n = ssize(s);
    vi pi(n, 0);
    for (int i = 1, j = 0; i < n; i++) {
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) pi[i] = ++j;
    }
    return pi;
}

// Find occurrences of pat in text
int kmp(string text, string pat) {
    auto pi = pi_function(pat);
    int res = 0;
    for (int i = 0, j = 0; i < ssize(text); i++) {
        while (j > 0 && text[i] != pat[j]) j = pi[j - 1];
        if (text[i] == pat[j]) ++j;
        if (j == ssize(pat))
            res++; // occurrence starting at text[i-pat.size()+1] found
    }
    return res;
}
