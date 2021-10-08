#include<algorithm>
using namespace std;

class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = nullptr;
        right = nullptr;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
/*

426 Convert Binary Search Tree to Sorted Doubly Linked List

Convert a Binary Search Tree to a sorted Circular Doubly-Linked List in place.

You can think of the left and right pointers as synonymous to the predecessor and successor pointers in a doubly-linked list. For a circular doubly linked list, the predecessor of the first element is the last element, and the successor of the last element is the first element.

We want to do the transformation in place. After the transformation, the left pointer of the tree node should point to its predecessor, and the right pointer should point to its successor. You should return the pointer to the smallest element of the linked list.

 

Example 1:



Input: root = [4,2,5,1,3]


Output: [1,2,3,4,5]

Explanation: The figure below shows the transformed BST. The solid line indicates the successor relationship, while the dashed line means the predecessor relationship.

Example 2:

Input: root = [2,1,3]
Output: [1,2,3]
Example 3:

Input: root = []
Output: []
Explanation: Input is an empty tree. Output is also an empty Linked List.
Example 4:

Input: root = [1]
Output: [1]
 

Constraints:

The number of nodes in the tree is in the range [0, 2000].
-1000 <= Node.val <= 1000
All the values of the tree are unique.

基本思想

遍历存入vector，排序，重组
**/
bool mcmp(const Node* r1, const Node* r2){
    return r1->val < r2->val;
}

class Solution {
    vector<Node*> node_list;
public:
    Node* treeToDoublyList(Node* root) {
        if(root == nullptr){return nullptr;}
        pre_order(root);
        sort(node_list.begin(), node_list.end(), mcmp);
        int ns = node_list.size();
        Node *head = node_list[0], *tail = node_list[ns - 1];
        head->left = tail;
        tail->right = head;

        if(ns < 2){
            return head;
        }

        head->right = node_list[1];
        tail->left = node_list[ns - 2];
        for(int i = 1;i < ns - 1;++i){
            node_list[i]->left = node_list[i - 1];
            node_list[i]->right = node_list[i + 1];
        }
        return head;
    }

    void pre_order(Node* root){
        if(root == nullptr){return;}
        node_list.push_back(root);
        pre_order(root->left);
        pre_order(root->right);
    }
};