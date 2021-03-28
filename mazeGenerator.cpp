#include <bits/stdc++.h>

using namespace std;

#define tt(n) for (int i=0; i<n; i++)
#define FOR(i,a,n) for (auto i=a; i!=n; i++)

bool validLimits(int x, int y, int nx, int ny) {
	if(
			x<0 ||
			x>=nx ||
			y<0 ||
			y>=nx 
	  ) return false;
	return true;

}

vector<pair<int,int>> winningPath(int grid[20][20], int i, int j) {
	vector<pair<int,int>> v;

	while(i>0 && j<19) {
		grid[i][j]=0;
		if(rand()%2==1 && i>0) {
			i--;
		} else if(rand()%2==0 && j<19) {
			j++;
		}

		v.push_back(make_pair(i,j));
	}
	return v;
}


void gimmeMaze(){
	freopen("./file", "w", stdout);

	int grid[20][20];

	memset(grid,-1,1600);

	vector<pair<int,int>> V = winningPath(grid, 18, 1);

		
	tt(90) vector<pair<int,int>> tmp = winningPath(grid, rand()%19, rand()%19);
	

	tt(20) {
		FOR(j,0,20)
			cout << right << setw(2) <<  grid[i][j] << " ";

		cout << endl;
	}

}

//int main(){ srand(time(0));gimmeMaze(); return 0;}
/*
   tt(20) cout << -1 << " ";
   cout << endl;

   tt(18) {
   cout << -1 << " ";
   FOR(j,0,18){
   cout << right << setw(2) <<  (rand()%2)-1 << " ";
   }
   cout << -1;
   cout << endl;
   }



   tt(20) cout << -1 << " ";
   cout << endl;
   */


