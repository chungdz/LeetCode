/*
273

整数转换英文表示
将非负整数转换为其对应的英文表示。可以保证给定输入小于 231 - 1 。

示例 1:

输入: 123
输出: "One Hundred Twenty Three"
示例 2:

输入: 12345
输出: "Twelve Thousand Three Hundred Forty Five"
示例 3:

输入: 1234567
输出: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
示例 4:

输入: 1234567891
输出: "One Billion Two Hundred Thirty Four Million Five Hundred Sixty Seven Thousand Eight Hundred Ninety One"
*/
#include <string>
using namespace std;
/*
每三个字符单独处理，得到百位以内的值

三个字符的子串之间插入对应的千，百万，十亿

有一位是零不输出，如果只有0就输出zero
*/
class Solution {
public:
    string numberToWords(int num) {

    }
};