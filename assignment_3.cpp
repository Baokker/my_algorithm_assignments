#include <iostream>
#include <vector>
#include <climits> // INT_MAX

using std::cin;
using std::cout;
using std::vector;

#define UNDEFINE -1

// 表示寻找P中第i个矩阵到第j个矩阵（均为闭区间）的最少操作数
// i起始为0
// 此外，因为长度为n的P仅表示n-1个矩阵
// 因此合理的参数应当为(0,P.size() - 2)
// dp用于存储数据 减少重复操作
// dp中UNDEFINE（-1）表示尚未被赋值
int matrixChainMultiplication(vector<int> &P, int i, int j, vector<vector<int>> &dp)
{
    // 如果已经计算好，则直接返回
    if (dp[i][j] != UNDEFINE)
        return dp[i][j];

    // 如果i==j，则赋0
    if (j == i)
    {
        dp[i][j] = 0;
        return dp[i][j];
    }

    dp[i][j] = INT_MAX;
    for (int m = i; m < j; m++)
    {
        // 对于矩阵i..j
        // 令k=[i..j)
        // dp[i][j]即为矩阵i..k的最少运算次数+矩阵k+1..j的最少运算次数+P[i]*P[k+1]*P[j+1]
        // 所有可能中的最小值
        dp[i][j] = std::min(dp[i][j], matrixChainMultiplication(P, i, m, dp) + matrixChainMultiplication(P, m + 1, j, dp) + P[i] * P[m + 1] * P[j + 1]);
    }
    return dp[i][j];
}

int matrixChainMultiplication(vector<int> &P)
{
    vector<vector<int>> dp = vector<vector<int>>(P.size() - 1, vector<int>(P.size() - 1, UNDEFINE));
    return matrixChainMultiplication(P, 0, P.size() - 2, dp); // 第0号矩阵..第size-2号矩阵
}

int main()
{
    int num;
    vector<int> P;
    while (cin >> num)
    {
        P.push_back(num);
        if (cin.get() == '\n')
            break;
    }

    cout << matrixChainMultiplication(P) << std::endl;
    return 0;
}