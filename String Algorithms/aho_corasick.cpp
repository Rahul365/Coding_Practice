#include<bits/stdc++.h>
using namespace std;
const int K = 26;
const int maxn = 1e5+1;
int trie[maxn][K];//Trie
int f[maxn];//failure links
int out[maxn];//to store the leaf
int states = 0;
void init(){
    memset(trie,-1,sizeof trie);
    memset(f,-1,sizeof f);
    memset(out, 0 ,sizeof out);
}

void add_str(string &word,int id){
    int curr_state = 0;
    for(char ch : word){
        int curr = ch-'a';
        if(trie[curr_state][curr] == -1){
            trie[curr_state][curr] = ++states;
        }
        curr_state = trie[curr_state][curr];
    }
    out[curr_state] |= (1<<id);
}

int getnextstate(int state,char input){
    int ip = input-'a';
    int answer = state;
    /*If direct transition is not defined, then we use failure link*/
    while(trie[answer][ip] == -1) answer = f[answer];
    return trie[answer][ip];
}

void buildFailureLinks(){
    for(int curr = 0;curr<K;++curr){
        if(trie[0][curr] == -1){
            trie[0][curr]= 0;
        }
    }

    queue<int> q;
    for(int curr = 0;curr < K; ++curr){
        if(trie[0][curr]!=0){
            /*At depth 1*/
            f[trie[0][curr]] = 0;
            q.push(trie[0][curr]);
        }
    }

    while(!q.empty()){
        int state = q.front(); q.pop();
        for(int curr = 0; curr < K;++curr){
            if(trie[state][curr]!=-1){
                int failure = f[state];
                /*Go up till find a failure link*/
                while(trie[failure][curr] == -1){
                    failure = f[failure];
                }
                failure = trie[failure][curr];
                /*update the failure link for this state*/
                f[trie[state][curr]] = failure;
                out[trie[state][curr]] |= out[failure];
                q.push(trie[state][curr]);
            }
        }
    }
}

void SearchWords(vector<string> &words,string &text){
    init();
    for(int i = 0;i<words.size();++i){
        add_str(words[i],i);
    }
    buildFailureLinks();
    int state = 0;
    for(int i= 0;i<text.length();i++){
        state = getnextstate(state,text[i]);
        for(int j = 0;j < words.size() && out[state];++j){
            if(out[state]&(1<<j)){
                cout << "word : "<<words[j] << " appears from index "<<(i-words[j].length()+1) << " to " << i <<"\n";
            }    
        }
    }
}


int main(){
    vector<string> words({"he","she","hers","his"});
    string text = "abhishersisthishewhat";
    SearchWords(words,text);
    return 0;
}