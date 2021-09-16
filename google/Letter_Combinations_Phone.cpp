/*

17

Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent. Return the answer in any order.

A mapping of digit to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.



 

Example 1:

Input: digits = "23"
Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
Example 2:

Input: digits = ""
Output: []
Example 3:

Input: digits = "2"
Output: ["a","b","c"]
 

Constraints:

0 <= digits.length <= 4
digits[i] is a digit in the range ['2', '9'].


基本思想：

暴力搜索
不需要set去重

*/
#include <map>
#include <string>
#include <vector>
#include <set>
using namespace std;

class Solution {
    map<char, vector<char>> phone_button;
    vector<string> results;
    int tail;
    string my_digits;
public:
    vector<string> letterCombinations(string digits) {
        if(digits == ""){
            return vector<string>();
        }

        phone_button['2'] = vector<char>({'a', 'b', 'c'});
        phone_button['3'] = vector<char>({'d', 'e', 'f'});
        phone_button['4'] = vector<char>({'g', 'h', 'i'});
        phone_button['5'] = vector<char>({'j', 'k', 'l'});
        phone_button['6'] = vector<char>({'m', 'n', 'o'});
        phone_button['7'] = vector<char>({'p', 'q', 'r', 's'});
        phone_button['8'] = vector<char>({'t', 'u', 'v'});
        phone_button['9'] = vector<char>({'w', 'x', 'y', 'z'});

        tail = digits.size();
        my_digits = digits;

        string origin = "";
        search_str(origin, 0);

        return results;
    }

    void search_str(string pre, int pos){
        if(pos >= tail){
            results.push_back(pre);
            return;
        }
        
        vector<char> *cur_v = &phone_button[my_digits[pos]];
        int cur_size = cur_v->size();
        for(int i = 0;i < cur_size;i++){
            string tmp = pre + (*cur_v)[i];
            search_str(tmp, pos + 1);
        }

        return;
    }
};