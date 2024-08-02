
// Subset sum equal to target

#include <iostream>
#include <vector>
using namespace std;

/*

--------------- Path for the recursive solution ---------------------------------
1. Express  index and target
2. Explore possibilites of that index
    --> arr[ind] is the part of that subsequence
    --> arr[ind] is not the part of that subquence
3. return true or false
*/

// Recursive solution with the memoiation ---> TC as O(n*target) and AS is O(n*target) + O(N)
// Here we will make dp array as 2d and of parameters bool/int dp[index][target] with size index = 10^3 +1 and target as size = 10^3 +1

bool solve(int arr[], int n, int target)
{
    if (target == 0)
    {
        return true;
    }
    if (n == 0)
    {
        return (arr[0] == target);
    }

    // if(dp[n][target]!=-1)
    // {
    //     return dp[n][target];
    // }
    bool notTake = solve(arr, n - 1, target);
    bool take = false;

    if (target >= arr[n])
    {
        take = solve(arr, n - 1, target - arr[n]);
    }

    // return dp[n][target]=(take || notTake);
    return (take || notTake);
}

// Tabulation based solution

bool subsetSumToK(vector<int> &arr, int n, int target)
{
    vector<vector<bool>> dp(n, vector<bool>(target + 1, 0));
    for (int i = 0; i < n; i++)
    {
        dp[i][0] = true;
    }
    dp[0][arr[0]] = true;

    for (int ind = 1; ind < n; ind++)
    {
        for (int j = 1; j <= target; j++)
        {
            bool notTake = dp[ind - 1][j];
            bool take = false;

            if (j >= arr[ind])
            {
                take = dp[ind - 1][j - arr[ind]];
            }
            dp[ind][j] = take || notTake;
        }
    }
    return dp[n - 1][target];
}
