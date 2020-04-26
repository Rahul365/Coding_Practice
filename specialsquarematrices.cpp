#include<bits/stdc++.h>
#define DD 1
#define R 0
#define D 2
#define L 0
#define U 2
using namespace std;
const int maxn = 2e3+1;
int n,m;
char mt[maxn][maxn];
int fromtop[maxn][maxn][3];
int frombottom[maxn][maxn][3];
int ids[maxn][maxn];

long long ans = 0;

class wavelet{
    public : 
        int low;
        int high;
        wavelet *left = NULL,*right = NULL;
        vector<int> freq;
        wavelet(int *from , int *to,int l,int r){
            low = l;
            high = r;
            freq.reserve(to - from + 1);
            freq.push_back(0);
            if(low == high){
                for(auto it = from ; it!=to;++it){
                    freq.push_back(freq.back() + 1);
                }
                return;
            }
            int mid = low + (high - low)/2;
            auto islessthan = [mid] (int x){
                return x <= mid;
            };

            for(auto it = from ;it!=to;++it){
                freq.push_back(freq.back() + islessthan(*it));
            }
            auto pivot = stable_partition(from,to,islessthan);
            left = new wavelet(from,pivot,low,mid);
            right = new wavelet(pivot,to,mid+1,high);
        }

        int lte(int l,int r,int k){
            if(l > r || k < low)
                return 0;
            if(high <= k){
                return r-l+1;
            }
            int ltcount = freq[l-1];
            int rtcount = freq[r];
            return this->left->lte(ltcount + 1,rtcount , k) + this->right->lte(l - ltcount,r - rtcount,k);
        }
        
        ~wavelet(){
            delete left;
            delete right;
        }
};

class bit{
    public:
    vector<long long> data;
    long long fullsum = 0;
    bit(){
        data = vector<long long>(maxn,0L);
    }
    
    void update(int idx,int val){
       // data[idx] = val;
       // return;
        ++idx;
        fullsum += val;
        while(idx < maxn){
            data[idx] += val;
            idx += (idx & -idx);
        }
    }
    
    long long read(int idx){
        int sum = 0;
        ++idx;
        while(idx > 0)
        {
            sum += data[idx];
            idx -= (idx & -idx);
        }
        return sum;
    }
    
    long long query(int x){
        return fullsum - read(x-1);
    }

    long long sum(int l,int r){
        /*
        long long s = 0;
        
        for(int i = l;i<=r;++i)
            s += (data[i]>=r+1);
        return s;
        */
        return read(r) - read(l-1);
    }
};

void countII(int i,int j){
    vector<pair<int,int>> queries;
    int r = i;
    int c = j;
    while(i <= n && j <= m){
        if(mt[i][j] == '0'){
            queries.push_back({-1,INT_MAX});
            ++i,++j;
            continue;
        }
        int top = min({fromtop[i][j][DD],fromtop[i][j][R],fromtop[i][j][D]});
        queries.push_back({j,top});
        ++i;
        ++j;
    }
    int N = queries.size();
    int arr[N];
    i = r;
    j = c;
    int idx = 0;
    int low  = 0;
    int high = maxn;
    while(i <= n && j <= m){
        if(mt[i][j] == '0'){
            arr[idx++] = INT_MAX;
            ++i,++j;
            continue;
        }
        int bottom = min({frombottom[i][j][DD],frombottom[i][j][U],frombottom[i][j][L]});
        arr[idx] = j - bottom + 1;
        low = min(low,arr[idx]);
        high = max(high,arr[idx]);
        ++idx;
        ++i, ++j;
    }
    wavelet *tree = new wavelet(arr,arr+N,low,high);
    for(idx = 0;idx < N;++idx){
        ans += tree->lte(idx+1,min(N,idx + queries[idx].second),queries[idx].first);
    }
    delete tree;
}

void countI(int i,int j){
    vector<int> stop_here[maxn] = {};
            for(int inc = 0;inc+i <= n && inc+j<=m;++inc){
                int top = min({fromtop[inc + i][inc + j][DD],fromtop[inc + i][inc + j][R],fromtop[inc + i][inc + j][D]});
                stop_here[inc + top].push_back(inc);
            }
            bit tree;
            for(int inc = 0;inc + i <= n && inc + j <=m;++inc){
                tree.update(inc,1);
                for(int x : stop_here[inc]){
                    tree.update(x,-1);
                }
                if(mt[inc+i][inc+j]=='0') continue;
                int bottom = min({frombottom[inc + i][inc + j][DD],frombottom[inc + i][inc + j][U],frombottom[inc+ i][inc + j][L]});
                ans += tree.query(inc-bottom + 1);
            }
            //int top = min({fromtop[i][j][DD],fromtop[i][j][R],fromtop[i][j][D]});
            //int bottom = min({frombottom[i][j][DD],frombottom[i][j][U],frombottom[i][j][L]});
            //for cell j count the elements x => a[j] where j->[j+1: j+top-1] such that x <= i
}

void precompute(){
    memset(fromtop,0,sizeof fromtop);
    memset(ids,-1,sizeof ids);
    memset(frombottom,0,sizeof frombottom);
    for(int i = n;i>0;--i){
        for(int j = m;j>0;--j){
            if(mt[i][j] == '1'){
                fromtop[i][j][R]  = 1 + fromtop[i][j+1][R];
                fromtop[i][j][DD] = 1 + fromtop[i+1][j+1][DD];
                fromtop[i][j][D]  = 1 + fromtop[i+1][j][D];
            }
        }
    }

    int id = 0;
    for(int i = 1;i<=n;++i){
        for(int j= 1 ;j<=m;++j){
            if(ids[i-1][j-1] == -1)
            {
                ids[i][j] = ++id;
            }
            else
            {
                ids[i][j] = ids[i-1][j-1];
            }
            if(mt[i][j] == '1'){
                frombottom[i][j][L]  = 1 + frombottom[i][j-1][L];
                frombottom[i][j][DD] = 1 + frombottom[i-1][j-1][DD];
                frombottom[i][j][U]  = 1 + frombottom[i-1][j][U];
            }
        } 
    }
    
    for(int i = 1;i<=n;++i)
    {
        for(int j = 1 ; j<=m;++j){
            if(!(i == 1 || j == 1)) continue;
            //if(mt[i][j] == '0') continue;
            countI(i,j);
        }
    }
    //subarray i => [l : r]
    //x <= a[i]
    //cout <<"\n";
}

int main(){
    cin >> n >> m;
    for(int i = 1;i<=n;++i){
        for(int j = 1;j<=m;++j)
        {
            cin >> mt[i][j];
         //   ans += (mt[i][j]=='1');
        }
    }
    
    precompute();
    /*
    for(int row = 1; row < n;++row){
        for(int col = 1;col < m;++col){
            if(mt[row][col] == '0') continue;
            int top = min({fromtop[row][col][DD],fromtop[row][col][R],fromtop[row][col][D]});
            int nextrow = row  + 1;
            int nextcol = col + 1;
            while(nextrow <=n && nextcol <= m){
                int bottom = min({frombottom[nextrow][nextcol][DD],frombottom[nextrow][nextcol][U],frombottom[nextrow][nextcol][L]});  
                if(top >= nextcol-col+1 && bottom >= nextcol - col + 1)
                {
                    ++ans;
                }
                ++nextrow,++nextcol;
            }
        }
    }
    */
    cout << ans<<"\n";
    return 0;
}