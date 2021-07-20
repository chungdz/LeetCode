#include<vector>
#include <cmath>
using namespace std;

/***
 * 手写堆
 * 
 * 用problem 912来验证堆排序正确性
 * 
 * 主要接口：构造函数，返回排序后数组的函数
 * 关键实现：shiftdown和shiftup以及构造函数
 * 
 * **/

class MyHeap{
    vector<int> *heap;
    bool reverse;

    void build_heap(){
        for(int i = (heap->size() / 2) - 1;i >= 0;i--){
            shift_down(i);
        }
    }

    int parent_index(int cur_index){
        return (cur_index - 1)/2;
    }

    int left_child_index(int cur_index){
        return 2 * cur_index + 1;
    }

    int right_child_index(int cur_index){
        return 2 * cur_index + 2;
    }

    bool prior(int num1, int num2){
        if(!reverse){
            // min heap
            return num1 <= num2;
        }
        else{
            // max heap
            return num1 >= num2;
        }
    }

    void shift_down(int cur_index){

        int left_index = left_child_index(cur_index);
        int right_index = right_child_index(cur_index);
        bool priority_over_left;
        bool priority_over_right;
        bool left_existence = true;
        bool right_existence = true;

        if(left_index < heap->size()){
            priority_over_left = prior((*heap)[cur_index], (*heap)[left_index]);
        }
        else{
            priority_over_left = true;
            left_existence = false;
        }

        if(right_index < heap->size()){
            priority_over_right = prior((*heap)[cur_index], (*heap)[right_index]);
        }
        else{
            priority_over_right = true;
            right_existence = false;
        }

        if(priority_over_left && priority_over_right){
            return;
        }
        // swap and incurrence
        int tmp = (*heap)[cur_index];
        bool swap_left;
        if(left_existence && !right_existence){swap_left = true;}
        else if(!left_existence && right_existence){swap_left = false;}
        else{
            if(prior((*heap)[left_index], (*heap)[right_index])){swap_left = true;}
            else{swap_left = false;}
        }

        if(swap_left){
            (*heap)[cur_index] = (*heap)[left_index];
            (*heap)[left_index] = tmp;
            shift_down(left_index);
        }
        else{
            (*heap)[cur_index] = (*heap)[right_index];
            (*heap)[right_index] = tmp;
            shift_down(right_index);
        }
    }

    void shift_up(int cur_index){
        int pindex = parent_index(cur_index);
        if(pindex < 0){return;}
        
        if(prior((*heap)[cur_index], (*heap)[pindex])){
            int tmp = (*heap)[pindex];
            (*heap)[pindex] = (*heap)[cur_index];
            (*heap)[cur_index] = tmp;

            shift_up(pindex);
        }
    }
public:
    vector<int> heap_array(){return *heap;}

    MyHeap(vector<int>& origin_array, bool reverse=false){
        heap = &origin_array;
        this->reverse = reverse;
        build_heap();
    }

    int pop_head(){
        int tmp = (*heap)[0];
        (*heap)[0] = (*heap)[heap->size() - 1];
        heap->pop_back();
        shift_down(0);
        return tmp;
    }

    vector<int> sorted_array(){
        vector<int> new_array(heap->size());
        int total_size = heap->size();
        for(int i = 0;i < total_size;i++){
            new_array[i] = pop_head();
        }
        return new_array;
    }

    void insert(int value){
        heap->push_back(value);
        shift_up(heap->size() - 1);
    }
};

class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        MyHeap h(nums);
        return h.sorted_array();
    }
};