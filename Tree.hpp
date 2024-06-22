#ifndef TREE_HPP
#define TREE_HPP

#include <memory>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Node.hpp"
#include "InOrderIterator.hpp"
#include "PreOrderIterator.hpp"
#include "PostOrderIterator.hpp"
#include "DfsIterator.hpp"
#include "BfsIterator.hpp"
#include "BaseIterator.hpp"
#include <SFML/Graphics.hpp>
#include <string>

template <typename T>
class Tree
{
public:
    /**
     * @brief Constructs a tree with a specified branching factor.
     * @param k The maximum number of children each node can have; default is 2 (binary tree).
     */
    Tree(size_t k = 2) : _root(nullptr), _k(k) {}

    /**
     * @brief Default destructor.
     */
    ~Tree() {}

    /**
     * @brief Sets the root node of the tree.
     * @param root The node to be set as root.
     * @exception std::runtime_error Throws if the node has more children than allowed (k).
     */
    void add_root(Node<T> &root)
    {
        if (root.get_children_num() > this->_k)
        {
            throw std::runtime_error("you can't add a root with more than k children!!!");
        }
        this->_root = &root;
        _root->set_is_parent();
        _root->set_max_children(this->_k);
    }

    /**
     * @brief Adds a child node to a parent node in the tree.
     * @param node1 The parent node.
     * @param node2 The child node to be added.
     * @exception std::runtime_error Throws if trying to create a cycle or exceed child limit.
     */
    void add_sub_node(Node<T> &node1, Node<T> &node2)
    {
        if (node2.get_is_parent())
        {
            throw std::runtime_error("you can't create cycles in a tree!!!");
        }
        node1.set_is_parent();
        node1.set_max_children(this->_k);
        node1.add_child(node2);
    }

    /**
     * @brief Begins in-order traversal of the tree.
     * @note DFS iterator will be returnd if the tree is not a binary tree.
     * @return std::unique_ptr<BaseIterator<T>> Unique pointer to the beginning of the in-order iterator.
     */
    std::unique_ptr<BaseIterator<T>> begin_in_order()
    {
        if (_k != 2)
        {
            return std::make_unique<DFSIterator<T>>(_root);
        }
        else
        {
            return std::make_unique<InOrderIterator<T>>(_root);
        }
    }

    /**
     * @brief Ends in-order traversal of the tree.
     * @return std::unique_ptr<BaseIterator<T>> Unique pointer to the end of the in-order iterator.
     */
    std::unique_ptr<BaseIterator<T>> end_in_order()
    {
        return std::make_unique<DFSIterator<T>>(nullptr);
    }

    /**
     * @brief Begins pre-order traversal of the tree.
     * @note DFS iterator will be returnd if the tree is not a binary tree.
     * @return std::unique_ptr<BaseIterator<T>> Unique pointer to the beginning of the pre-order iterator.
     */
    std::unique_ptr<BaseIterator<T>> begin_pre_order()
    {
        if (_k != 2)
        {
            return std::make_unique<DFSIterator<T>>(_root);
        }
        else
        {
            return std::make_unique<PreOrderIterator<T>>(_root);
        }
    }

    /**
     * @brief Ends pre-order traversal of the tree.
     * @return std::unique_ptr<BaseIterator<T>> Unique pointer to the end of the pre-order iterator.
     */
    std::unique_ptr<BaseIterator<T>> end_pre_order()
    {
        return std::make_unique<DFSIterator<T>>(nullptr);
    }

    /**
     * @brief Begins post-order traversal of the tree.
     * @note DFS iterator will be returnd if the tree is not a binary tree.
     * @return std::unique_ptr<BaseIterator<T>> Unique pointer to the beginning of the post-order iterator.
     */
    std::unique_ptr<BaseIterator<T>> begin_post_order()
    {
        if (_k != 2)
        {
            return std::make_unique<DFSIterator<T>>(_root);
        }
        else
        {
            return std::make_unique<PostOrderIterator<T>>(_root);
        }
    }

    /**
     * @brief Ends post-order traversal of the tree.
     * @return std::unique_ptr<BaseIterator<T>> Unique pointer to the end of the post-order iterator.
     */
    std::unique_ptr<BaseIterator<T>> end_post_order()
    {
        return std::make_unique<DFSIterator<T>>(nullptr);
    }

    /**
     * @brief Begins depth-first search (DFS) traversal of the tree.
     * @return DFSIterator<T> DFS iterator to the beginning of the tree.
     */
    DFSIterator<T> begin_dfs()
    {
        return DFSIterator<T>(_root);
    }

    /**
     * @brief Ends depth-first search (DFS) traversal of the tree.
     * @return DFSIterator<T> DFS iterator to the end of the tree.
     */
    DFSIterator<T> end_dfs()
    {
        return DFSIterator<T>(nullptr);
    }

    /**
     * @brief Begins breadth-first search (BFS) traversal of the tree.
     * @return BFSIterator<T> BFS iterator to the beginning of the tree.
     */
    BFSIterator<T> begin_bfs()
    {
        return BFSIterator<T>(_root);
    }

    /**
     * @brief Ends breadth-first search (BFS) traversal of the tree.
     * @return BFSIterator<T> BFS iterator to the end of the tree.
     */
    BFSIterator<T> end_bfs()
    {
        return BFSIterator<T>(nullptr);
    }

    /**
     * @brief Generates a heap from the tree elements using in-order traversal.
     * @return std::vector<T> A heap containing the tree's elements.
     * @exception std::runtime_error Throws if the tree is not a binary tree.
     */
    std::vector<T> myHeap()
    {
        if (this->_k != 2)
        {
            throw runtime_error("you cant build a heap from non-binary tree");
        }

        std::vector<T> elements;
        auto begin = this->begin_in_order();
        auto end = this->end_in_order();
        for (; *begin != *end; ++(*begin))
        {
            elements.push_back((*begin)->get_value());
        }
        std::make_heap(elements.begin(), elements.end(), std::greater<T>());
        return elements;
    }

    /**
     * @brief Overloads the output stream operator for tree visualization.
     * @param os Reference to the output stream.
     * @param tree Constant reference to the tree to be visualized.
     * @return std::ostream& Reference to the modified output stream.
     */
    friend std::ostream &operator<<(std::ostream &os, const Tree<T> &tree)
    {
        sf::RenderWindow window(sf::VideoMode(800, 800), "Tree Visualization");
        window.setFramerateLimit(60);
        sf::Font font;
        if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"))
        {
            throw std::runtime_error("Failed to load font");
        }
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear(sf::Color::White);
            float start_x = window.getSize().x / 2;
            tree.draw_node(window, tree._root, start_x, 50, 400, font);
            window.display();
        }
        window.close();
        return os;
    }

    Node<T> *get_root()
    {
        return this->_root;
    }

private:
    Node<T> *_root; ///< Pointer to the root node of the tree.
    size_t _k;      ///< Maximum number of children each node can have.

    /**
     * @brief Helper function to draw a node and its children.
     * @param window Reference to the SFML window for drawing.
     * @param node Pointer to the node to be drawn.
     * @param x Horizontal position of the node.
     * @param y Vertical position of the node.
     * @param x_offset Horizontal offset for positioning children nodes.
     * @param font Reference to the font used for node labels.
     * @return float Horizontal position of the node after drawing.
     */
    float draw_node(sf::RenderWindow &window, Node<T> *node, float x, float y, float x_offset, sf::Font &font) const
    {
        if (!node)
        {
            return x;
        }
        sf::CircleShape shape(20);
        shape.setFillColor(sf::Color::Blue);
        shape.setPosition(x - shape.getRadius(), y - shape.getRadius());
        sf::Text text;
        text.setFont(font);
        std::stringstream ss;
        ss << node->get_value();
        text.setString(ss.str());
        text.setCharacterSize(14);
        text.setFillColor(sf::Color::White);
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        text.setPosition(x, y);
        window.draw(shape);
        window.draw(text);
        float child_x_offset = x_offset / 3.1f;
        float child_y = y + 100;
        float subtree_width = (node->get_children_num() - 1) * child_x_offset;
        float start_x = x - subtree_width / 2;
        for (size_t i = 0; i < node->get_children_num(); ++i)
        {
            Node<T> *child = node->get_children()[i];
            float child_x = start_x + i * child_x_offset;
            sf::Vertex line[] =
                {
                    sf::Vertex(sf::Vector2f(x, y)),
                    sf::Vertex(sf::Vector2f(child_x, child_y))};
            line[0].color = sf::Color::Black;
            line[1].color = sf::Color::Black;

            window.draw(line, 2, sf::Lines);
            draw_node(window, child, child_x, child_y, child_x_offset, font);
        }

        return x;
    }
};

#endif