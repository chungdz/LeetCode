#include<vector>
#include<set>
#include<map>
#include<algorithm>
#include<iostream>
using namespace std;

//ordered by key
template <class KeyType, class ValueType>
class Ordered_Map{
    vector<KeyType> ordered_key;
    map<KeyType, ValueType> my_map;
public:
    bool find(KeyType cur_key){
        typename map<KeyType, ValueType>::iterator it = my_map.find(cur_key);
        if(it != my_map.end()){
            return true;
        }
        return false;
    }

    void update(KeyType cur_key, ValueType cur_value){
        my_map[cur_key] = cur_value;
    }

    ValueType get_value(KeyType cur_key){
        return my_map[cur_key];
    }

    typename vector<KeyType>::iterator find_first_iterator(KeyType cur_key){
        return lower_bound(ordered_key.begin(), ordered_key.end(), cur_key);
    }

    void print_map(){
        for(KeyType k: ordered_key){
            cout << k << " " << my_map[k] << endl;
        }
        cout << endl;
    }

    void insert(typename vector<KeyType>::iterator it, KeyType cur_key, ValueType cur_value){
        ordered_key.insert(it, cur_key);
        my_map[cur_key] = cur_value;
    }
    //for even jump
    ValueType max_small(typename vector<KeyType>::iterator it){
        if(it == ordered_key.begin()){return -1;}

        KeyType small_key = *(--it);
        return my_map[small_key];
    }
    //for odd jump
    ValueType min_large(typename vector<KeyType>::iterator it){
        if(it == ordered_key.end()){return -1;}

        KeyType large_key = *it;
        return my_map[large_key];
    }
};

//ordered by key
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