'''
282 Expression Add Operators
Given a string num that contains only digits and an integer target, return all possibilities to insert the binary operators '+', '-', and/or '*' between the digits of num so that the resultant expression evaluates to the target value.

Note that operands in the returned expressions should not contain leading zeros.

 

Example 1:

Input: num = "123", target = 6
Output: ["1*2*3","1+2+3"]
Explanation: Both "1*2*3" and "1+2+3" evaluate to 6.
Example 2:

Input: num = "232", target = 8
Output: ["2*3+2","2+3*2"]
Explanation: Both "2*3+2" and "2+3*2" evaluate to 8.
Example 3:

Input: num = "105", target = 5
Output: ["1*0+5","10-5"]
Explanation: Both "1*0+5" and "10-5" evaluate to 5.
Note that "1-05" is not a valid expression because the 5 has a leading zero.
Example 4:

Input: num = "00", target = 0
Output: ["0*0","0+0","0-0"]
Explanation: "0*0", "0+0", and "0-0" all evaluate to 0.
Note that "00" is not a valid expression because the 0 has a leading zero.
Example 5:

Input: num = "3456237490", target = 9191
Output: []
Explanation: There are no expressions that can be created from "3456237490" to evaluate to 9191.
 

Constraints:

1 <= num.length <= 10
num consists of only digits.
-2^31 <= target <= 2^31 - 1

基本思想

两步：生成 + 计算

递归生成valid的算式，然后计算算式结果
'''

import copy

class Solution:
    def Calculate_res(self, arro):
        # check for *
        arr = copy.copy(arro)
        index = 1
        while index < len(arr) - 1:
            if arr[index] == '*':
                arr[index - 1] = arr[index - 1] * arr[index + 1]
                arr.pop(index + 1)
                arr.pop(index)
            else:
                index += 1

        # print(arr)
        index = 1
        while index < len(arr) - 1:
            if arr[index] == '+':
                arr[index - 1] = arr[index - 1] + arr[index + 1]
                arr.pop(index + 1)
                arr.pop(index)
            elif arr[index] == '-':
                arr[index - 1] = arr[index - 1] - arr[index + 1]
                arr.pop(index + 1)
                arr.pop(index)
            else:
                index += 1
        return arr[0]
    
    def change_to_string(self, arro):
        res = ""
        for it in arro:
            res += str(it)
        return res

    def addOperators(self, num: str, target: int) -> List[str]:
        self.t = target
        self.num = num
        self.nlen = len(num)
        self.valid = []
        self.cur_str = []
        self.seq_generator(0)
        return self.valid

    def seq_generator(self, index):
        
        if index == self.nlen:
            cal = self.Calculate_res(self.cur_str)
            if cal == self.t:
                self.valid.append(self.change_to_string(self.cur_str))
            return
        
        if self.num[index] == '0':
            self.cur_str.append(0)
            self.add_operator(index + 1)
            self.cur_str.pop(-1)
        else:
            end = index + 1
            while end <= self.nlen:
                cur_num = int(self.num[index: end])
                self.cur_str.append(cur_num)
                self.add_operator(end)
                self.cur_str.pop(-1)
                end += 1
            

    def add_operator(self, cindex):
        if cindex == self.nlen:
            self.seq_generator(cindex)
        else:
            self.cur_str.append('+')
            self.seq_generator(cindex)
            self.cur_str.pop(-1)
            self.cur_str.append('-')
            self.seq_generator(cindex)
            self.cur_str.pop(-1)
            self.cur_str.append('*')
            self.seq_generator(cindex)
            self.cur_str.pop(-1)

