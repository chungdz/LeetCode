#include<string>
#include<vector>
#include<algorithm>
using namespace std;

/*

425

Given an array of unique strings words, return all the word squares you can build from words. The same word from words can be used multiple times. You can return the answer in any order.

A sequence of strings forms a valid word square if the kth row and column read the same string, where 0 <= k < max(numRows, numColumns).

For example, the word sequence ["ball","area","lead","lady"] forms a word square because each word reads the same both horizontally and vertically.
 

Example 1:

Input: words = ["area","lead","wall","lady","ball"]
Output: [["ball","area","lead","lady"],["wall","area","lead","lady"]]
Explanation:
The output consists of two word squares. The order of output does not matter (just the order of words in each word square matters).
Example 2:

Input: words = ["abat","baba","atan","atal"]
Output: [["baba","abat","baba","atal"],["baba","abat","baba","atan"]]
Explanation:
The output consists of two word squares. The order of output does not matter (just the order of words in each word square matters).
 

Constraints:

1 <= words.length <= 1000
1 <= words[i].length <= 5
All words[i] have the same length.
words[i] consists of only lowercase English letters.
All words[i] are unique.

基本思路

迭代搜索，剪枝

剪枝方式：确定第i行的单词，就确定了第i列的形状，在搜索下一行时，需要满足前i列已经预设的情况

将词汇按字典序排序，把预设情况的前缀填充上a和z来作为搜索上下限，用lower bound二分搜索快速找到对应单词


**/

class Solution {
    vector<string> squares;
    int wsize;
    vector<vector<string>> res;
public:
    vector<vector<string>> wordSquares(vector<string>& words) {
        sort(words.begin(), words.end());
        wsize = words[0].size();
        for(int i = 0;i < wsize;++i){
            squares.push_back(string(wsize, 'a'));
        }

        vector<string> record;
        search_squares(record, words, 0);

        return res;
    }

    void search_squares(vector<string>& record, vector<string>& words, int cur_index){
        if(cur_index == wsize){
            res.push_back(record);
            record.pop_back();
            return;
        }

        vector<string>::iterator wbegin, wend;
        if(cur_index == 0){
            wbegin = words.begin();
            wend = words.end();
        }
        else{
            string header = squares[cur_index].substr(0, cur_index);
            string beginstr = header + string(wsize - cur_index, 'a');
            string endstr = header + string(wsize - cur_index, 'z');

            wbegin = lower_bound(words.begin(), words.end(), beginstr);
            wend = wbegin;
            // wend = upper_bound(words.begin(), words.end(), endstr);
            while(wend != words.end() && *wend <= endstr){++wend;}
        }

        if(wend == wbegin){
            if(record.size() > 0){record.pop_back();}
            return;
        }
        for(vector<string>::iterator it = wbegin;it != wend;++it){
            squares[cur_index] = *it;
            record.push_back(*it);
            for(int j = cur_index + 1;j < wsize;++j){
                squares[j][cur_index] = squares[cur_index][j];
            }
            search_squares(record, words, cur_index + 1);
        }

        if(record.size() > 0){record.pop_back();}
        return;
    }

};