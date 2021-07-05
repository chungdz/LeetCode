/*
二叉树的层序遍历
给你一个二叉树，请你返回其按 层序遍历 得到的节点值。 （即逐层地，从左到右访问所有节点）。
*/
#include <vector>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/*
维护一个队列，遇到新节点返回值，然后在队列尾部压入数据
需要标记层数，所以队列里保存一个pair
*/
typedef pair<TreeNode*, int> QueueItem;

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<QueueItem> infoq;
        infoq.push(QueueItem(root, 0));
        vector<vector<int>> result;

        if(!root){
            return result;
        }

        while(infoq.size() > 0){
            vector<int> tmp_list;
            int level = infoq.front().second;

            while(true){
                TreeNode* new_node = infoq.front().first;
                int new_level = infoq.front().second;
                if(new_level != level){
                    result.push_back(tmp_list);
                    break;
                }

                tmp_list.push_back(new_node->val);
                if(new_node->left){
                    infoq.push(QueueItem(new_node->left, level + 1));
                }
                if(new_node->right){
                    infoq.push(QueueItem(new_node->right, level + 1));
                }

                infoq.pop();
                if(infoq.size() <= 0){
                    result.push_back(tmp_list);
                    break;
                }
            }
        }

        return result;
    }
};