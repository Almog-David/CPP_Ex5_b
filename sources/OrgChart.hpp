#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <unistd.h>
#include <stack>
#include <map>
#include <queue>
#include <list>
#include "Node.hpp"

namespace ariel
{
    enum class direction
    {
        levelOrder,
        preOrder,
        reverseOrder
    };

    class OrgChart
    {

    private:
        ariel::Node *root;
        int employes = 0;

    public:
        OrgChart();
        OrgChart(OrgChart &other) = default;
        OrgChart(OrgChart &&other) = default;
        OrgChart &operator=(OrgChart &&other) = default;
        OrgChart &operator=(const OrgChart &other) = default;
        ~OrgChart()
        {
            this->root = nullptr;
        }
        ariel::Node *get_root();
        int get_employes() const;
        // void printChart(std::ostream &output);

        OrgChart add_root(const std::string &name);
        OrgChart add_sub(const std::string &super, const std::string &sub);
        void addSubordinate(ariel::Node *root, const std::string &super, const std::string &sub);

        friend std::ostream &operator<<(std::ostream &output, const OrgChart &chart);

        class Iterator
        {

        public:
            ariel::Node *cur;
            std::list<ariel::Node *> nodes;

            Iterator(direction type, Node *node = nullptr);
            void levelOrder(Node *node = nullptr);
            void reverseLevelOrder(Node *node = nullptr);
            void preOrder(Node *node = nullptr);

            std::string &operator*() const;
            // {
            //     return this->cur->_title;
            // }
            std::string *operator->() const;
            // {
            //     return &this->cur->_title;
            // }
            ariel::OrgChart::Iterator &operator++();
            ariel::OrgChart::Iterator operator++(int);
            // {
            //     OrgChart::Iterator iter = *this;
            //     return iter;
            // }
            bool operator==(const OrgChart::Iterator &other) const;
            // { return this->cur == other.cur; }
            bool operator!=(const OrgChart::Iterator &other) const;
            // { return this->cur != other.cur; }
        };
        Iterator begin_level_order();
        Iterator end_level_order();
        Iterator begin_reverse_order();
        Iterator reverse_order();
        Iterator begin_preorder();
        Iterator end_preorder();
        Iterator begin();
        Iterator end();
    };
}
