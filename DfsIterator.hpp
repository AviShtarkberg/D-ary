#ifndef DFS_ITERATOR_HPP
#define DFS_ITERATOR_HPP

#include "BaseIterator.hpp"
#include <stack>

// Template class DFSIterator which extends BaseIterator.
// This iterator implements Depth-First Search (DFS) traversal of a tree data structure.
template <typename T>
class DFSIterator : public BaseIterator<T>
{
public:
    // Constructor that initializes the iterator starting from the 'root' node.
    // If 'root' is not nullptr, the root is pushed onto the stack and set as the current node.
    // If 'root' is nullptr, the current node is set to nullptr, indicating the end of the traversal.
    DFSIterator(Node<T> *root)
    {
        if (root != nullptr)
        {
            _node_stack.push(root);
            this->_current = root;
        }
        else
        {
            this->_current = nullptr;
        }
    }

    // Overloaded prefix increment operator.
    // Advances the iterator to the next node in DFS order.
    // Pops the top node from the stack, pushes all its children onto the stack,
    // and updates the current node to the new top of the stack.
    // If the stack is empty after popping, sets the current node to nullptr.
    DFSIterator &operator++() override
    {
        if (!_node_stack.empty())
        {
            Node<T> *node = _node_stack.top();
            _node_stack.pop();

            const auto &children = node->get_children();
            // Reverse the iteration to maintain the correct DFS order
            for (auto it = children.rbegin(); it != children.rend(); ++it)
            {
                _node_stack.push(*it);
            }

            this->_current = !_node_stack.empty() ? _node_stack.top() : nullptr;
        }
        else
        {
            this->_current = nullptr;
        }

        return *this;
    }

    // Overloaded inequality operator.
    // Checks if the current node of this iterator differs from another iterator's current node.
    bool operator!=(const BaseIterator<T> &other) const override
    {
        return this->_current != static_cast<const DFSIterator *>(&other)->_current;
    }

    // Overloaded dereference operator.
    // Returns the current node pointed by the iterator.
    Node<T> *operator*() const override
    {
        return this->_current;
    }

    // Overloaded arrow operator.
    // Provides direct access to the current node's members.
    Node<T> *operator->() const override
    {
        return this->_current;
    }

private:
    // Stack to hold nodes for DFS traversal.
    // Nodes are pushed and popped as per DFS rules.
    std::stack<Node<T> *> _node_stack;
};

#endif
