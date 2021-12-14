#include<algorithm>
#include<vector>
#include<list>
#include<unordered_map>
#include<map>
using namespace std;

/*
295 Find Median from Data Stream

Solution
The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value and the median is the mean of the two middle values.

For example, for arr = [2,3,4], the median is 3.
For example, for arr = [2,3], the median is (2 + 3) / 2 = 2.5.
Implement the MedianFinder class:

MedianFinder() initializes the MedianFinder object.
void addNum(int num) adds the integer num from the data stream to the data structure.
double findMedian() returns the median of all elements so far. Answers within 10-5 of the actual answer will be accepted.
 

Example 1:

Input
["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
[[], [1], [2], [], [3], []]
Output
[null, null, null, 1.5, null, 2.0]

Explanation
MedianFinder medianFinder = new MedianFinder();
medianFinder.addNum(1);    // arr = [1]
medianFinder.addNum(2);    // arr = [1, 2]
medianFinder.findMedian(); // return 1.5 (i.e., (1 + 2) / 2)
medianFinder.addNum(3);    // arr[1, 2, 3]
medianFinder.findMedian(); // return 2.0
 

Constraints:

-105 <= num <= 105
There will be at least one element in the data structure before calling findMedian.
At most 5 * 104 calls will be made to addNum and findMedian.
 

Follow up:

If all integer numbers from the stream are in the range [0, 100], how would you optimize your solution?
If 99% of all integer numbers from the stream are in the range [0, 100], how would you optimize your solution?

基本思想

朴素做法：
维护一个vector，使得它从小到大排序，每次独立查询

优化
维护一个map<number, count>，并且维护第total size / 2 + 1个数的位置，每次插入数字后，更新map和中位数位置，为此需要记录
在这个中位数之前的所有数字的和

其他做法我们用两个优先队列 \textit{queMax}queMax 和 \textit{queMin}queMin 分别记录大于中位数的数和小于等于中位数的数。当累计添加的数的数量为奇数时，\textit{queMin}queMin 中的数的数量比 \textit{queMax}queMax 多一个，此时中位数为 \textit{queMin}queMin 的队头。当累计添加的数的数量为偶数时，两个优先队列中的数的数量相同，此时中位数为它们的队头的平均值。

当我们尝试添加一个数 \textit{num}num 到数据结构中，我们需要分情况讨论：

\textit{num} \leq \max \{\textit{queMin}\}num≤max{queMin}

此时 \textit{num}num 小于等于中位数，我们需要将该数添加到 \textit{queMin}queMin 中。新的中位数将小于等于原来的中位数，因此我们可能需要将 \textit{queMin}queMin 中最大的数移动到 \textit{queMax}queMax 中。

\textit{num} > \max \{\textit{queMin}\}num>max{queMin}

此时 \textit{num}num 大于中位数，我们需要将该数添加到 \textit{queMin}queMin 中。新的中位数将大于等于原来的中位数，因此我们可能需要将 \textit{queMax}queMax 中最小的数移动到 \textit{queMin}queMin 中。

特别地，当累计添加的数的数量为 00 时，我们将 \textit{num}num 添加到 \textit{queMin}queMin 中。

*/

class MedianFinder {
    vector<int> buff;
public:
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        vector<int>::iterator it = lower_bound(buff.begin(), buff.end(), num);
        buff.insert(it, num);
        return;
    }
    
    double findMedian() {
        int bs = buff.size();
        if(bs % 2 == 0){
            int ind = bs / 2;
            int ind2 = bs / 2 - 1;
            double res = buff[ind] + buff[ind2];
            return res / 2;

        }
        else{
            int ind = bs / 2;
            return buff[ind];
        }
    }
};

class MedianFinder {
    map<int, int> num_count;
    int total_size = 0;
    bool isEven = true;
    // the number at total size / 2 + 1
    int cur_middle = 100001;
    map<int, int>::iterator mid_it;
    int cur_sum;
public:
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        if(num_count.find(num) == num_count.end()){
            num_count[num] = 1;
        }
        else{
            num_count[num] += 1;
        }
        total_size += 1;
        isEven = !isEven;

        if(cur_middle == 100001){
            cur_middle = num;
            mid_it = num_count.begin();
            cur_sum = 1;
        }
        else{
            int new_ind = total_size / 2 + 1;
            if(num > cur_middle){
                if(cur_sum < new_ind){
                    ++mid_it;
                    cur_middle = mid_it->first;
                    cur_sum += mid_it->second;
                }
            }
            else if(num == cur_middle){
                cur_sum += 1;
            }
            else{
                cur_sum += 1;
                if(cur_sum - mid_it->second >= total_size / 2 + 1){
                    cur_sum = cur_sum - mid_it->second;
                    --mid_it;
                    cur_middle = mid_it->first;
                }
            }
        }

        return;
    }
    
    double findMedian() {
        if(isEven){
            int ind = total_size / 2;
            map<int, int>::iterator sit = mid_it;
            if(cur_sum - mid_it->second >= ind){
                sit--;
            }
            double res = sit->first + cur_middle;
            return res / 2;
        }
        else{
            return cur_middle;
        }
    }
};