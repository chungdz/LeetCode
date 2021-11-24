#include<queue>
#include<map>
#include<vector>
#include<algorithm>
#include<string>
#include<climits>
#include<unordered_set>
using namespace std;

/*
127 Word Ladder II

A transformation sequence from word beginWord to word endWord using a dictionary wordList is a sequence of words beginWord -> s1 -> s2 -> ... -> sk such that:

Every adjacent pair of words differs by a single letter.
Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to be in wordList.
sk == endWord
Given two words, beginWord and endWord, and a dictionary wordList, return all the shortest transformation sequences from beginWord to endWord, or an empty list if no such sequence exists. Each sequence should be returned as a list of the words [beginWord, s1, s2, ..., sk].

 

Example 1:

Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
Output: [["hit","hot","dot","dog","cog"],["hit","hot","lot","log","cog"]]
Explanation: There are 2 shortest transformation sequences:
"hit" -> "hot" -> "dot" -> "dog" -> "cog"
"hit" -> "hot" -> "lot" -> "log" -> "cog"
Example 2:

Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
Output: []
Explanation: The endWord "cog" is not in wordList, therefore there is no valid transformation sequence.
 

Constraints:

1 <= beginWord.length <= 5
endWord.length == beginWord.length
1 <= wordList.length <= 1000
wordList[i].length == beginWord.length
beginWord, endWord, and wordList[i] consist of lowercase English letters.
beginWord != endWord
All the words in wordList are unique.

基本思想

建立图，和word ladder I思想一样，用*代替某一个char作为中间值节点
从begin word宽搜所有词，得到每个词的最短距离
深度优先搜索 + 剪枝，剪枝根据最短距离来
*/

class Solution {
public:
    unordered_map<string, int> wordId;
    unordered_map<string, bool> wordType;
    unordered_map<int, string> Id2Word;
    vector<unordered_set<int>> edge;
    vector<vector<string>> res;
    vector<int> dis;
    vector<string> cur_path;

    int nodeNum = 0;
    int beginId, endId;

    void addWord(string& word, bool isMid) {
        if (!wordId.count(word)) {
            wordId[word] = nodeNum;
            Id2Word[nodeNum] = word;
            wordType[word] = isMid; 
            nodeNum += 1;
            edge.emplace_back();
        }
    }

    void addEdge(string& word) {
        addWord(word, false);
        int id1 = wordId[word];
        for (char& it : word) {
            char tmp = it;
            it = '*';
            addWord(word, true);
            int id2 = wordId[word];
            edge[id1].insert(id2);
            edge[id2].insert(id1);
            it = tmp;
        }
    }

    void dfs_all_path(int cur_id, int cur_dis){
        if(cur_dis > dis[cur_id])
            return;
        if(cur_id == endId){
            cur_path.push_back(Id2Word[cur_id]);
            res.push_back(cur_path);
            cur_path.pop_back();
            return;
        }
        string curw = Id2Word[cur_id];
        if(!wordType[curw])
            cur_path.push_back(curw);
        for(int next_id: edge[cur_id]){
            dfs_all_path(next_id, cur_dis + 1);
        }
        if(!wordType[curw])
            cur_path.pop_back();
        return;
    }

    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        for (string& word : wordList) {
            addEdge(word);
        }
        addEdge(beginWord);
        if (!wordId.count(endWord)) {
            return res;
        }
        dis = vector<int>(nodeNum, INT_MAX);
        beginId = wordId[beginWord];
        endId = wordId[endWord];
        dis[beginId] = 0;

        queue<int> que;
        que.push(beginId);
        while (!que.empty()) {
            int x = que.front();
            que.pop();
            for (int it : edge[x]) {
                if (dis[it] == INT_MAX) {
                    dis[it] = dis[x] + 1;
                    que.push(it);
                }
            }
        }
        if(dis[endId] != INT_MAX)
            dfs_all_path(beginId, 0);
        
        return res;
    }
};