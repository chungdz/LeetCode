'''
763 Partition Labels
You are given a string s. We want to partition the string into as many parts as possible so that each letter appears in at most one part.

Return a list of integers representing the size of these parts.

 

Example 1:

Input: s = "ababcbacadefegdehijhklij"
Output: [9,7,8]
Explanation:
The partition is "ababcbaca", "defegde", "hijhklij".
This is a partition so that each letter appears in at most one part.
A partition like "ababcbacadefegde", "hijhklij" is incorrect, because it splits s into less parts.
Example 2:

Input: s = "eccbbbbdec"
Output: [10]
 

Constraints:

1 <= s.length <= 500
s consists of lowercase English letters.

基本思想

先把每个字符出现的第一次和最后一次找到，得到多个interval
排序interval，并合并有交集的
算出每个interval的长度并返回
'''

class Solution:
    def partitionLabels(self, s: str) -> List[int]:
        rangeDict = {}
        for index, c in enumerate(s):
            if c not in rangeDict:
                rangeDict[c] = [index, index]
            else:
                rangeDict[c][1] = index
        
        rangeList = sorted(list(rangeDict.values()), key=lambda x: x[0])
        finalRange = []
        rlen = len(rangeList)
        finalRange.append(rangeList[0])
        findex = 0
        for i in range(1, rlen):
            if finalRange[findex][1] > rangeList[i][0]:
                if finalRange[findex][1] < rangeList[i][1]:
                    finalRange[findex][1] = rangeList[i][1]
            else:
                finalRange.append(rangeList[i])
                findex += 1
        
        res = []
        for interval in finalRange:
            res.append(interval[1] - interval[0] + 1)
        return res
