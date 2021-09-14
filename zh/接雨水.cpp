/*

42

给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。

上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接 6 个单位的雨水（蓝色部分表示雨水）。 感谢 Marcos 贡献此图。

示例:

输入: [0,1,0,2,1,0,1,3,2,1,2,1]
输出: 6
*/
#include <vector>
#include <iostream>
using namespace std;

/*
解法一：
扫描两遍，第一遍得到水面高度，第二遍得到水深
水面高度初始化全为0

得到左边墙高之后，找到右边第一个大于等于它的墙，这两个之间的水位就是左边墙的高度
找不到返回最高的墙值和位置,在最高墙和基准墙之间的水位为最高的墙的值，水位减去墙高就是水深
下一个基准墙为上一次的最高墙，如果没有找到任何一个最高的墙，就结束扫描

从0位置到n - 1的位置全部扫一遍，水位取最高值
剪枝：如果当前位置水位已经大于等于墙高，就没必要再扫描了

应该可以把两遍合成一遍
*/
class Solution {
public:
    int trap(vector<int>& height) {
        int length = height.size();
        
        int idx = 0;
        int result = 0;
        while(idx < length){
            
            int next_pos = -1;
            int high_value = 0;
            int high_pos = -1;
            for(int j = idx + 1;j < length;j++){
                if(height[j] >= height[idx]){
                    next_pos = j;
                    break;
                }
                else if(height[j] > high_value){
                    high_pos = j;
                    high_value = height[j];
                }
            }
            if(next_pos != -1){
                for(int k = idx;k < next_pos;k++){
                    if(height[idx] > height[k]){result += height[idx] - height[k];}
                }
                idx = next_pos;
            }
            else if(high_pos != -1){
                for(int k = idx;k < high_pos;k++){
                    if(high_value > height[k]){result += high_value - height[k];}
                }
                idx = high_pos;
            }
            else{break;}
        }

        return result;
    }
};


int main()
{
	Solution c;
    vector<int> v = {0,1,0,2,1,0,1,3,2,1,2,1};
    c.trap(v);
}

/*
方法 3：栈的应用
直观想法

我们可以不用像方法 2 那样存储最大高度，而是用栈来跟踪可能储水的最长的条形块。使用栈就可以在一次遍历内完成计算。

我们在遍历数组时维护一个栈。如果当前的条形块小于或等于栈顶的条形块，我们将条形块的索引入栈，意思是当前的条形块被栈中的前一个条形块界定。如果我们发现一个条形块长于栈顶，我们可以确定栈顶的条形块被当前条形块和栈的前一个条形块界定，因此我们可以弹出栈顶元素并且累加答案到 \text{ans}ans 。

算法

使用栈来存储条形块的索引下标。
遍历数组：
当栈非空且 \text{height}[current]>\text{height}[st.top()]height[current]>height[st.top()]
意味着栈中元素可以被弹出。弹出栈顶元素 \text{top}top。
计算当前元素和栈顶元素的距离，准备进行填充操作
\text{distance} = \text{current} - \text{st.top}() - 1distance=current−st.top()−1
找出界定高度
\text{bounded\_height} = \min(\text{height[current]}, \text{height[st.top()]}) - \text{height[top]}bounded_height=min(height[current],height[st.top()])−height[top]
往答案中累加积水量\text{ans} \mathrel{+}= \text{distance} \times \text{bounded\_height}ans+=distance×bounded_height
将当前索引下标入栈
将 \text{current}current 移动到下个位置

作者：LeetCode
链接：https://leetcode-cn.com/problems/trapping-rain-water/solution/jie-yu-shui-by-leetcode/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/

/*
方法 4：使用双指针
直观想法

和方法 2 相比，我们不从左和从右分开计算，我们想办法一次完成遍历。
从动态编程方法的示意图中我们注意到，只要 \text{right\_max}[i]>\text{left\_max}[i]right_max[i]>left_max[i] （元素 0 到元素 6），积水高度将由 left_max 决定，类似地 \text{left\_max}[i]>\text{right\_max}[i]left_max[i]>right_max[i]（元素 8 到元素 11）。
所以我们可以认为如果一端有更高的条形块（例如右端），积水的高度依赖于当前方向的高度（从左到右）。当我们发现另一侧（右侧）的条形块高度不是最高的，我们则开始从相反的方向遍历（从右到左）。
我们必须在遍历时维护 \text{left\_max}left_max 和 \text{right\_max}right_max ，但是我们现在可以使用两个指针交替进行，实现 1 次遍历即可完成。

算法

初始化 \text{left}left 指针为 0 并且 \text{right}right 指针为 size-1
While \text{left}< \text{right}left<right, do:
If \text{height[left]}height[left] < \text{height[right]}height[right]
If \text{height[left]} \geq \text{left\_max}height[left]≥left_max, 更新 \text{left\_max}left_max
Else 累加 \text{left\_max}-\text{height[left]}left_max−height[left] 到 \text{ans}ans
\text{left}left = \text{left}left + 1.
Else
If \text{height[right]} \geq \text{right\_max}height[right]≥right_max, 更新 \text{right\_max}right_max
Else 累加 \text{right\_max}-\text{height[right]}right_max−height[right] 到 \text{ans}ans
\text{right}right = \text{right}right - 1.


作者：LeetCode
链接：https://leetcode-cn.com/problems/trapping-rain-water/solution/jie-yu-shui-by-leetcode/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
