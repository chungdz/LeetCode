#include<queue>
#include<string>
#include<sstream>
using namespace std;

/*
297

Serialize and Deserialize Binary Tree

Solution
Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.

Clarification: The input/output format is the same as how LeetCode serializes a binary tree. You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.

 

Example 1:


Input: root = [1,2,3,null,null,4,5]
Output: [1,2,3,null,null,4,5]
Example 2:

Input: root = []
Output: []
Example 3:

Input: root = [1]
Output: [1]
Example 4:

Input: root = [1,2]
Output: [1,2]
 

Constraints:

The number of nodes in the tree is in the range [0, 10^4].
-1000 <= Node.val <= 1000



基本思想

将树节点存在数组中，要么就按照常规方法
i 的左子树在2 * i + 1，右子树在2 * i + 2
这个时候需要用宽度优先搜索，来遍历树，同时记录子树为空指针在每一层的数量，如果子树空指针 = 当前层节点数量 * 2，就说明树遍历完了

非常规方法
额外开销两个数组，一个存左子树，一个存右子树

标准答案

深度优先搜索，有nullptr记录null，重建树时用同样的顺序遍历返回

**/

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/*


正常结构TLE



**/

class Codec {
    vector<int> series_tree;
    int nullptr_number = 2000;
    int ssize;

    vector<string> tokenize(string s, string del = " "){
        int start = 0;
        int end = s.find(del);
        vector<string> all_substr;
        while (end != -1) {
            all_substr.push_back(s.substr(start, end - start));
            start = end + del.size();
            end = s.find(del, start);
        }
        all_substr.push_back(s.substr(start, end - start));
        return all_substr;
    }

    TreeNode *return_a_tree(int cur_index){
        int cur_v = series_tree[cur_index];
        if(cur_v == nullptr_number){return nullptr;}

        TreeNode *newn = new TreeNode(cur_v);
        int left_index = cur_index * 2 + 1;
        int right_index = cur_index * 2 + 2;
        if(left_index >= ssize){
            newn->left = nullptr;
        }
        else{
            newn->left = return_a_tree(left_index);
        }

        if(right_index >= ssize){
            newn->right = nullptr;
        }
        else{
            newn->right = return_a_tree(right_index);
        }
        
        return newn;
    }
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string res = "";
        if(root == nullptr){return res;}

        series_tree.clear();
        queue<TreeNode*> bfs;
        bfs.push(root);
        int level = 0;
        int cur_level_num = 1;
        int nxt_level_num = 2 * cur_level_num;
        int children_null = 0;
        int remain_num = cur_level_num;

        while(true){
            TreeNode *cur_node = bfs.front();
            bfs.pop();
            if(cur_node != nullptr){
                series_tree.push_back(cur_node->val);
                bfs.push(cur_node->left);
                bfs.push(cur_node->right);

                if(cur_node->left == nullptr){children_null += 1;}
                if(cur_node->right == nullptr){children_null += 1;}
            }
            else{
                series_tree.push_back(nullptr_number);
                children_null += 2;
                bfs.push(nullptr);
                bfs.push(nullptr);
            }

            remain_num -= 1;
            if(remain_num == 0){
                if(children_null == nxt_level_num){break;}
                cur_level_num = nxt_level_num;
                nxt_level_num = cur_level_num * 2;
                remain_num = cur_level_num;
                children_null = 0;
                level += 1;
            }
        }

        for(int value: series_tree){
            res += to_string(value) + " ";
        }

        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if(data == ""){return nullptr;}

        series_tree.clear();
        stringstream ss(data);
        string v;
        while(ss >> v){
            series_tree.push_back(stoi(v));
        }
        ssize = series_tree.size();

        return return_a_tree(0);
    }
};

/*



额外开辟新的空间



**/

class Codec {
    vector<int> series_tree;
    vector<int> l_child;
    vector<int> r_child;
    int nullptr_number = 200000;

    vector<string> tokenize(string s, string del = " "){
        int start = 0;
        int end = s.find(del);
        vector<string> all_substr;
        while (end != -1) {
            all_substr.push_back(s.substr(start, end - start));
            start = end + del.size();
            end = s.find(del, start);
        }
        all_substr.push_back(s.substr(start, end - start));
        return all_substr;
    }

    int build_tree(TreeNode *root){
        series_tree.push_back(root->val);
        l_child.push_back(nullptr_number);
        r_child.push_back(nullptr_number);

        int cur_index = series_tree.size() - 1;
        if(root->left != nullptr){
            l_child[cur_index] = build_tree(root->left);
        }
        if(root->right != nullptr){
            r_child[cur_index] = build_tree(root->right);
        }

        return cur_index;
    }

    TreeNode *return_a_tree(int cur_index){
        int cur_v = series_tree[cur_index];
        TreeNode *newn = new TreeNode(cur_v);

        int left_index = l_child[cur_index];
        int right_index = r_child[cur_index];
        if(left_index == nullptr_number){
            newn->left = nullptr;
        }
        else{
            newn->left = return_a_tree(left_index);
        }

        if(right_index == nullptr_number){
            newn->right = nullptr;
        }
        else{
            newn->right = return_a_tree(right_index);
        }
        
        return newn;
    }
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string res = "";
        if(root == nullptr){return res;}

        series_tree.clear();
        l_child.clear();
        r_child.clear();
        build_tree(root);
        
        for(int value: series_tree){
            res += to_string(value) + " ";
        }
        res += "# ";
        for(int value: l_child){
            res += to_string(value) + " ";
        }
        res += "# ";
        for(int value: r_child){
            res += to_string(value) + " ";
        }

        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if(data == ""){return nullptr;}

        series_tree.clear();
        l_child.clear();
        r_child.clear();
        vector<string> tmp = tokenize(data, "#");

        stringstream ss(tmp[0]);
        string v;
        while(ss >> v){
            series_tree.push_back(stoi(v));
        }
        
        stringstream s2(tmp[1]);
        while(s2 >> v){
            l_child.push_back(stoi(v));
        }

        stringstream s3(tmp[2]);
        while(s3 >> v){
            r_child.push_back(stoi(v));
        }


        return return_a_tree(0);
    }
};

/*

标准答案

**/

class Codec {
    string res;
    int null_num = 200000;

    TreeNode *return_a_tree(vector<int>& series_tree){
        int cur_num = series_tree.front();
        series_tree.erase(series_tree.begin());
        if(cur_num == null_num){return nullptr;}

        TreeNode *newn = new TreeNode(cur_num);
        newn->left = return_a_tree(series_tree);
        newn->right = return_a_tree(series_tree);

        return newn;
    }

    void build_tree(TreeNode *root){
        if(root == nullptr){
            res += to_string(null_num) + " ";
            return;
        }
        else{
            res += to_string(root->val) + " ";
            build_tree(root->left);
            build_tree(root->right);
        }
        return;
    }
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        res = "";
        build_tree(root);
        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        
        stringstream ss(data);
        string v;
        vector<int> series_tree;
        while(ss >> v){
            series_tree.push_back(stoi(v));
        }
        return return_a_tree(series_tree);
    }
};