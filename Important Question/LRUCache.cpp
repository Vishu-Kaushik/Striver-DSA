#include <iostream>
#include <vector>
#include <list>
#include <map>
using namespace std;

// Brute Force Approach
class LRUCache
{
    //  TC - O(N^2) and SC= O(N) so it is costly
    // Sbse naya element at the the end becoz used recently
    // sbse purana element at front becoz bhot pehle use hua tha

    vector<pair<int, int>> che;
    int cap;

public:
    LRUCache(int capacity)
    {
        cap = capacity;
        // che.resize(cap);
    }

    int get(int key)
    {
        auto it = che.begin();
        for (int i = 0; i < che.size(); i++) // ---> O(N)
        {
            if (che[i].first == key)
            {
                int value = che[i].second;
                che.erase(it); // ---> O(N)
                che.push_back({key, value});
                return value;
            }
            it++;
        }
        return -1;
    }

    void put(int key, int value)
    {
        for (int i = 0; i < che.size(); i++)
        {
            if (che[i].first == key)
            {
                che.erase(che.begin() + i);
                che.push_back({key, value});
                return;
            }
        }
        if (che.size() >= cap)
        {
            che.erase(che.begin());
            // return;
        }
        che.push_back({key, value});
    }
};

// Optimized Appraoch

class LRUCache
{

    // Idea -- > use Doubly linked list
    // put fresh bande at front  taaki koi unhe delete na krde
    // put purane bande at last so that they can be deleted becoz they are not recently used
    list<int> dll;                                 // used to store keys
    map<int, pair<list<int>::iterator, int>> umap; // key , address , value
    int cap;

public:
    LRUCache(int capacity)
    {
        cap = capacity;
    }

    void recentused(int key)
    {
        dll.erase(umap[key].first);
        dll.push_front(key);
        umap[key].first = dll.begin();
    }

    int get(int key)
    {
        if (umap.find(key) == umap.end())
        {
            return -1;
        }
        recentused(key);
        return umap[key].second;
    }

    void put(int key, int value)
    {
        if (umap.find(key) != umap.end())
        {
            umap[key].second = value;
            recentused(key);
        }
        else
        {
            dll.push_front(key);
            // insert entry into map data structure
            umap[key] = {dll.begin(), value};
            cap--;
        }
        if (cap < 0)
        {
            int keyToDelete = dll.back();
            dll.pop_back();
            umap.erase(keyToDelete);
            cap++;
        }
    }
};