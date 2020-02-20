#include <bits/stdc++.h>
#define interval pair<int, int>
using namespace std;

bool comp(const interval &a, const interval &b)
{
    if (a.first == b.first)
        return a.second < b.second;
    return a.first < b.first;
}

int partition(interval *p, int l, int r)
{
    interval piv = p[l];
    int i = l + 1;
    int j = r;
    while (i <= j)
    {
        while (i <= j && comp(p[i], piv))
        {
            ++i;
        }
        while (i <= j && comp(piv, p[j]))
        {
            --j;
        }
        if (i < j)
        {
            swap(p[i], p[j]);
        }
    }
    swap(p[j], p[l]);
    return j;
}

int randpartition(interval *p, int l, int r)
{
    int i = l + rand() % (r - l + 1);
    swap(p[l], p[i]);
    return partition(p, l, r);
}

void quicksort(interval *p, int l, int r)
{
    if (l < r)
    {
        int pid = randpartition(p, l, r);
        quicksort(p, l, pid - 1);
        quicksort(p, pid + 1, r);
    }
}

void print(interval *p, int n)
{
    for (int i = 0; i < n; i++)
        cout << "(" << p[i].first << "," << p[i].second << "), ";
    cout << "END\n";
}

int getpartitions(interval *p, int n)
{
    quicksort(p, 0, n - 1); //sort by start time
    print(p, n);

    int partition = -1;
    vector<int> mark(n, -1); //store the subset ID of the interval[i]
    //iterate over intervals
    for (int i = 0; i < n; i++)
    {
        if (mark[i] != -1)
            continue;
        ++partition;
        int index = i;
        mark[index] = partition;

        for (int j = i + 1; j < n; j++)
        {
            if (mark[j] != -1)
                continue;
            if (p[index].second > p[j].first)
                continue; //jth interval overlaps with currently selected interval
            mark[j] = mark[index];
            index = j;
        }
    }
    vector<interval> subsets[partition + 1];
    for (int i = 0; i < n; i++)
    {
        subsets[mark[i]].push_back(p[i]);
    }

    for (int i = 0; i <= partition; i++)
    {
        cout << "Subset " << (i + 1) << " : ";
        for (interval it : subsets[i])
            cout << "(" << it.first << "," << it.second << "), ";
        cout << "END\n";
    }
    return partition + 1;
}

int main()
{
    //sort the intervals by their start time
    int n;
    cin >> n;
    interval *p = new interval[n];
    for (int i = 0; i < n; i++)
    {
        cin >> p[i].first >> p[i].second;
    }
    cout << getpartitions(p, n) << "\n";
    return 0;
}