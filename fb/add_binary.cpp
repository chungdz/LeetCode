#include<string>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;

/**
67
Add Binary

Solution
Given two binary strings a and b, return their sum as a binary string.

 

Example 1:

Input: a = "11", b = "1"
Output: "100"
Example 2:

Input: a = "1010", b = "1011"
Output: "10101"
 

Constraints:

1 <= a.length, b.length <= 104
a and b consist only of '0' or '1' characters.
Each string does not contain leading zeros except for the zero itself.

基本思想

加法的应用
 * 
 */

class Solution {
public:
    string addBinary(string a, string b) {
        int index_a = a.size() - 1, index_b = b.size() - 1;

        int low = 0, high = 0;
        string s = "";
        while(index_a >= 0 || index_b >= 0){
            char cur_a, cur_b;
            if(index_a >= 0){cur_a = a[index_a];}
            else{cur_a = '0';}

            if(index_b >= 0){cur_b = b[index_b];}
            else{cur_b = '0';}

            int res = cur_a - '0' + cur_b - '0' + high;
            if(res > 1){
                high = 1;
                low = res - 2;
            }
            else{
                low = res;
                high = 0;
            }
            s.push_back(low + '0');

            index_a -= 1;
            index_b -= 1;
        }
        if(high > 0){
            s.push_back('1');
        }
        reverse(s.begin(), s.end());

        return s;
    }
};