/*************************************************************************
	> File Name: LCountBits.cpp
	> Author: enning
	> Mail: enningwan@gmail.com 
	> Created Time: 2021年03月03日 星期三 22时40分24秒
 ************************************************************************/

#include<iostream>
using namespace std;
#ifndef LCOUNTBITS_H
#define LCOUNTBITS_H

/*
 * @简介：比特位计数 - 给定一个非负整数 num。对于 0 ≤ i ≤ num 范围中的每个数字 i ，计算其二进制数中的 1 的数目并将它们作为数组返回。
 */
class LCountBits
{

public:
	LCountBits();
	virtual ~LCountBits();
	public int[] countBits(int num)
	{
		if (num == 0) {
			int results[1] = {
				0
			};
			return results;
		}
		else
		{
			int results[num];
		}
		int currentNum;
		int count;
		for (int i = 0; i < num; ++i) {
			count = 0;
			currentNum = i;
			while(currentNum > 0)
			{
				count += currentNum & 0x1;
				currentNum = currentNum >> 1;
			}
			results[i] = count;
		}
		return results;
	}
};

#endif /* LCOUNTBITS_H */
