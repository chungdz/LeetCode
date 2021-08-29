#include<queue>
#include<map>
#include<vector>
#include<algorithm>
#include<string>
#include<climits>
using namespace std;

/*
127 

A transformation sequence from word beginWord to word endWord using a dictionary wordList is a sequence of words beginWord -> s1 -> s2 -> ... -> sk such that:

Every adjacent pair of words differs by a single letter.
Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to be in wordList.
sk == endWord
Given two words, beginWord and endWord, and a dictionary wordList, return the number of words in the shortest transformation sequence from beginWord to endWord, or 0 if no such sequence exists.

 

Example 1:

Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
Output: 5
Explanation: One shortest transformation sequence is "hit" -> "hot" -> "dot" -> "dog" -> cog", which is 5 words long.
Example 2:

Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
Output: 0
Explanation: The endWord "cog" is not in wordList, therefore there is no valid transformation sequence.
 

Constraints:

1 <= beginWord.length <= 10
endWord.length == beginWord.length
1 <= wordList.length <= 5000
wordList[i].length == beginWord.length
beginWord, endWord, and wordList[i] consist of lowercase English letters.
beginWord != endWord
All the words in wordList are unique.


基本思想

单源最短路径dijkstra

把每个字符串当成节点，根据字符串比较建立边，找到最短路径

由于边长固定为1，用广度优先搜索也可以

优化字符匹配方式，对每个词，构建新的词，只是把其中一个字符替换成“*”，把新的字符也看成节点，连接节点和当前词
如果节点已经存在了，用map来快速搜索节点

这样会使得路径翻倍

**/

#define WINF 100000

struct CustomCompare
{
    bool operator()(const pair<int, int>& lhs, const pair<int, int>& rhs)
    {
        return lhs.first > rhs.first;
    }
};

class Solution {
    map<int, vector<int>> node_edges;
    int distance[6000];
    priority_queue<pair<int, int>, vector<pair<int, int>>, CustomCompare> dque;

    bool cmp_s(string s1, string s2){
        int slen = s1.size();
        int diff = 0;
        for(int i = 0;i < slen;++i){
            if(s1[i] != s2[i]){
                diff += 1;
                if(diff > 1){
                    return false;
                }
            }
        }

        return true;
    }
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        // add beginWord in the wordlist
        wordList.insert(wordList.begin(), beginWord);
        int listlen = wordList.size();
        // init node and find index of start node and end node
        int sindex = 0, eindex = -1;
        for(int i = 0;i < listlen;++i){
            node_edges[i] = vector<int>();
            if(endWord == wordList[i]){
                eindex = i;
            }
        }
        if(eindex == -1){return 0;}
        // build graph
        for(int i = 0;i < listlen - 1;++i){
            for(int j = i + 1;j < listlen;++j){
                if(cmp_s(wordList[i], wordList[j])){
                    node_edges[i].push_back(j);
                    node_edges[j].push_back(i);
                }
            }
        }
        // dijistra
        distance[0] = 0;
        for(int i = 1;i < listlen;++i){
            distance[i] = WINF;
        }

        dque.push(pair<int, int>(0, 0));
        while(!dque.empty()){
            pair<int, int> cur_node = dque.top();
            dque.pop();
            if(distance[cur_node.second] < cur_node.first) continue;
            for(int neighbor: node_edges[cur_node.second]){
                if(distance[neighbor] > cur_node.first + 1){
                    distance[neighbor] = cur_node.first + 1;
                    dque.push(pair<int, int>(distance[neighbor], neighbor));
                }
            }
        }

        if(distance[eindex] == WINF){return 0;}
        return distance[eindex] + 1;
    }
};

class Solution {
public:
    unordered_map<string, int> wordId;
    vector<vector<int>> edge;
    int nodeNum = 0;

    void addWord(string& word) {
        if (!wordId.count(word)) {
            wordId[word] = nodeNum++;
            edge.emplace_back();
        }
    }

    void addEdge(string& word) {
        addWord(word);
        int id1 = wordId[word];
        for (char& it : word) {
            char tmp = it;
            it = '*';
            addWord(word);
            int id2 = wordId[word];
            edge[id1].push_back(id2);
            edge[id2].push_back(id1);
            it = tmp;
        }
    }

    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        for (string& word : wordList) {
            addEdge(word);
        }
        addEdge(beginWord);
        if (!wordId.count(endWord)) {
            return 0;
        }
        vector<int> dis(nodeNum, INT_MAX);
        int beginId = wordId[beginWord], endId = wordId[endWord];
        dis[beginId] = 0;

        queue<int> que;
        que.push(beginId);
        while (!que.empty()) {
            int x = que.front();
            que.pop();
            if (x == endId) {
                return dis[endId] / 2 + 1;
            }
            for (int& it : edge[x]) {
                if (dis[it] == INT_MAX) {
                    dis[it] = dis[x] + 1;
                    que.push(it);
                }
            }
        }
        return 0;
    }
};