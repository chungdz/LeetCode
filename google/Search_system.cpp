#include<string>
#include<vector>
#include<algorithm>
#include<map>
#include<unordered_map>
using namespace std;

/*

642

Design Search Autocomplete System
Design a search autocomplete system for a search engine. Users may input a sentence (at least one word and end with a special character '#').

You are given a string array sentences and an integer array times both of length n where sentences[i] is a previously typed sentence and times[i] is the corresponding number of times the sentence was typed. For each input character except '#', return the top 3 historical hot sentences that have the same prefix as the part of the sentence already typed.

Here are the specific rules:

The hot degree for a sentence is defined as the number of times a user typed the exactly same sentence before.
The returned top 3 hot sentences should be sorted by hot degree (The first is the hottest one). If several sentences have the same hot degree, use ASCII-code order (smaller one appears first).
If less than 3 hot sentences exist, return as many as you can.
When the input is a special character, it means the sentence ends, and in this case, you need to return an empty list.
Implement the AutocompleteSystem class:

AutocompleteSystem(String[] sentences, int[] times) Initializes the object with the sentences and times arrays.
List<String> input(char c) This indicates that the user typed the character c.
Returns an empty array [] if c == '#' and stores the inputted sentence in the system.
Returns the top 3 historical hot sentences that have the same prefix as the part of the sentence already typed. If there are fewer than 3 matches, return them all.
 

Example 1:

Input
["AutocompleteSystem", "input", "input", "input", "input"]
[[["i love you", "island", "iroman", "i love leetcode"], [5, 3, 2, 2]], ["i"], [" "], ["a"], ["#"]]
Output
[null, ["i love you", "island", "i love leetcode"], ["i love you", "i love leetcode"], [], []]

Explanation
AutocompleteSystem obj = new AutocompleteSystem(["i love you", "island", "iroman", "i love leetcode"], [5, 3, 2, 2]);
obj.input("i"); // return ["i love you", "island", "i love leetcode"]. There are four sentences that have prefix "i". Among them, "ironman" and "i love leetcode" have same hot degree. Since ' ' has ASCII code 32 and 'r' has ASCII code 114, "i love leetcode" should be in front of "ironman". Also we only need to output top 3 hot sentences, so "ironman" will be ignored.
obj.input(" "); // return ["i love you", "i love leetcode"]. There are only two sentences that have prefix "i ".
obj.input("a"); // return []. There are no sentences that have prefix "i a".
obj.input("#"); // return []. The user finished the input, the sentence "i a" should be saved as a historical sentence in system. And the following input will be counted as a new search.
 

Constraints:

n == sentences.length
n == times.length
1 <= n <= 100
1 <= sentences[i].length <= 100
1 <= times[i] <= 50
c is a lowercase English letter, a hash '#', or space ' '.
Each tested sentence will be a sequence of characters c that end with the character '#'.
Each tested sentence will have a length in the range [1, 200].
The words in each input sentence are separated by single spaces.
At most 5000 calls will be made to input.

基本思想

前缀树的应用

前缀树帮助查找相同前缀的子节点，剩下的用unordered_map去记录对应的数值，注意每次查询结尾"#"都是一次字符串更新


**/

class Trie {
public:
    
    int index;
    bool has_word = false;
    map<char, Trie*> children;

    /** Initialize your data structure here. */
    Trie() {}
    
    /** Inserts a word into the trie. */
    void insert(string word, int ind) {
        Trie *cur_node = this;
        for(char c: word){
            if(cur_node->children.find(c) == cur_node->children.end()){
                Trie *nc = new Trie();
                cur_node->children[c] = nc;
            }
            cur_node = cur_node->children[c];
        }
        cur_node->has_word = true;
        cur_node->index = ind;
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

    vector<int> all_words(string prefix){
        Trie *cur_node = search_prefix(prefix);
        vector<int> res;
        add_child(cur_node, res);
        return res;
    }

    void add_child(Trie *cur_node, vector<int>& res){
        if(cur_node == nullptr){return;}
        if(cur_node->has_word){
            res.push_back(cur_node->index);
        }
        for(auto p: cur_node->children){
            add_child(p.second, res);
        }
    }
};

bool cmp(const pair<string, int> &v, const pair<string, int> &v2){
    if(v.second == v2.second){
        return v.first < v2.first;
    }
    else{
        return v.second > v2.second;
    }
}

class AutocompleteSystem {
    Trie *sentence_record;
    string rec = "";
    vector<string> *m_sentences;
    vector<int> *m_times;
    unordered_map<string, int> pos_record;
public:
    AutocompleteSystem(vector<string>& sentences, vector<int>& times) {
        sentence_record = new Trie();
        int ssize = sentences.size();
        for(int i = 0;i < ssize;++i){
            sentence_record->insert(sentences[i], i);
            pos_record[sentences[i]] = i;
        }
        m_sentences = &sentences;
        m_times = &times;
    }
    
    vector<string> input(char c) {
        vector<int> index_res;
        vector<pair<string, int>> order_res;
        vector<string> res;
        if(c == '#'){
            if(pos_record.find(rec) == pos_record.end()){
                m_sentences->push_back(rec);
                m_times->push_back(1);
                sentence_record->insert(rec, m_sentences->size() - 1);
                pos_record[rec] = m_sentences->size() - 1;
            }
            else{
                int cur_ind = pos_record[rec];
                (*m_times)[cur_ind] += 1;
            }
            rec = "";
            return res;
        }

        rec.push_back(c);
        index_res = sentence_record->all_words(rec);
        for(int ind: index_res){
            order_res.push_back(pair<string, int>((*m_sentences)[ind], (*m_times)[ind]));
        }
        sort(order_res.begin(), order_res.end(), cmp);

        int os = order_res.size();
        for(int i = 0;i < os;++i){
            if(i == 3){break;}
            res.push_back(order_res[i].first);
        }

        return res;
    }
};
