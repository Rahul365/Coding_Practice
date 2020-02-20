#include<bits/stdc++.h>
using namespace std;

class Solution{
    public:

        void dfs(string word,string &endWord,unordered_map<string,vector<string>> &access,vector<vector<string>> &ans,vector<string> path){
            path.push_back(word);
            if(word == endWord){
                ans.push_back(path);
                return;
            }
            for(string next : access[word]){
                dfs(next,endWord,access,ans,path);
            }
        }

        vector<vector<string>> findLadders(string beginWord,string endWord,vector<string> &wordList){
            vector<vector<string>> ans;
            //create adjacency list for the wordlist
            unordered_map<string,vector<string>> access;

            //create a lookup set
            unordered_set<string> lookup(wordList.begin(),wordList.end());
            if(!lookup.count(endWord)){
                return ans;
            }

            bool isend = false;//to indicate whether endWord is reached or not

            queue<string> q;
            q.push(beginWord);

            while(!q.empty()){
                //words explored in the current level
                unordered_set<string> words;
                while(!q.empty()){
                    string word = q.front();
                    q.pop();
                    words.insert(word);
                    lookup.erase(word);
                    if(word == endWord){
                        isend = true;
                        break;
                    }
                }
                if(isend) break;

                for(string word : words){
                    //for each word in the current level
                    for(int j = 0;j<word.size();j++){
                        string newWord(word);
                        for(char ch = 'a';ch<='z';++ch){
                            newWord[j] = ch;
                            if(lookup.count(newWord) && newWord != word){
                                q.push(newWord);
                                access[word].push_back(newWord);
                            }
                        }
                    }
                }
            }//end of while loop


            //build and store all the paths from beginword to endword
            
            vector<string> path;

            dfs(beginWord,endWord,access,ans,path);

            return ans;
        }
};

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    string beginWord,endWord;
    vector<string> wordlist;
    cin>>beginWord>>endWord;
    int n;
    cin>>n;
    getchar();
    while(n--)
    {
        string s;
        cin>>s;
        wordlist.push_back(s);
    }

    vector<vector<string>> paths = Solution().findLadders(beginWord,endWord,wordlist);

    for(vector<string> path : paths){
        for(string word : path){
            cout<<word<<"->";
        }
        cout<<"end\n";
    }
    return 0;
}