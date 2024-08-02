#include <iostream>
#include <vector>
using namespace std;
/*
We learnt that to Optimize a DP solution :
1D ---> 2 variables
2D ---> 1D dp
3D ---> 2D dp
*/

// Recursive Solution --> TC = O(3^row + 3^row) ans SC = O(N)

int solveRec(int i, int j1, int j2, int r, int c, vector<vector<int>> &grid)
{
    if (j1 < 0 || j1 >= c || j2 < 0 || j2 >= c)
    {
        return -1e8;
    }
    if (i == r - 1)
    {
        if (j1 == j2)
        {
            return grid[i][j1];
        }
        else
        {
            return grid[i][j1] + grid[i][j2];
        }
    }
    // Explore all paths for both bob and alice simultaneously
    int maxi = -1e8;
    for (int dj1 = -1; dj1 <= 1; dj1++)
    {
        for (int dj2 = -1; dj2 <= 1; dj2++)
        {
            int value = 0;
            if (j1 == j2)
            {
                value = grid[i][j1];
            }
            else
            {
                value = grid[i][j1] + grid[i][j2];
            }
            value += solveRec(i + 1, j1 + dj1, j2 + dj2, r, c, grid);
            maxi = max(maxi, value);
        }
    }
    return maxi;
}

int maximumChocolatesRec(int r, int c, vector<vector<int>> &grid)
{
    return solveRec(0, 0, c - 1, r, c, grid);
}

// --------------------------------------------------------------------------------------------------
// Memoiation Solution
// TC  = O(N*M*M) ans SC = O(N*M*M) + O(N)
// There are total 3 parameteres which are changing so IT is a question of 3D dp so we will have a vector of 3 dimensions

int solveMemo(int i, int j1, int j2, int r, int c, vector<vector<int>> &grid, vector<vector<vector<int>>> dp)
{
    if (j1 < 0 || j1 >= c || j2 < 0 || j2 >= c)
    {
        return -1e8;
    }
    if (dp[i][j1][j2] != -1)
    {
        return dp[i][j1][j2];
    }
    if (i == r - 1)
    {
        if (j1 == j2)
        {
            return grid[i][j1];
        }
        else
        {
            return grid[i][j1] + grid[i][j2];
        }
    }

    int maxi = -1e8;
    for (int dj1 = -1; dj1 <= 1; dj1++)
    {
        for (int dj2 = -1; dj2 <= 1; dj2++)
        {
            int value = 0;
            if (j1 == j2)
            {
                value = grid[i][j1];
            }
            else
            {
                value = grid[i][j1] + grid[i][j2];
            }
            value += solveMemo(i + 1, j1 + dj1, j2 + dj2, r, c, grid, dp);
            maxi = max(maxi, value);
        }
    }
    return dp[i][j1][j2] = maxi;
}

int maximumChocolates(int r, int c, vector<vector<int>> &grid)
{
    vector<vector<vector<int>>> dp(r, vector<vector<int>>(c, vector<int>(c, -1)));

    return solveMemo(0, 0, c - 1, r, c, grid, dp);
}

// Tabulation Solution -->

int maximumChocolatesTab(int r, int c, vector<vector<int>> &grid)
{
    vector<vector<vector<int>>> dp(r, vector<vector<int>>(c, vector<int>(c, 0)));
    // Base Case
    for (int j1 = 0; j1 < c; j1++)
    {
        for (int j2 = 0; j2 < c; j2++)
        {
            if (j1 == j2)
            {
                dp[r - 1][j1][j2] = grid[r - 1][j1];
            }
            else
            {
                dp[r - 1][j1][j2] = grid[r - 1][j1] + grid[r - 1][j2];
            }
        }
    }

    // Exploring all the paths
    for (int i = r - 2; i >= 0; i--)
    {
        for (int j1 = 0; j1 < c; j1++)
        {
            for (int j2 = 0; j2 < c; j2++)
            {
                int maxi = -1e8;
                for (int dj1 = -1; dj1 <= 1; dj1++)
                {
                    for (int dj2 = -1; dj2 <= 1; dj2++)
                    {
                        int value = 0;
                        if (j1 == j2)
                        {
                            value = grid[i][j1];
                        }
                        else
                        {
                            value = grid[i][j1] + grid[i][j2];
                        }
                        if (j1 + dj1 >= 0 && j1 + dj1 < c && j2 + dj2 >= 0 && j2 + dj2 < c)
                        {
                            value += dp[i + 1][j1 + dj1][j2 + dj2];
                        }
                        else
                        {
                            value += -1e8;
                        }
                        maxi = max(maxi, value);
                    }
                }
                dp[i][j1][j2] = maxi;
            }
        }
    }
    return dp[0][0][c - 1];
}

// Space Optimization of the above Solution
int maximumChocolatesSpaceOP(int r, int c, vector<vector<int>> &grid)
{
    // vector<vector<vector<int>>> dp(r, vector<vector<int>>(c, vector<int>(c, 0)));
    // Base Case
    vector<vector<int>> front(c, vector<int>(c, 0));
    vector<vector<int>> curr(c, vector<int>(c, 0));
    for (int j1 = 0; j1 < c; j1++)
    {
        for (int j2 = 0; j2 < c; j2++)
        {
            if (j1 == j2)
            {
                front[j1][j2] = grid[r - 1][j1];
            }
            else
            {
                front[j1][j2] = grid[r - 1][j1] + grid[r - 1][j2];
            }
        }
    }

    // Exploring all the paths
    for (int i = r - 2; i >= 0; i--)
    {
        for (int j1 = 0; j1 < c; j1++)
        {
            for (int j2 = 0; j2 < c; j2++)
            {
                int maxi = -1e8;
                for (int dj1 = -1; dj1 <= 1; dj1++)
                {
                    for (int dj2 = -1; dj2 <= 1; dj2++)
                    {
                        int value = 0;
                        if (j1 == j2)
                        {
                            value = grid[i][j1];
                        }
                        else
                        {
                            value = grid[i][j1] + grid[i][j2];
                        }
                        if (j1 + dj1 >= 0 && j1 + dj1 < c && j2 + dj2 >= 0 && j2 + dj2 < c)
                        {
                            value += front[j1 + dj1][j2 + dj2];
                        }
                        else
                        {
                            value += -1e8;
                        }
                        maxi = max(maxi, value);
                    }
                }
                curr[j1][j2] = maxi;
            }
        }
        front = curr;
    }
    return curr[0][c - 1];
}