#include <algorithm>
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
using std::abs;
using std::sort;

// Define states for grid cells
enum class State {kEmpty, kObstacle, kClosed, kPath};

// Define directional deltas
const int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

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

// Function to compare two nodes
bool Compare(const vector<int> node_one, const vector<int> node_two) {
  // node structure is {x, y, g, h}
  int f1 = node_one[2] + node_one[3]; // f1 = g1 + h1
  int f2 = node_two[2] + node_two[3]; // f2 = g2 + h2
  return f1 > f2;
}

// Function to sort two dimensional vector of ints in descending order
// -> and * related to C++ pointers
void CellSort(vector<vector<int>> *v) {
  sort(v->begin(), v->end(), Compare);
}

// Function to calculate Manhattan distance heuristic
int Heuristic(int x1, int y1, int x2, int y2) {
    return abs(x2 - x1) + abs(y2 - y1);
}

// Function to check if the cell is on the grid and not an obstacle (i.e., equals kEmpty)
bool CheckValidCell(int x, int y, vector<vector<State>> &grid){
  bool on_grid_x = (x >= 0 && x < grid.size());
  bool on_grid_y = (y >= 0 && y < grid[0].size());
  if (on_grid_x && on_grid_y)
    return grid[x][y] == State::kEmpty;
  return false;
}

// Function to add a node to the open list
void AddToOpen(int x, int y, int g, int h, vector<vector<int>> &open_nodes, vector<vector<State>> &grid) {
    vector<int> node {x, y, g, h};
    open_nodes.push_back(node);
    // Mark node as closed in the grid
    grid[x][y] = State::kClosed;
}

void ExpandNeighbors(const vector<int> &current, int goal[2], vector<vector<int>> &open_nodes, vector<vector<State>> &grid) {
    // Get current node's data
    int x = current[0];
    int y = current[1];
    int g = current[2];
    
    // Loop through current node's potential neighbor
    for (int i = 0; i < 4; i++) {
      int neighbor_x = x + delta[i][0];
      int neighbor_y = y + delta[i][1];

      // Check that the potential neighbor are on the grid and not closed
      if (CheckValidCell(neighbor_x, neighbor_y, grid)){
        int g2 = g + 1;
        int h2 = Heuristic(neighbor_x, neighbor_y, goal[0], goal[1]);
        AddToOpen(neighbor_x, neighbor_y, g2, h2, open_nodes, grid);
      }

    }
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

    while (!open.empty()) {
      // Sort open list
      CellSort(&open);
      // Get the last node from open vector
      vector<int> current_node = open.back();
      // Remove the last node
      open.pop_back();
      // Get x and y values from current_node
      int current_x = current_node[0];
      int current_y = current_node[1];
      // Set grid[x][y] to kPath
      grid[current_x][current_y] = State::kPath;
      // Check if the end goal has been reached. If yes, return grid
      if (current_x == goal[0] && current_y == goal[1]) {
        return grid;
      }

      ExpandNeighbors(current_node, goal, open, grid);
    }

    cout << "No path found!" << "\n";
    return std::vector<vector<State>> {};
}

// Function to convert cell state to string for printing
string CellString(State cell) {
    if (cell == State::kObstacle) {
        return "⛰️   "; // Mountain emoji for obstacles
    } else if (cell == State::kPath) {
      return "🚗  "; // Vehicle emoji for self-driving car
    } else {
        return "0   "; // Empty cell
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
