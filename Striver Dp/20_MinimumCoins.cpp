#include<iostream>
#include<vector>
using namespace std;

// Recursive Solution --> TC = exponential and Sc= Greater than linear
int solveRec(int n, vector<int> &coins, int V)
{

    if (n == 0)
    {
        if ((V % coins[0]) == 0)
        {
            return V / coins[0];
        }
        return 1e9;
    }

    int notPick = 0 + solveRec(n - 1, coins, V);
    int pick = 1e9;
    if (coins[n] <= V)
    {
        pick = 1 + solveRec(n, coins, V - coins[n]);
    }
    return min(pick, notPick);
}

int minCoinsRec(vector<int> &coins, int M, int V)
{
    // Your code goes here
    int ans = solveRec(M - 1, coins, V);
    if (ans >= 1e9)
    {
        return -1;
    }
    return ans;
}

// Memoiation SOlution --> TC= O(N*v) ans SC = O(N*V) +O(N){much greater than N}
int solveMemo(int n, vector<int> &coins, int V, vector<vector<int>> &dp)
{

    if (n == 0)
    {
        if ((V % coins[0]) == 0)
        {
            return V / coins[0];
        }
        return 1e9;
    }
    if (dp[n][V] != -1)
    {
        return dp[n][V];
    }
    int notPick = 0 + solveMemo(n - 1, coins, V, dp);
    int pick = 1e9;
    if (coins[n] <= V)
    {
        pick = 1 + solveMemo(n, coins, V - coins[n], dp);
    }
    return dp[n][V] = min(pick, notPick);
}

int minCoins(vector<int> &coins, int M, int V)
{
    // Your code goes here
    vector<vector<int>> dp(M, vector<int>(V + 1, -1));
    int ans = solveMemo(M - 1, coins, V, dp);
    if (ans >= 1e9)
    {
        return -1;
    }
    return ans;
}

// Tabulation Solution --> TC = O(N*V) and SC = O(N*v)
int minCoinsTab(vector<int> &coins, int M, int V)
{
    // Your code goes here
    vector<vector<int>> dp(M, vector<int>(V + 1, 0));
    // Base cases:
    for (int t = 0; t <= V; t++)
    {
        if (t % coins[0] == 0)
        {
            dp[0][t] = t / coins[0];
        }
        else
        {
            dp[0][t] = 1e9;
        }
    }

    for (int ind = 1; ind < M; ind++)
    {
        for (int target = 0; target <= V; target++)
        {
            int notPick = dp[ind - 1][target];
            int pick = INT_MAX;
            if (coins[ind] <= target)
            {
                pick = 1 + dp[ind][target - coins[ind]];
            }
            dp[ind][target] = min(pick, notPick);
        }
    }

    int ans = dp[M - 1][V];
    if (ans >= 1e9)
    {
        return -1;
    }
    return ans;
}

// Space Optimization --> Same as before

int minCoinsSpace(vector<int> &coins, int M, int V)
{
    // Your code goes here
    vector<int>prev (V + 1, 0),curr(V+1,0);
    // Base cases:
    for (int t = 0; t <= V; t++)
    {
        if (t % coins[0] == 0)
        {
            prev[t] = t / coins[0];
        }
        else
        {
            prev[t] = 1e9;
        }
    }

    for (int ind = 1; ind < M; ind++)
    {
        for (int target = 0; target <= V; target++)
        {
            int notPick = prev[target];
            int pick = INT_MAX;
            if (coins[ind] <= target)
            {
                pick = 1 + curr[target - coins[ind]];
            }
            curr[target] = min(pick, notPick);
        }
        prev = curr;
    }

    int ans = prev[V];
    if (ans >= 1e9)
    {
        return -1;
    }
    return ans;
}