/*
 * @lc app=leetcode.cn id=372 lang=cpp
 *
 * [372] 超级次方
 */

// @lc code=start
class Solution {
public:
    int getNum(int num, int iter_nums, int expNums, int stand)
    {
        //int result = 1;
        int mod = num % 1337;
        int result = mod;
        for (int i = 0; i < expNums; i++)
        {
            mod = result;
            for (int i = 0; i < iter_nums; i++)
            {
                //result = result*tmp;
                result = (result * mod) % 1337;
            }
        }
        return result;
    }
    // 速度慢了，需要优化
    int superPow(int a, vector<int> &b)
    {
        int result = 1;
        int mod_a = a % 1337;
        int length = b.size();
        std::vector<int> index_nums;
        index_nums.push_back(1);
        index_nums.push_back(mod_a);
        index_nums.push_back((index_nums[1]*mod_a) % 1337);
        index_nums.push_back((index_nums[2]*mod_a) % 1337);
        index_nums.push_back((index_nums[3]*mod_a) % 1337);
        index_nums.push_back((index_nums[4]*mod_a) % 1337);
        index_nums.push_back((index_nums[5]*mod_a) % 1337);
        index_nums.push_back((index_nums[6]*mod_a) % 1337);
        index_nums.push_back((index_nums[7]*mod_a) % 1337);
        index_nums.push_back((index_nums[8]*mod_a) % 1337);
        //int last_index;
        std::vector<int> last_indexs;
        last_indexs.push_back(1);
        last_indexs.push_back(1);
        last_indexs.push_back(1);
        last_indexs.push_back(1);
        last_indexs.push_back(1);
        last_indexs.push_back(1);
        last_indexs.push_back(1);
        last_indexs.push_back(1);
        last_indexs.push_back(1);
        last_indexs.push_back(1);
        int current_exp;
        int iter_nums = 9;
        int tmp_num;
        for (int i = length - 1; i >= 0; i--)
        {
            current_exp = b[i];
            if (i < length - 1)
            {

                tmp_num = last_indexs[current_exp];
                for (size_t j = 0; j < last_indexs.size(); j++)
                {
                    if (j != current_exp)
                        last_indexs[j]++;
                    else
                        last_indexs[j] = 1;
                }

                //index_nums[0] = 1;
                //iter_nums = tmp_num * 10 - 1;
                // 遍历次数应该不是乘以10，而是10的次方
                iter_nums = 10 - 1;
                index_nums[current_exp] = getNum(index_nums[current_exp], iter_nums, tmp_num, 1337);
            }

            result = (result * index_nums[current_exp]) % 1337;
           // std::cout << "i: " << i << "current_exp " << current_exp << ", tmp_num: " << tmp_num << ", iter_nums: " << iter_nums
              //        << ", index_nums[current_exp]: " << index_nums[current_exp] << ", result " << result << std::endl;
            // updateStatus
        }
        return result;
    }
};
// @lc code=end
