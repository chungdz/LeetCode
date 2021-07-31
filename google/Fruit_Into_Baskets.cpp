#include<vector>
#include<map>
#include <algorithm>
using namespace std;

/***
 * 904
 * 
 * You are visiting a farm that has a single row of fruit trees arranged from left to right. The trees are represented by an integer array fruits where fruits[i] is the type of fruit the ith tree produces.

You want to collect as much fruit as possible. However, the owner has some strict rules that you must follow:

You only have two baskets, and each basket can only hold a single type of fruit. There is no limit on the amount of fruit each basket can hold.
Starting from any tree of your choice, you must pick exactly one fruit from every tree (including the start tree) while moving to the right. The picked fruits must fit in one of your baskets.
Once you reach a tree with fruit that cannot fit in your baskets, you must stop.
Given the integer array fruits, return the maximum number of fruits you can pick.

 

Example 1:

Input: fruits = [1,2,1]
Output: 3
Explanation: We can pick from all 3 trees.
Example 2:

Input: fruits = [0,1,2,2]
Output: 3
Explanation: We can pick from trees [1,2,2].
If we had started at the first tree, we would only pick from trees [0,1].
Example 3:

Input: fruits = [1,2,3,2,2]
Output: 4
Explanation: We can pick from trees [2,3,2,2].
If we had started at the first tree, we would only pick from trees [1,2].
Example 4:

Input: fruits = [3,3,3,1,2,1,1,2,3,3,4]
Output: 5
Explanation: We can pick from trees [1,2,1,1,2].
 

Constraints:

1 <= fruits.length <= 10^5
0 <= fruits[i] < fruits.length
 * 
 * 
 * 
 * 解题思路：动态规划
 * 
 * 和传统动态规划不同的地方在于需要记录更多的信息用于判断状态转移
 * 
 * 用struct start_info来记录
 * 从尾部开始初始化，往前走
 * 转移时分为两种情况，tree type相等和tree type不等
 * 在tree type 不等时，又分为两种情况，next tree的type number = 1，或者next tree的number = 2
 * 在next tree的number = 2时，又分为tree type为新和不为新
 * 
 * 一共有四种状态需要考虑，每种状态都要把start info的信息填满
 * 
 * 最后选择tree number最多的返回
 * 
*/

struct start_info{
    int type_number = 0;
    int tree_number;
    int tree_type[2];
    int type_change;
};

class Solution {
    start_info arr_record[100000]; 
public:
    int totalFruit(vector<int>& fruits) {
        int total_size = fruits.size();
        int max_tree = 1;

        arr_record[total_size - 1].type_number = 1;
        arr_record[total_size - 1].tree_type[0] = fruits[total_size - 1];
        arr_record[total_size - 1].tree_number = 1;
        arr_record[total_size - 1].type_change = total_size - 1;

        for(int cur_tree = total_size - 2;cur_tree >= 0;--cur_tree){

            int next_tree = cur_tree + 1;

            if(fruits[cur_tree] == fruits[next_tree]){
                
                arr_record[cur_tree].type_change = arr_record[next_tree].type_change;
                arr_record[cur_tree].type_number = arr_record[next_tree].type_number;
                arr_record[cur_tree].tree_number = arr_record[next_tree].tree_number + 1;
                for(int j = 0;j < arr_record[cur_tree].type_number;j++){
                    arr_record[cur_tree].tree_type[j] = arr_record[next_tree].tree_type[j];
                }
            }
            else{
                arr_record[cur_tree].type_change = cur_tree;
                arr_record[cur_tree].type_number = 2;
                arr_record[cur_tree].tree_type[0] = fruits[cur_tree];
                arr_record[cur_tree].tree_type[1] = arr_record[next_tree].tree_type[0];

                if(arr_record[next_tree].type_number == 1){
                    arr_record[cur_tree].tree_number = arr_record[next_tree].tree_number + 1;
                }
                else if(arr_record[next_tree].type_number == 2){
                    if(fruits[cur_tree] == arr_record[next_tree].tree_type[1]){
                        arr_record[cur_tree].tree_number = arr_record[next_tree].tree_number + 1;
                    }
                    else{
                        arr_record[cur_tree].tree_number = 1 + arr_record[next_tree].type_change - cur_tree;
                    }
                }
            }
            
            max_tree = max(max_tree, arr_record[cur_tree].tree_number);
        }

        return max_tree;
    }
};