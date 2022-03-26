'''
418 Sentence Screen Fitting
Given a rows x cols screen and a sentence represented as a list of strings, return the number of times the given sentence can be fitted on the screen.

The order of words in the sentence must remain unchanged, and a word cannot be split into two lines. A single space must separate two consecutive words in a line.

 

Example 1:

Input: sentence = ["hello","world"], rows = 2, cols = 8
Output: 1
Explanation:
hello---
world---
The character '-' signifies an empty space on the screen.
Example 2:

Input: sentence = ["a", "bcd", "e"], rows = 3, cols = 6
Output: 2
Explanation:
a-bcd- 
e-a---
bcd-e-
The character '-' signifies an empty space on the screen.
Example 3:

Input: sentence = ["i","had","apple","pie"], rows = 4, cols = 5
Output: 1
Explanation:
i-had
apple
pie-i
had--
The character '-' signifies an empty space on the screen.
 

Constraints:

1 <= sentence.length <= 100
1 <= sentence[i].length <= 10
sentence[i] consists of lowercase English letters.
1 <= rows, cols <= 2 * 10^4


next_pos[[x, y, z]] 表示下一次填满在x行之后的第y列，一共填入了z次句子

column的index从0开始

暴力搜索 + 动态规划

两个优化：

下一次从头开始的时候，不再遍历，因为已经开始循环

行内循环，当句子足够小的时候，行内循坏也不遍历，而是直接跳到最后一次循环的位置
'''

from itertools import cycle


class Solution:
    def wordsTyping(self, sentence: List[str], rows: int, cols: int) -> int:
        next_pos = [[-1, -1, -1]] * cols
        self.wlen = []
        for w in sentence:
            if len(w) > cols:
                return 0
            else:
                self.wlen.append(len(w))
        
        self.r = rows
        self.c = cols
        self.s = sentence
        self.slen = len(self.s)
        self.whole_len = sum(self.wlen) + self.slen - 1
        self.n = next_pos

        cur_row = 0
        times = 0
        cur_idx = self.c - 1
        cycled = False
        while cur_row <= rows:
            added_r, new_idx, added_times = self.search_row_col(cur_idx)
            if added_r + cur_row > rows:
                break
            cur_row = cur_row + added_r
            cur_idx = new_idx
            times += added_times
            # means the next index needs to be at first of the columns
            # so the whole thing start to loop
            # jump to last loop
            left = self.c - new_idx - 1
            if left < self.wlen[0] + 1:
                if not cycled:
                    cycled = True
                else:
                    print("error")
                    exit()
                left_rows = rows - cur_row
                cycle_times = left_rows // cur_row
                if cycle_times > 0:
                    times += cycle_times * times
                    cur_row += cycle_times * cur_row
        
        return times
    
    def search_row_col(self, index):
        if self.n[index][0] != -1:
            return self.n[index]

        widx = 0
        cur_idx = index
        row = 0

        row_left = self.c - index - 1
        stimes = row_left // (self.whole_len + 1)
        # loop inside the columns, when sentence is small enough
        # jump to last loop
        if stimes > 0:
            cur_idx += stimes * (self.whole_len + 1)
            self.n[index] = [0, cur_idx, stimes]
            return self.n[index]
        # need to change row, when sentence is big enough
        while widx < self.slen:
            left = self.c - cur_idx - 1
            if left >= self.wlen[widx] + 1:
                cur_idx += self.wlen[widx] + 1
            else:
                row += 1
                cur_idx = self.wlen[widx] - 1
            widx += 1
        
        self.n[index] = [row, cur_idx, 1]

        return self.n[index]
