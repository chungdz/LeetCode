/*
无重复字符的最长子串
给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。

示例 1:

输入: "abcabcbb"
输出: 3 
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
示例 2:

输入: "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
示例 3:

输入: "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。
*/
#include <string>
#include <vector>
using namespace std;

/*
滑动窗口解法：

维护一个当前窗口有的字符
维护一个最大值，初始化为零

1、往右拓展直到遇到重复字符停下
2、计算当前大小，更新最大值
3、左边向右移动一格
4、回到1
*/

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        
    }
};