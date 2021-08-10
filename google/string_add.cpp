#include<string>
#include<algorithm>
using namespace std;

/***
 * 415
 * 
 * 大整数相加
 * 
 * 基本思想：
 * 从尾部相加，记录进位，最后反转字符串
 * 
 * 
 * 
 * 
*/

class Solution {
    int add_char(char c1, char c2, int high_n){
        int n1 = c1 - '0';
        int n2 = c2 - '0';
        return n1 + n2 + high_n;
    }
public:
    string addStrings(string num1, string num2) {
        int size1 = num1.size();
        int size2 = num2.size();
        string *shorts, *longs;
        int short_size, long_size;
        if(size1 <= size2){
            shorts = &num1;
            longs = &num2;
            short_size = size1;
            long_size = size2;
        }
        else{
            shorts = &num2;
            longs = &num1;
            short_size = size2;
            long_size = size1;
        }

        string result = "";
        int sp = short_size - 1;
        int lp = long_size - 1;
        int high_n = 0;
        int low_n;
        while(lp >= 0){
            int short_num;
            if(sp >= 0){short_num = shorts->at(sp);}
            else{short_num = '0';}

            int res = add_char(short_num, longs->at(lp), high_n);
            if(res > 9){
                high_n = 1;
                low_n = res - 10;
            }
            else{
                high_n = 0;
                low_n = res;
            }
            --sp;
            --lp;
            result.push_back(low_n + '0');
        }

        if(high_n > 0){
            result.push_back('1');
        }

        reverse(result.begin(), result.end());
        return result;
    }
};