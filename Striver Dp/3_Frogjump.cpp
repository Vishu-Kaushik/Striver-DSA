#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// Recursion --> ALL possible ways and then count all possible ways  and take the best

// Here Greedy solution will not always work

/* 1. Express all the things in terms of index
2. Do stuff on that index
3. Find the answer according to the problem

Here f(n-1) means minimum energy required to reach to (n-1) stair from 0
F(0) means the energy required to reach stair zero to zero
*/

// Recursive solution with TC as O(2^N)
int solve1(vector<int> heights, int ind)
{
    if (ind == 0)
    {
        return 0;
    }

    int left = solve1(heights, ind - 1) + abs(heights[ind] - heights[ind - 1]);
    int right = INT16_MAX;
    if (ind > 1)
    {
        right = solve1(heights, ind - 2) + abs(heights[ind] - heights[ind - 2]);
    }
    return min(left, right);
}

// Memoiation solution --> with TC as O(N) and with Space complexity of O(N)+O(N)

int solve2(vector<int> heights, int ind, vector<int> &dp)
{
    if (ind == 0)
    {
        return 0;
    }
    if (dp[ind] != -1)
    {
        return dp[ind];
    }
    int left = solve2(heights, ind - 1, dp) + abs(heights[ind] - heights[ind - 1]);
    int right = INT16_MAX;
    if (ind > 1)
    {
        right = solve2(heights, ind - 2, dp) + abs(heights[ind] - heights[ind - 2]);
    }
    return dp[ind] = min(left, right);
}

int f(vector<int> heights, int n)
{
    vector<int> dp(n + 1, -1);
    // return solve1(heights, n - 1);
    return solve2(heights, n - 1, dp);
}

// Tabulation Based solution
int tabSolution(vector<int> heights, int n)
{
    vector<int> dp(n, 0); // vector<int> dp(n+1,0);
    dp[0] = 0;

    for (int i = 1; i < n; i++)
    {
        int fs = dp[i - 1] + abs(heights[i] - heights[i - 1]);
        int rs = INT16_MAX;
        if (i > 1)
        {
            rs = dp[i - 2] + abs(heights[i] - heights[i - 2]);
        }
        dp[i] = min(fs, rs);
    }
    return dp[n - 1]; // dp[n];
}

//  Space optimized
int opSolution(vector<int> heights, int n)
{
    // vector<int> dp(n, 0); // vector<int> dp(n+1,0);
    int prev = 0;
    int prev2 = 0;

    for (int i = 1; i < n; i++)
    {
        int fs = prev + abs(heights[i] - heights[i - 1]);
        int rs = INT16_MAX;
        if (i > 1)
        {
            rs = prev2 + abs(heights[i] - heights[i - 2]);
        }
        int curri = min(fs, rs);
        prev2 = prev;
        prev = curri;
    }
    return prev;
}
int main(int argc, char const *argv[])
{
    vector<int> a{30, 10, 60, 10, 60, 50};
    cout << f(a, a.size());
    return 0;
}
