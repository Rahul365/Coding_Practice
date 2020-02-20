#include<bits/stdc++.h>
using namespace std;
/**
 * Problem : Solve Sudoku Puzzle
*/
int s[9][9];
int blockId[9][9];
pair<int,int> block[] = {{0,0},{0,3},{0,6},{3,0},{3,3},{3,6},{6,0},{6,3},{6,6}};

/**
 * Assign block Ids to each sub-block of size 3*3 
 */
void fillBlockIds(){
    int id = 0;
    for(int i = 0;i<9;i+=3){
        for(int j = 0;j<9;j+=3){
            for(int r = i;r<i+3;r++){
                 for(int c = j;c<j+3;c++){
                    blockId[r][c] = id;
                 }
            }
            ++id;
        }
    }
}
/**
 * Validate whether the value assigned to cell s[i][j] is as per sudoku rules
 */
bool validFill(int i,int j,int val){
    int block_x = block[blockId[i][j]].first;
    int block_y = block[blockId[i][j]].second;
    // cout<<block_x<<" "<<block_y<<"\n";
    // cout<<val<<"\n";
    /*
      Check the current 3*3 block
      whether the val is assigned to any s[row][col] for the block under consideration
    */
    for(int row = block_x;row < block_x + 3;row++){
        for(int col = block_y;col  < block_y + 3;col++){
            if(row == i && col == j) continue;
            if(s[row][col] == val) return false;
        }
    }

    //check all the rows
    for(int row = 0;row < 9;row++){
        if(row == i) continue;
        if(s[row][j] == val) return false;
    }

    //check all the columns
    for(int col = 0;col < 9;col++){
        if(col == j) continue;
        if(s[i][col] == val) return false;
    }    
    return true;
}

bool fillSudoku(int row,int col);

bool fill_cell(int i,int j){
    for(int v = 1;v <= 9;v++){
        s[i][j] = v;
        if(validFill(i,j,v) && (j+1 == 9?fillSudoku(i+1,0):fillSudoku(i,j+1))){
            return true;
        }
    }
    return false;
}

bool fillSudoku(int row,int col){
    if(row == 9){
        return true;
    }
    int c = col;
    while(c < 9){
        if(s[row][c] == 0){
            if(!fill_cell(row,c)){
                //backtrack steps
                s[row][c] = 0;
                return false;
            }
        }
        c++;
    }
    
    return fillSudoku(row+1,0);
    
}

int main(){
    fillBlockIds();
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int t;
    cin>>t;
    for(int T = 0;T<t;T++){
        for(int i = 0;i<9;i++){
            for(int j = 0;j<9;j++){
                cin>>s[i][j];
            }
        }

        fillSudoku(0,0);
        cout<<"Case #"<<T+1<<"\n";
        for(int i = 0;i<9;i++){
            for(int j = 0;j<9;j++){
                cout<<s[i][j]<<" ";
            }
            cout<<"\n";
        }
        cout<<"\n";
    }
    return 0;
}