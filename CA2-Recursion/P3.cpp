#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

void find_max_path(vector<vector<int> > matrix, vector< vector<int> >visited, int row, int column, int currRow, int currCol, int& totalTreasure, int& max_Treasure);
void Get_Maximum_Gold_Mine_Path(vector<vector<int> > matrix, int row, int column, int& max_Treasure);
bool isSafe(vector< vector<int> > matrix, vector< vector<int> >visited, int x, int y);
bool isValid(int x, int y, int r, int c);

int main() {
	int row_Index  = 0, row, col, temp;
	vector<vector<int> > vec;
	vector<int> rowVector;
	cin >> row >> col;
	int max_Treasure = 0;
	while (row_Index != row)
	{
		while (rowVector.size() != col)
		{
			cin >>temp ;
			rowVector.push_back(temp);
		}
		vec.push_back(rowVector);
		rowVector.clear();
		row_Index ++;
	}
	Get_Maximum_Gold_Mine_Path(vec,row,col, max_Treasure);
	cout <<endl<< max_Treasure << endl;
}

void find_max_path(vector<vector<int> > matrix, vector< vector<int> >visited,int row,int column,int currRow,int currCol,
	int &totalTreasure,int& max_Treasure) {
	int theRow[] = { -1,1,0,0 };
	int theCol[] = { 0,0,-1,1 };
	int new_row;
	int new_col;
	visited[currRow][currCol] = 1;

	for (int move = 0; move < 4; move++) {
		new_row = currRow + theRow[move];
		new_col = currCol + theCol[move];
		if ( (!isValid(new_row, new_col,row,column)) || (!isSafe(matrix,visited,new_row,new_col)))
			continue;
		visited[new_row][new_col] = 1;
		totalTreasure += matrix[new_row][new_col];
		find_max_path(matrix, visited, row, column, new_row, new_col, totalTreasure, max_Treasure);
	}
	visited[currRow][currCol] = 0;
	max_Treasure = max(max_Treasure, totalTreasure);
	totalTreasure -= matrix[currRow][currCol];
}

void Get_Maximum_Gold_Mine_Path(vector<vector<int> > matrix, int row, int column, int& max_Treasure) {
	vector<vector<int> > visited;
	vector<int> temp(column, 0);
	for (int i = 0; i < row; i++)
		visited.push_back(temp);
	for (int initRow = 0; initRow < row; initRow++) {
		for (int initCol = 0; initCol < column; initCol++) {
			if(matrix[initRow][initCol]==0)
			continue;
			int terasure = matrix[initRow][initCol];
			find_max_path(matrix,visited,row,column,initRow,initCol, terasure, max_Treasure);
		}
	}
}

bool isSafe(vector< vector<int> > matrix, vector< vector<int> >visited, int x, int y) {
	if (matrix[x][y] == 0 || visited[x][y] == 1) {
		return false;
	}
	return true;
}

bool isValid(int x, int y,int row,int column) {
	if (x < row && y < column && x >= 0 && y >= 0)
		return true;
	return false;
}

