#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// Recursive Solution
int solve1(vector<int> heights, int ind, int k)
{
    if (ind == 0)
    {
        return 0;
    }
    int minStepsWithEnergy = INT16_MAX;
    for (int i = 1; i <= k; i++)
    {
        if ((ind - i) >= 0)
        {
            int rec = solve1(heights, ind - i, k) + abs(heights[ind] - heights[ind - i]);
            minStepsWithEnergy = min(rec, minStepsWithEnergy);
        }
    }

    return minStepsWithEnergy;
}

// Memoiation Solution
int solve2(vector<int> heights, int ind, vector<int> &dp, int k)
{
    if (ind == 0)
    {
        return 0;
    }
    if (dp[ind] != -1)
    {
        return dp[ind];
    }
    int minStepsWithEnergy = INT16_MAX;
    for (int i = 1; i <= k; i++)
    {
        if ((ind - i) >= 0)
        {
            int rec = solve2(heights, ind - i, dp, k) + abs(heights[ind] - heights[ind - i]);
            minStepsWithEnergy = min(rec, minStepsWithEnergy);
        }
    }
    return dp[ind] = minStepsWithEnergy;
}

int f(vector<int> heights, int n, int k)
{
    vector<int> dp(n + 1, -1);
    // return solve1(heights, n - 1,k);
    return solve2(heights, n - 1, dp, k);
}

// Tabulation Based solution
int tabSolution(vector<int> heights, int n, int k)
{
    vector<int> dp(n, 0); // vector<int> dp(n+1,0);
    dp[0] = 0;

    for (int i = 1; i < n; i++)
    {
        int minStepsWithEnergy = INT16_MAX;
        for (int j = 1; j <= k; j++)
        {
            if ((i - j) >= 0)
            {
                int left = dp[i - j] + abs(heights[i] - heights[i - j]);
                minStepsWithEnergy = min(left, minStepsWithEnergy);
            }
        }
        dp[i] = minStepsWithEnergy;
    }
    return dp[n - 1]; // dp[n];
}
