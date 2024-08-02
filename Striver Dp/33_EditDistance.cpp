#include <iostream>
#include <vector>
using namespace std;

// Recursive + Memoization solution
int solveMemo1(int i, int j, string &s, string &t, vector<vector<int>> &dp)
{
    if (i < 0)
    {
        return j + 1;
    }
    if (j < 0)
    {
        return i + 1;
    }
    if (dp[i][j] != -1)
    {
        return dp[i][j];
    }
    if (s[i] == t[j])
    {
        return dp[i][j] = solveMemo1(i - 1, j - 1, s, t, dp);
    }
    int insert = 1 + solveMemo1(i, j - 1, s, t, dp);
    int del = 1 + solveMemo1(i - 1, j, s, t, dp);
    int rep = 1 + solveMemo1(i - 1, j - 1, s, t, dp);
    return dp[i][j] = min(insert, min(del, rep));
}
int editDistanceMemo1(string s, string t)
{
    // Code here
    int n = s.size();
    int m = t.size();
    vector<vector<int>> dp(n, vector<int>(m, -1));
    return solveMemo1(n - 1, m - 1, s, t, dp);
}

// Recursive+ memoization Solution : by doing 1 bit shifing in the index of both the strings
int solve(int i, int j, string &s, string &t, vector<vector<int>> &dp)
{
    if (i == 0)
    {
        return j; // no need to add 1 to it becoz we are following the 1 based indexing
    }
    if (j == 0)
    {
        return i; // no need to add 1 to it becoz we are following the 1 based indexing
    }
    if (dp[i][j] != -1)
    {
        return dp[i][j];
    }
    if (s[i - 1] == t[j - 1]) // this remains the same as the strings always follows 0 based indexing
    {
        return dp[i][j] = solve(i - 1, j - 1, s, t, dp);
    }
    int insert = 1 + solve(i, j - 1, s, t, dp);
    int del = 1 + solve(i - 1, j, s, t, dp);
    int rep = 1 + solve(i - 1, j - 1, s, t, dp);
    return dp[i][j] = min(insert, min(del, rep));
}
int editDistanceMemo2(string s, string t)
{
    // Code here
    int n = s.size();
    int m = t.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1)); // but here we are trying to follow 1 based indexing for the dp vector
    return solve(n, m, s, t, dp);
}

// Tabulation Solution :

int editDistanceTab(string s, string t)
{
    // Code here
    int n = s.size();
    int m = t.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int j = 0; j <= m; j++)
    {
        dp[0][j] = j;
    }
    for (int i = 0; i <= n; i++)
    {
        dp[i][0] = i;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s[i - 1] == t[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else
            {
                int ins = 1 + dp[i][j - 1];
                int del = 1 + dp[i - 1][j];
                int rep = 1 + dp[i - 1][j - 1];
                dp[i][j] = min(ins, min(del, rep));
            }
        }
    }
    return dp[n][m];
}

// Space Optimization Code:

int editDistanceSpace(string s, string t)
{
    // Code here
    int n = s.size();
    int m = t.size();
    // vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    vector<int> prev(m + 1, 0);
    vector<int> curr(m + 1, 0);
    for (int j = 0; j <= m; j++)
    {
        prev[j] = j;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            if (j == 0)
            {
                curr[0] = i;
            }
            if (s[i - 1] == t[j - 1])
            {
                curr[j] = prev[j - 1];
            }
            else
            {
                int ins = 1 + curr[j - 1];
                int del = 1 + prev[j];
                int rep = 1 + prev[j - 1];
                curr[j] = min(ins, min(del, rep));
            }
        }
        prev = curr;
    }
    return prev[m];
}
