//infinite maze
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2000;
char grid[maxn][maxn];
pair<int,int> vis[maxn][maxn];//store the image of the same cell in the different grid
int n,m;
const int dr[] = {-1,1,0,0};
const int dc[] = {0,0,-1,1};

int f(int x,int y){
	x = x%y;
	if(x < 0)
		x += y;
	return x;
}
//idea was to check iff we can reach the same cell from our current grid to any other grid
//then the person can move infinitly far from the starting position
//to do that 
//we mainatain a visited array of pairs
//when the person visits the cell first time 
//then vis[cell] = cell
//Then again when person visits the image of this cell in other
//grid then we check if image(cell) != vis[original(image(cell))] return true i.e we can go infinitely far from the starting point
//here image(cell) -> position of the cell (x,y) in the repeated grid adjacent to the current grid
//image(cell) can be mapped to it's original position in the matrix as
// let (r,c) be the image(cell)
// so original position of image(cell) => cell(x) = (r%n + n)%n , cell(y) = (c%m + m)%m
// So when vis[original(image(cell))] != image(cell) return true;
// else continue dfs search
// search couldn't be more than n*m

bool dfs(pair<int,int> p){
	int &r = p.first;
	int &c = p.second;
	int x = f(r,n);
	int y = f(c,m);
    if(grid[x][y] == '#')
		return false;
	if(vis[x][y] != make_pair(-1,-1))
		return vis[x][y] != p;//check the image of cell (r,c) in the original grid
	vis[x][y] = p;//store the original cell image (r,c) == (x,y)
	for(int i = 0;i<4;++i){
			if(dfs({r + dr[i],c + dc[i]}))
				return true;
	}
	return false;
}
	
int main(){
	ios_base::sync_with_stdio(NULL);
	cin.tie(NULL);
	pair<int,int> start;
	cin >> n >> m;
	for(int i= 0;i<n;++i){
		for(int j = 0;j<m;++j){
				cin >> grid[i][j];
				if(grid[i][j] == 'S')
				start = {i,j};
				vis[i][j] = make_pair(-1,-1);
		}
	}
	if(dfs(start))
		cout << "Yes\n";
	else
		cout << "No\n";
	return 0;
}
