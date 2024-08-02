#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// Brute Force - O(N^2) checking every pair for the divisibility

bool isPair(int arr[], int n, int k)
{
    vector<bool> used(n, false);
    for (int i = 0; i < n - 1; i++)
    {
        if (used[i])
        {
            continue;
        }
        bool foundPair = false;
        for (int j = i + 1; j < n; j++)
        {
            if (used[j])
            {
                continue;
            }
            if ((arr[i] + arr[j]) % k == 0)
            {
                used[i] = true;
                used[j] = true;

                foundPair = true;
                break;
            }
        }
        if (foundPair == false)
        {
            return false;
        }
    }
    return true;
}

/* Better Approach
idea is Pair (a,b) is valid if (a+b)%k == 0 if  a %k == r1  and b %k == r2  then r1+r2 = k
Then these two numbers can be considered as pairs
*/

bool ispair2(vector<int> nums, int k)

{
    if (nums.size() % 2 != 0)
    {
        return false;
    }

    unordered_set<int> st;
    for (int i = 0; i < nums.size(); i++)
    {
        int r1 = nums[i] % k;
        int r2 = k - r1;

        if (st.find(r2) != st.end())
        {
            st.erase(r2);
        }
        else if (r1 == 0 && st.find(0) != st.end())
        {
            st.erase(0);
        }
        else
        {
            st.insert(r1);
        }
    }
    return st.size();
}

// Using Unordered_map

bool canPair(vector<int> nums, int k)
{
    // Code here.
    if (nums.size() % 2 != 0)
    {
        return false;
    }
    unordered_map<int, int> mp;
    for (int i = 0; i < nums.size(); i++)
    {
        mp[nums[i] % k]++;
    }

    if (mp[0] % 2 != 0)
    {
        return false;
    }
    mp.erase(0);
    if (k / 2 == 0)
    {
        if (mp[k / 2] % 2 != 0)
        {
            return false;
        }
        mp.erase(k / 2);
    }
    for (auto x : mp)
    {
        if (mp[x.first] != mp[k - x.first])
        {
            return false;
        }
    }
    return true;
}