//id:322530080 mail:avishb1213@gmail.com
#include <iostream>
#include "Tree.hpp"
#include "Complex.hpp"
using namespace std;
int main()
{

    /*  _     _                          _
       | |   (_)                        | |
       | |__  _ _ __   __ _ _ __ _   _  | |_ _ __ ___  ___
       | '_ \| | '_ \ / _` | '__| | | | | __| '__/ _ \/ _ \
       | |_) | | | | | (_| | |  | |_| | | |_| | |  __/  __/
       |_.__/|_|_| |_|\__,_|_|   \__, |  \__|_|  \___|\___|
                                  __/ |
                                 |___/
        */
    // graph creation:
    Node<int> root_node(1);
    Tree<int> b_tree;
    b_tree.add_root(root_node);
    Node<int> n1(2);
    Node<int> n2(3);
    Node<int> n3(4);
    b_tree.add_sub_node(root_node, n1);
    b_tree.add_sub_node(root_node, n2);
    b_tree.add_sub_node(n1, n3);

    cout << "In-order traversal: ";
    for (auto node = b_tree.begin_in_order(); *node != *b_tree.end_in_order(); ++(*node))
    {
        cout << (*node)->get_value() << " ";
    }
    cout << endl;

    // preforming Pre-order traversal using the iterator:
    cout << "Pre-order traversal: ";
    for (auto node = b_tree.begin_pre_order(); *node != *b_tree.end_pre_order(); ++(*node))
    {
        cout << (*node)->get_value() << " ";
    }
    cout << endl;

    // preforming Post-order traversal using the iterator:
    cout << "Post-order traversal: ";
    for (auto node = b_tree.begin_post_order(); *node != *b_tree.end_post_order(); ++(*node))
    {
        cout << (*node)->get_value() << " ";
    }
    cout << endl;

    vector<int> heap = b_tree.myHeap();
    cout << "after using myHeap mehod: ";
    for (auto i = heap.begin(); i != heap.end(); ++i)
    {
        cout << *i << " ";
    }
    cout << endl;
    cout << b_tree;

    /*____     _
     |___ \   | |
       __) |  | |_ _ __ ___  ___
      |__  |  | __| '__/ _ \/ _ \
      ___) |  | |_| | |  __/  __/
     |____/    \__|_|  \___|\___|
    */
    // graph creation:
    Complex a(1, 1);
    Complex b(1, 2);
    Complex c(-1, 1);
    Complex d(2, 2);
    Complex e(-1, -1);
    Complex f(-2, -2);
    Complex g(1, -1);
    Node<Complex> n13(a);
    Node<Complex> n23(b);
    Node<Complex> n33(c);
    Node<Complex> n43(d);
    Node<Complex> n53(e);
    Node<Complex> n63(f);
    Node<Complex> n73(g);
    Tree<Complex> tree_3(3);
    tree_3.add_root(n13);
    tree_3.add_sub_node(n13, n23);
    tree_3.add_sub_node(n13, n53);
    tree_3.add_sub_node(n13, n73);
    tree_3.add_sub_node(n23, n33);
    tree_3.add_sub_node(n23, n43);
    tree_3.add_sub_node(n53, n63);

    cout << "tree_3 Dfs: ";
    // preforming DFS using the iterator:
    for (auto it = tree_3.begin_dfs(); it != tree_3.end_dfs(); ++it)
    {
        std::cout << (*it)->get_value() << " ";
    }
    cout << endl;

    cout << "tree_3 Bfs: ";
    for (auto it = tree_3.begin_bfs(); it != tree_3.end_bfs(); ++it)
    {
        std::cout << (*it)->get_value() << " ";
    }
    cout << endl;

    cout << "In-order traversal that runs as DFS: ";
    for (auto node = tree_3.begin_in_order(); *node != *tree_3.end_in_order(); ++(*node))
    {
        cout << (*node)->get_value() << " ";
    }

    cout << endl;
    try
    {
        vector<Complex> heap = tree_3.myHeap();
    }
    catch (const exception &e)
    {
        cout << e.what() << endl;
    }

    // will open the gui that represent 3_tree!
    cout << tree_3;
    return 0;
}
