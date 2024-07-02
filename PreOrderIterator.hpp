//id:322530080 mail:avishb1213@gmail.com
#ifndef PRE_ORDER_ITERATOR_HPP
#define PRE_ORDER_ITERATOR_HPP

#include "BaseIterator.hpp"
#include <stack>

template <typename T>
class PreOrderIterator : public BaseIterator<T>
{
public:
    PreOrderIterator(Node<T> *root)
    {
        if (root != nullptr)
        {
            _node_stack.push(root);
            this->_current = root;
        }
    }

    PreOrderIterator &operator++() override
    {
        if (!_node_stack.empty())
        {
            Node<T> *node = _node_stack.top();
            _node_stack.pop();

            const auto &children = node->get_children();
            for (auto it = children.rbegin(); it != children.rend(); ++it)
            {
                _node_stack.push(*it);
            }

            if (!_node_stack.empty())
            {
                this->_current = _node_stack.top();
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

    bool operator!=(const BaseIterator<T> &other) const override
    {
        return this->_current != static_cast<const PreOrderIterator *>(&other)->_current;
    }

    Node<T> *operator*() const override
    {
        return this->_current;
    }

    Node<T> *operator->() const override
    {
        return this->_current;
    }

private:
    std::stack<Node<T> *> _node_stack;
};

#endif
