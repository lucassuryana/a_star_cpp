#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using std::cout;
using std::string;
using std::vector;
using std::ifstream;

void ReadBoardFile(string file_name) {
    ifstream my_file(file_name);
    if (my_file) {
        string line;
        while (getline(my_file, line))
        {
            cout << line << "\n";
        }
        
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

int main() {
    return 0;
}