#include <iostream>
#include <vector>
using namespace std;

#define mod 1000000007

// Recursive + memoization solution --> TC=O(N*M)  and SC = O(N*M)+O(N+M)
int solveMemo(int i, int j, string &s, string &t, vector<vector<int>> &dp)
{
    if (j < 0)
    {
        return 1;
    }
    if (i < 0)
    {
        return 0;
    }
    if (dp[i][j] != -1)
    {
        return dp[i][j];
    }
    if (s[i] == t[j])
    {
        return dp[i][j] = (solveMemo(i - 1, j - 1, s, t, dp) + solveMemo(i - 1, j, s, t, dp)) % mod;
    }
    else
    {
        return dp[i][j] = solveMemo(i - 1, j, s, t, dp) % mod;
    }
}
int subsequenceCountMemo(string s, string t)
{

    int n = s.size();
    int m = t.size();
    vector<vector<int>> dp(n, vector<int>(m, -1));
    return solveMemo(n - 1, m - 1, s, t, dp);
}

// Recursive + Memo Solution after doing 1 place shifting in the index or 1 bit indexing

int solveMemo2(int i, int j, string &s, string &t, vector<vector<int>> &dp)
{
    if (j == 0)
    {
        return 1;
    }
    if (i == 0)
    {
        return 0;
    }
    if (dp[i][j] != -1)
    {
        return dp[i][j];
    }
    if (s[i - 1] == t[j - 1])
    {
        return dp[i][j] = (solveMemo2(i - 1, j - 1, s, t, dp) + solveMemo2(i - 1, j, s, t, dp)) % mod;
    }
    else
    {
        return dp[i][j] = solveMemo2(i - 1, j, s, t, dp) % mod;
    }
}
int subsequenceCountMemo2(string s, string t)
{

    int n = s.size();
    int m = t.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    return solveMemo2(n, m, s, t, dp);
}

// Tabulation Solution :
int subsequenceCountTab(string s, string t)
{

    int n = s.size();
    int m = t.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i <= n; i++)
    {
        dp[i][0] = 1;
    }
    for (int j = 1; j <= m; j++)
    {
        dp[0][j] = 0;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s[i - 1] == t[j - 1])
            {
                dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % mod;
            }
            else
            {
                dp[i][j] = dp[i - 1][j] % mod;
            }
        }
    }
    return dp[n][m];
}

// Space Optimization:
int subsequenceCountSpace1(string s, string t)
{

    int n = s.size();
    int m = t.size();
    vector<int> prev(m + 1, 0), curr(m + 1, 0);
    prev[0] = 1;
    curr[0] = 1;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s[i - 1] == t[j - 1])
            {
                curr[j] = (prev[j - 1] + prev[j]) % mod;
            }
            else
            {
                curr[j] = prev[j] % mod;
            }
        }
        prev = curr;
    }
    return prev[m];
}

// Space Optimization 2  :
int subsequenceCountSpace2(string s, string t)
{

    int n = s.size();
    int m = t.size();
    vector<int> prev(m + 1, 0);
    prev[0] = 1;

    for (int i = 1; i <= n; i++)
    {
        for (int j = m; j >= 1; j--)
        {
            if (s[i - 1] == t[j - 1])
            {
                prev[j] = (prev[j - 1] + prev[j]) % mod;
            }
            // Also we can omit the else part because we are overwriting which in not necessary
            //     else
            //     {
            // prev[j] = prev[j] % mod;
            //     }
            // }
        }
        return prev[m];
    }
