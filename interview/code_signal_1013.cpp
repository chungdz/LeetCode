/*
返回a[i - 1] + a[i + 1] = 2 * a[i]的个数 如果越界视作0

二维滑动窗口
3 * 3 的矩阵滑过 3 * n 的矩阵 (n >= 3)，记录窗口里1-9这9个数字全有一个的index

方块下滑
给定m*n的二维矩阵，给定brick，给定obstacle，brick任意一处被obstacle挡住就不能下滑，返回最小的删除obstacle使得brick触底的值

关键：
记录brick最底下的edge的形状，用dict{edge_column: edge_height}记录，然后找到最底下的edge需要下滑x格，然后粉碎所有最下面的
board[edge_height: edge_height + x + 1][edge_column]的obstacles

最大连续序列变式

给定prices，给定0，1数组algo，给定k

total_revenue的定义是对每个prices[i]，algo[i]如果等于1，total_revenue + price[i]，如果等于0， total_revenue - prices[i]
现在将一个连续长为k的algo子串全部设为1，在所有可能性中，返回最大的total_revenue

算出初始的total_revenue，这是累加和用于求子串和的变式，在这里面累加的时候，只有当algo等于0的时候，才累加，因为algo等于1的时候
设置它不会有增益，然后对所有k长的子段求和得到sk[i]，total_revenue + sk[i] * 2就是新的revenue（之前是减去，现在是加上，差了2倍）

**/