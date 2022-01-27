#include<string>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;

/*
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