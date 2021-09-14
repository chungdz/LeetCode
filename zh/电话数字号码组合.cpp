/*

17

电话号码的字母组合
给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。

给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。



示例:

输入："23"
输出：["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
说明:
尽管上面的答案是按字典序排列的，但是你可以任意选择答案输出的顺序。
*/
#include <map>
#include <string>
#include <vector>
#include <set>
using namespace std;

/*
暴力组合，set去重
*/
class Solution {
    map<char, vector<char>> phone_button;
    set<string> results;
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

        return vector<string>(results.begin(), results.end());
    }

    void search_str(string pre, int pos){
        if(pos >= tail){
            results.insert(pre);
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