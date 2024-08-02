#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// REcursive Solution
int solveRec(int ind, int sum, int arr[])
{
    if (sum == 0)
    {
        return 1;
    }
    if (ind == 0)
    {
        return (arr[0] == sum);
    }
    int notPick = solveRec(ind - 1, sum, arr);
    int pick = 0;

    if (arr[ind] <= sum)
    {
        pick = solveRec(ind - 1, sum - arr[ind], arr);
    }
    return (notPick + pick) % 1000000007;
}
int perfectSum(int arr[], int n, int sum)
{
    // Your code goes here
    sort(arr, arr + n, greater<int>());
    return solveRec(n - 1, sum, arr);
}

// Memoiation Solution
int solveMemo(int ind, int sum, int arr[], vector<vector<int>> &dp)
{
    if (sum == 0)
    {
        return 1;
    }
    if (ind == 0)
    {
        return (arr[0] == sum);
    }
    if (dp[ind][sum] != -1)
    {
        return dp[ind][sum];
    }
    int notPick = solveMemo(ind - 1, sum, arr, dp);
    int pick = 0;

    if (arr[ind] <= sum)
    {
        pick = solveMemo(ind - 1, sum - arr[ind], arr, dp);
    }
    return dp[ind][sum] = (notPick + pick) % 1000000007;
}
int perfectSum(int arr[], int n, int sum)
{
    // Your code goes here
    vector<vector<int>> dp(n, vector<int>(sum + 1, -1));
    sort(arr, arr + n, greater<int>());
    return solveMemo(n - 1, sum, arr, dp);
}

// Tabulation Solution
// Sorting is done for the cases when the array contains 0 in it --> EX : {1,0,2,2,3}
int countSubsetTab(int arr[], int n, int sum)
{
    // code here
    // int n = arr.size();
    sort(arr, arr + n, greater<int>());
    vector<vector<int>> dp(n, vector<int>(sum + 1, 0));
    for (int i = 0; i < n; i++)
    {
        dp[i][0] = 1;
    }
    if (arr[0] <= sum)
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

// Similarly Space Optimization can be done in the similar way as we have done it before using the prev and the curr array to store tha answers

// Another approach when the array have the numbers arr[i] >= 0

int solveAnother(int ind, int sum, int arr[], vector<vector<int>> &dp)
{
    // Here the base cases are altered to consider the zeroes of the array
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
    int notPick = solveAnother(ind - 1, sum, arr, dp);
    int pick = 0;

    if (arr[ind] <= sum)
    {
        pick = solveAnother(ind - 1, sum - arr[ind], arr, dp);
    }
    return dp[ind][sum] = (notPick + pick) % 1000000007;
}
int perfectSumAnother(int arr[], int n, int sum)
{
    // Your code goes here
    vector<vector<int>> dp(n, vector<int>(sum + 1, -1));
    // sort(arr,arr+n,greater<int>());
    return solveAnother(n - 1, sum, arr, dp);
}