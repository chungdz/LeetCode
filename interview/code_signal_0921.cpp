#include<string>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
#include<map>
#include<set>
#include <iostream>
#include <queue>
#include <stdlib.h>
using namespace std;


/*

输出正方形的框，给定n，输出*和空格组成的正方形

**/




/*

给定字符串（数字序列）和k，每次把字符串分成k长度的字串，字串内部数字相加，再重新把所有结果按顺序合并得到新的字串，递归直到长度小于等于k

**/



/*

国际象棋黑白格

给定字矩形，重新排序，黑白格分别排序

**/



/*

给定一维坐标上的路灯和位置和半径，找到最亮的地方（路灯有多个）
路灯数量最大10^5，坐标最大10^9

滑动窗口问题

记录所有边缘点，排序去重
用一个最小堆，保存路灯interval，（排序方式为路灯范围的右坐标）
每次到达一个新的interval，检查是否需要新加路灯，检查堆内路灯是否在覆盖，不覆盖的删掉，堆的大小就是灯的数量

**/