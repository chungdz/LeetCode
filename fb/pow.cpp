/*
50 Pow(x, n)

Implement pow(x, n), which calculates x raised to the power n (i.e., x^n).

 

Example 1:

Input: x = 2.00000, n = 10
Output: 1024.00000
Example 2:

Input: x = 2.10000, n = 3
Output: 9.26100
Example 3:

Input: x = 2.00000, n = -2
Output: 0.25000
Explanation: 2-2 = 1/22 = 1/4 = 0.25
 

Constraints:

-100.0 < x < 100.0
-2^31 <= n <= 2^31-1
-10^4 <= xn <= 10^4

基本思想

倍数指数递增，结果连乘对应的倍数，判断依据是n的对应位上是否有1
**/

class Solution {
public:
    double myPow(double x, int n) {
        if(n == 0){return 1;}
        bool sign = false;
        long long nn = n;
        if(nn < 0){
            sign = true;
            nn = -nn;
        }
        double cmul = x;
        double res = 1;
        for(int i = 0;i < 32;++i){
            if(nn & 1 == 1){
                res *= cmul;
            }
            nn = nn >> 1;
            cmul = cmul * cmul;
        }

        if(sign){res = 1 / res;}
        return res;
    }
};