#include <iostream>
#include <vector>
using namespace std;

// Subset: A subset of an array is a tuple that can be obtained from the array by removing some (possibly all) elements of it
// Subsequence: A subsequence is a string derived from the input string by deleting zero or more elements from the input string without changing the order of the remaining
// characters. Example: str="abcd" "ad" is a subsequence of str obtained by deleting 'b' and 'c'.

// Recursive Solution: TC = O(2^n) ans SC = o(N)
bool solveRec(int index, int target, vector<int> &arr)
{
    if (target == 0)
    {
        return true;
    }
    if (index == 0)
    {
        return (arr[0] == target);
    }
    bool notTake = solveRec(index - 1, target, arr);
    bool take = false;
    if (target >= arr[index])
    {
        take = solveRec(index - 1, target - arr[index], arr);
    }
    return (notTake || take);
}
bool isSubsetSumRec(vector<int> arr, int sum)
{
    int size = arr.size();
    return solveRec(size - 1, sum, arr);
}

// Memoiation Solution: TC = O(n*target) and SC = O(N*target) + O(N)
bool solveMemo(int index, int target, vector<int> &arr, vector<vector<int>> &dp)
{
    if (target == 0)
    {
        return true;
    }
    if (index == 0)
    {
        return (arr[0] == target);
    }
    if (dp[index][target] != -1)
    {
        return dp[index][target];
    }
    bool notTake = solveMemo(index - 1, target, arr, dp);
    bool take = false;
    if (target >= arr[index])
    {
        take = solveMemo(index - 1, target - arr[index], arr, dp);
    }
    return dp[index][target] = (notTake || take);
}
bool isSubsetSumMemo(vector<int> arr, int sum)
{
    int size = arr.size();
    vector<vector<int>> dp(size, vector<int>(sum + 1, -1));
    return solveMemo(size - 1, sum, arr, dp);
}

// Tabulation Solution
bool isSubsetSum(vector<int> arr, int sum)
{
    // code here
    int n = arr.size();
    vector<vector<bool>> dp(n, vector<bool>(sum + 1, 0));
    for (int i = 0; i < n; i++)
    {
        dp[i][0] = true;
    }
    dp[0][arr[0]] = true;
    for (int index = 1; index < n; index++)
    {
        for (int target = 1; target <= sum; target++)
        {
            bool notTake = dp[index - 1][target];

            bool take = false;

            if (target >= arr[index])
            {
                take = dp[index - 1][target - arr[index]];
            }
            dp[index][target] = take || notTake;
        }
    }
    return dp[n - 1][sum];
}

// Space Optimization of the above code
bool isSubsetSum(vector<int> arr, int sum)
{
    // code here
    int n = arr.size();
    vector<bool> prev(sum + 1, 0);
    vector<bool> curr(sum + 1, 0);
    prev[0] = true;
    curr[0] = true;

    if (arr[0] <= sum)
    {
        prev[arr[0]] = true;
    }
    for (int ind = 1; ind < n; ind++)
    {
        for (int target = 1; target <= sum; target++)
        {
            bool notTake = prev[target];

            bool take = false;

            if (target >= arr[ind])
            {
                take = prev[target - arr[ind]];
            }
            curr[target] = take || notTake;
        }
        prev = curr;
    }
    return prev[sum];
}