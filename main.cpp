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

vector<State> ParseLine(string line) {
    istringstream sline(line);
    int n;
    char c;
    vector<State> row;
    while (sline >> n >> c && c == ',') {
      if (n == 0) {
      	row.push_back(State::kEmpty);
      }
      else {
      	row.push_back(State::kObstacle);
      }
    }
    return row;
}

string CellString(State cell) {
	if (cell == State::kObstacle) {
    	return "⛰️ ";
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