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

template <class KeyType, class ValueType>
class Ordered_Map_Duplicate_key{
    vector<KeyType> ordered_key;
    vector<ValueType> my_map;
public:
    bool find(KeyType cur_key){
        typename vector<KeyType>::iterator it = find_first_iterator(cur_key);
        if(*it == cur_key){
            return true;
        }
        return false;
    }

    ValueType get_value(int key_index){
        return my_map[key_index];
    }

    int find_first_index(KeyType cur_key){
        return lower_bound(ordered_key.begin(), ordered_key.end(), cur_key) - ordered_key.begin();
    }

    void print_map(){
        for(int i = 0;i < ordered_key.size();i++){
            cout << ordered_key[i] << " ";
        }
        cout << endl;
        for(int i = 0;i < ordered_key.size();i++){
            cout << my_map[i] << " ";
        }
        cout << endl;
        cout << endl;
    }

    void insert(int index, KeyType cur_key, ValueType cur_value){
        ordered_key.insert(ordered_key.begin() + index, cur_key);
        my_map.insert(my_map.begin() + index, cur_value);
    }
    //for even jump
    ValueType max_small(int cur_it){
        // check if value is same
        int next_it = cur_it + 1;
        if(next_it < ordered_key.size() && ordered_key[next_it] == ordered_key[cur_it]){
            return my_map[next_it];
        }

        if(cur_it == 0){return -1;}
        //check if previous value is duplicate
        int previous_it = cur_it - 1;
        int far_it = previous_it - 1;
        while(far_it >= 0 && ordered_key[previous_it] == ordered_key[far_it]){
            previous_it--;
            far_it--;
        }
        return my_map[previous_it];
    }
    //for odd jump
    ValueType min_large(int cur_it){
        cur_it++;
        if(cur_it == ordered_key.size()){return -1;}
        return my_map[cur_it];
    }
};


class Solution {
    // index 0 is for odd jump, index 1 is for even jump
    // in the end gather the true of the index 0
    bool valid_jump[20000][2] = {0};
    Ordered_Map_Duplicate_key<int, int> om;
public:
    int oddEvenJumps(vector<int>& arr) {
        int arr_size = arr.size();
        //initialize the edge
        valid_jump[arr_size - 1][0] = true;
        valid_jump[arr_size - 1][1] = true;
        om.insert(om.find_first_index(arr[arr_size - 1]), arr[arr_size - 1], arr_size - 1);

        int total_good_jump = 1;
        for(int cur_index = arr_size - 2;cur_index >= 0;cur_index--){
            int cur_arr_number = arr[cur_index];
            int odd_jump_index;
            int even_jump_index;

            int cur_it = om.find_first_index(cur_arr_number);
            om.insert(cur_it, cur_arr_number, cur_index);

            odd_jump_index = om.min_large(cur_it);
            even_jump_index = om.max_small(cur_it);
            
            if(odd_jump_index != -1){
                valid_jump[cur_index][0] = valid_jump[odd_jump_index][1];
                if(valid_jump[cur_index][0]){total_good_jump += 1;}
            }
            if(even_jump_index != -1){valid_jump[cur_index][1] = valid_jump[even_jump_index][0];}
        }

        return total_good_jump;
    }
};

