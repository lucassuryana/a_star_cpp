#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using std::cout;
using std::string;
using std::vector;
using std::ifstream;
using std::istringstream;

enum class State {kEmpty, kObstacle};

vector<int> ParseLine(string line_value) {
    vector<int> row;
    istringstream sline(line_value);

    char c;
    int n;

    // while sline is an integer then character, push integer to row
    while (sline >> n >> c) {
        row.push_back(n);
    }
    return row;
}

vector<vector<int>> ReadBoardFile(string path) {
  ifstream myfile (path);
  vector<vector<int>> board;
  vector<int> row;

  if (myfile) {
    string line;
    while (getline(myfile, line)) {
      row = ParseLine(line);
      board.push_back(row);        
    }
  }
  return board;
}

string CellString(State cell) {
	if (cell == State::kObstacle) {
    	return "⛰️ ";git
    }
  	else {
    	return "0 ";
    }
}

void PrintBoard(const vector< vector<int> > board) {
    for (int i=0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            cout << board[i][j];
        }
        cout << "\n";
    }
}

#include "test.cpp"  // for testing

int main() {
    vector<vector<int>> board;
    board = ReadBoardFile("1.board");
    PrintBoard(board);
}