//id:322530080 mail:avishb1213@gmail.com
#ifndef POST_ORDER_ITERATOR_HPP
#define POST_ORDER_ITERATOR_HPP

#include "BaseIterator.hpp"
#include <stack>

// Template class PostOrderIterator which extends BaseIterator.
// This iterator implements post-order traversal for trees, where each node is processed
// after its children. It's useful for operations where children nodes must be processed
// before their parents, such as tree deletions or bottom-up evaluations.
template <typename T>
class PostOrderIterator : public BaseIterator<T>
{
public:
    // Constructor initializes the iterator starting from the 'root' node.
    // It populates a stack with all nodes in post-order by using a temporary stack
    // to first reverse the order of node traversal.
    PostOrderIterator(Node<T> *root)
    {
        if (root != nullptr)
        {
            fill_stack(root);
            if (!_post_order_stack.empty())
            {
                this->_current = _post_order_stack.top();
                _post_order_stack.pop();
            }
        }
        else
        {
            this->_current = nullptr;
        }
    }

    // Overloaded prefix increment operator.
    // Advances the iterator to the next node in post-order sequence.
    PostOrderIterator &operator++() override
    {
        if (this->_current == nullptr)
        {
            return *this;
        }

        if (!_post_order_stack.empty())
        {
            this->_current = _post_order_stack.top();
            _post_order_stack.pop();
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
        return this->_current != static_cast<const PostOrderIterator *>(&other)->_current;
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
    std::stack<Node<T> *> _post_order_stack;

    // Helper function to populate _post_order_stack with nodes in post-order.
    // Uses a temporary stack to reverse the traversal order temporarily.
    void fill_stack(Node<T> *root)
    {
        std::stack<Node<T> *> temp_stack;
        temp_stack.push(root);

        // Reverse order traversal using a temporary stack to achieve post-order.
        while (!temp_stack.empty())
        {
            Node<T> *node = temp_stack.top();
            temp_stack.pop();
            _post_order_stack.push(node);

            const auto &children = node->get_children();
            for (const auto &child : children)
            {
                temp_stack.push(child);
            }
        }
    }
};

#endif
