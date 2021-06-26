#include <bits/stdc++.h>
using namespace std;

template <typename T, typename U>
class minIpq
{
    map<T, int> kToki;
    vector<T> kiTok;
    vector<U> kiTov;
    vector<int> kiToid;
    vector<int> idToki;
    int sz;
    int mN;
    U inf;
    bool less(int i, int j)
    {
        const int &a_id = idToki[i];
        const int &b_id = idToki[j];
        const int &a_val = kiTov[a_id];
        const int &b_val = kiTov[b_id];
        return a_val < b_val;
    }

    void swapNodes(int i, int j)
    {
        /**
         * Swap key indexes stored at nodes i and j
         */
        int &a_ki = idToki[i];
        int &b_ki = idToki[j];
        int &a_id = kiToid[a_ki];
        int &b_id = kiToid[b_ki];
        swap(a_ki, b_ki);
        swap(a_id, b_id);
    }

    void fixdown(int id)
    {
        while (id < sz)
        {
            int min_child = id;
            int l_child = id + id + 1;
            int r_child = id + id + 2;
            if (l_child < sz && less(l_child, min_child))
            {
                min_child = l_child;
            }
            if (r_child < sz && less(r_child, min_child))
            {
                min_child = r_child;
            }
            if (min_child != id)
            {
                swapNodes(min_child, id);
                id = min_child;
            }
            else
                break;
        }
    }

    void fixup(int id)
    {
        while (id)
        {
            if (!less(id >> 1, id))
            {
                swapNodes(id >> 1, id);
                id = id >> 1;
            }
            else
                break;
        }
    }

    int KI(T k)
    {
        return kToki[k];
    }

public:
    minIpq(int N, U inf) : inf(inf)
    {
        mN = N;
        sz = 0;
        kiTov = vector<U>(N, inf);
        /**heap is managed by ki to id and id to ki map **/
        kiToid = vector<int>(N, -1);
        idToki = vector<int>(N, -1);
        kiTok = vector<T>(N);
        kToki = map<T, int>();
    }

    pair<T, U> deleteKey(T k)
    {
        int ki = KI(k);
        int node_index = kiToid[ki];
        pair<T, U> ret = {kiTok[ki], kiTov[ki]};
        swapNodes(node_index, sz - 1);
        --sz;
        fixup(node_index);
        fixdown(node_index);
        kiTov[ki] = inf;
        idToki[sz] = -1;
        kiToid[ki] = -1;
        kToki.erase(kToki.find(k));
        return ret;
    }

    T valueOf(T k)
    {
        return kiTov[kiTok[k]];
    }

    bool contains(T k)
    {
        return kiTok.count(k) > 0;
    }

    pair<T, U> top()
    {
        pair<T, U> ret = {kiTok[idToki[0]], kiTov[idToki[0]]};
        return ret;
    }

    pair<T, U> deleteTop()
    {
        pair<T, U> ret = {kiTok[idToki[0]], kiTov[idToki[0]]};
        swapNodes(0, sz - 1);
        --sz;
        fixdown(0);
        kiTov[idToki[sz]] = inf;
        kiToid[idToki[sz]] = -1;
        idToki[sz] = -1;
        kToki.erase(kToki.find(kiTok[idToki[sz]]));
        return ret;
    }

    void insert(T k, U val)
    {
        kToki[k] = sz;
        int ki = KI(k);
        kiTov[ki] = val;
        kiToid[ki] = sz;
        idToki[sz] = ki;
        sz += 1;
        fixup(sz);
    }

    void update(T k, U val)
    {
        int ki = KI(k);
        //update the value for ki
        kiTov[ki] = val;
        fixup(kiToid[ki]);
        fixdown(kiToid[ki]);
    }

    void decreaseKey(T k, U val)
    {
        int ki = kToki[k];
        if (kiTov[ki] > val)
        {
            kiTov[ki] = val;
            fixup(kiToid[ki]);
        }
    }

    void increaseKey(T k, U val)
    {
        int ki = kToki[k];
        if (kiTov[ki] < val)
        {
            kiTov[ki] = val;
            fixdown(kiToid[ki]);
        }
    }
};

int main()
{
    return 0;
}