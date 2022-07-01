# document

# 原理

解决本题主要采用了**动态规划**的算法，即将原问题分解为相对简单的子问题解决。

核心的递推公式为：
$$
F(n)=\begin{cases} 0，&n=0\\-1，&n<0且F(n-Ci) = -1，其中1<=i<=coinsize\\min(F(n-Ci))+1，&1<=i<=coinsize，且F(n-Ci)!=-1\end{cases}
$$
其中`-1`表示未找到。

在本程序中，首先输入**一行**以空格隔开的数字，表示可能的币值（coins），再输入一个数字表示找零总额（amount），随后执行`getLeastNum`函数，得到最少的找零数量

```c++
// dp
// 引用，以减少内存占用；此外，传入的coin数组已经按递增顺序排序
int getLeastNum(const vector<int>& coins,const int& amount){ 
    // 存储dp的数组，minValue[i]即表示当找零总额为i时所需要的最少的钞票数
    vector<int> minValue; 
    // 找零总额为0时，需要0张钞票
    minValue.push_back(0); 

    // 分解问题，从计算给1块钱找零开始，逐渐递增到给amount数量的钱找零
    for (int i = 1;i <= amount;i++){ 
        // 初始设为最大值
        int temp = INT_MAX; 
        // 对每种硬币的可能性进行遍历
        for (const int& j : coins){ 
            // 因为币值已按升序排列，若小于零则表示当前的币值j无法给i找零，则后面
            // 的硬币也不可能满足，直接退出循环
            if (i - j < 0) 
                break;
            // 如果minValue[i - j]=-1，则表示这种情况不能找齐，跳过
            if (minValue[i - j] == UNFIND) // if the F(n - Ci) can't be found ..
                continue;
            
            // 选择所有可行方案里最小的硬币总数
            temp = min(temp,minValue[i - j]); // find the min(F(n - Ci)), 0 <= i <= size - 1
        }

        if (temp == INT_MAX) // 找不到任何方案，设为-1
            minValue.push_back(UNFIND);
        else
            minValue.push_back(temp + 1); // F[n] = min(F(n - Ci)) + 1
    }

    return minValue[minValue.size() - 1]; // F[n]即为所求数量
}
```



# 复杂度分析

- 设币值种类为m，找零数amount为n，则该程序时间复杂度为O(mn)
  1. input size为m和n
  2. basic operation为`if (i - j < 0) `，因为每次循环都会经过此句
  3. 该算法不存在best,average,worst情况
  4. 计算总运行次数。此程序中，basic operation在两层for循环下运行，其中最外层次数为n，内层次数为m，因此共需要运行m*n次
  5. 因此，时间复杂度为O(mn)
- 该函数中，为保存F(n)的各项值，需要开辟一个长度为n的数组，因此，其空间复杂度为O（n）



# 如何运行

以Linux系统环境下，用g++编译为例：

```bash
# in the directory where the cpp locates
g++ assignment_1.cpp -o assignment_1
./assignment_1
```

即可运行



# 运行截图

![](img\a1_img1.png)

- 运行环境：Ubuntu 20.04
- IDE：VS Code
- 编译器：g++ （gcc version 9.4.0 (Ubuntu 9.4.0-1ubuntu1~20.04.1) ）