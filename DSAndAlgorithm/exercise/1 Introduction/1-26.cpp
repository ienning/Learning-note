// 就算算法

int shift(int* A, int n, int k)
{
    k = k % n;
    reverse(A, k);
    reverse(A+k, n-k);
    reverse(A, n);
    // 返回累计操作次数
    return 3*n;

}