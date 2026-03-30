/**
 * Author: chilli
 * License: CC0
 * Description: Search, Delete, Add Words
 * Time: O(AlphaBet)
 * Status: stress-tested
 */

struct trieNode {
    trieNode* child[26];
    int freq;     // Number of words sharing this prefix
    int endCount; // Number of words ending exactly here

    trieNode() {
        for (int i = 0; i < 26; i++) child[i] = nullptr;
        freq = 0;
        endCount = 0;
    }
};

trieNode* root = new trieNode();

// Adds a string to the Trie
void add(string word) {
    trieNode* cur = root;
    cur->freq++; 
    for (char c : word) {
        int idx = c - 'a';
        if (!cur->child[idx]) {
            cur->child[idx] = new trieNode();
        }
        cur = cur->child[idx];
        cur->freq++;
    }
    cur->endCount++;
}

// Counts occurrences of a specific word
int countWord(string word) {
    trieNode* cur = root;
    for (char c : word) {
        int idx = c - 'a';
        if (!cur->child[idx] || cur->child[idx]->freq == 0) return 0;
        cur = cur->child[idx];
    }
    return cur->endCount;
}

// Checks if a word exists (at least once)
bool search(string word) {
    return countWord(word) > 0;
}

// Deletes one instance of a string
void del(string word) {
    if (countWord(word) == 0) return; // Word doesn't exist, nothing to delete

    trieNode* cur = root;
    cur->freq--;
    for (char c : word) {
        int idx = c - 'a';
        trieNode* next = cur->child[idx];
        next->freq--;
        cur = next;
    }
    cur->endCount--;
}