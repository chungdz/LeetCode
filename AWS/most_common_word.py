import re

'''
819 Most Common Word

Given a string paragraph and a string array of the banned words banned, return the most frequent word that is not banned. It is guaranteed there is at least one word that is not banned, and that the answer is unique.

The words in paragraph are case-insensitive and the answer should be returned in lowercase.

 

Example 1:

Input: paragraph = "Bob hit a ball, the hit BALL flew far after it was hit.", banned = ["hit"]
Output: "ball"
Explanation: 
"hit" occurs 3 times, but it is a banned word.
"ball" occurs twice (and no other word does), so it is the most frequent non-banned word in the paragraph. 
Note that words in the paragraph are not case sensitive,
that punctuation is ignored (even if adjacent to words, such as "ball,"), 
and that "hit" isn't the answer even though it occurs more because it is banned.
Example 2:

Input: paragraph = "a.", banned = []
Output: "a"
 

Constraints:

1 <= paragraph.length <= 1000
paragraph consists of English letters, space ' ', or one of the symbols: "!?',;.".
0 <= banned.length <= 100
1 <= banned[i].length <= 10
banned[i] consists of only lowercase English letters.

基本思想

使用translate来转换多个字符
'''

punctuation = '!,.;:?"\''
def removePunctuation(text):
    text = re.sub(r'[{}]+'.format(punctuation),'',text)
    return text.strip().lower()

def replacePunctuation(text):
    cdict = {}
    for c in punctuation:
        cdict[c] = ' '
    text = text.translate(str.maketrans(cdict))
    return text.strip().lower()

class Solution:
    def mostCommonWord(self, paragraph: str, banned: List[str]) -> str:
        parsed_para = replacePunctuation(paragraph)
        ban_set = set(banned)
        wd = {}
        parr = parsed_para.split()

        maxw = ""
        max_f = 0
        for w in parr:
            if w in ban_set:
                continue
            if w not in wd:
                wd[w] = 1
            else:
                wd[w] += 1
            
            if wd[w] > max_f:
                max_f = wd[w]
                maxw = w
        
        return maxw


