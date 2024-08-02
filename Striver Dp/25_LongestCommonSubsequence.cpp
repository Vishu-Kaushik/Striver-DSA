#include <iostream>
#include <vector>
using namespace std;

// Recursive Solution where TC = O(2^n + 2^m)

int solveRec(int n, int m, string s1, string s2)
{
    if (n < 0 || m < 0)
    {
        return 0;
    }
    if (s1[n] == s2[m])
    {
        return 1 + solveRec(n - 1, m - 1, s1, s2);
    }

    return max(solveRec(n - 1, m, s1, s2), solveRec(n, m - 1, s1, s2));
}
int lcsRec(int n, int m, string s1, string s2)
{
    return solveRec(n - 1, m - 1, s1, s2);
}

// ------------------- End of recursive Solution ----------------------------------

// --------------------- Memoiation Solution -------------------------------------
// Time Complexity is O(N*M) and Space Complexity = O(N*M) + O(N+M)

int solveMemo(int n, int m, string s1, string s2, vector<vector<int>> &dp)
{
    if (n < 0 || m < 0)
    {
        return 0;
    }
    if (dp[n][m] != -1)
    {
        return dp[n][m];
    }
    if (s1[n] == s2[m])
    {
        return dp[n][m] = 1 + solveMemo(n - 1, m - 1, s1, s2, dp);
    }

    return dp[n][m] = max(solveMemo(n - 1, m, s1, s2, dp), solveMemo(n, m - 1, s1, s2, dp));
}
int lcsMemo(int n, int m, string s1, string s2)
{
    vector<vector<int>> dp(n, vector<int>(m, -1));
    return solveMemo(n - 1, m - 1, s1, s2, dp);
}

// The Above solution  is pretty complex to be converted into the Tabulation Solution becoz of that negative index. So
// in order to avoid that we do shifting of index and we shift the index  one place to the right
// Which means that now after shifting index 0 --> -1 , 1 --> 0 , 2 --> 1 , 3 --> 2 ......... n --> n-1
// -------------------------------- End of Memoiation Solution ----------------------------------------

// --------------------------------- Memoiation Solution using the Shifting of indexes ------------------------------------

int solveMemoShift(int n, int m, string s1, string s2, vector<vector<int>> &dp)
{
    if (n == 0 || m == 0)
    {
        return 0;
    }
    if (dp[n][m] != -1)
    {
        return dp[n][m];
    }
    if (s1[n - 1] == s2[m - 1])
    {
        return dp[n][m] = 1 + solveMemoShift(n - 1, m - 1, s1, s2, dp);
    }

    return dp[n][m] = max(solveMemoShift(n - 1, m, s1, s2, dp), solveMemoShift(n, m - 1, s1, s2, dp));
}
int lcsMemoShift(int n, int m, string s1, string s2)
{
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    return solveMemoShift(n, m, s1, s2, dp);
}

// --------------------------------- End Memoiation Solution using the Shifting of indexes ------------------------------------

// Tabulation Solution : This Solution is written according to the 2nd memoiation solution
// TC :

int lcsTab(int n, int m, string s1, string s2)
{
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    // Base Cases
    for (int i = 0; i <= n; i++)
    {
        dp[i][0] = 0;
    }
    for (int j = 0; j <= m; j++)
    {
        dp[0][j] = 0;
    }

    // Wrting the nested loops
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[n][m];
}

// ------------------ Space Optimization ------------------------------------------------------
int lcsSpace(int n, int m, string s1, string s2)
{
    // vector<vector<int>> dp(n+1,vector<int>(m+1,0));
    vector<int> prev(m + 1, 0), curr(m + 1, 0);
    // Base Cases
    for (int j = 0; j <= m; j++)
    {
        prev[j] = 0;
    }
    // Writing the nested loops
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                curr[j] = 1 + prev[j - 1];
            }
            else
            {
                curr[j] = max(prev[j], curr[j - 1]);
            }
        }
        prev = curr;
    }
    return prev[m];
}