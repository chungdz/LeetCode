#include<vector>
#include<algorithm>
#include<numeric>
using namespace std;

/*
135

Candy

There are n children standing in a line. Each child is assigned a rating value given in the integer array ratings.

You are giving candies to these children subjected to the following requirements:

Each child must have at least one candy.
Children with a higher rating get more candies than their neighbors.
Return the minimum number of candies you need to have to distribute the candies to the children.

 

Example 1:

Input: ratings = [1,0,2]
Output: 5
Explanation: You can allocate to the first, second and third child with 2, 1, 2 candies respectively.
Example 2:

Input: ratings = [1,2,2]
Output: 4
Explanation: You can allocate to the first, second and third child with 1, 2, 1 candies respectively.
The third child gets 1 candy because it satisfies the above two conditions.
 

Constraints:

n == ratings.length
1 <= n <= 2 * 10^4
0 <= ratings[i] <= 2 * 10^4

基本思想

初始化最低谷为1（小于等两边）

循环直到全部填充完毕
    对每个i，把大于两边且大于的那个边数字存在的i填充为 +1，如果两边同时大就max后 +1
    如果存在大于的边且那个边不确定大小，跳过

为了防止极端情况，遍历的时候先正向后负向
**/

class Solution {
public:
    int candy(vector<int>& ratings) {
        int total_c = ratings.size();
        vector<int> mountain(total_c, -1);

        //init
        for(int i = 0;i < total_c;++i){
                int pre = i - 1;
                int nxt = i + 1;
                if(pre >= 0 && ratings[i] > ratings[pre]){
                    continue;
                }
                if(nxt < total_c && ratings[i] > ratings[nxt]){
                    continue;
                }
                mountain[i] = 1;
        }
        
        bool turn = true;
        while(true){
            int allocated = 0;
            
            // forward & backward 
            int i;
            if(turn){i = -1;}
            else{i = total_c;}

            while(true){
                if(turn){++i;}
                else{--i;}

                if(turn && i >= total_c){break;}
                else if(!turn && i < 0){break;}

                if(mountain[i] != -1){
                    allocated += 1;
                    continue;
                }    

                int pre = i - 1;
                int nxt = i + 1;
                int cur_candy = -1;
                if(pre >= 0 && ratings[i] > ratings[pre] && mountain[pre] != -1){
                    // bigger than both
                    if(nxt < total_c && ratings[i] > ratings[nxt]){
                        if(mountain[nxt] != -1){
                            mountain[i] = max(mountain[nxt], mountain[pre]) + 1;
                            allocated += 1;
                        }
                        else{
                            continue;
                        }
                    }
                    // bigger than only left side
                    else{
                        mountain[i] = mountain[pre] + 1;
                        allocated += 1;
                    }
                }
                else if(nxt < total_c && ratings[i] > ratings[nxt] && mountain[nxt] != -1){
                    if(pre >= 0 && ratings[i] > ratings[pre] && mountain[pre] == -1){
                        continue;
                    }
                    // bigger than only right side
                    mountain[i] = mountain[nxt] + 1;
                    allocated += 1;
                }
            }

            if(allocated == total_c){break;}
            allocated = 0;
            turn = !turn;
        }

        return accumulate(mountain.begin(), mountain.end(), 0);
    }
};