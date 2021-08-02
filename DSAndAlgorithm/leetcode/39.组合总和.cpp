/*
 * @lc app=leetcode.cn id=39 lang=cpp
 *
 * [39] 组合总和
 */

// @lc code=start
//#include <stack>
//using namespace std;
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int> &candidates, int target)
    {
        vector<vector<int>> result;
        int length = (int)candidates.size();
        sort(candidates.begin(), candidates.end());
        vector<int> numStack;
        int sum = 0;
        //int maxSize = 0;
        int startPosition = 0;
        /*
        if (length > 1 && candidates[0] == 0)
        {
            maxSize = target / candidates[1];
        }
        else */
        if (length == 0)
        {
            return result;
        }
        /*
        else
        {
            maxSize = target / candidates[0];
        }
        */
        for (int i = 0; i < length; i++)
        {

            if (candidates[i] <= target)
            {
                numStack.push_back(i);
                sum = candidates[i];
                startPosition = i;
               // cout << "cycle position " << to_string(startPosition) << endl;
                while (!numStack.empty())
                {
                    //cout << "position " << to_string(startPosition) << endl;
                    if (sum < target)
                    {
                        //cout << " + " << to_string(candidates[startPosition]);
                        sum += candidates[startPosition];
                        numStack.push_back(startPosition);
                    }
                    else if (sum > target)
                    {
                        //cout << " - " << to_string(candidates[numStack.back()]);
                        sum = sum - candidates[numStack.back()];
                        numStack.pop_back();
                        //numStack.erase(numStack.size);

                        //cout << "3.";
                        startPosition = numStack.back() + 1;
                        while (startPosition == length && numStack.size() > 2)
                        {
                            //cout << " - " << to_string(candidates[numStack.back()]);
                            sum -= candidates[numStack.back()];
                            numStack.pop_back();
                            startPosition = numStack.back() + 1;
                        }
                        //cout << " - " << to_string(candidates[numStack.back()]);
                        sum -= candidates[numStack.back()];
                        numStack.pop_back();
                    }
                    else
                    {
                        //cout << "result line is ";
                        vector<int> solve;
                        for (auto iter = numStack.begin(); iter != numStack.end(); iter++)
                        {
                            cout << to_string(candidates[*iter]) << " ";
                            solve.push_back(candidates[*iter]);
                        }
                        //cout << endl;
                        result.push_back(solve);

                        //cout << "5. " << endl;
                        if (numStack.size() > 1)
                        {
                            sum -= candidates[numStack.back()];
                            numStack.pop_back();
                            startPosition = numStack.back() + 1;
                            // 用于删除尾部相同部位达到了最大位置的数组
                            while (startPosition == length && numStack.size() > 2)
                            {
                                //cout << " - " << to_string(candidates[numStack.back()]);
                                sum -= candidates[numStack.back()];
                                numStack.pop_back();
                                startPosition = numStack.back() + 1;
                            }
                            sum -= candidates[numStack.back()];
                            numStack.pop_back();
                        }
                        else
                        {
                            numStack.clear();
                            break;
                        }
                    }
                    if (startPosition >= length)
                    {
                        numStack.clear();
                        break;
                    }
                }
                //cout << endl;
            }
            else
            {
                break;
            }
            //sum = 0;
        }
        return result;
    }
};
// @lc code=end
