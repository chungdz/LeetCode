/*

22

 括号生成
数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。

 

示例：

输入：n = 3
输出：[
       "((()))",
       "(()())",
       "(())()",
       "()(())",
       "()()()"
     ]
*/
#include <string>
#include <vector>
using namespace std;

class Solution {
    vector<string> result;
public:
    vector<string> generateParenthesis(int n) {
        search_space(n, 0, "");
        return result;
    }

    void search_space(int left, int right, string cur_str){
        if(left == 0 && right == 0){
            result.push_back(cur_str);
            return;
        }

        if(right > 0){
            string new_str = cur_str + ")";
            search_space(left, right - 1, new_str);
        }
        if(left > 0){
            string new_str = cur_str + "(";
            search_space(left - 1, right + 1, new_str);
        }

        return;
    }
};