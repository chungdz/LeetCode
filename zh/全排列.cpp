/*
46

全排列
给定一个 没有重复 数字的序列，返回其所有可能的全排列。

示例:

输入: [1,2,3]
输出:
[
  [1,2,3],
  [1,3,2],
  [2,1,3],
  [2,3,1],
  [3,1,2],
  [3,2,1]
]
*/
#include <vector>
using namespace std;

class Solution {
    vector<vector<int>> result;
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<int> origin;
        search_permute(nums, origin);
        return result;
    }
    void search_permute(vector<int>& remain, vector<int>& cur_v){
        int cur_size = remain.size();
        if(cur_size == 0){
            result.push_back(cur_v);
            return;
        }
        for(int i = 0;i < cur_size;i++){
            vector<int> tmp_r = remain;
            vector<int> tmp_c = cur_v;

            tmp_c.push_back(tmp_r[i]);
            tmp_r.erase(tmp_r.begin() + i);

            search_permute(tmp_r, tmp_c);
        }
        return;
    }
};