#include <iostream>
#include <string>
#include "Node.hpp"

namespace ariel
{

    Node::Node()
    {
        this->name = "";
        this->level = 0;
    }
    Node::Node(const std::string &title, int level)
    {
        this->name = title;
        this->level = level;
    }

    std::string Node::get_name() const
    {
        return this->name;
    }
    void Node::set_name(std::string newName)
    {
        this->name = std::move(newName);
    }

    std::vector<Node *> Node::get_subNodes() const
    {
        return this->sub_Nodes;
    }

    int Node::get_level() const
    {
        return this->level;
    }
    void Node::set_level(int level)
    {
        this->level = level;
    }
}
