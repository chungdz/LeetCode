#include<string>
#include<unordered_map>
#include<vector>
#include<unordered_set>
using namespace std;

/*
212 word search II

Given an m x n board of characters and a list of strings words, return all words on the board.

Each word must be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.

 

Example 1:


Input: board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], words = ["oath","pea","eat","rain"]
Output: ["eat","oath"]
Example 2:


Input: board = [["a","b"],["c","d"]], words = ["abcb"]
Output: []
 

Constraints:

m == board.length
n == board[i].length
1 <= m, n <= 12
board[i][j] is a lowercase English letter.
1 <= words.length <= 3 * 104
1 <= words[i].length <= 10
words[i] consists of lowercase English letters.
All the strings of words are unique.


基本思想：
用Tire保存所有待搜索的词汇
DFS每个格子
剪枝猜想
Trie删除某个词汇
**/

class Trie {
public:
    string word;
    bool has_word = false;
    unordered_map<char, Trie*> children;

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

class Solution {
    char search_record[13][13] = {0};
    int m, n;
    unordered_set<string> ans;
    vector<string> res;
    int direction[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    Trie *root;
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        m = board.size();
        n = board[0].size();
        // build trie
        root = new Trie();
        for(string w: words){
            root->insert(w);
        }
        // dfs all node
        for(int i = 0;i < m;++i){
            for(int j = 0;j < n;++j){
                char cur_c = board[i][j];
                Trie *cur_node = root->find_child(cur_c);
                if(cur_node != nullptr){
                    dfs(i, j, cur_node, board);
                }
            }
        }

        return vector<string>(ans.begin(), ans.end());
    }

    void dfs(int crow, int ccol, Trie *node, vector<vector<char>>& board){
        if(node->has_word){
            ans.insert(node->word);
        }

        search_record[crow][ccol] = 1;
        for(int d = 0;d < 4;++d){
            int nxt_row = crow + direction[d][0];
            int nxt_col = ccol + direction[d][1];
            if(nxt_row >= 0 && nxt_row < m && nxt_col >=0 && nxt_col < n && search_record[nxt_row][nxt_col] == 0){
                char nxt_c = board[nxt_row][nxt_col];
                Trie *nxt_node = node->find_child(nxt_c);
                if(nxt_node != nullptr){
                    dfs(nxt_row, nxt_col, nxt_node, board);
                }
            }
        }

        search_record[crow][ccol] = 0;
        return;
    }
};
