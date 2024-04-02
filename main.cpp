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

// Define states for grid cells
enum class State {kEmpty, kObstacle, kClosed};

// Function to parse a line from the board file and create a row vector
vector<State> ParseLine(string line) {
    istringstream sline(line);
    int n;
    char c;
    vector<State> row;
    // Read comma-separated values from the line
    while (sline >> n >> c && c == ',') {
        // Convert value to State and add it to the row
        if (n == 0) {
            row.push_back(State::kEmpty);
        } else {
            row.push_back(State::kObstacle);
        }
    }
    return row;
}

// Function to read the board file and create a 2D vector representing the board
vector<vector<State>> ReadBoardFile(string path) {
    ifstream myfile(path);
    vector<vector<State>> board{};
    // Check if file is opened successfully
    if (myfile) {
        string line;
        // Read each line from the file
        while (getline(myfile, line)) {
            // Parse line to create a row vector and add it to the board
            vector<State> row = ParseLine(line);
            board.push_back(row);
        }
    }
    return board;
}

// Function to calculate Manhattan distance heuristic
int Heuristic(int x1, int y1, int x2, int y2) {
    return abs(x2 - x1) + abs(y2 - y1);
}

// Function to add a node to the open list
void AddToOpen(int x, int y, int g, int h, vector<vector<int>> &open_nodes, vector<vector<State>> &grid) {
    vector<int> node {x, y, g, h};
    open_nodes.push_back(node);
    // Mark node as closed in the grid
    grid[x][y] = State::kClosed;
}

// Function to perform A* search algorithm
vector<vector<State>> Search(vector<vector<State>> grid, int init[2], int goal[2]) {
    // Initialize open_node
    vector<vector<int>> open {};
    // Initialize variables for starting node
    int x = init[0];
    int y = init[1];
    int g = 0;
    int h = Heuristic(x, y, goal[0], goal[1]);
    // Add first node to open vector using AddToOpen
    AddToOpen(x, y, g, h, open, grid);

    cout << "No path found!" << "\n";
    return std::vector<vector<State>> {};
}

// Function to convert cell state to string for printing
string CellString(State cell) {
    if (cell == State::kObstacle) {
        return "⛰️ "; // Mountain emoji for obstacles
    } else {
        return "0 "; // Empty cell
    }
}

// Function to print the board
void PrintBoard(const vector<vector<State>> board) {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            // Print each cell with appropriate representation
            cout << CellString(board[i][j]);
        }
        cout << "\n"; // Newline after each row
    }
}

int main() {
    int init[2]{0, 0}; // Initial position
    int goal[2]{4, 5}; // Goal position
    auto board = ReadBoardFile("1.board"); // Read board from file
    auto solution = Search(board, init, goal); // Search for path
    PrintBoard(solution); // Print the solution path or the original board if no path found
}
