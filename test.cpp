// id:322530080 mail:avishb1213@gmail.com
#include "doctest.h"
#include "Tree.hpp"
#include "Complex.hpp"
#include <iostream>
using namespace std;
using namespace doctest;

TEST_CASE("Tree")
{
    // will check a binary tree
    Node<string> root_node("aaa");
    Tree<string> b_tree;
    b_tree.add_root(root_node);
    Node<string> n1("bbb");
    Node<string> n2("ccc");
    Node<string> n3("ddd");
    b_tree.add_sub_node(root_node, n1);
    b_tree.add_sub_node(root_node, n2);
    b_tree.add_sub_node(n1, n3);

    // will test that the tree is desigd as disired.
    CHECK(b_tree.get_root()->get_children()[0]->get_value() == "bbb");
    CHECK(b_tree.get_root()->get_children()[1]->get_value() == "ccc");
    CHECK_FALSE(b_tree.get_root()->get_children()[1]->get_value() == "aaa");

    // will check that if a tree is 2-ary addidg 3 children to a node will throw.
    CHECK_THROWS(b_tree.add_sub_node(root_node, n3));

    // will check that if we try to create a cycle than the constructor will throw.
    CHECK_THROWS(b_tree.add_sub_node(n3, root_node));

    // will test a tree with more than d=2 and with double type.
    Node<double> n11(3.1);
    Tree<double> ary3_tree(3);
    Node<double> n12(3.2);
    Node<double> n13(3.3);
    Node<double> n14(3.4);
    ary3_tree.add_root(n11);
    ary3_tree.add_sub_node(n11, n12);
    ary3_tree.add_sub_node(n11, n13);
    ary3_tree.add_sub_node(n11, n14);
    CHECK(ary3_tree.get_root()->get_children()[0]->get_value() == 3.2);
    CHECK(ary3_tree.get_root()->get_children()[1]->get_value() == 3.3);
    CHECK(ary3_tree.get_root()->get_children()[2]->get_value() == 3.4);

    // will check that trows for making a cycle in 3-ary tree.
    CHECK_THROWS(ary3_tree.add_sub_node(n12, n11));

    // will ceck that if we try to add a root that have 2 children to 1-ary tree
    // it will throw
    Node<string> root2_node("aaa");
    root2_node.set_max_children(2);
    Node<string> n22("bbb");
    Node<string> n23("ccc");
    root2_node.add_child(n22);
    root2_node.add_child(n23);
    Tree<string> tree_s(1);
    CHECK_THROWS(tree_s.add_root(root2_node));
}

TEST_CASE("Tree with complex")
{
    // will check that the complex calues are added as disired
    Complex a(1, 1);
    Complex b(1, 2);
    Complex c(-1, 1);
    Node<Complex> root_node(a);
    Tree<Complex> b_tree;
    b_tree.add_root(root_node);
    Node<Complex> c2(b);
    Node<Complex> c3(c);
    b_tree.add_sub_node(root_node, c2);
    b_tree.add_sub_node(root_node, c3);
    CHECK(b_tree.get_root()->get_children()[0]->get_value().to_string() == "1.000000+2.000000i");
    CHECK(b_tree.get_root()->get_children()[1]->get_value().to_string() == "-1.000000+1.000000i");

    // will check the > operator as i dicided it to work
    CHECK(!(a > b));
    CHECK(a > c);
}

TEST_CASE("Binary tree iterators")
{
    // will check the in order operator in a regular binary tree
    Node<int> root_node(1);
    Tree<int> b_tree;
    b_tree.add_root(root_node);
    Node<int> n1(2);
    Node<int> n2(1);
    Node<int> n3(0);
    Node<int> n4(2);
    Node<int> n5(3);
    Node<int> n6(7);
    Node<int> n7(4);
    Node<int> n8(8);
    b_tree.add_sub_node(root_node, n1);
    b_tree.add_sub_node(root_node, n4);
    b_tree.add_sub_node(n1, n2);
    b_tree.add_sub_node(n1, n3);
    b_tree.add_sub_node(n4, n5);
    b_tree.add_sub_node(n5, n6);
    b_tree.add_sub_node(n6, n7);
    b_tree.add_sub_node(n6, n8);
    // will check the in order iterator
    vector<int> in_result;
    for (auto node = b_tree.begin_in_order(); *node != *b_tree.end_in_order(); ++(*node))
    {
        in_result.push_back((*node)->get_value());
    }
    string in_exp = "120147832";
    for (size_t i = 0; i < in_result.size(); i++)
    {
        CHECK(in_result[i] == in_exp[i] - '0');
    }

    // will check the preorder iterator
    vector<int> pre_result;
    for (auto node = b_tree.begin_pre_order(); *node != *b_tree.end_pre_order(); ++(*node))
    {
        pre_result.push_back((*node)->get_value());
    }
    string pre_exp = "121023748";
    for (size_t i = 0; i < pre_result.size(); i++)
    {
        CHECK(pre_result[i] == pre_exp[i] - '0');
    }

    // will check the postorder iteraor
    vector<int> post_result;
    for (auto node = b_tree.begin_post_order(); *node != *b_tree.end_post_order(); ++(*node))
    {
        post_result.push_back((*node)->get_value());
    }
    string post_exp = "102487321";
    for (size_t i = 0; i < post_result.size(); i++)
    {
        CHECK(post_result[i] == post_exp[i] - '0');
    }
    string post_expf = "102487320";
    CHECK_FALSE(post_result[8] == post_expf[8] - '0');

    // will check that when we want to preform in/pre/post order on non binary heap the
    // in oreder iterator will return a dfs iterator:
    Node<int> n11(3);
    Tree<int> ary3_tree(3);
    Node<int> n12(2);
    Node<int> n13(4);
    Node<int> n14(6);
    ary3_tree.add_root(n11);
    ary3_tree.add_sub_node(n11, n12);
    ary3_tree.add_sub_node(n11, n13);
    ary3_tree.add_sub_node(n11, n14);
    // in-order
    vector<int> in3_result;
    for (auto node = ary3_tree.begin_in_order(); *node != *ary3_tree.end_in_order(); ++(*node))
    {
        in3_result.push_back((*node)->get_value());
    }
    string in3_expf = "3246";
    for (size_t i = 0; i < in3_result.size(); i++)
    {
        CHECK(in3_result[i] == in3_expf[i] - '0');
    }
    // pre-order
    vector<int> pre3_result;
    for (auto node = ary3_tree.begin_pre_order(); *node != *ary3_tree.end_pre_order(); ++(*node))
    {
        pre3_result.push_back((*node)->get_value());
    }
    string pre3_expf = "3246";
    for (size_t i = 0; i < pre3_result.size(); i++)
    {
        CHECK(pre3_result[i] == pre3_expf[i] - '0');
    }

    // post-order
    vector<int> post3_result;
    for (auto node = ary3_tree.begin_post_order(); *node != *ary3_tree.end_post_order(); ++(*node))
    {
        post3_result.push_back((*node)->get_value());
    }
    string post3_expf = "3246";
    for (size_t i = 0; i < post3_result.size(); i++)
    {
        CHECK(post3_result[i] == post3_expf[i] - '0');
    }
}

TEST_CASE("myHeap test")
{
    // will check that the myHeap operator constructs the right min heap from the tree.
    Node<int> root_node(1);
    Tree<int> b_tree;
    b_tree.add_root(root_node);
    Node<int> n1(2);
    Node<int> n2(1);
    Node<int> n3(0);
    Node<int> n4(2);
    Node<int> n5(3);
    Node<int> n6(7);
    Node<int> n7(4);
    Node<int> n8(8);
    b_tree.add_sub_node(root_node, n1);
    b_tree.add_sub_node(root_node, n4);
    b_tree.add_sub_node(n1, n2);
    b_tree.add_sub_node(n1, n3);
    b_tree.add_sub_node(n4, n5);
    b_tree.add_sub_node(n5, n6);
    b_tree.add_sub_node(n6, n7);
    b_tree.add_sub_node(n6, n8);
    vector<int> heap = b_tree.myHeap();
    string exp = "011247832";
    for (size_t i = 0; i < heap.size(); i++)
    {
        CHECK(heap[i] == exp[i] - '0');
    }

    // will check that its not allowed to creat a heap from non binary tree
    Node<double> n11(3.1);
    Tree<double> ary3_tree(3);
    Node<double> n12(3.2);
    Node<double> n13(3.3);
    Node<double> n14(3.4);
    ary3_tree.add_root(n11);
    ary3_tree.add_sub_node(n11, n12);
    ary3_tree.add_sub_node(n11, n13);
    ary3_tree.add_sub_node(n11, n14);
    CHECK_THROWS(ary3_tree.myHeap());
}

TEST_CASE("Non binary tree")
{
    Node<int> n1(1);
    Tree<int> ary3_tree(3);
    Node<int> n2(2);
    Node<int> n3(3);
    Node<int> n4(4);
    Node<int> n5(5);
    Node<int> n6(6);
    Node<int> n7(7);
    Node<int> n8(8);
    Node<int> n9(9);
    ary3_tree.add_root(n1);
    ary3_tree.add_sub_node(n1, n2);
    ary3_tree.add_sub_node(n1, n3);
    ary3_tree.add_sub_node(n1, n4);
    ary3_tree.add_sub_node(n2, n5);
    ary3_tree.add_sub_node(n2, n6);
    ary3_tree.add_sub_node(n2, n7);
    ary3_tree.add_sub_node(n3, n8);
    ary3_tree.add_sub_node(n4, n9);
    vector<int> dfs_result;
    for (auto it = ary3_tree.begin_dfs(); it != ary3_tree.end_dfs(); ++it)
    {
        dfs_result.push_back((*it)->get_value());
    }
    string dfs_exp = "125673849";
    for (size_t i = 0; i < dfs_result.size(); i++)
    {
        CHECK(dfs_result[i] == dfs_exp[i] - '0');
    }

    vector<int> bfs_result;
    for (auto it = ary3_tree.begin_bfs(); it != ary3_tree.end_bfs(); ++it)
    {
        bfs_result.push_back((*it)->get_value());
    }
    string bfs_exp = "123456789";
    for (size_t i = 0; i < bfs_result.size(); i++)
    {
        CHECK(bfs_result[i] == bfs_exp[i] - '0');
    }

    string bfs_fexp = "213456789";
    CHECK_FALSE(bfs_result[0] == bfs_fexp[0] - '0');
}