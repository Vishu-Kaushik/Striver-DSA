#include <iostream>
#include <vector>
using namespace std;

// This was the memoiation solution
int mod = (int)1000000007;
int solve(int ind, int sum, vector<int> &arr, vector<vector<int>> &dp)
{
    if (ind == 0)
    {
        if (sum == 0 && arr[0] == 0)
        {
            return 2;
        }
        if (sum == 0 || arr[0] == sum)
        {
            return 1;
        }
        return 0;
    }

    if (dp[ind][sum] != -1)
    {
        return dp[ind][sum];
    }
    int notPick = solve(ind - 1, sum, arr, dp);
    int pick = 0;
    if (arr[ind] <= sum)
    {
        pick = solve(ind - 1, sum - arr[ind], arr, dp);
    }
    return dp[ind][sum] = (notPick + pick) % mod;
}

int perfectSum(vector<int> &arr, int n, int sum)
{
    // Your code goes here
    vector<vector<int>> dp(n, vector<int>(sum + 1, -1));
    return solve(n - 1, sum, arr, dp);
}

int countPartitions(int n, int d, vector<int> &arr)
{
    // Write your code here.
    int totSum = 0;
    for (int i = 0; i < n; i++)
    {
        totSum += arr[i];
    }

    if ((totSum - d) < 0 || (totSum - d) % 2)
    {
        return 0;
    }
    return perfectSum(arr, n, (totSum - d) / 2);
}

// Tabulation Solution

int perfectSum(vector<int> &arr, int n, int sum)
{
    vector<vector<int>> dp(n, vector<int>(sum + 1, 0));
    if (arr[0] == 0)
    {
        dp[0][0] = 2;
    }
    else
    {
        dp[0][0] = 1;
    }
    if (arr[0] != 0 && arr[0] <= sum)
    {
        dp[0][arr[0]] = 1;
    }
    for (int index = 1; index < n; index++)
    {
        for (int target = 0; target <= sum; target++)
        {
            int notTake = dp[index - 1][target];

            int take = 0;

            if (target >= arr[index])
            {
                take = dp[index - 1][target - arr[index]];
            }
            dp[index][target] = (take + notTake) % 1000000007;
        }
    }
    return dp[n - 1][sum];
}
int countPartitions(int n, int d, vector<int> &arr)
{
    // Write your code here.
    int totSum = 0;
    for (int i = 0; i < n; i++)
    {
        totSum += arr[i];
    }

    if ((totSum - d) < 0 || (totSum - d) % 2)
    {
        return 0;
    }
    return perfectSum(arr, n, (totSum - d) / 2);
}