#include<bits/stdc++.h>
using namespace std;

/**
 * Given two words (beginWord and endWord), and a dictionary's word list, 
 * find the length of shortest transformation sequence from beginWord to endWord, such that:

    Only one letter can be changed at a time.
    Each transformed word must exist in the word list. Note that beginWord is not a transformed word.
    Note:

    Return 0 if there is no such transformation sequence.
    All words have the same length.
    All words contain only lowercase alphabetic characters.
    You may assume no duplicates in the word list.
    You may assume beginWord and endWord are non-empty and are not the same.

    Input:
    beginWord = "hit",
    endWord = "cog",
    wordList = ["hot","dot","dog","lot","log","cog"]

    Output: 5

    Explanation: As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
    return its length 5.
*/
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        int L = wordList[0].size();
        map<string,vector<string>> generictoword;//this will work as adjacency list for traversing the string sequences
        //preprocessing each word
        bool flag = false;
        for(string word : wordList){
            if(word == endWord) flag = true;
            for(int i = 0;i<L;i++){
                string temp = word;
                temp[i] = '*';
                generictoword[temp].push_back(word);
            }
        }
        if(!flag) return 0;
        int minlen = 0;
        
        
        map<string,bool> vis;
        //use BFS
        queue<pair<string,int>> q;
        q.push({beginWord,1});
        vis[beginWord] = true;
        
        while(!q.empty()){
            string s = q.front().first;
            int len = q.front().second;
            q.pop();
            if(s == endWord){
                minlen = minlen==0?len:min(minlen,len);
                break;
            }
            for(int i = 0;i<L;i++){
                string temp = s;
                temp[i] = '*';
                for(string v  :  generictoword[temp]){
                    if(vis[v]) continue;
                    vis[v] = true;
                    q.push({v,len+1});
                }
            }
        }
        return minlen;
    }
};