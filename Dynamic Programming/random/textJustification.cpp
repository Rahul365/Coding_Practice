#include <bits/stdc++.h>
#define INF INT_MAX
using namespace std;

/*Greedy Text Justification*/
vector<string> fullJustify(vector<string> &words, int maxwidth)
{
    int n = words.size();
    int i = 0;
    vector<string> ans;
    while (i < n)
    {
        string line;   //current line store the words from [i,j) from the wordlist given
        int j = i + 1; //(j==n) when it is last line
        int len = words[i].length();
        int spaceneeded = 1; //after ith word
        while (j < n && len + words[j].length() <= maxwidth - spaceneeded)
        {
            len += words[j].length();
            ++spaceneeded;
            j++;
        }
        int num = (j - i);      //number of words that fit in the line
        int f = maxwidth - len; //number of free spaces available here

        if (j == n)
        { //last line is left justified
            for (int k = i; k < j - 1; k++)
            {
                line += words[k];
                line += " ";
                --f;
            }
            line += words[j - 1];
            line += string(f, ' ');
        }
        else
        {
            //cout<<f<<"  "<<num<<" | ";
            int evenspaces = f / (num > 1 ? (num - 1) : num);
            int extraspaces = f % (num > 1 ? (num - 1) : num) /*f-(evenspaces * (num-1))*/;
            //each extraspace must be equally distributed among the rest
            //cout<<evenspaces<< " "<<extraspaces<<"\n";
            for (int k = i; k < j - 1; ++k)
            {
                line += words[k];
                if (extraspaces)
                {
                    line += string(1, ' ');
                    --extraspaces;
                }
                line += string(evenspaces, ' ');
            }
            line += words[j - 1];
            if (num == 1)
            {
                line += string(f, ' ');
            }
        }
        i = j;

        ans.push_back(line);
    }
    return ans;
}

/*Optimal Text Justification using Dynamic Programming*/
int *justify(int n, int w, vector<int> &wl)
{
    int extras[n + 1][n + 1]; //store least space needed to store word from i to j in one line
    int cost[n + 1][n + 1];   //stores the cost of storing word from i to j in one line = freespaces^2
    int c[n + 1];             //store the cost of optimal arrangement possible
    int *p = new int[n + 1];  //store the range e.g strings from p[i] to i will be in one line

    //build extras
    for (int i = 1; i <= n; i++)
    {
        extras[i][i] = w - wl[i - 1];
        for (int j = i + 1; j <= n; j++)
        {
            extras[i][j] = extras[i][j - 1] - wl[j - 1] - 1; //-1 is for atleast one extra space after each word
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j <= n; j++)
        {
            if (extras[i][j] < 0)
            {
                cost[i][j] = INF;
            }
            else if (j == n && extras[i][j] >= 0)
            {
                cost[i][j] = 0; //for the last to be fully left justified
            }
            else
            {
                cost[i][j] = extras[i][j] * extras[i][j];
            }
        }
    }

    //compute optimal cost
    //c[i] = stores the cost of optimal arrangement from string 1 to i
    c[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        c[i] = INF;
        for (int j = 1; j <= i; j++)
        {
            if (c[j - 1] != INF && cost[j][i] != INF && (c[i] > c[j - 1] + cost[j][i]))
            {
                c[i] = c[j - 1] + cost[j][i];
                p[i] = j;
            }
        }
    }
    return p;
}
//Space : O(n) time : O(n^2)------------------------------------------------

/**
 * Recursive Text Justification Memoization DP
*/
int memo[1001], p[1001];
int mincost(vector<int> &wl, int i, int n, int width)
{
    if (i == n)
        return 0;
    //current line starts from word i upto
    int cost = INT_MAX;
    int freespaces = width;
    for (int word = i; word < n; word++)
    {
        freespaces = freespaces - wl[word];
        if (freespaces - (word - i) >= 0)
        {
            int fsp = freespaces - (word - i);
            int tcost = mincost(wl, word + 1, n, width); //minimum cost of putting words from (word + 1) in the next line
            if (tcost != INT_MAX && cost > (word == n - 1 ? 0 : tcost + fsp * fsp))
            {
                //when word == n-1 , then this means that it's a last line so to make left justified
                //cost is set to 0 and p[i] = word + 1;
                p[i] = word + 1; //current line = words [i,p[i])
                cost = (word == n - 1 ? 0 : (tcost + fsp * fsp));
            }
        }
    }
    return cost;
}
void printmemosolution(int n)
{
    int pos = 0;
    while (pos < n)
    {
        cout << (pos + 1) << " " << p[pos] << " ";
        pos = p[pos];
    }
    cout << "\n";
}

void justifyTextII(vector<int> &wl, int n, int W)
{
    int cost[n], p[n];
    cost[n - 1] = 0;
    p[n - 1] = n - 1;

    for (int i = n - 2; i >= 0; i--)
    {
        int freespaces = W;
        cost[i] = INT_MAX;
        for (int j = i; j < n; j++)
        {
            freespaces -= wl[j];
            if (freespaces - (j - i) >= 0)
            {
                int fsp = freespaces - (j - i);
                //cost of putting words from i to j in one line = cost[i+1] + newcost[i,j]
                if (cost[j + 1] != INF && (j == n - 1 ? 0 : fsp * fsp + cost[j + 1]) < cost[i])
                {
                    cost[i] = (j == n - 1 ? 0 : cost[j + 1] + (fsp * fsp));
                    p[i] = j;
                }
            }
            else
                break;
        }
    }
    int i = 0;

    while (i < n)
    {
        cout << (i + 1) << " " << (p[i] + 1) << " ";
        i = p[i] + 1;
    }
    cout << "\n";
}
//----------------------------------------------------------------------------------------

void solve()
{
    int n;     //number of words
    int width; //length of a line in file

    cin >> n >> width;

    vector<string> wordlist(n); //store the words given in sequence
    vector<int> wordlength(n);  //store the length of wordlist[i]

    for (int i = 0; i < n; i++)
    {
        cin >> wordlist[i];
        wordlength[i] = wordlist[i].length();
        // cout << wordlength[i] << " ";
    }
    // cout << "\n";

    int *p = justify(n, width, wordlength);
    stack<vector<int>> stk;

    int i = n;
    while (i)
    {
        vector<int> line;
        for (int j = p[i]; j <= i; j++)
        {
            line.push_back(j - 1);
        }
        i = p[i] - 1;
        stk.push(line);
        line.clear();
    }

    vector<string> ans;
    while (!stk.empty())
    {
        string line;
        int f = width; //number of free spaces in line
        int num = stk.top().size();
        for (int word : stk.top())
        {
            f -= wordlist[word].length();
        }
        if (stk.size() == 1)
        {
            //last line
            for (int i = 0; i < num; i++)
            {
                line += (wordlist[stk.top()[i]] + ' ');
                --f;
            }
            line += string(f, ' ');
        }
        else
        {
            int equalspaces = f / (num > 1 ? (num - 1) : num);
            int extraspaces = f % (num > 1 ? (num - 1) : num);
            int id = 0;
            while (id < num - 1)
            {
                line += wordlist[stk.top()[id]];
                if (extraspaces)
                {
                    line += string(1, ' ');
                    extraspaces--;
                }
                line += string(equalspaces, ' ');
                ++id;
            }
            line += wordlist[stk.top()[num - 1]];
        }
        ans.push_back(line);
        // cout << "\n";
        stk.pop();
    }

    for (string s : ans)
    {
        cout << s << "\n";
    }
}

int main()
{
    freopen("input_tj.txt", "r", stdin);
    freopen("output_tj.txt", "w", stdout);
    solve();
    return 0;
}