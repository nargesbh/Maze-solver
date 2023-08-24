# Maze Solver using Dijkstra's Algorithm

This repository contains a C++ program for solving a maze using Dijkstra's algorithm. The program is organized into several classes, including a B-tree implementation for efficient storage and retrieval of visited maze cells.

## Overview

Dijkstra's algorithm is a graph search algorithm that finds the shortest path between nodes in a graph. In this context, the maze is treated as a graph, where each cell represents a node, and adjacent cells are connected by edges. The program finds the shortest path from a starting point to an endpoint in the maze while avoiding obstacles.

## Usage

To use this program, follow these steps:

1. Clone the repository to your local machine:

   ```
   git clone https://github.com/yourusername/maze-solver-dijkstra.git
   '''
2. Compile the C++ program. Make sure you have a C++ compiler installed on your system. You can use g++ for this purpose:

  ```
   g++ maze_solver.cpp -o maze_solver
  ```
3. run the program:
```
./maze_solver
```

# Classes

## BTreeNode
`BTreeNode` represents a node in a B-tree. It is used for efficient storage and retrieval of visited maze cells.

**Private members:**
- `keys`: An array of keys representing cell IDs.
- `childPointerArr`: An array of pointers to child nodes.
- `n`: The current number of keys in the node.
- `leaf`: A boolean indicating whether the node is a leaf node.

**Public methods:**
- `insertNonFull(int k)`: Inserts a key into a non-full node.
- `split(int i, BTreeNode *y)`: Splits a node into two nodes.
- `search(int k)`: Searches for a key in the B-tree.
- `~BTreeNode()`: Destructor for releasing memory.

## BTree
`BTree` represents a B-tree data structure for efficiently storing visited maze cells.

**Private members:**
- `root`: Pointer to the root node of the B-tree.

**Public methods:**
- `insert(int k)`: Inserts a key into the B-tree.
- `search(int k)`: Searches for a key in the B-tree.

## dijkstraMain
`dijkstraMain` is the main class that handles maze solving using Dijkstra's algorithm.

**Private members:**
- `maze`: A 2D array representing the maze.
- `ids`: A 2D array representing the unique ID of each maze cell.
- `m`, `n`: Maze dimensions (rows and columns).
- `V`: Total number of vertices (maze cells).
- `count`: Counter for assigning unique IDs to maze cells.
- `startX`, `startY`: Starting coordinates in the maze.
- `endX`, `endY`: Ending coordinates in the maze.
- `path`: Vector to store the shortest path.

**Public methods:**
- `dijkstra(int** graph, int srcX, int srcY, BTree t)`: Performs Dijkstra's algorithm to find the shortest path.
- `minDistance(int dist[], BTree t)`: Finds the vertex with the minimum distance.
- `printPath(int parent[], int j)`: Prints the path from the starting point to the endpoint.
- `makeOutput()`: Modifies the maze to mark the path and prints the result.
