# GraphPath Explorer

**A Graph-Based Path Finding and Minimum Spanning Tree Project in C**

## About the Project

GraphPath Explorer is a C programming project that explores different graph algorithms to find paths between vertices and understand how a graph is connected.

The project uses Dijkstra's algorithm to find the shortest path between a source and destination. It also implements Kruskal's and Prim's algorithms to construct Minimum Spanning Trees (MSTs) and find paths within those trees.

Another feature is edge removal. When a selected edge is removed, the program rebuilds the graph and runs the algorithms again to show how the path and connectivity change.

The main goal of this project is to understand how different graph algorithms work and how they handle changes in a graph.

## Features

- **Dijkstra's Algorithm:** Finds the shortest path between two vertices.
- **Kruskal's Algorithm:** Builds a Minimum Spanning Tree using Disjoint Set Union (DSU).
- **Prim's Algorithm:** Builds a Minimum Spanning Tree using a greedy approach.
- **Path Finding:** Finds the path between source and destination inside an MST.
- **Edge Removal:** Removes a selected edge and updates the graph.
- **Path Recalculation:** Runs the algorithms again after edge removal.
- **File Handling:** Reads graph information from an external text file.
- **Connectivity Checking:** Displays `Not Possible` when a required path or spanning tree cannot be found.

## Algorithms and Concepts Used

| Algorithm / Concept | Purpose |
|---|---|
| Dijkstra | Shortest Path |
| Kruskal | Minimum Spanning Tree |
| Prim | Minimum Spanning Tree |
| DSU | Cycle Detection in Kruskal |
| BFS | Finding paths inside an MST |
| Adjacency Matrix | Graph Representation |
| File Handling | Reading Input |
| Dynamic Memory Allocation | Storing Edge Data |

## Project Structure

```text
GraphPath-Explorer/
│
├── main.c
├── graph.txt
└── README.md
```

## Input Format

The program reads input from `graph.txt`.

Example:

```text
6 8
0 2 2
2 3 2
0 1 2
1 3 2
3 5 2
4 5 4
0 4 5
0 5 5
0 5
3 5
```

### Input Explanation

- First line: Number of vertices (`N`) and edges (`M`).
- Next `M` lines: Source vertex, destination vertex and edge weight.
- Next line: Source and destination for path finding.
- Last line: The edge to be removed.

Vertices are numbered from `0` to `N-1`.

The graph is undirected and uses positive edge weights.

## Sample Output

```text
Shortest Path: 0 -> 5 (Cost: 5)
Kruskal Path: 0 -> 2 -> 3 -> 5 (Cost: 6)
Prim Path: 0 -> 1 -> 3 -> 5 (Cost: 6)

After Removing Edge (3,5):
Updated Shortest Path: 0 -> 5 (Cost: 5)
Updated Kruskal Path: 0 -> 4 -> 5 (Cost: 9)
Updated Prim Path: 0 -> 4 -> 5 (Cost: 9)
```

*Note: When multiple edges have equal weights, different valid MST paths may be produced.*

## How to Run

**1. Clone the repository**

```bash
git clone https://github.com/your-username/GraphPath-Explorer.git
```

**2. Open the project folder**

```bash
cd GraphPath-Explorer
```

**3. Compile the C program**

```bash
gcc main.c -o graph -std=c99
```

**4. Run the program**

```bash
./graph
```

On Windows:

```bash
graph.exe
```

Make sure `graph.txt` is in the same working directory as the executable.

## Technologies Used

- C Programming Language
- Standard C Library
- Graph Theory
- Data Structures and Algorithms
- File Handling

## Learning Objectives

Through this project, I explored how different graph algorithms solve path-finding and connectivity problems. It helped me understand greedy algorithms, graph representation, Disjoint Set Union, BFS, and the effect of removing an edge from a graph.

## Author

**Your Name**

Algorithm Lab Project  
Department of Computer Science and Engineering

---

*This project was developed for educational purposes as part of an Algorithm Lab course.*
