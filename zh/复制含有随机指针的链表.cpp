/*
138

给定一个链表，每个节点包含一个额外增加的随机指针，该指针可以指向链表中的任何节点或空节点。

要求返回这个链表的 深拷贝。 

我们用一个由 n 个节点组成的链表来表示输入/输出中的链表。每个节点用一个 [val, random_index] 表示：

val：一个表示 Node.val 的整数。
random_index：随机指针指向的节点索引（范围从 0 到 n-1）；如果不指向任何节点，则为  null 。

提示：

-10000 <= Node.val <= 10000
Node.random 为空（null）或指向链表中的节点。
节点数目不超过 1000 。
*/
#include <map>
using namespace std;

class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
/*
解法一
维护一个键值对，key为原链表节点指针，value为新链表相同位置的节点指针
第一遍建立新表，构建键值对
第二遍补充random，使用键值对

运行中出现了栈溢出的情况，将map的声明改为new的形式放入堆中
*/
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(!head){
            return NULL;
        }

        Node* root = new Node(head->val);
        map<Node*, Node*>* pos = new map<Node*, Node*>();

        Node* myPoint = root;
        Node* givenPoint = head;
        while(givenPoint){
            (*pos)[givenPoint] = myPoint;
            if(givenPoint->next){
                myPoint->next = new Node(givenPoint->next->val);
            }
            givenPoint = givenPoint->next;
            myPoint = myPoint->next;
        }

        myPoint = root;
        givenPoint = head;
        while(givenPoint){
            if(givenPoint->random){
                myPoint->random = (*pos)[givenPoint->random];
            }
            givenPoint = givenPoint->next;
            myPoint = myPoint->next;
        }

        return root;
    }
};

/*
解法二：
回溯
从当前节点出发，记录被访问过的点，没有被访问过就创建一个新的
*/
class Solution2 {
map<Node*, Node*>* pos = new map<Node*, Node*>();
public:
    Node* copyRandomList(Node* head) {
        if (!head) {
            return NULL;
        }

        if (pos->find(head) != pos->end()) {
            return (*pos)[head];
        }

        // Create a new node with the value same as old node. (i.e. copy the node)
        Node* node = new Node(head->val);

        // Save this value in the hash map. This is needed since there might be
        // loops during traversal due to randomness of random pointers and this would help us avoid
        // them.
        (*pos)[head] = node;

        // Recursively copy the remaining linked list starting once from the next pointer and then from
        // the random pointer.
        // Thus we have two independent recursive calls.
        // Finally we update the next and random pointers for the new node created.
        node->next = copyRandomList(head->next);
        node->random = copyRandomList(head->random);

        return node;
    }
};

/*
解法三
在复制原节点，在它后面插入这个新的节点，这样子原节点random指向的节点必定在新节点random指向的节点之后
之后将链表还原
*/
