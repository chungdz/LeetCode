#include<unordered_set>
#include<string>
#include<algorithm>
using namespace std;

/*

771

You're given strings jewels representing the types of stones that are jewels, and stones representing the stones you have. Each character in stones is a type of stone you have. You want to know how many of the stones you have are also jewels.

Letters are case sensitive, so "a" is considered a different type of stone from "A".

 

Example 1:

Input: jewels = "aA", stones = "aAAbbbb"
Output: 3
Example 2:

Input: jewels = "z", stones = "ZZ"
Output: 0

基本思想

map的应用


**/

class Solution {
public:
    int numJewelsInStones(string jewels, string stones) {
        unordered_set<char> jew_set;
        for(char jw: jewels){
            jew_set.insert(jw);
        }
        int cnt = 0;
        for(char st: stones){
            if(jew_set.find(st) != jew_set.end()){
                ++cnt;
            }
        }
        return cnt;
    }
};