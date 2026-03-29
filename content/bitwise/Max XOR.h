/**
 * Author: Lukas Polacek
 * Date: 2009-10-30
 * License: CC0
 * Source: folklore/TopCoder
 * Description: Using Tries to extract max subarray XOR
 * Time: Both operations are $O(\log N)$.
 * Status: Stress-tested
 */

struct trie {
   int val;
   trie* arr[2];
   trie() {
       arr[0] = NULL;
       arr[1] = NULL;
   }
};
void insert(trie *root,int n) {
   trie* temp = root;
   for(int i=32;i>=0;i--) {
       bool x = n&(1LL<<i);
       if(temp->arr[x]!=NULL) {
           temp = temp->arr[x];
       } else {
           temp->arr[x] = new trie();
           temp = temp->arr[x];
       }
   }
   temp->val = n;
}
int query(trie *root,int n) {
   trie* temp = root;
   for(int i=32;i>=0;i--) {
       bool x = n&(1LL<<i);
       if(temp->arr[!x]!=NULL) {
           temp = temp->arr[!x];
       } else if(temp->arr[x]!=NULL) {
           temp = temp->arr[x];
       }
   }
   return n^temp->val;
}
//Usage :
//trie *root = new trie();
