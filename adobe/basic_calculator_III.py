'''
772. Basic Calculator III

Implement a basic calculator to evaluate a simple expression string.

The expression string contains only non-negative integers, '+', '-', '*', '/' operators, and open '(' and closing parentheses ')'. The integer division should truncate toward zero.

You may assume that the given expression is always valid. All intermediate results will be in the range of [-231, 231 - 1].

Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().

 

Example 1:

Input: s = "1+1"
Output: 2
Example 2:

Input: s = "6-4/2"
Output: 4
Example 3:

Input: s = "2*(5+5*2)/3+(6/2+8)"
Output: 21
 

Constraints:

1 <= s <= 104
s consists of digits, '+', '-', '*', '/', '(', and ')'.
s is a valid expression.

基本思想

用list保存之前的数字，如果出现乘和除，就可以和之前的数字结合更新，如果是加和减，就直接push，最后返回list的和
遇到括号递归调用，需要把括号内的和以及index位置都返回，这样才能保证线性时间完成
'''

class Solution:
    def calculate(self, s: str) -> int:
        self.s = '(' + s.replace(' ', '') + ')'
        self.sign = {'+', '-', '*', '/', ')'}
        num, endidx = self.cal_brackets(1)
        return num
    
    def cal_brackets(self, begin):
        numl = []
        idx = begin
        pre_sign = '+'
        cur_num = 0
        while True:
            if self.s[idx].isdigit():
                cur_num = cur_num * 10 + int(self.s[idx])
                idx += 1
            elif self.s[idx] in self.sign:

                if pre_sign == '+':
                    numl.append(cur_num)
                elif pre_sign == '-':
                    numl.append(-cur_num)
                elif pre_sign == '*':
                    numl[-1] = numl[-1] * cur_num
                elif pre_sign == '/':
                    numl[-1] = int(numl[-1] / cur_num)
                cur_num = 0

                if self.s[idx] == ')':
                    break
                pre_sign = self.s[idx]
                idx += 1
            elif self.s[idx] == '(':
                nxt_num, nxt_idx = self.cal_brackets(idx + 1)
                cur_num = nxt_num
                idx = nxt_idx + 1
            else:
                print('Invalid input')
                exit(0)
        
        return sum(numl), idx
        

                