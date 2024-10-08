/*
 * @lc app=leetcode.cn id=83 lang=cpp
 *
 * [83] 删除排序链表中的重复元素
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
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* start = head;
        ListNode* next;
        while( start != nullptr)
        {
            next = start->next;
            if (next != nullptr)
            {
                if (start->val == next->val)
                {
                    start->next = next->next;
                    next->next = nullptr;
                    delete next;
                    next = nullptr;
                    
                }
                else
                {
                    start = next;
                }
            }
            else
            {
                break;
            }
        }
        return head;
    }
};
// @lc code=end

