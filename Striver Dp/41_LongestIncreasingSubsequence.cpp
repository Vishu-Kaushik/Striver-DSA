#include <iostream>
#include <vector>
using namespace std;

// Recursive + Memoized Solution --> TC = O(n*n) and SC = O(n*n)+O(n)
// int solveMemo(int ind, int pInd, vector<int> &nums, vector<vector<int>> &dp)
// {
//     if (ind == nums.size())
//     {
//         return 0;
//     }
//     if (dp[ind][pInd + 1] != -1)
//     {
//         return dp[ind][pInd + 1];
//     }
//     int len = solveMemo(ind + 1, pInd, nums, dp);
//     *** int take = 0; ***
//     if (pInd == -1 || nums[ind] > nums[pInd])
//     {
//         len =max(len, 1 + solveMemo(ind + 1, ind, nums, dp));
//     }
//     ****** return dp[ind][pInd + 1] = max(take, notTake);*****
//     return dp[ind][pInd + 1] = len;
// }

int solveMemo(int ind, int pInd, vector<int> &nums, vector<vector<int>> &dp)
{
    if (ind == nums.size())
    {
        return 0;
    }
    if (dp[ind][pInd + 1] != -1)
    {
        return dp[ind][pInd + 1];
    }
    int notTake = solveMemo(ind + 1, pInd, nums, dp);
    int take = 0;
    if (pInd == -1 || nums[ind] > nums[pInd])
    {
        take = 1 + solveMemo(ind + 1, ind, nums, dp);
    }
    return dp[ind][pInd + 1] = max(take, notTake);
}
int lengthOfLISMemo(vector<int> &nums)
{
    int ind = 0;
    int pInd = -1;
    int n = nums.size();
    vector<vector<int>> dp(n, vector<int>(n + 1, -1));
    return solveMemo(ind, pInd, nums, dp);
}

// ----------------------------------------------------
// Tabulation Solution
int lengthOfLISTab(vector<int> &nums)
{
    // int ind = 0;
    // int pInd = -1;
    int n = nums.size();
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    for (int ind = n - 1; ind >= 0; ind--)
    {
        for (int prev = ind - 1; prev >= -1; prev--)
        {
            int notTake = dp[ind + 1][prev + 1]; // becoz of coordinate change
            int take = 0;
            if (prev == -1 || nums[ind] > nums[prev])
            {
                take = 1 + dp[ind + 1][ind + 1]; // "+1" becoz of coordinate change
            }
            dp[ind][prev + 1] = max(take, notTake);
        }
    }
    return dp[0][0];
}

// Space optimization Solution :
int lengthOfLISSpaceOP(vector<int> &nums)
{

    int n = nums.size();
    // vector<vector<int>> dp(n+1,vector<int>(n+1,0));
    vector<int> next(n + 1, 0), curr(n + 1, 0);
    for (int ind = n - 1; ind >= 0; ind--)
    {
        for (int prev = ind - 1; prev >= -1; prev--)
        {
            int notTake = next[prev + 1]; // becoz of coordinate change
            int take = 0;
            if (prev == -1 || nums[ind] > nums[prev])
            {
                take = 1 + next[ind + 1]; // "+1" becoz of coordinate change
            }
            curr[prev + 1] = max(take, notTake);
        }
        next = curr;
    }
    return next[0];
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*New approach
    --> Intuition : what does dp[i] signifies  -->  a LIS that ends at index i
    --> Now we declare an array which has all value as 1
    --> Becoz in the worst case there will be always be a LIS of length 1 that ends at index 'i' which consist of that single element only.. so initially minimum length will be 1 only becoz of that single element subsequence that ends at that index only 
    --> THis solution will be required when we need to trace back the LIS
    // TC --> O(N^2) and SC = O(N)
 */

int LISNewApproach(vector<int> &nums)
{
    int n = nums.size();
    // vector<vector<int>> dp(n+1,vector<int>(n+1,0));
    vector<int> dp(n, 1); // becoz there is already exist a subsquence that ends at index i which is LIS of length 1
    int maxi = 1;
    for (int ind = 0; ind < n; ind++)
    {
        for (int prev = 0; prev <= ind - 1; prev++)
        {
            if (nums[prev] < nums[ind])
            {
                dp[ind] = max(1 + dp[prev], dp[ind]);
            }
            maxi = max(maxi, dp[ind]);
        }
    }
    return maxi;
}