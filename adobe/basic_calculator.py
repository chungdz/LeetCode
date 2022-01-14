'''
224 Basic Calculator

Given a string s representing a valid expression, implement a basic calculator to evaluate it, and return the result of the evaluation.

Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().

 

Example 1:

Input: s = "1 + 1"
Output: 2
Example 2:

Input: s = " 2-1 + 2 "
Output: 3
Example 3:

Input: s = "(1+(4+5+2)-3)+(6+8)"
Output: 23
 

Constraints:

1 <= s.length <= 3 * 105
s consists of digits, '+', '-', '(', ')', and ' '.
s represents a valid expression.
'+' is not used as a unary operation (i.e., "+1" and "+(2 + 3)" is invalid).
'-' could be used as a unary operation (i.e., "-1" and "-(2 + 3)" is valid).
There will be no two consecutive operators in the input.
Every number and running calculation will fit in a signed 32-bit integer.

基本思想

滑动窗口，每次滑动直到取得一个数字/找到一个左括号/找到一个右括号

注意：不能递归处理括号，这样会导致TLE，每次遇到左括号，就把括号前应该是什么符号找到，压入栈中，到了右括号，弹出栈
这样就能直接计算所有数字
'''

class Solution:
    def calculate(self, s: str) -> int:
        s = s.replace(' ', '')
        return self.cal(s)

    def cal(self, s):
        slen = len(s)
        cur_s = 0
        total = 0
        pre_sign = [1]
        
        while cur_s < slen:
            
            if s[cur_s].isdigit():
                cur_end = cur_s + 1
                while cur_end < slen and s[cur_end].isdigit():
                    cur_end += 1
                total += int(s[cur_s: cur_end]) * pre_sign[-1]
                cur_s = cur_end
            elif s[cur_s] == '(':
                pre_sign.append(pre_sign[-1])
                cur_s += 1
            elif s[cur_s] == ')':
                pre_sign.pop()
                cur_s += 1
            else:
                if s[cur_s] == '+':
                    cur_sign = 1
                else:
                    cur_sign = -1
                
                cur_end = cur_s + 1
                if s[cur_end].isdigit():
                    cur_end += 1
                    while cur_end < slen and s[cur_end].isdigit():
                        cur_end += 1
                    total += int(s[cur_s: cur_end]) * pre_sign[-1]
                    cur_s = cur_end
                elif s[cur_end] == '(':
                    pre_sign.append(pre_sign[-1] * cur_sign)
                    cur_s = cur_end + 1

        return total



