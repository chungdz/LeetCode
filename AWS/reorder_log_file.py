'''
937 Reorder Log Files

You are given an array of logs. Each log is a space-delimited string of words, where the first word is the identifier.

There are two types of logs:

Letter-logs: All words (except the identifier) consist of lowercase English letters.
Digit-logs: All words (except the identifier) consist of digits.
Reorder these logs so that:

The letter-logs come before all digit-logs.
The letter-logs are sorted lexicographically by their contents. If their contents are the same, then sort them lexicographically by their identifiers.
The digit-logs maintain their relative ordering.
Return the final order of the logs.

 

Example 1:

Input: logs = ["dig1 8 1 5 1","let1 art can","dig2 3 6","let2 own kit dig","let3 art zero"]
Output: ["let1 art can","let3 art zero","let2 own kit dig","dig1 8 1 5 1","dig2 3 6"]
Explanation:
The letter-log contents are all different, so their ordering is "art can", "art zero", "own kit dig".
The digit-logs have a relative order of "dig1 8 1 5 1", "dig2 3 6".
Example 2:

Input: logs = ["a1 9 2 3 1","g1 act car","zo4 4 7","ab1 off key dog","a8 act zoo"]
Output: ["g1 act car","a8 act zoo","ab1 off key dog","a1 9 2 3 1","zo4 4 7"]
 

Constraints:

1 <= logs.length <= 100
3 <= logs[i].length <= 100
All the tokens of logs[i] are separated by a single space.
logs[i] is guaranteed to have an identifier and at least one word after the identifier.

基本思想

字符串处理和比较
'''

from functools import cmp_to_key

class Solution:
    def reorderLogFiles(self, logs: List[str]) -> List[str]:
        dig_logs = []
        let_logs = []
        for log in logs:
            ldict = Solution.parse_log(log)
            if ldict["type"] == "digit":
                dig_logs.append(log)
            else:
                let_logs.append(ldict)
        let_logs = sorted(let_logs, key=cmp_to_key(Solution.mycmp2))
        res = []
        for l in let_logs:
            res.append(l["identifier"] + ' ' + l["logs"])
        return res + dig_logs
    
    @staticmethod
    def parse_log(log: str):
        log_arr = log.split()
        contents = ' '.join(log_arr[1:])
        if log_arr[1].isdigit():
            return {
                "type": "digit",
                "identifier": log_arr[0],
                "logs": contents
            }
        else:
            return {
                "type": "letter",
                "identifier": log_arr[0],
                "logs": contents
            }
    
    @staticmethod
    def mycmp2(x, y):
        if x["logs"] == y["logs"]:
            if x["identifier"] < y["identifier"]:
                return 1
            elif x["identifier"] > y["identifier"]:
                return -1
            else:
                return 0
        else:
            if x["logs"] < y["logs"]:
                return 1
            elif x["logs"] > y["logs"]:
                return -1