#include<string>
#include<vector>
#include<algorithm>
using namespace std;

/***
 * 
 * 43
 * 
 * 大整数相乘
 * 
 * 基本思路
 * 乘数每个数字和被乘数相乘，得到的结果相加
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

    int mult_char(char c1, char c2, int high_n){
        int n1 = c1 - '0';
        int n2 = c2 - '0';
        return n1 * n2 + high_n;
    }

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
public:
    string multiply(string num1, string num2){
        string result = "0";
        if(num1 == "0" || num2 == "0"){return result;}

        int size1 = num1.size();
        int size2 = num2.size();
        
        int zeros = 0;
        for(int p = size1 - 1;p >= 0;--p, ++zeros){
            string tmp = "";
            char cur_num = num1[p];
            for(int j = 0;j < zeros;++j){tmp.push_back('0');}

            int high_n = 0, low_n;
            for(int k = size2 - 1;k >= 0;--k){
                int res = mult_char(cur_num, num2[k], high_n);
                if(res > 9){
                    high_n = res / 10;
                    low_n = res % 10;
                }
                else{
                    high_n = 0;
                    low_n = res;
                }
                tmp.push_back(low_n + '0');
            }
            if(high_n > 0){
                tmp.push_back(high_n + '0');
            }

            reverse(tmp.begin(), tmp.end());
            result = addStrings(result, tmp);
        }

        return result;
    }
};

/***
 * 
 * 
 * 
 * 
 * 高级优化
 * 
 * 
 * 
 * 
*/
class Solution {
public:
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") {
            return "0";
        }
        int m = num1.size(), n = num2.size();
        auto ansArr = vector<int>(m + n);
        for (int i = m - 1; i >= 0; i--) {
            int x = num1.at(i) - '0';
            for (int j = n - 1; j >= 0; j--) {
                int y = num2.at(j) - '0';
                ansArr[i + j + 1] += x * y;
            }
        }
        for (int i = m + n - 1; i > 0; i--) {
            ansArr[i - 1] += ansArr[i] / 10;
            ansArr[i] %= 10;
        }
        int index = ansArr[0] == 0 ? 1 : 0;
        string ans;
        while (index < m + n) {
            ans.push_back(ansArr[index]);
            index++;
        }
        for (auto &c: ans) {
            c += '0';
        }
        return ans;
    }
};
