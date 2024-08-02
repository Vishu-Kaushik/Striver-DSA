#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <string>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <utility>
#include <algorithm>
#include <sstream>
using namespace std;

set<int> st;
int funct(int n, int a, int b)
{
    if (n < a)
    {
        return -1;
    }
    if (n < b)
    {
        return -1;
    }
    st.insert(n);
    if (funct(n - a, a, b))
    {
        int suba = 1 + funct(n - a, a, b);
    }
    if (funct(n - a, a, b))
    {
        int subb = 1 + funct(n - b, a, b);
    }
    return st.size();
}

int main(int argc, char const *argv[])
{
    int ans = funct(10, 2, 5);
    cout << ans;
    return 0;
}