#ifndef NODE_HPP
#define NODE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <stdexcept>
#include <typeinfo>
#include <string>

using namespace std;

template <typename T>
class Node
{
public:
    // Constructor
    Node(T value) : value(value), is_parent(false), max_children(0) {}

    // Get the value stored in the node
    T get_value() const
    {
        return value;
    }

    // Add a child node
    void add_child(Node<T> &child)
    {
        if (children.size() >= max_children)
        {
            throw std::runtime_error("Cannot add more children!");
        }
        children.push_back(&child);
    }

    // Get the children of the node
    const std::vector<Node<T> *> &get_children() const
    {
        return children;
    }

    // Get the number of children
    size_t get_children_num() const
    {
        return children.size();
    }

    // Check if the node is a parent
    bool get_is_parent() const
    {
        return is_parent;
    }

    // Set the node as a parent
    void set_is_parent()
    {
        is_parent = true;
    }

    // Set the maximum number of children
    void set_max_children(size_t max_children)
    {
        this->max_children = max_children;
    }

    void set_value(T t)
    {
        this->value = t;
    }

private:
    T value;
    bool is_parent;
    size_t max_children;
    std::vector<Node<T> *> children;
};

#endif
