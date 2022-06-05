// #ifndef _NODE_HPP_
// #define _NODE_HPP_

#include <iostream>
#include <vector>

namespace ariel
{
    class Node
    {

    public:
        std::string name;
        std::vector<Node *> sub_Nodes;
        int level;

        Node();
        Node(const std::string &title, int level);
        Node(Node &other) = default;
        Node(Node &&other) = default;
        Node &operator=(Node &&other) = default;
        Node &operator=(const Node &other) = default;
        ~Node() {}
        std::string get_name() const;
        void set_name(std::string newName);
        std::vector<Node *> get_subNodes() const;
        int get_level() const;
        void set_level(int level);
    };
}