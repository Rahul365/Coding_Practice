#include<bits/stdc++.h>
using namespace std;
#define pp pair<int,list<int>::iterator>
//(value,iterator in the list)
class LFUCache {
private:
    int N;//cache size
    unordered_map<int,int> freqmap;//key to frequecny map
    map<int,list<int>> freq_keyval;//frequency to list(keys)
    unordered_map<int,pp> key_valadd;//key to (value,list(iterator(key))) 
    
public:
    LFUCache(int capacity) {
        N = capacity;
    }
    
    int get(int key) {
        if(N==0 || freqmap.find(key)==freqmap.end()) return -1;
        //remove the key from the current frequency category
        int lfu_cat = freqmap[key];
        freq_keyval[lfu_cat].erase(key_valadd[key].second);
        if(freq_keyval[lfu_cat].size() == 0) freq_keyval.erase(lfu_cat);//remove the category if the list is empty 
        //update the frequency category for given key
        lfu_cat = ++freqmap[key];
        freq_keyval[lfu_cat].push_front(key);
        key_valadd[key].second = freq_keyval[lfu_cat].begin();
        //return the value
        return key_valadd[key].first;
    }
    
   
    
    void put(int key, int value) {
        if(N == 0) return;
        if(freqmap.find(key) == freqmap.end()){
            //if the key is not already present
            if(freqmap.size() == N){
               //if the cache is full
               auto itr = *freq_keyval.begin();
               int lfu_cat = itr.first;//least recently used freq category
               int val = freq_keyval[lfu_cat].back();
               key_valadd.erase(freq_keyval[lfu_cat].back());//remove the lr used item from the map 
               freqmap.erase(freq_keyval[lfu_cat].back());//remove the key from the freqmap
              
                //remove the least recently used key
                //under this frequency category
             
               freq_keyval[lfu_cat].pop_back();
               if(freq_keyval[lfu_cat].size()==0){
                   freq_keyval.erase(lfu_cat);
               }
             
            }
        }
        else
        {//if the key is alrady present
         //find the frequency category of the key
         //remove the key from list under current frequency category (remove category if list is empty after)
         //remove the entry from key=>(value,iterator) map
          int lfu_cat = freqmap[key];//get the frequency category
          freq_keyval[lfu_cat].erase(key_valadd[key].second);//remove the key from the frequency category
          if(freq_keyval[lfu_cat].size() == 0) freq_keyval.erase(lfu_cat);
          key_valadd.erase(key);
        }
       freqmap[key]++;//update the category for the key
       freq_keyval[freqmap[key]].push_front(key);//insert the key into the list under new frequency category
       key_valadd[key] = {value,freq_keyval[freqmap[key]].begin()};//update the key->(value,iterator) map
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */