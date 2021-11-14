/*
 * @lc app=leetcode.cn id=374 lang=cpp
 *
 * [374] 猜数字大小
 */

// @lc code=start
/** 
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return 	     -1 if num is lower than the guess number
 *			      1 if num is higher than the guess number
 *               otherwise return 0
 * int guess(int num);
 */

class Solution {
public:
    int guessNumber(int n) {
        unsigned int middle = n/2;
        unsigned int low = 1;
        unsigned int high = n;
        if (n == 1)
            return 1;
        int result;
        while ((result = guess(middle)) != 0)
        {
            if (result == -1)
            {
                high = middle;
                middle = (low + middle) / 2;

            }
            else
            {
                low = middle;
                if ((middle + high) / 2 != middle)
                    middle = (middle + high) / 2;
                else
                    middle += 1;
            }
            //std::cout << "middle " << std::to_string(middle) << ", result " << std::to_string(result) << std::endl;

        }
        return middle;
        
    }
};
// @lc code=end

