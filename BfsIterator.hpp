//id:322530080 mail:avishb1213@gmail.com
#ifndef BFS_ITERATOR_HPP
#define BFS_ITERATOR_HPP

#include "BaseIterator.hpp"
#include <queue>

// Template class BFSIterator which extends BaseIterator.
// This iterator implements Breadth-First Search (BFS) traversal of a tree data structure.
template <typename T>
class BFSIterator : public BaseIterator<T>
{
public:
    // Constructor that takes a pointer to the root node of the tree.
    // If the root is not nullptr, it initializes the queue with the root node
    // and sets the current node to root. Otherwise, it sets the current node to nullptr.
    BFSIterator(Node<T> *root)
    {
        if (root != nullptr)
        {
            _node_queue.push(root);
            this->_current = root;
        }
        else
        {
            this->_current = nullptr;
        }
    }

    // Overloaded prefix increment operator.
    // Advances the iterator to the next node in BFS order.
    // If the queue is not empty, it dequeues the front node, enqueues its children,
    // and updates the current node to the new front of the queue.
    // If the queue is empty after popping, sets the current node to nullptr.
    BFSIterator &operator++() override
    {
        if (!_node_queue.empty())
        {
            Node<T> *node = _node_queue.front();
            _node_queue.pop();

            const auto &children = node->get_children();
            for (auto it = children.begin(); it != children.end(); ++it)
            {
                _node_queue.push(*it);
            }

            if (!_node_queue.empty())
            {
                this->_current = _node_queue.front();
            }
            else
            {
                this->_current = nullptr;
            }
        }
        else
        {
            this->_current = nullptr;
        }

        return *this;
    }

    // Overloaded inequality operator.
    // Compares the current node of this iterator with another iterator.
    // Returns true if the current nodes are different, false otherwise.
    bool operator!=(const BaseIterator<T> &other) const override
    {
        return this->_current != static_cast<const BFSIterator *>(&other)->_current;
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
    // Queue to hold nodes at each level of the tree.
    // Nodes are enqueued for visiting in the order of BFS traversal.
    std::queue<Node<T> *> _node_queue;
};

#endif
