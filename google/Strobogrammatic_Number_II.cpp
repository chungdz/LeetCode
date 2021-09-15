#include<string>
#include<vector>
#include<algorithm>
using namespace std;

/*
247

Strobogrammatic Number II
Given an integer n, return all the strobogrammatic numbers that are of length n. You may return the answer in any order.

A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

 

Example 1:

Input: n = 2
Output: ["11","69","88","96"]
Example 2:

Input: n = 1
Output: ["0","1","8"]
 

Constraints:

1 <= n <= 14


基本思想

暴力搜索合规字符，注意第一个位置不能放0

由题意，数字应该是对称的，或者是6转9，9转6，所以暴力搜索前半部分就能知道后半部分

**/

class Solution {
    int number_to_choose[5] = {0, 1, 8, 6, 9};
    int half;
    int mid;
    vector<string> res;
public:
    vector<string> findStrobogrammatic(int n) {
        half = n / 2;
        mid = n % 2;

        string pre = "";
        search_valid(0, pre);
        return res;
    }

    void search_valid(int index, string cur_string){
        if(index >= half){
            string tmp = cur_string;
            string tmp2 = cur_string;
            reverse(tmp2.begin(), tmp2.end());
            for(int k = 0;k < index;++k){
                if(tmp2[k] == '6'){tmp2[k] = '9';}
                else if(tmp2[k] == '9'){tmp2[k] = '6';}
            }
            if(mid != 0){
                for(int i = 0;i < 3;++i){
                    string midc = "";
                    midc.push_back(number_to_choose[i] + '0');
                    res.push_back(tmp + midc + tmp2);
                }
            }
            else{
                res.push_back(tmp + tmp2);
            }

            return;
        }

        for(int i = 0;i < 5;++i){
            if(index == 0 && i == 0){continue;}
            string tmp = cur_string;
            tmp.push_back(number_to_choose[i] + '0');
            search_valid(index + 1, tmp);
        }

        return;
    }
};