#include <iostream>
using namespace std;

// Brute force --> Tc = O(N^3) and AS = O(1)

int maxProduct(int arr[], int n)
{
    int maxi = INT16_MIN;
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            int prod = 1;
            for (int k = i; j <= j; k++)
            {
                prod = prod * arr[k];
            }
            maxi = max(prod, maxi);
        }
    }
    return maxi;
}

// Brute force (Method 2) --> Tc = O(N^2) and AS = O(1)

int maxProduct(int arr[], int n)
{
    int maxi = INT16_MIN;
    for (int i = 0; i < n; i++)
    {
        int prod = 1;
        for (int j = i; j < n; j++)
        {
            prod *= arr[j];
            maxi = max(prod, maxi);
        }
    }
    return maxi;
}

/* ----------------- Optimal Solution 1 ---------------------------------
Intuition :
1. All positive elements
2. Even Negatives , positives
3. Odd negatives , positives
4. If it has zeroes --> [(-2,3,4,-1), 0, (-2,3,1,4,) 0, (4,6,-1,4)] so we will take maximum of all these three partitioned array
with the junction as zero

*/

int subarrayProduct(int arr[], int n)
{
    int pre = 1;
    int suffix = 1;
    int ans = INT16_MIN;
    for (int i = 0; i < n; i++)
    {
        if (pre == 0)
        {
            pre = 1;
        }
        if (suffix == 0)
        {
            suffix = 1;
        }
        pre = pre * arr[i];
        suffix = suffix * arr[n - i - 1];
        ans = max(ans, max(pre, suffix));
    }
    return ans;
}