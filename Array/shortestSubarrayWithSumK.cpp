#include <iostream>
#include <unordered_map>
using namespace std;

int longestSubarrayWithSumK(vector<int> a, long long k)
{
    unordered_map<long long, int> mpp;
    long long sum = 0;
    int len = -1e9;
    for (int i = 0; i < a.size(); i++)
    {
        sum += a[i];
        if (sum == k)
        {
            len = max(len, i + 1);
        }
        long long rem = sum - k;
        if (mpp.find(rem) != mpp.end())
        {
            int remlen = i - mpp[rem];
            len = max(len, remlen);
        }
        mpp[sum] = i;
        
    }
    return len;
}