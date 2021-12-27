/*
 * @lc app=leetcode.cn id=61 lang=cpp
 *
 * [61] 旋转链表
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    // 优化时间
    ListNode* rotateRight(ListNode* head, int k) {
        int node_size = 0;
        ListNode* resultNode = head;
        if (head == nullptr)
        {
            return head;
        }
        
        ListNode* endNode = head;
        while (endNode->next != nullptr)
        {
            node_size++;
            endNode = endNode->next;
        }
        node_size++;
        int cycle_times = (node_size - (k % (node_size)))%node_size;
        
        ListNode* tmpNode = head;
        ListNode* reverseNode = head;
        //cout << "node " << cycle_times << endl;
        for (size_t i = 0; i < cycle_times; i++)
        {
            tmpNode = resultNode;
            resultNode = resultNode->next;
        }
        if (cycle_times != 0)
        {
            endNode->next = head;
            tmpNode->next = nullptr;
        }
        return resultNode;
        
        
        //return 
        
    }
};
// @lc code=end

