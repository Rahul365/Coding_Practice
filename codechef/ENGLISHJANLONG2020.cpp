#include <bits/stdc++.h>
#define ll long long int
#define pp pair<ll, pair<int, int>>
using namespace std;
const int MAXN = 1e5 + 11;
const int MAXC = 26;
bool vis[MAXN];

ll **pref;
ll **suff;

struct Trie
{
    bool end;
    vector<int> track; //keeps track of which word has prefix or suffix upto current child node
    Trie *child[MAXC];
    Trie()
    {
        end = false;
        for (int i = 0; i < MAXC; i++)
            child[i] = NULL;
    }
};

void insert(Trie *root, string x, int wordId, bool pf)
{
    int s = 0;
    int e = x.length();
    int incr = 1;
    if (!pf)
        s = e - 1, e = -1, incr = -1;

    for (int i = s; i != e; i += incr)
    {
        char ch = x[i];
        bool newline = true;
        if (!root->child[ch - 'a'])
        {
            root->child[ch - 'a'] = new Trie();
            newline = false;
        }
        root = root->child[ch - 'a'];

        for (int j : root->track)
        {
            if (pf)
            {
                pref[j][wordId]++, pref[wordId][j]++;
            }
            else
            {
                suff[j][wordId]++, suff[wordId][j]++;
            }
        }
        root->track.push_back(wordId);
    }

    root->end = true; //mark the end of the word
}

bool search(Trie *root, string s)
{
    if (!root)
        return s == "";
    for (char ch : s)
    {
        if (!root->child[ch - 'a'])
            return false;
        root = root->child[ch - 'a'];
    }
    return root->end;
}

void printWords(Trie *root, string s = "")
{
    if (root->end)
        cout << s << "\n";
    for (int i = 0; i < MAXC; i++)
    {
        if (root->child[i])
        {
            printWords(root->child[i], s + (char)('a' + i));
        }
    }
}

void preprocessing(vector<string> &w, int n)
{
    Trie *root_pref = new Trie();
    Trie *root_suff = new Trie();
    pref = new ll *[n];
    suff = new ll *[n];

    for (int i = 0; i < n; i++)
    {
        pref[i] = new ll[n];
        suff[i] = new ll[n];
        for (int j = 0; j < n; j++)
        {
            pref[i][j] = 0;
            suff[i][j] = 0;
        }
    }
    sort(w.begin(), w.end());
    for (int i = 0; i < n; i++)
    {
        insert(root_pref, w[i], i, true);  //insert word into trie
        insert(root_suff, w[i], i, false); //insert reversed word into trie
    }
}

void testTrie()
{
    Trie *root = new Trie();
    insert(root, "rahul", 0, true);
    insert(root, "dhiman", 1, true);
    printWords(root);
    exit(0);
}

ll computebeauty(int i, int j)
{
    ll res = min(pref[i][j], suff[i][j]);
    res *= res;
    return res;
}

bool check(string x, string y)
{
    return x[0] == y[0] || x[x.length() - 1] == y[y.length() - 1];
}

ll computespecial(vector<string> &w, int n)
{
    if (n < MAXN - 11)
        return;
    //when all strings are of length 1
    int cnt[MAXC];
    memset(cnt, 0, sizeof cnt);
    for (int i = 0; i < n; i++)
    {
        char ch = w[i][0];
        cnt[ch - 'a']++;
    }
    ll ans = 0;
    for (int i = 0; i < MAXC; i++)
    {
        if (cnt[i])
        {
            ans += cnt[i] / 2;
        }
    }
    return ans;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<string> w; //word list
        unordered_map<string, ll> wtoc;
        string ww;
        ll ans = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> ww;
            wtoc[ww]++;
        }

        for (auto p : wtoc)
        {
            ll len = p.first.length();
            ans += ((len * len) * (p.second / 2));
            if (p.second & 1)
                w.push_back(p.first);
        }

        n = w.size();

        preprocessing(w, n);

        vector<pp> data;
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                ll beauty = computebeauty(i, j); //O(1)
                if (beauty)
                    data.push_back({-beauty, {i, j}});
            }
        }

        sort(data.begin(), data.end());

        memset(vis, false, sizeof(vis));
        for (pp p : data)
        {
            int x = p.second.first;
            int y = p.second.second;
            if (vis[x] || vis[y])
                continue;
            vis[x] = vis[y] = true;
            ans += abs(p.first);
        }
        cout << ans << "\n";
    }
    return 0;
}