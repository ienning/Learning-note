/*
 * @lc app=leetcode.cn id=68 lang=cpp
 *
 * [68] 文本左右对齐
 */

// @lc code=start
#include <string>
#include <vector>
#include <iostream>

using namespace std;
class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        int wordSize = words.size();
        vector<string> reArrangeWords;
        int spaceNums = 0;
        int lineWords = 0;
        int index = 0;
        int sum = 0;
        for (int i = 0; i < wordSize; i++)
        {
            if (maxWidth < words[i].length())
            {
                return reArrangeWords;
            }
        }

        while ((index < wordSize) || (index == wordSize && sum > maxWidth+1))
        {
            //cout << "index " << to_string(index) << ", sum " << to_string(sum)
            //<< ", lineWords " << to_string(lineWords) << endl;
            if (sum <= maxWidth+1)
            {
                sum += words[index].length() + 1;
                lineWords++;
            }
            else
            {
                lineWords--;
                if (lineWords == 0)
                {
                    reArrangeWords.push_back(words[index-1]);
                    sum = 0;
                    continue;
                }
                index--;
                sum = sum - words[index--].length() - 2;
                spaceNums = maxWidth - sum + lineWords - 1;
                //cout << "2. index " << to_string(index) << ", sum " << to_string(sum)
                     //<< ", lineWords " << to_string(lineWords) << ", spaceNum " << to_string(spaceNums) << endl;
                if (lineWords == 1)
                {
                    reArrangeWords.push_back(appendSpaces(words[index], spaceNums));
                }
                else
                {
                    reArrangeWords.push_back(stringJust(words, index, lineWords, spaceNums));
                }
                //if (spaceNums > 0)
                lineWords = 0;
                sum = 0;
                spaceNums = 0;
            }
            index++;
        }
        // 处理最后一行

        //cout << "index " << to_string(index) << ", sum " << to_string(sum)
             //<< ", lineWords " << to_string(lineWords) << endl;
        if (lineWords != 0)
        {
            //sum = 0;
            std::string line = "";
            for (int i = lineWords; i > 1; i--)
            {
                line += words[index - i] + " ";
            }
            line += words[index - 1];
            line = appendSpaces(line, maxWidth - sum + 1);
            reArrangeWords.push_back(line);
        }
        return reArrangeWords;

    }

    string appendSpaces(string str, int nums)
    {
        for (int i = 0; i < nums; i++)
        {
            str += " ";
        }
        return str;
    }

    string stringJust(vector<string>& words, int index, int lineWords, int spaces)
    {
        int intervalSpaces = spaces / (lineWords-1);
        int middle = spaces % (lineWords - 1);
        string line = "";
        int interval = 0;
        //cout << "       intervalSpaces " << to_string(intervalSpaces) << ", middle " << to_string(middle) << endl;
        for (int i = 0; i < lineWords - 1; i++)
        {
            // 小于i
            if (middle == 0)
                line += appendSpaces(words[index - lineWords + 1 + i], intervalSpaces);
            else if (middle > i)
                line += appendSpaces(words[index - lineWords + 1 + i], intervalSpaces + 1);
            else
                line += appendSpaces(words[index - lineWords + 1 + i], intervalSpaces);
        }
        line += words[index];
        return line;
    }
};
// @lc code=end

