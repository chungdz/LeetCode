#include<string>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;

/*

212

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
1 <= words.length <= 3 * 10^4
1 <= words[i].length <= 10
words[i] consists of lowercase English letters.
All the strings of words are unique.


基本思想

前缀树的应用

如果根据每个单词来搜索全路径，时间复杂度将是 words.length * dfs(all)

剪枝操作也不会改变第一个值的大小

反过来，如果搜索全路径，然后匹配路径对应的单词，时间复杂度是df(all) * 匹配效率
前缀树可以大大提升匹配的时间，因为它可以用节点和路径对应，所以匹配时间复杂度是O(1)


**/

/*

S1:

暴力搜索，记录每个word的第一个位置减少搜索时间

**/

class Solution {
    char search_record[13][13] = {0};
    int m, n;
    map<char, vector<pair<int, int>>> char_pos;
    vector<string> res;
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        m = board.size();
        n = board[0].size();
        // record first c
        for(int i = 0;i < m;++i){
            for(int j = 0;j < n;++j){
                char c = board[i][j];
                if(char_pos.find(c) == char_pos.end()){
                    char_pos[c] = vector<pair<int, int>>();
                }
                char_pos[c].push_back(pair<int, int>(i, j));
            }
        }
        for(string w: words){
            for(auto p: char_pos[w[0]]){
                if(search_w(0, p.first, p.second, w, board)){
                    break;
                }
            }
        }

        return res;
    }

    bool search_w(int cur_index, int crow, int ccol, string w, vector<vector<char>>& board){
        if(cur_index == w.size() - 1){
            res.push_back(w);
            return true;
        }

        search_record[crow][ccol] = 1;
        bool isfind = false;

        int nxt_index = cur_index + 1;
        char nxt_c = w[nxt_index];
        // start search
        int up_row = crow - 1;
        if(up_row >= 0 && search_record[up_row][ccol] == 0 && board[up_row][ccol] == nxt_c){
            isfind = search_w(nxt_index, up_row, ccol, w, board);
            if(isfind){
                search_record[crow][ccol] = 0;
                return true;
            }
        }
        int left_col = ccol - 1;
        if(left_col >= 0 && search_record[crow][left_col] == 0 && board[crow][left_col] == nxt_c){
            isfind = search_w(nxt_index, crow, left_col, w, board);
            if(isfind){
                search_record[crow][ccol] = 0;
                return true;
            }
        }
        int down_row = crow + 1;
        if(down_row < m && search_record[down_row][ccol] == 0 && board[down_row][ccol] == nxt_c){
            isfind = search_w(nxt_index, down_row, ccol, w, board);
            if(isfind){
                search_record[crow][ccol] = 0;
                return true;
            }
        }
        int right_col = ccol + 1;
        if(right_col < n && search_record[crow][right_col] == 0 && board[crow][right_col] == nxt_c){
            isfind = search_w(nxt_index, crow, right_col, w, board);
            if(isfind){
                search_record[crow][ccol] = 0;
                return true;
            }
        }

        search_record[crow][ccol] = 0;
        return isfind;
    }
};

/*

S2

在S1的基础上记录了每个位置的邻居信息，可以直接根据邻居信息搜索


**/


class Solution {
    char search_record[13][13] = {0};
    int m, n;
    map<char, vector<pair<int, int>>> char_pos;
    map<char, vector<pair<int, int>>> neighbors[13][13];
    vector<string> res;
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        m = board.size();
        n = board[0].size();
        // record first c
        for(int i = 0;i < m;++i){
            for(int j = 0;j < n;++j){
                char c = board[i][j];
                if(char_pos.find(c) == char_pos.end()){
                    char_pos[c] = vector<pair<int, int>>();
                }
                char_pos[c].push_back(pair<int, int>(i, j));

                // record neighbor characters
                int up = i - 1;
                if(up >= 0){
                    char upc = board[up][j];
                    if(neighbors[i][j].find(upc) == neighbors[i][j].end()){
                        neighbors[i][j][upc] = vector<pair<int, int>>();
                    }
                    neighbors[i][j][upc].push_back(pair<int, int>(up, j));
                }
                int left = j - 1;
                if(left >= 0){
                    char leftc = board[i][left];
                    if(neighbors[i][j].find(leftc) == neighbors[i][j].end()){
                        neighbors[i][j][leftc] = vector<pair<int, int>>();
                    }
                    neighbors[i][j][leftc].push_back(pair<int, int>(i, left));
                }
                int down = i + 1;
                if(down < m){
                    char downc = board[down][j];
                    if(neighbors[i][j].find(downc) == neighbors[i][j].end()){
                        neighbors[i][j][downc] = vector<pair<int, int>>();
                    }
                    neighbors[i][j][downc].push_back(pair<int, int>(down, j));
                }
                int right = j + 1;
                if(right < n){
                    char rightc = board[i][right];
                    if(neighbors[i][j].find(rightc) == neighbors[i][j].end()){
                        neighbors[i][j][rightc] = vector<pair<int, int>>();
                    }
                    neighbors[i][j][rightc].push_back(pair<int, int>(i, right));
                }
            }
        }
        for(string w: words){
            for(auto p: char_pos[w[0]]){
                if(search_w(0, p.first, p.second, w, board)){
                    break;
                }
            }
        }

        return res;
    }

    bool search_w(int cur_index, int crow, int ccol, string w, vector<vector<char>>& board){
        if(cur_index == w.size() - 1){
            res.push_back(w);
            return true;
        }

        search_record[crow][ccol] = 1;
        bool isfind = false;

        int nxt_index = cur_index + 1;
        char nxt_c = w[nxt_index];
        // start search
        for(auto np: neighbors[crow][ccol][nxt_c]){
            int nxt_row = np.first;
            int nxt_col = np.second;
            if(search_record[nxt_row][nxt_col] == 0){
                isfind = search_w(nxt_index, nxt_row, nxt_col, w, board);
                if(isfind){
                    break;
                }
            }
        }

        search_record[crow][ccol] = 0;
        return isfind;
    }
};

/*

S3

word 多而搜索的borad小，改用针对borad全搜索，使用前缀树判断路径是不是合规

然后将能搜索到树叶的路径记录

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

class Solution {
    char search_record[13][13] = {0};
    int m, n;
    set<string> ans;
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
