#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// All the solutions
// https://www.geeksforgeeks.org/minimum-number-swaps-required-sort-array/

// Another solution
int minSwaps(vector<int> &nums)
{
    // Code here
    vector<pair<int, int>> p;
    for (int i = 0; i < nums.size(); i++)
    {
        p.push_back({nums[i], i});
    }
    sort(p.begin(), p.end());

    int swaps = 0;
    for (int i = 0; i < nums.size();)
    {
        pair<int, int> temp = p[i];

        int value = temp.first;
        int index = temp.second;

        if (i != index)
        {
            swaps++;
            swap(p[i], p[index]);
        }
        else
        {
            i++;
        }
    }
    return swaps;