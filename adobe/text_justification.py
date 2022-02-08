'''
68 Text Justification

Given an array of strings words and a width maxWidth, format the text such that each line has exactly maxWidth characters and is fully (left and right) justified.

You should pack your words in a greedy approach; that is, pack as many words as you can in each line. Pad extra spaces ' ' when necessary so that each line has exactly maxWidth characters.

Extra spaces between words should be distributed as evenly as possible. If the number of spaces on a line does not divide evenly between words, the empty slots on the left will be assigned more spaces than the slots on the right.

For the last line of text, it should be left-justified and no extra space is inserted between words.

Note:

A word is defined as a character sequence consisting of non-space characters only.
Each word's length is guaranteed to be greater than 0 and not exceed maxWidth.
The input array words contains at least one word.
 

Example 1:

Input: words = ["This", "is", "an", "example", "of", "text", "justification."], maxWidth = 16
Output:
[
   "This    is    an",
   "example  of text",
   "justification.  "
]
Example 2:

Input: words = ["What","must","be","acknowledgment","shall","be"], maxWidth = 16
Output:
[
  "What   must   be",
  "acknowledgment  ",
  "shall be        "
]
Explanation: Note that the last line is "shall be    " instead of "shall     be", because the last line must be left-justified instead of fully-justified.
Note that the second line is also left-justified becase it contains only one word.
Example 3:

Input: words = ["Science","is","what","we","understand","well","enough","to","explain","to","a","computer.","Art","is","everything","else","we","do"], maxWidth = 20
Output:
[
  "Science  is  what we",
  "understand      well",
  "enough to explain to",
  "a  computer.  Art is",
  "everything  else  we",
  "do                  "
]
 

Constraints:

1 <= words.length <= 300
1 <= words[i].length <= 20
words[i] consists of only English letters and symbols.
1 <= maxWidth <= 100
words[i].length <= maxWidth

基本思想

按照规则编程
'''

class Solution:
    def fullJustify(self, words: List[str], maxWidth: int) -> List[str]:
        res = []
        wlen = len(words)
        s = 0
        while True:
            t = s
            left = maxWidth - len(words[t])
            t += 1
            while t < wlen and left >= len(words[t]) + 1:
                left -= len(words[t]) + 1
                t += 1
            
            cur_str = words[s]
            if t != wlen:
                gaps = t - s - 1
                if gaps == 0:
                    cur_str += " " * left
                    s = t
                    res.append(cur_str)
                    continue
                
                tail_interval = (left // gaps)
                head_interval_num = left - gaps * tail_interval
                
                fi = tail_interval + 2
                last = tail_interval + 1
                tmpi = s + 1
                iidx = 0
                while tmpi < t:
                    if iidx < head_interval_num:
                        cur_str += " " * fi
                    else:
                        cur_str += " " * last
                    cur_str += words[tmpi]
                    tmpi += 1
                    iidx += 1
                
                s = t
                res.append(cur_str)
            else:
                tmpi = s + 1
                while tmpi < t:
                    cur_str += " "
                    cur_str += words[tmpi]
                    tmpi += 1
                cur_str += " " * left
                s = t
                res.append(cur_str)
                break
        return res
            