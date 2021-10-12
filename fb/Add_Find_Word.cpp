#include<string>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;

class Trie {
public:
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
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        vector<Trie*> nodes = search_prefix(word, 0);
        for(Trie* n: nodes){
            if(n->has_word){
                return true;
            }
        }
        return false;
    }

    vector<Trie*> search_prefix(string prefix, int index){
        vector<Trie*> res;
        if(index == prefix.size()){
            res.push_back(this);
            return res;
        }

        char c = prefix[index];
        if(c == '.'){
            for(auto cp: children){
                for(Trie* n: cp.second->search_prefix(prefix, index + 1)){
                    res.push_back(n);
                }
            }
        }
        else if(children.find(c) != children.end()){
            for(Trie* n: children[c]->search_prefix(prefix, index + 1)){
                    res.push_back(n);
            }
        }
        
        return res;
    }
};

/*
211 Add and Search Word - Data structure design
Design a data structure that supports adding new words and finding if a string matches any previously added string.

Implement the WordDictionary class:

WordDictionary() Initializes the object.
void addWord(word) Adds word to the data structure, it can be matched later.
bool search(word) Returns true if there is any string in the data structure that matches word or false otherwise. word may contain dots '.' where dots can be matched with any letter.
 

Example:

Input
["WordDictionary","addWord","addWord","addWord","search","search","search","search"]
[[],["bad"],["dad"],["mad"],["pad"],["bad"],[".ad"],["b.."]]
Output
[null,null,null,null,false,true,true,true]

Explanation
WordDictionary wordDictionary = new WordDictionary();
wordDictionary.addWord("bad");
wordDictionary.addWord("dad");
wordDictionary.addWord("mad");
wordDictionary.search("pad"); // return False
wordDictionary.search("bad"); // return True
wordDictionary.search(".ad"); // return True
wordDictionary.search("b.."); // return True
 

Constraints:

1 <= word.length <= 500
word in addWord consists lower-case English letters.
word in search consist of  '.' or lower-case English letters.
At most 50000 calls will be made to addWord and search.

基本思想

Trie的变式，搜索的时候用迭代而不是loop
第一个类返回所有合规的word

**/

class Trie2 {
public:
    bool has_word = false;
    map<char, Trie2*> children;

    /** Initialize your data structure here. */
    Trie2() {}
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        Trie2 *cur_node = this;
        for(char c: word){
            if(cur_node->children.find(c) == cur_node->children.end()){
                Trie2 *nc = new Trie2();
                cur_node->children[c] = nc;
            }
            cur_node = cur_node->children[c];
        }
        cur_node->has_word = true;
    }

    bool search_prefix(string prefix, int index){
        bool res = false;
        if(index == prefix.size() && has_word){
            return true;
        }

        char c = prefix[index];
        if(c == '.'){
            for(auto cp: children){
                res |= cp.second->search_prefix(prefix, index + 1);
                if(res){
                    return true;
                }
            }
        }
        else if(children.find(c) != children.end()){
            res |=  children[c]->search_prefix(prefix, index + 1);
        }
        
        return res;
    }
};

class WordDictionary {
    Trie2* root;
public:
    WordDictionary() {
        root = new Trie2();
    }
    
    void addWord(string word) {
        root->insert(word);
    }
    
    bool search(string word) {
        return root->search_prefix(word, 0);
    }
};
