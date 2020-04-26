#include<bits/stdc++.h>
using namespace std;

class wavelet{
    public:
        int low,high;
        wavelet *l = NULL,*r = NULL;
        vector<int> freq;//to  store the number of element upto some ith  index which will go to left subtree
        /**
         * building a wavelet
         * 
        */
        wavelet(int *from,int *to,int x,int y){
            low = x;
            high = y;
            freq.reserve(to - from + 1);
            freq.push_back(0);
            if(low == high){
                //homogeneous state
                for(auto it = from ;it!=to;++it){
                    freq.push_back(freq.back()+1);
                }
                return;
            }
            int mid = (low+high)>>1;
            auto islessthan = [mid](int x){
                return x <= mid;
            };
            for(auto it = from;it!=to;++it){
                freq.push_back(freq.back() + islessthan(*it));
            }
            auto pivot = stable_partition(from,to,islessthan);
            l = new wavelet(from,pivot,low,mid);
            r = new wavelet(pivot,to,mid+1,high);
        }

        /**
         * Problem 1)
         * Given a query of the form [l:r] and k .Find the number of elements <= k in the subarray [l:r]
         * 
        */
        int lte(int l,int r,int k){
            if(l > r || k < low)
                return 0;
            if(high <= k)
                return r - l+1;
            int ltcount = freq[l-1];
            int rtcount = freq[r];
            return this->l->lte(ltcount+1, rtcount , k) + this->r->lte(l - ltcount,r - rtcount,k);
        }

        /**
         * Problem 2)
         * For query of the form (l,r,k) . find the number of occurrences of k in the subarray [l:r]
        */
       int countOccurrences(int pos,int k)
       {
            if(k < low || k > high)
                return 0;
            if(low == high){
                return k == high?freq[pos]:0;
            }   
            int left = freq[pos];
            int mid = (low+high) >> 1;
            if(k <= mid){
                return this->l->countOccurrences(left,k);
            }
            return this->r->countOccurrences(pos - left,k);
       }

       int count(int l,int r,int k){
           if(l > r || k < low  || k > high)
                return 0;
            if(low == high){
                return r-l+1;
            }
            int lcount = freq[l-1];
            int rcount = freq[r];
            int mid = (low + high) >> 1;
            if(k <= mid){
                return this->l->count(lcount + 1,rcount,k);
            }
            return this->r->count(l-lcount, r - rcount , k);
       }


        /**
         * Problem 3) For a given query (l,r,k) find the kth smallest elment in the subarray arr[l : r].
         * 
        */
        int findkth(int l,int r,int k){
            if(l > r)
                return -1;
            if(low == high)
                return low;
            int inrange = freq[r] - freq[l-1];
            int ltcount = freq[l-1];
            int rtcount = freq[r];
            if(inrange >= k){
                return this->l->findkth(ltcount + 1,rtcount,k);
            }
            return this->r->findkth(l - ltcount, r - rtcount , k - inrange);
        }

        ~wavelet(){
            delete l;
            delete r;
        }
};

int main(){
    int n = 10;
    int arr[n];
    srand(time(NULL));
    for(int &x : arr)
        x = rand()%13;
    int copy[n];
    int low = INT_MAX;
    int high = INT_MIN;
    cout << "id : ";//indexes 
    for(int i = 1;i<=n;++i) cout <<setw(2)<< i << " ";
    cout <<"\n";
    cout << "vl : ";//values
    for(int i = 0;i<n;++i){
        copy[i] = arr[i];
        cout << setw(2)<<arr[i] << " ";
        low =  min(low ,copy[i]);
        high = max(copy[i],high);
    }
    cout <<"\n";

    wavelet *tree = new wavelet(copy,copy+n,low,high);
    int t,l,r,k;
    cin >> t >> l >> r >> k;
    if(t == 0){
        /**
         * Solution for problem 1)
         * Given a query (l,r,k) , find the number of elements less than or equal to k in the subarray arr[l : r]
        */
        cout << tree->lte(l,r,k) << "\n";
    }
    else if(t == 1){
    /**
     * Solution for problem 2)
     * Given a query of the form (l,r,k) , find the number of occurrences of element == k
     * in the subarray [l:r].
     * 
    */
        cout << tree->countOccurrences(r,k)-tree->countOccurrences(l-1,k) <<"\n";//O(2 * log(high))
        cout << tree->count(l,r,k) << "\n";//O(log(high))
    }
    else if(t == 2){
        /**
         * Solution for problem 3)
         * For a query (l,r, k ) find the kth smallest number in the  subarray [l : r]
        */
       cout << tree->findkth(l,r,k) << "\n";
    }
    for(int i = 1;i<=n;++i){
      cout << tree->findkth(1,n,i)<<" " ;
    }
    cout << "\n";
    return 0;
}