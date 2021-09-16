#include<algorithm>
#include<set>
#include<map>
#include<memory.h>
using namespace std;

/*

351

Android devices have a special lock screen with a 3 x 3 grid of dots. Users can set an "unlock pattern" by connecting the dots in a specific sequence, forming a series of joined line segments where each segment's endpoints are two consecutive dots in the sequence. A sequence of k dots is a valid unlock pattern if both of the following are true:

All the dots in the sequence are distinct.
If the line segment connecting two consecutive dots in the sequence passes through the center of any other dot, the other dot must have previously appeared in the sequence. No jumps through the center non-selected dots are allowed.
For example, connecting dots 2 and 9 without dots 5 or 6 appearing beforehand is valid because the line from dot 2 to dot 9 does not pass through the center of either dot 5 or 6.
However, connecting dots 1 and 3 without dot 2 appearing beforehand is invalid because the line from dot 1 to dot 3 passes through the center of dot 2.
Here are some example valid and invalid unlock patterns:



The 1st pattern [4,1,3,6] is invalid because the line connecting dots 1 and 3 pass through dot 2, but dot 2 did not previously appear in the sequence.
The 2nd pattern [4,1,9,2] is invalid because the line connecting dots 1 and 9 pass through dot 5, but dot 5 did not previously appear in the sequence.
The 3rd pattern [2,4,1,3,6] is valid because it follows the conditions. The line connecting dots 1 and 3 meets the condition because dot 2 previously appeared in the sequence.
The 4th pattern [6,5,4,1,9,2] is valid because it follows the conditions. The line connecting dots 1 and 9 meets the condition because dot 5 previously appeared in the sequence.
Given two integers m and n, return the number of unique and valid unlock patterns of the Android grid lock screen that consist of at least m keys and at most n keys.

Two unlock patterns are considered unique if there is a dot in one sequence that is not in the other, or the order of the dots is different.

 

Example 1:

Input: m = 1, n = 1
Output: 9
Example 2:

Input: m = 1, n = 2
Output: 65
 

Constraints:

1 <= m, n <= 9




暴力搜索，去除相邻两数出现穿越未选择的中间数的情况

优化：使用Bitmap + 动态规划，注意除了bitmap之外还有个状态是pre-selected number，所以dp数组是二维的
第一维度用Bitmap记录已经被选择的数字（对应的位置上1为被选择，0为未选择），注意由于数字从1开始，在bitmap的记录位置需要减一
第二维度表示之前选择了哪个数字，第二维度我选择了10，实际上只用到了1-9，第0位是空出来的，但是为了方便写代码就加上了

S1 1400ms 400MB
S2 优化后 19ms 6.2MB

**/

class Solution {
    int cross_relation[8][3] = {{1, 3, 2}, {3, 9, 6}, {7, 9, 8}, {1, 7, 4}, {1, 9, 5}, {3, 7, 5}, {4, 6, 5}, {2, 8, 5}};
    map<int, map<int, int>> trail_map;
    int res = 0;
    int mm, nn;
public:
    Solution(){
        for(int i = 0;i < 8;++i){
            if(trail_map.find(cross_relation[i][0]) == trail_map.end())
            {trail_map[cross_relation[i][0]] = map<int, int>();}
            if(trail_map.find(cross_relation[i][1]) == trail_map.end())
            {trail_map[cross_relation[i][1]] = map<int, int>();}

            trail_map[cross_relation[i][0]][cross_relation[i][1]] = cross_relation[i][2];
            trail_map[cross_relation[i][1]][cross_relation[i][0]] = cross_relation[i][2];
        }
    }

    int numberOfPatterns(int m, int n) {
        mm = m;
        nn = n;
        set<int> init;
        for(int i = 1;i < 10;++i){
            init.insert(i);
        }

        dfs(init, 0, -1);
        return res;
    }

    void dfs(set<int> unselected, int key_num, int pre){
        if(key_num >= mm && key_num <= nn){
            res++;
        }
        if(key_num == nn){return;}

        for(int i = 1;i < 10;++i){
            if(unselected.find(i) != unselected.end()){
                if(pre != -1){
                    if(trail_map.find(pre) != trail_map.end() && trail_map[pre].find(i) != trail_map[pre].end()){
                        int tocheck = trail_map[pre][i];
                        if(unselected.find(tocheck) != unselected.end()){
                            continue;
                        }
                    }
                }

                set<int> next_s = unselected;
                next_s.erase(i);
                dfs(next_s, key_num + 1, i);
            }
        }
    }
};


class Solution {
    int cross_relation[8][3] = {{1, 3, 2}, {3, 9, 6}, {7, 9, 8}, {1, 7, 4}, {1, 9, 5}, {3, 7, 5}, {4, 6, 5}, {2, 8, 5}};
    map<int, map<int, int>> trail_map;
    int res = 0;
    int mm, nn;
    int dp[512][10];
public:
    Solution(){
        for(int i = 0;i < 8;++i){
            if(trail_map.find(cross_relation[i][0]) == trail_map.end())
            {trail_map[cross_relation[i][0]] = map<int, int>();}
            if(trail_map.find(cross_relation[i][1]) == trail_map.end())
            {trail_map[cross_relation[i][1]] = map<int, int>();}

            trail_map[cross_relation[i][0]][cross_relation[i][1]] = cross_relation[i][2];
            trail_map[cross_relation[i][1]][cross_relation[i][0]] = cross_relation[i][2];
        }
        // init all to -1
        memset(dp, -1, sizeof(int) * 512 * 10);
    }

    int numberOfPatterns(int m, int n) {
        mm = m;
        nn = n;
        set<int> init;
        for(int i = 1;i < 10;++i){
            init.insert(i);
        }

        return dfs(0, 0, 0);
    }

    int dfs(int bitmap, int key_num, int pre){
        if(dp[bitmap][pre] != -1){return dp[bitmap][pre];}

        int total = 0;
        if(key_num >= mm && key_num <= nn){
            total += 1;
        }
        if(key_num == nn){
            dp[bitmap][pre] = total;
            return total;
        }

        for(int i = 1;i < 10;++i){
            int bitmap_pos = i - 1;
            int selected = (bitmap >> bitmap_pos) & 1;
            if(selected == 0){
                if(pre != 0){
                    if(trail_map.find(pre) != trail_map.end() && trail_map[pre].find(i) != trail_map[pre].end()){
                        int tocheck = trail_map[pre][i] - 1;
                        int check_selected = (bitmap >> tocheck) & 1;
                        if(check_selected == 0){
                            continue;
                        }
                    }
                }

                int next_bitmap = bitmap | (1 << bitmap_pos);
                total += dfs(next_bitmap, key_num + 1, i);
            }
        }

        dp[bitmap][pre] = total;
        return total;
    }
};