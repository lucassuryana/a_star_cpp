# A* algorithm (C++)
- This is the project from [Udacity's Introduction to Self-Driving Cars Nanodegree Program](https://learn.udacity.com/nanodegrees/nd113).
- The code was developed based on the "A* Search" course from the Nanodegree program. 
- The assignment was to code a route planner using the A* algorithm to find the shortest path from the start node to the goal node.

---

## Project Overview
### Goals
* Write an A* algorithm that can find the shortest path from start node to goal node, given the grid of the environment

### Structures
This project consists of two files:
* `1.board`: This data is the grid map of the environment.
* `main.cpp`: This code reads the map of the environment, calculate the shortest path from the start node to the goal node, and visualize the map and the shortest path.

### Run the code
To run the code:
1. Clone this respository: https://github.com/lucassuryana/traffic_light_classifier.git
2. Open `main.cpp` and modify the start and goal position as desired on lines 179 and 180 
2. In your terminal, run the command: "g++ -std=c++17 -g main.cpp"
3. Then execute the compiled program by running "./a.out"

### Results
1. If we choose the start node is grid (0,0) and the goal node is grid (4,5), we will get the result as follows:

🚦  ⛰️   0   0   0   0   
🚗  ⛰️   0   0   0   0   
🚗  ⛰️   0   0   0   0   
🚗  ⛰️   0   🚗  🚗  🚗  
🚗  🚗   🚗  🚗  ⛰️  🏁 
2. If we choose the start node is grid (0,0) and the goal node is grid (0,4), we will get the result as follows:

🚦  ⛰️   0   0   🏁  0   
🚗  ⛰️   0   0   🚗  0   
🚗  ⛰️   0   0   🚗  0   
🚗  ⛰️   0   🚗  🚗  0   
🚗  🚗   🚗   🚗  ⛰️  0 