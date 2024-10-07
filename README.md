# Monte Carlo Tree Search (MCTS) Implementations

This repository contains three implementations of the Monte Carlo Tree Search (MCTS) algorithm in different programming languages:

- **C++**: A basic version demonstrating the core structure of MCTS.
- **Python**: A more accessible version that maintains the functionality while making it easier to understand for Python users.
- **Julia**: A translated version for those interested in using Julia's syntax and performance advantages.

## Overview
Monte Carlo Tree Search (MCTS) is a popular algorithm used for decision-making in games and other applications where large state spaces make traditional approaches impractical. MCTS uses simulations to evaluate possible moves and gradually builds a search tree, balancing exploration and exploitation.

The algorithm works in four main phases:
1. **Selection**: Traverse the tree from the root to a leaf node, using the UCT formula to balance exploration and exploitation.
2. **Expansion**: Expand the tree by adding a new child node if the selected node is not terminal and not fully expanded.
3. **Simulation**: Perform a random simulation from the newly added node to estimate its value.
4. **Backpropagation**: Backpropagate the result of the simulation to update the values of ancestor nodes.

## Code Versions
### C++ Version
The C++ version demonstrates the fundamental steps of MCTS and is suitable for those familiar with lower-level programming. It includes classes for nodes and uses standard libraries for random number generation and mathematical functions.

- **File**: `mcts_vanilla.cpp`
- **Features**:
  - Explicit memory management (use of pointers for parent and children nodes).
  - A simple implementation of UCT (Upper Confidence Bound for Trees) for selection.

### Python Version
The Python version of the MCTS algorithm is written in an easily readable way, making it perfect for educational purposes or rapid prototyping.

- **File**: `mcts_vanilla.py`
- **Features**:
  - Object-oriented approach using Python classes.
  - Random outcomes simulated with Python's `random` library.
  - Suitable for beginners and those looking for a more understandable version of MCTS.

### Julia Version
The Julia version is a translation from Python and takes advantage of Julia's features for numerical computation.

- **File**: `mcts_vanilla.jl`
- **Features**:
  - Utilizes Julia's `mutable struct` for defining nodes.
  - Fast execution due to Julia's performance advantages.
  - Ideal for those who work in scientific computing and wish to integrate MCTS with other Julia tools.

## How to Run the Code
### Prerequisites
- **C++**: You need a C++ compiler (e.g., `g++`).
- **Python**: Python 3.x is required.
- **Julia**: Install Julia (v1.x or later).

### Running the Code
- **C++**:
  ```sh
  g++ -o mcts mcts_vanilla.cpp
  ./mcts
  ```
- **Python**:
  ```sh
  python mcts_vanilla.py
  ```
- **Julia**:
  ```sh
  julia mcts_vanilla.jl
  ```

## Acknowledgments
The implementations are intentionally kept simple to facilitate learning. The code balances exploration and exploitation using the UCT formula and is inspired by popular examples of MCTS used in board games and other AI applications.

