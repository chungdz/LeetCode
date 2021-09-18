#include<string>
#include<unordered_map>
#include<algorithm>
using namespace std;

/*
246

Strobogrammatic Number

Solution
Given a string num which represents an integer, return true if num is a strobogrammatic number.

A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

 

Example 1:

Input: num = "69"
Output: true
Example 2:

Input: num = "88"
Output: true
Example 3:

Input: num = "962"
Output: false
Example 4:

Input: num = "1"
Output: true
 

Constraints:

1 <= num.length <= 50
num consists of only digits.
num does not contain any leading zeros except for zero itself.

基本思想

把对应关系找好，用map保存，然后检查

**/

class Solution {
    int number_to_choose[5] = {0, 1, 8, 6, 9};
    int number_good[5] = {0, 1, 8, 9, 6};
    unordered_map<int, int> record;
public:
    bool isStrobogrammatic(string num) {
        for(int i = 0;i < 5;++i){
            record[number_to_choose[i]] = number_good[i];
        }

        int ns = num.size();
        int ends = ns / 2;
        for(int i = 0;i <= ends;++i){
            int cur_num = num[i] - '0';
            if(record.find(cur_num) == record.end()){return false;}
            if(num[ns - 1 - i] - '0' != record[cur_num]){return false;}
        }
        return true;
    }
};