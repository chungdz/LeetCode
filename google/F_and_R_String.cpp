#include<string>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

/**
 * 833
 * 
 * 
You are given a 0-indexed string s that you must perform k replacement operations on. The replacement operations are given as three 0-indexed parallel arrays, indices, sources, and targets, all of length k.

To complete the ith replacement operation:

Check if the substring sources[i] occurs at index indices[i] in the original string s.
If it does not occur, do nothing.
Otherwise if it does occur, replace that substring with targets[i].
For example, if s = "abcd", indices[i] = 0, sources[i] = "ab", and targets[i] = "eee", then the result of this replacement will be "eeecd".

All replacement operations must occur simultaneously, meaning the replacement operations should not affect the indexing of each other. The testcases will be generated such that the replacements will not overlap.

For example, a testcase with s = "abc", indices = [0, 1], and sources = ["ab","bc"] will not be generated because the "ab" and "bc" replacements overlap.
Return the resulting string after performing all replacement operations on s.

A substring is a contiguous sequence of characters in a string.

Example 1:


Input: s = "abcd", indices = [0, 2], sources = ["a", "cd"], targets = ["eee", "ffff"]
Output: "eeebffff"
Explanation:
"a" occurs at index 0 in s, so we replace it with "eee".
"cd" occurs at index 2 in s, so we replace it with "ffff".
Example 2:


Input: s = "abcd", indices = [0, 2], sources = ["ab","ec"], targets = ["eee","ffff"]
Output: "eeecd"
Explanation:
"ab" occurs at index 0 in s, so we replace it with "eee".
"ec" does not occur at index 2 in s, so we do nothing.
 

Constraints:

1 <= s.length <= 1000
k == indices.length == sources.length == targets.length
1 <= k <= 100
0 <= indexes[i] < s.length
1 <= sources[i].length, targets[i].length <= 50
s consists of only lowercase English letters.
sources[i] and targets[i] consist of only lowercase English letters.
 * 
 * 
 * 
 * 基本思路
 * 
 * 逐个遍历，依次比较，记录合规的替换符
 * 
 * 由于输入没有排序，需要先排序
 * 
 * 排序的目的是为了让不被替换的字符有顺序的被记录
 * 
 */

bool comp(const pair<int, int> &a, const pair<int, int> &b){
        return a.first < b.first;
};

class Solution {
    vector<pair<int, int>> record;
    bool replaced[1000] = {0};
    vector<pair<int, int>> in2source;
public:
    string findReplaceString(string s, vector<int>& indices, vector<string>& sources, vector<string>& targets) {

        int k = indices.size();

        for(int i = 0;i < k;++i){
            in2source.push_back(pair<int, int>(indices[i], i));
        }
        sort(in2source.begin(), in2source.end(), comp);
        // check zero
        int re_index = 0;
        if(0 < in2source[0].first){
            record.push_back(pair<int, int>(0, in2source[0].first));
            replaced[re_index] = false;
            ++re_index;
        }
        
        // push last index for better loop
        in2source.push_back(pair<int, int>(s.size(), s.size()));
        for(int i = 0;i < k;++i){
            int nxt = i + 1;
            int source_index = in2source[i].second;
            int origin_s;
            string cur_sub_str = s.substr(in2source[i].first, sources[source_index].size());
            if(cur_sub_str == sources[source_index]){
                record.push_back(pair<int, int>(in2source[i].first, source_index));
                replaced[re_index] = true;
                ++re_index;
                origin_s = in2source[i].first + cur_sub_str.size();
            }
            else{
                origin_s = in2source[i].first;
            }

            if(origin_s < in2source[nxt].first){
                int cur_size = in2source[nxt].first - origin_s;
                record.push_back(pair<int, int>(origin_s, cur_size));
                replaced[re_index] = false;
                ++re_index;
            }
        }

        string res = "";
        int r_size = record.size();
        for(int j = 0;j < r_size;++j){
            if(replaced[j]){
                res += targets[record[j].second];
            }
            else{
                res += s.substr(record[j].first, record[j].second);
            }
        }
        return res;
    }
};