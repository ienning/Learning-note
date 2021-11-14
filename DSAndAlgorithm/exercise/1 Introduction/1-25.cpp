// 九章算术：最大公约数
#include <cmath>

int gcd(int a, int b)
{
    if (a == 0 || b == 0)
        return 0;
    int p = 1;
    while (a%2 == 0 && b%2 == 0)
    {
        p *= 2;
        a = a/2;
        b = b/2;
        
    }
    int t = abs(a - b);
    while (t > 0)
    {
       if (t%2 == 1) 
       {
           if (a >= b)
           {
               a = t;
           }
           else 
           {
               b = t;
           }
           t = abs(a - b);
       }
       else
       {
           t = t/2;
       }
    }
    return p * a;
}
