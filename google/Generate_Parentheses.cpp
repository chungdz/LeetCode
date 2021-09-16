/*

22

Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

 

Example 1:

Input: n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]
Example 2:

Input: n = 1
Output: ["()"]
 

Constraints:

1 <= n <= 8

基本思想

只有左括号超过右括号数量时，才能生成右括号

暴力搜索，要么放左，要么放右

直到左括号数量等于n并且右括号生成完毕
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