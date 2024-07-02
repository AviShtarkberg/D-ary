//id:322530080 mail:avishb1213@gmail.com
#ifndef IN_ORDER_ITERATOR_HPP
#define IN_ORDER_ITERATOR_HPP

#include "BaseIterator.hpp"
#include <stack>

// Template class InOrderIterator which extends BaseIterator.
// This iterator implements in-order traversal for binary trees, visiting the left child, 
// the node itself, and then the right child recursively.
template <typename T>
class InOrderIterator : public BaseIterator<T>
{
public:
    // Constructor that initiates in-order traversal from the 'root' node.
    // It pushes all the left children onto a stack starting from the root.
    InOrderIterator(Node<T> *root)
    {
        this->_current = nullptr;
        if (root != nullptr)
        {
            traverse_left(root);
            if (!_node_stack.empty())
            {
                this->_current = _node_stack.top();
                _node_stack.pop();
            }
        }
    }

    // Overloaded prefix increment operator.
    // Moves the iterator to the next node in in-order sequence.
    // After visiting a node, it traverses left from the right child if available.
    InOrderIterator &operator++() override
    {
        if (this->_current == nullptr)
        {
            return *this;
        }

        const auto &children = this->_current->get_children();
        if (children.size() > 1)
        {
            traverse_left(children[1]); // Assuming binary tree, process the right child.
        }

        if (!_node_stack.empty())
        {
            this->_current = _node_stack.top();
            _node_stack.pop();
        }
        else
        {
            this->_current = nullptr;
        }

        return *this;
    }

    // Overloaded inequality operator.
    // Compares the current node of this iterator with another iterator's current node.
    bool operator!=(const BaseIterator<T> &other) const override
    {
        return this->_current != static_cast<const InOrderIterator *>(&other)->_current;
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
    std::stack<Node<T> *> _node_stack;

    // Helper function to traverse and push all left children of a node onto the stack.
    void traverse_left(Node<T> *node)
    {
        while (node != nullptr)
        {
            _node_stack.push(node);
            const auto &children = node->get_children();
            node = !children.empty() ? children[0] : nullptr; // Move to the left child.
        }
    }
};

#endif
