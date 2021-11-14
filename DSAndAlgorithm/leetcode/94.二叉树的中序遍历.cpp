//#include <stack>
/*
 * @lc app=leetcode.cn id=94 lang=cpp
 *
 * [94] 二叉树的中序遍历
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        if (root == nullptr)
            return result;
        stack<TreeNode*> tempNode;
        TreeNode* tempPtr = nullptr;
        TreeNode* tempPtr1 = nullptr;
        tempNode.push(root);
        bool isRoot = true;
        while (!tempNode.empty())
        {
            tempPtr = tempNode.top();
            while (tempPtr->left != nullptr)
            {
                if (tempPtr->right != nullptr)
                {
                    tempNode.pop();
                    tempNode.push(tempPtr->right);
                    tempNode.push(tempPtr);
                    tempPtr->right = nullptr;

                }
                tempPtr1 = tempPtr->left;
                tempPtr->left = nullptr;
                tempPtr = tempPtr1;

                tempNode.push(tempPtr);
            }

            tempPtr = tempNode.top();
            tempNode.pop();
            result.push_back(tempPtr->val);
            if (tempPtr->right != nullptr)
                tempNode.push(tempPtr->right);

        }

        return result;
    }
};
// @lc code=end
