#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <unistd.h>
#include <stack>
#include <map>
#include <queue>
#include "OrgChart.hpp"

using namespace std;
namespace ariel
{
    OrgChart::OrgChart()
    {
        this->root = nullptr;
        this->employes = 0;
    }

    ariel::Node *OrgChart::get_root()
    {
        return this->root;
    }
    int OrgChart::get_employes() const
    {
        return this->employes;
    }

    OrgChart OrgChart::add_root(const std::string &name)
    {
        if (this->root == nullptr)
        {
            this->root = new Node(name, 0);
        }
        else
        {
            this->root->set_name(name);
        }
        this->employes++;
        return *this;
    }

    OrgChart OrgChart::add_sub(const std::string &super, const std::string &sub)
    {
        if (this->root == nullptr)
        {
            throw std::invalid_argument("this organization has no root");
        }
        if (super.empty() || sub.empty())
        {
            throw std::invalid_argument("theres no name to enter the organization");
        }

        int x = this->employes;
        addSubordinate(this->root, super, sub);
        if (x == this->employes)
        {
            throw std::invalid_argument("no super was found");
        }
        return *this;
    }

    void OrgChart::addSubordinate(Node *root, const std::string &super, const std::string &sub)
    {
        if (root->get_name() == super)
        {
            ariel::Node *new_node = nullptr;
            new_node = new ariel::Node(sub, root->get_level() + 1);
            root->sub_Nodes.push_back(new_node);
            this->employes++;
        }
        else
        {
            for (uint i = 0; i < root->sub_Nodes.size(); i++)
            {
                addSubordinate(root->sub_Nodes[i], super, sub);
            }
        }
    }

    OrgChart::Iterator ariel::OrgChart::begin_level_order()
    {
        if (this->root == nullptr)
        {
            throw std::invalid_argument("There is no root");
        }
        return OrgChart::Iterator{direction::levelOrder, this->root};
    }
    OrgChart::Iterator ariel::OrgChart::end_level_order()
    {
        if (this->root == nullptr)
        {
            throw std::invalid_argument("There is no root");
        }
        return OrgChart::Iterator{direction::levelOrder, nullptr};
    }
    OrgChart::Iterator ariel::OrgChart::begin_reverse_order()
    {
        if (this->root == nullptr)
        {
            throw std::invalid_argument("There is no root");
        }
        return OrgChart::Iterator{direction::reverseOrder, this->root};
    }
    OrgChart::Iterator ariel::OrgChart::reverse_order()
    {
        if (this->root == nullptr)
        {
            throw std::invalid_argument("There is no root");
        }
        return OrgChart::Iterator{direction::reverseOrder, nullptr};
    }
    OrgChart::Iterator ariel::OrgChart::begin_preorder()
    {
        if (this->root == nullptr)
        {
            throw std::invalid_argument("There is no root");
        }
        return OrgChart::Iterator{direction::preOrder, this->root};
    }
    OrgChart::Iterator ariel::OrgChart::end_preorder()
    {
        if (this->root == nullptr)
        {
            throw std::invalid_argument("There is no root");
        }
        return OrgChart::Iterator{direction::preOrder, nullptr};
    }
    // iterator end_reverse_order() {return OrgChart::Iterator{reverseLevelOrder, nullptr, &this->levelMap};} //maybe will change

    // for the for each loops
    OrgChart::Iterator ariel::OrgChart::begin()
    {
        if (this->root == nullptr)
        {
            throw std::invalid_argument("There is no root");
        }
        return OrgChart::Iterator{direction::levelOrder, this->root};
    }
    OrgChart::Iterator ariel::OrgChart::end()
    {
        if (this->root == nullptr)
        {
            throw std::invalid_argument("There is no root");
        }
        return OrgChart::Iterator{direction::levelOrder, nullptr};
    }

    std::ostream &operator<<(std::ostream &output, const OrgChart &chart)
    {
        // std::vector<Node*> temp_childs = chart._org_chart->get_children();
        // chart.printChart(output);
        return output;
    }

    /*--------------------------------------Iterator class implementation--------------------------------------*/

    ariel::OrgChart::Iterator::Iterator(ariel::direction type, Node *node)
    {
        if (node != nullptr)
        {
            switch (type)
            {
            case direction::levelOrder:
                levelOrder(node);
                break;
            case direction::reverseOrder:
                reverseLevelOrder(node);
                break;
            case direction::preOrder:
                preOrder(node);
                break;
            }
            this->cur = this->nodes.front();
            this->nodes.pop_front();
        }
        else
        {
            this->cur = nullptr;
        }
    }

    void OrgChart::Iterator::levelOrder(Node *node)
    {
        std::queue<ariel::Node *> queue;

        queue.push(node);
        while (!queue.empty())
        {
            this->cur = queue.front();
            queue.pop();
            nodes.push_back(this->cur);
            for (ariel::Node *n : this->cur->sub_Nodes)
            {
                queue.push(n);
            }
        }
    }

    void OrgChart::Iterator::reverseLevelOrder(Node *node)
    {
        std::map<int, std::vector<ariel::Node *>> levels;
        std::queue<Node *> queue;
        queue.push(node);
        while (!queue.empty())
        {
            this->cur = queue.front();
            queue.pop();
            levels[this->cur->get_level()].push_back(this->cur);
            for (ariel::Node *n : this->cur->sub_Nodes)
            {
                queue.push(n);
            }
        }

        for (size_t key = levels.size(); key > 0; key--)
        {
            for (ariel::Node *n : levels[key - 1])
            {
                this->nodes.push_back(n);
            }
        }
    }

    void OrgChart::Iterator::preOrder(Node *node)
    {
        std::stack<Node *> stack;
        stack.push(node);
        while (!stack.empty())
        {
            this->cur = stack.top();
            stack.pop();
            this->nodes.push_back(this->cur);

            for (uint i = this->cur->sub_Nodes.size(); i > 0; i--)
            {
                stack.push(this->cur->sub_Nodes[i - 1]);
            }
        }
    }

    std::string &OrgChart::Iterator::operator*() const
    {
        return this->cur->name;
    }
    std::string *OrgChart::Iterator::operator->() const
    {
        return &(this->cur->name);
    }

    ariel::OrgChart::Iterator &ariel::OrgChart::Iterator::operator++()
    {
        if (!this->nodes.empty())
        {
            this->cur = this->nodes.front();
            this->nodes.pop_front();
        }
        else
        {
            this->cur = nullptr;
        }
        return *this;
    }

    // void ariel::OrgChart::printChart(std::ostream &output)
    // {
    //     std::cout << "hey" << std::endl;
    // }
    ariel::OrgChart::Iterator ariel::OrgChart::Iterator::operator++(int)
    {
        OrgChart::Iterator iter = *this;
        return iter;
    }
    bool ariel::OrgChart::Iterator::operator==(const OrgChart::Iterator &other) const
    {
        return this->cur == other.cur;
    }
    bool ariel::OrgChart::Iterator::operator!=(const OrgChart::Iterator &other) const
    {
        return this->cur != other.cur;
    }
}
