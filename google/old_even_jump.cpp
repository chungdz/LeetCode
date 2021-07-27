#include<vector>
#include<set>
#include<map>
#include<algorithm>
#include<iostream>
using namespace std;

/**
 * 
 * 
 * 解题思路
 * 
 * 动态规划 + 有序字典(字典key可以重复)
 * 
 * 动态规划转移方程
 * 
 * valid_jump[cur_index][0] = valid_jump[odd_jump_index][1] // if can odd jump
 * valid_jump[cur_index][0] = false // if cannot odd jump
 * 
 * valid_jump[cur_index][1] = valid_jump[even_jump_index][0] // if can even jump
 * valid_jump[cur_index][1] = false // if cannot even jump
 * 
 * 边界条件
 * valid_jump[arr_size - 1][0] = true
 * valid_jump[arr_size - 1][1] = true
 * 
 * 
 */
class Solution {
    // index 0 is for odd jump, index 1 is for even jump
    // in the end gather the true of the index 0
    bool valid_jump[20000][2] = {0};
    map<int, int> om;
public:
    int oddEvenJumps(vector<int>& arr) {
        int arr_size = arr.size();
        //initialize the edge
        valid_jump[arr_size - 1][0] = true;
        valid_jump[arr_size - 1][1] = true;
        om[arr[arr_size - 1]] = arr_size - 1;

        int total_good_jump = 1;
        for(int cur_index = arr_size - 2;cur_index >= 0;cur_index--){
            int cur_arr_number = arr[cur_index];
            int odd_jump_index;
            int even_jump_index;

            if(om.find(cur_arr_number) != om.end()){
                odd_jump_index = om[cur_arr_number];
                even_jump_index = om[cur_arr_number];
            }
            else{
                map<int, int>::iterator odd_it = om.lower_bound(cur_arr_number);
                if(odd_it == om.end()){
                    odd_jump_index = -1;
                    map<int, int>::iterator even_it = --odd_it;
                    even_jump_index = even_it->second;
                }
                else if(odd_it == om.begin()){
                    odd_jump_index = odd_it->second;
                    even_jump_index = -1;
                }
                else{
                    odd_jump_index = odd_it->second;
                    map<int, int>::iterator even_it = --odd_it;
                    even_jump_index = even_it->second;
                }
            }

            // cout << "odd jump: " << odd_jump_index << " even jump: " << even_jump_index << endl;
            om[cur_arr_number] = cur_index;
            
            if(odd_jump_index != -1){
                valid_jump[cur_index][0] = valid_jump[odd_jump_index][1];
                if(valid_jump[cur_index][0]){
                    total_good_jump += 1;
                    // cout << "good jump: " << cur_index << endl;
                }
            }
            if(even_jump_index != -1){valid_jump[cur_index][1] = valid_jump[even_jump_index][0];}

            // cout << "map: " <<endl; 
            // for(auto it: om){
            //     cout<< it.first << " ";
            // }
            // cout << endl;
            // for(auto it: om){
            //     cout<< it.second << " ";
            // }
            // cout << endl << endl;
        }

        return total_good_jump;
    }
};

