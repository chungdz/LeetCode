import copy

'''
301

Remove Invalid Parentheses

Given a string s that contains parentheses and letters, remove the minimum number of invalid parentheses to make the input string valid.

Return all the possible results. You may return the answer in any order.

 

Example 1:

Input: s = "()())()"
Output: ["(())()","()()()"]
Example 2:

Input: s = "(a)())()"
Output: ["(a())()","(a)()()"]
Example 3:

Input: s = ")("
Output: [""]
 

Constraints:

1 <= s.length <= 25
s consists of lowercase English letters and parentheses '(' and ')'.
There will be at most 20 parentheses in s.

基本思想

遍历，先找到要删除多少个左符号，反向遍历，找到要删除多少个右符号

从左到右遍历，如果遇到左符号或者右符号，有两种选择，跳过或者添加，添加右符号需要检查当前score > 0 （意思是之前必须要有左符号）
添加左符号不需要检查，跳过需要检查右边删除个数是否已经满了，满了就不能跳过
'''

class Solution:
    def removeInvalidParentheses(self, s: str) -> List[str]:
        self.slen = len(s)
        self.res = set()
        self.left_cut = 0
        self.right_cut = 0
        self.s = s
        for c in s:
            if c == '(':
                self.left_cut += 1
            elif c == ')' and self.left_cut > 0:
                self.left_cut -= 1
        
        for i in range(self.slen - 1, -1, -1):
            if s[i] == ')':
                self.right_cut += 1
            elif s[i] == '(' and self.right_cut > 0:
                self.right_cut -= 1
        
        self.build_valid("", 0, 0, 0, 0)
        return self.res
    
    def build_valid(self, cur_str, index, left, right, score):
        if index == self.slen:
            if score == 0:
                self.res.add(copy.copy(cur_str))
            return
        
        if self.s[index] == '(':
            # opt 1
            cur_str += '('
            self.build_valid(cur_str, index + 1, left, right, score + 1)
            cur_str = cur_str[:-1]
            # opt 2
            if self.left_cut > left:
                self.build_valid(cur_str, index + 1, left + 1, right, score)
        elif self.s[index] == ')':
            if self.right_cut > right:
                self.build_valid(cur_str, index + 1, left, right + 1, score)
            if score > 0:
                # opt 1
                cur_str += ')'
                self.build_valid(cur_str, index + 1, left, right, score - 1)
                cur_str = cur_str[:-1]
        else:
            cur_str += self.s[index]
            self.build_valid(cur_str, index + 1, left, right, score)
            cur_str = cur_str[:-1]