#include<bits/stdc++.h>
#define mkb(a,b) make_pair(a,b)
using namespace std;
//Valid traversal of bishop's tour with 40 moves starting from cell (4,4)
//Max moves it will take for any cell to reach (4,4) will not be more than 3 steps
//Thus total length of the path will be max 43(excluding the initial cell(r,c) count)
//Similarly if the starting position of the cell is (4,4) then total length of the path will be 39
vector<pair<int,int>> path = {
mkb(4,4),mkb(5,5),mkb(4,6),mkb(3,5),mkb(2,4),mkb(3,3),mkb(4,2),mkb(5,3),mkb(6,4),mkb(7,5),
mkb(6,6),mkb(5,7),mkb(4,8),mkb(3,7),mkb(2,6),mkb(1,5),mkb(2,4),mkb(1,3),mkb(2,2),mkb(1,1),
mkb(2,2),mkb(3,1),mkb(4,2),mkb(5,1),mkb(6,2),mkb(7,1),mkb(8,2),mkb(7,3),mkb(8,4),mkb(7,5),
mkb(8,6),mkb(7,7),mkb(8,8),mkb(7,7),mkb(6,8),mkb(5,7),mkb(4,8),mkb(3,7),mkb(2,8),mkb(1,7)
};

void printpath(const vector<pair<int,int>> &trace,int skip){
    for(auto &p : trace){
        if(skip)
        {
            --skip;
            continue;
        }
        printf("%d %d\n",p.first,p.second);
    }
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int r,c;
        scanf("%d%d",&r,&c);
        //take the source to (4,4)
        if(mkb(r,c) == mkb(4,4)){
            int path_length = (int)path.size()-1;
            printf("%d\n",path_length);
            printpath(path,1);
        }
        else{
            vector<pair<int,int>> init;
            int rinc = r > c?-1:1;
            int cinc = r > c?1:-1;
            while(r!=c){
                init.push_back(mkb(r,c));
                r+=rinc;
                c+=cinc;
            }
            if(mkb(r,c)!=mkb(4,4)){
                if(r > 4){
                    while(r!=4 && c!=4){
                        init.push_back(mkb(r,c));
                        --r,--c;
                    }
                }
                else if(r < 4){
                    while(r!=4 && c!=4)
                    {
                        init.push_back(mkb(r,c));
                        ++r,++c;
                    }
                }
            }
            int total = init.size() + path.size()-1;
             assert(total <= 64);
            printf("%d\n",total);
            printpath(init,1);
            printpath(path,0);
        }
    }
    return 0;
}