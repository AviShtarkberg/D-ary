
# D-ary Trees with iterators and Visualization

## Overview

This C++ project provides an implementation of various tree traversal algorithms along with tree structures that support different branching factors. The library allows for the visualization of trees using the SFML graphics library, which helps in understanding the tree's layout and structure visually. It supports traversal techniques such as In-Order, Pre-Order, Post-Order, Depth-First Search (DFS), and Breadth-First Search (BFS).

## Features

- **Different Tree Traversals**: Implements In-Order, Pre-Order, Post-Order, DFS, and BFS traversals.
- **Customizable Tree Structure**: Allows trees to have a specified maximum number of children (branching factor).
- **Visualization**: Utilizes SFML to visually represent the tree structure.
- **Complex Data Type Support**: Capable of handling complex data types for node values, demonstrated with complex numbers.
- **Error Handling**: Includes robust error handling for tree operations, such as avoiding cycles and enforcing child limits.

## Runnig commands:
   - To run the built-in demo which visualizes the tree structures and traversals:
   ```bash
   make tree
   ```

   - To run the built-in valgrind on the demo file:
   ```bash
   make valgrind_demo
   ```
   *note that when you run  valgrind on the demo there is a false positive memory leak
   detection that is yields from the SFML library.

   - To run the built-in tests class:
   ```bash
   make run_test
   ```

   - To run the built-in valgrind on the tests class:
   ```bash
   make valgrind_test
   ```
## Usage

You can create a tree by instantiating the `Tree` class and using `add_root` and `add_sub_node` to build the tree. For example:

```cpp
Node<int> root(1);
Tree<int> intTree;
intTree.add_root(root);
Node<int> child1(2), child2(3);
intTree.add_sub_node(root, child1);
intTree.add_sub_node(root, child2);
```

You can iterate the tree with pre/in/post order iterators like this:
```cpp
for (auto node = b_tree.begin_in_order(); *node != *b_tree.end_in_order(); ++(*node))
    {
        cout << (*node)->get_value() << " ";
    }
```

Or using dfs/bfs iterators like this:
```cpp
for (auto it = tree_3.begin_dfs(); it != tree_3.end_dfs(); ++it)
    {
        std::cout << (*it)->get_value() << " ";
    }
```

To convert a binary tree to a heap tou should use:
```cpp
   vector<int> heap = b_tree.myHeap();
```

## Libraries Used

This project utilizes several libraries, each chosen for specific functionality needed in the tree traversal and visualization tasks:

- **SFML (Simple and Fast Multimedia Library)**: Used for graphical representation of the trees. SFML provides capabilities for window management, graphics, sound, and network. In this project, it is primarily used to draw nodes and edges of the tree visually on a window, which helps in understanding the structural relationships within the tree.

- **Standard Template Library (STL)**: Utilized for its data structures and algorithms. Vectors, queues, stacks, and algorithms like `std::sort` and `std::make_heap` are used extensively to manage nodes during traversal and to facilitate operations like building heaps from tree elements.

## Project Files Overview

The project is structured into several header and source files, each serving a specific purpose in the tree data structure and traversal implementations:

- **Node.hpp**: Defines the `Node` class, which is a fundamental building block of the tree. Each node can store a value and has links to its children, facilitating the creation of a tree structure.

- **Tree.hpp**: Contains the `Tree` class that manages the overall structure of the tree, including adding nodes and performing different traversal operations. This class uses the `Node` to create the tree and utilizes various iterators for traversal.

- **BaseIterator.hpp**: Abstract base class for all iterators. It defines the common interface that all specific tree traversal iterators adhere to, ensuring consistency across different types of traversals.

- **BFSIterator.hpp**, **DFSIterator.hpp**, **InOrderIterator.hpp**, **PreOrderIterator.hpp**, **PostOrderIterator.hpp**: These files implement specific traversal strategies. Each one extends `BaseIterator` and implements the traversal logic according to the type (BFS, DFS, In-Order, Pre-Order, Post-Order).

- **Complex.hpp**: Defines a `Complex` class for managing complex numbers, which demonstrates handling custom data types within the tree.
