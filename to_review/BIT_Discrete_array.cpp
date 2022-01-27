#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;

/*
BIT 和 离散化数组
注意BIT数组从1开始有意义
*/

class BIT{
    int *bit;
    int n;
public:
    BIT(int number){
        n = number;
        bit = new int[n + 1];
        for(int j = 1;j <= n;++j){
            bit[j] = 0;
        }
    }

    int _sum(int i){
        int s = 0;
        while(i > 0){
            s += bit[i];
            i -= i & -i;
        }
        return s;
    }

    void _add(int i, int x){
        while(i <= n){
            bit[i] += x;
            i += i & -i;
        }
    }

    void _print(){
        for(int i = 1;i <= n;++i){cout << bit[i] << ' ';}
        cout << endl;
    }
};


vector<int> discretize_array(vector<int>& origin, int start = 0){
    
    vector<int> s(origin);
    sort(s.begin(), s.end());
    vector<int>::iterator new_end = unique(s.begin(), s.end());

    int total_size = origin.size();
    vector<int> res(total_size);
    for(int i = 0;i < total_size;++i){
        res[i] = lower_bound(s.begin(), new_end, origin[i]) - s.begin() + 1;
    }
    return res;
}