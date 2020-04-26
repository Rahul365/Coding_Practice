#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;
    while(t--){
        int h;
        cin >> h;
        int q = (h<<1) + 1;
        int ans = -1;
        int prevNode = 1;
        int depth = h;
        for(int i = 1;i<=q;++i){
            if(i&1){
                //ask for the node at distance = depth from currentNode 
                cout << 2 << " " << prevNode << " " << depth<<"\n"; fflush(stdout);
                cin >> prevNode;//read the next node 
            }
            else {
                //ask the new distance b/w the updated node and special node
                cout << 1 <<" " << prevNode <<"\n"; fflush(stdout);
                cin >> depth;//read the new distance b/w current node and special node
                if(depth == 0){
                    break;//current node is the special node
                }
            }
        }
        cout << 3 << " " << prevNode <<"\n";
        int verdict;
        cin >> verdict;
        if(verdict == -1) exit(0);
        continue;
    }
    return 0;    
}