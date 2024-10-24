# Gator AVL Tree Project


## Table of Contents

- [Project Overview](#project-overview)
- [Features](#features)
- [Time Complexities](#time-complexities)
- [Setup](#setup)
  - [Prerequisites](#prerequisites)
  - [Compilation](#compilation)
  - [Running the Program](#running-the-program)
- [File Structure](#file-structure)
- [Key Operations](#key-operations)
  - [Insert](#insert)
  - [Delete](#delete)
  - [Search](#search)
  - [Traversal](#traversal)
  - [Balancing](#balancing)
- [Known Issues and Improvements](#known-issues-and-improvements)
- [Acknowledgments](#acknowledgments)

---

## Project Overview

This project implements an AVL tree data structure, a self-balancing binary search tree (BST). The tree keeps itself balanced by ensuring that the height difference between the left and right subtrees of every node is no more than one. This structure supports efficient operations for insertion, deletion, and search by automatically rebalancing through rotations.

---

## Features

- **Insert**: Add nodes to the AVL tree while maintaining its balance.
- **Delete**: Remove nodes either by ID or by position (Nth node).
- **Search**: Perform searches by ID or name.
- **Traversal**: Supports in-order, pre-order, and post-order traversals.
- **Balancing**: Automatic rebalancing using rotations (left and right).
- **Height Maintenance**: Functions to update and check node heights.

---

## Time Complexities

- **Insert**: `O(log n)` in a balanced AVL tree.
- **Delete**: `O(log n)` on average, `O(n)` in the worst case.
- **Search**: `O(log n)` on average, `O(n)` in the worst case.
- **Traversal**: `O(n)` for in-order, pre-order, and post-order traversals.
- **Rotations**: `O(1)` for both left and right rotations.
- **Height Update**: `O(1)` for updating node height, `O(n)` for checking the tree’s height.

---

## Setup

### Prerequisites

Ensure that you have the following:
- A C++ compiler (e.g., g++).

### Compilation

Use the following command to compile the project:

```bash
g++ -o gator_avl_tree main.cpp
```

### Running the Program

After compilation, run the executable generated with:

```bash
./gator_avl_tree
```

---

## File Structure

- **main.cpp**: The main file that includes the implementation of the AVL tree and related operations.
- **BST.cpp**: Contains the core functionalities such as insert, delete, search, and balancing methods.
- **BST.h**: Header file defining the AVL tree structure and function prototypes.

---

## Key Operations

### Insert

- **Description**: Adds a node while maintaining the balance of the AVL tree.
- **Time Complexity**: `O(log n)`

### Delete

- **Description**: Removes a node by ID or its position in the tree (Nth node).
- **Time Complexity**: `O(log n)` on average, `O(n)` in the worst case.

### Search

- **Description**: Searches for a node by ID or name.
- **Time Complexity**: `O(log n)` on average, `O(n)` in the worst case.

### Traversal

- **Description**: Supports in-order, pre-order, and post-order traversal methods.
- **Time Complexity**: `O(n)` for all traversal methods.

### Balancing

- **Description**: The tree uses left and right rotations to maintain balance.
- **Time Complexity**: `O(1)` for both rotations.


---


