/*
 * @lc app=leetcode.cn id=375 lang=cpp
 *
 * [375] 猜数字大小 II
 */
#include <vector>

// @lc code=start
class Solution {
public:
    int getMoneyAmount(int n) {
        // 根据n，任意选择一个数作为结果，然后去猜测，猜错一次增加相对应的数的数目作为成本，
        // 知道猜中相应的数目（猜中的不用算到成本里），给出最小的成本方案
        int min_left;
        int min_right;
        int min;
        int current = 0;
        //std::map<std::string, int> record_vec;
        //for (size_t i = 0; i < n; i++)
        //{
        //    record_vec.push(n*n);
        //}
        int max = n*n;
        std::vector<std::vector<int>> record_vec(n+1, std::vector<int>(n+1));
        //for (int i = 0; i < n; i++)
        //{
        //    for (int j = i; j < n; j++)
        //    {
        //        record_vec.insert(std::pair<std::string, int>(std::string(i) +"-"+std::string(j), n*n));
        //    }
        //    
        //}
        //std::vector<int>(n + 1, INT_MAX);
        //for (int i = 0; i < n+1; i++)
        //{
        //    record_vec.push_back(std::vector<int>(n+1, INT_MAX));
        //    //for (int j = i+1; j < n; j++)
        //    //{
        //    //    //record_vec.push_back(max);
        //    //    //record_vec[i][j] = max;
        //    //    record_vec[i][j] = INT_MAX;
        //    //}
        //}

        std::stack<int> nums;
        int low = 1;
        int highCols = n;
        int highRows = n;
        // 迭代版
        int minNum = n * n;
        for (int i = n-1; i > 0; i--)
        {
            for (int j = i+1; j <= n; j++)
            {
                // 最大是直接在树最优的树顶部加上一个值，这个值是最大的了
                record_vec[i][j] = j + record_vec[i][j-1];
                for (int k = i; k < j; k++)
                {
                    record_vec[i][j] = std::min(record_vec[i][j],
                     k + std::max(record_vec[i][k-1], record_vec[k+1][j]));
                    /* code */
                }
                
            }
            
            /* code */

            /* code */
        }

        return record_vec[1][n];
        // 递归版
        //min = getMaxMoneyAmount(1, n, record_vec);

        //std::cout << "  ";
        //for (size_t i = 0; i < record_vec.size(); i++)
        //{
        //     std::cout << std::setw(11) << i << " ";
        //}
        //std::cout << std::endl;
        //for (size_t i = 0; i < record_vec.size(); i++)
        //{
        //    std::cout << i << " ";
        //    for (size_t j = 0; j < record_vec[i].size(); j++)
        //    {
        //        std::cout << std::setw(11) << record_vec[i][j] << " ";
        //    }
        //    std::cout << std::endl;
        //
        //    /* code */
        //}

        //return min;

        //for (int i = 0; i <= n; i++)
        //{
        //    current = getMaxMoneyAmount(0, i, record_vec) + i + getMaxMoneyAmount(i+1, n, record_vec);
        //    if (current <= min)
        //    {
        //        min = current;
        //    }
        //
        //}
    }

    // 如果采用递归，性能比较差，而且还没有进行剪枝，导致重复计算，需要优化
    int getMaxMoneyAmount(int low, int high, std::vector<std::vector<int>> &record_vec)
    {
        if (low >= high)
        {
            return 0;
        }

        //std::cout << "================================================================================" << std::endl;
        //std::cout << "current low: " << low << ", high: " << high << std::endl;
        int current = 0;
        int min = high * high;
        int preMin;
        int nextMin;
        for (int i = low; i < high; i++)
        {
            // code
            //std::cout << "before: i: " << i << ", record_vec[" << low <<"][" << i << "]="
            // << record_vec[low][i] << ", " << "record_vec[" << std::to_string(i+1)
            //  << "][" << high << "]=" << record_vec[i+1][high] << std::endl;
            if (record_vec[low][i - 1] == INT_MAX)
            {
                /* code */
                record_vec[low][i - 1] = getMaxMoneyAmount(low, i - 1, record_vec);
            }

            if (record_vec[i + 1][high] == INT_MAX)
            {
                /* code */
                record_vec[i + 1][high] = getMaxMoneyAmount(i + 1, high, record_vec);
            }

            //std::cout << "after: i: " << i << ", record_vec[" << low <<"][" << i << "]="
            //<< record_vec[low][i] << ", " << "record_vec[" << std::to_string(i+1)
            //<< "][" << high << "]=" << record_vec[i+1][high] << std::endl;

            //current = record_vec[low][i-1] + i + record_vec[i+1][high];
            if (record_vec[low][i-1] > record_vec[i+1][high])
            {
                current = record_vec[low][i-1] + i;
            }
            else
            {
                current = record_vec[i+1][high] + i;
            }
            if (current < min)
            {
                min = current;
            }
        }
        //std::cout << "================================================================================" << std::endl;
        return min;
    }
};
// @lc code=end

