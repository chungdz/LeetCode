#include<string>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;

/*
208

A trie (pronounced as "try") or prefix tree is a tree data structure used to efficiently store and retrieve keys in a dataset of strings. There are various applications of this data structure, such as autocomplete and spellchecker.

Implement the Trie class:

Trie() Initializes the trie object.
void insert(String word) Inserts the string word into the trie.
boolean search(String word) Returns true if the string word is in the trie (i.e., was inserted before), and false otherwise.
boolean startsWith(String prefix) Returns true if there is a previously inserted string word that has the prefix prefix, and false otherwise.
 

Example 1:

Input
["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
[[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
Output
[null, null, true, false, true, null, true]

Explanation
Trie trie = new Trie();
trie.insert("apple");
trie.search("apple");   // return True
trie.search("app");     // return False
trie.startsWith("app"); // return True
trie.insert("app");
trie.search("app");     // return True
 

Constraints:

1 <= word.length, prefix.length <= 2000
word and prefix consist only of lowercase English letters.
At most 3 * 104 calls in total will be made to insert, search, and startsWith.



基本思想

建立自己可用的前缀树


**/

class Trie {
public:
    string word;
    bool has_word = false;
    map<char, Trie*> children;

    /** Initialize your data structure here. */
    Trie() {}
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        Trie *cur_node = this;
        for(char c: word){
            if(cur_node->children.find(c) == cur_node->children.end()){
                Trie *nc = new Trie();
                cur_node->children[c] = nc;
            }
            cur_node = cur_node->children[c];
        }
        cur_node->has_word = true;
        cur_node->word = word;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        Trie *wnode = search_prefix(word);
        if(wnode != nullptr && wnode->has_word){return true;}
        return false;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        if(search_prefix(prefix) != nullptr){return true;}
        return false;
    }

    Trie* search_prefix(string prefix){
        Trie *cur_node = this;
        for(char c: prefix){
            if(cur_node->children.find(c) == cur_node->children.end()){
                return nullptr;
            }
            cur_node = cur_node->children[c];
        }
        return cur_node;
    }

    Trie* find_child(char c){
        Trie *cur_node = this;
        if(cur_node->children.find(c) == cur_node->children.end()){
            return nullptr;
        }
        cur_node = cur_node->children[c];
        return cur_node;
    }
};