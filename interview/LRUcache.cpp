#include<bits/stdc++.h>
using namespace std;

class LRUcache{
    private:
     int N;//cache size
     unordered_map<int,pair<int,list<int>::iterator>> cache;
     list<int> recent; // used as double ended queue to store most recently used items at front and least recently used ones at the rear end
    
    /**
     * Use this method if you are not using map to store the address for a key 
     * Returns iterator form the list for given key value 
     * use =>  cache.erase(finditr(x)); instead of cache.erase(cache[x].second);
    */
     list<int>::iterator finditr(int x){
         list<int>::iterator itr = recent.begin();
         while(*itr != x) itr++;
         return itr;
     }

    public:
    LRUcache(int N){
        this->N = N;
        cache.clear();
        recent.clear();
    }
    

    void set(int x,int y){
        if(cache.find(x) == cache.end()){
            //key is not present in the cache
            if(recent.size() == N){
            //if the cache is full
                cache.erase(recent.back());
                recent.pop_back();
            }
        }
        else{
            recent.erase(cache[x].second);
            cache.erase(x);
        }
        recent.push_front(x);
        cache[x] = {y,recent.begin()};
    }
    
    int get(int x){
     if(cache.find(x) == cache.end()) return -1;
        recent.erase(cache[x].second);
        recent.push_front(x);
        cache[x].second = recent.begin();
        return cache[x].first;
    }
};

int main(){
    int t;//test cases
    cin>>t;
    while(t--){
     int n;
        cin>>n;
        LRUcache ch(n);
        string s;
        int x,y;
        int q;
        cin>>q;
        while(q--){
            cin>>s;
            if(s == "SET"){
                cin>>x>>y;
                ch.set(x,y);
            }
            else if(s == "GET"){
                cin>>x;
                cout<<ch.get(x)<<" ";
            }
        }
        cout<<"\n";
    }
 return 0;
}