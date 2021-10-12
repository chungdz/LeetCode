#include<vector>
#include<unordered_map>
#include<algorithm>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/*
173 Binary Search Tree Iterator

Implement the BSTIterator class that represents an iterator over the in-order traversal of a binary search tree (BST):

BSTIterator(TreeNode root) Initializes an object of the BSTIterator class. The root of the BST is given as part of the constructor. The pointer should be initialized to a non-existent number smaller than any element in the BST.
boolean hasNext() Returns true if there exists a number in the traversal to the right of the pointer, otherwise returns false.
int next() Moves the pointer to the right, then returns the number at the pointer.
Notice that by initializing the pointer to a non-existent smallest number, the first call to next() will return the smallest element in the BST.

You may assume that next() calls will always be valid. That is, there will be at least a next number in the in-order traversal when next() is called.

 

Example 1:


Input
["BSTIterator", "next", "next", "hasNext", "next", "hasNext", "next", "hasNext", "next", "hasNext"]
[[[7, 3, 15, null, null, 9, 20]], [], [], [], [], [], [], [], [], []]
Output
[null, 3, 7, true, 9, true, 15, true, 20, false]

Explanation
BSTIterator bSTIterator = new BSTIterator([7, 3, 15, null, null, 9, 20]);
bSTIterator.next();    // return 3
bSTIterator.next();    // return 7
bSTIterator.hasNext(); // return True
bSTIterator.next();    // return 9
bSTIterator.hasNext(); // return True
bSTIterator.next();    // return 15
bSTIterator.hasNext(); // return True
bSTIterator.next();    // return 20
bSTIterator.hasNext(); // return False
 

Constraints:

The number of nodes in the tree is in the range [1, 10^5].
0 <= Node.val <= 10^6
At most 10^5 calls will be made to hasNext, and next.
 

Follow up:

Could you implement next() and hasNext() to run in average O(1) time and use O(h) memory, where h is the height of the tree?

基本思想：
保证被访问的节点一定先被访问了左子树

init：
保存root，找到最小值，新建一个树节点，保存更小值，假设更小值在最小值左子树，保存所有路径上的树节点

has next
要么有更高的树节点，要么有右子树

next
如果有右子树，先走右子树，找到右子树中最小值，保存路径上的值

如果没有右子树，返回之前保存的路径值，访问并删除出队列
**/

class BSTIterator {
    TreeNode *root, *it, *start;
    vector<TreeNode*> higher;
public:
    BSTIterator(TreeNode* root) {
        this->root = root;
        it = root;
        while(it->left != nullptr){
            higher.push_back(it);
            it = it->left;
        }
        start =  new TreeNode(it->val - 1);
        higher.push_back(it);
        it = start;
    }
    
    int next() {
        if(it->right == nullptr){
            it = higher.back();
            higher.pop_back();
        }
        else{
            it = it->right;
            while(it->left != nullptr){
                higher.push_back(it);
                it = it->left;
            }
        }
        return it->val;
    }
    
    bool hasNext() {
        if(higher.size() > 0 || it->right != nullptr){
            return true;
        }
        return false;
    }
};
