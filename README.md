# 8-Puzzle Solver

## Overview
This C++ program solves the 8-puzzle problem using two search algorithms:
- **Uniform Cost Search (UCS)**
- **A\* Search** with two heuristics:
  - Misplaced Tiles
  - Manhattan Distance

The program is built to run both interactive and batch experiments. Each algorithm follows a strict node expansion and insertion order: **Up, Right, Down, Left**.

---

## 🧠 Algorithms Implemented

### 🔹 Uniform Cost Search (UCS)
- Uses a priority queue (min-heap) for the frontier.
- Expands the lowest-cost node first.
- Does **not** use heuristics.

### 🔹 A\* Search
- Also uses a min-heap priority queue.
- Expands nodes based on cost `f(n) = g(n) + h(n)` where:
  - `g(n)` is the cost so far (path length)
  - `h(n)` is the heuristic estimate to goal

Two heuristics used:
1. **Misplaced Tiles** – Counts how many tiles are not in the correct position.
2. **Manhattan Distance** – Sum of vertical and horizontal distances of each tile from its goal.

---

## 🔧 Build Instructions

### Requirements
- C++17 compatible compiler (e.g. g++ 13.2 or later)
- Provided startup framework and `AnimateSolution()` support

### To Compile
```bash
g++ -std=c++17 -O2 main.cpp -o puzzle_solver
