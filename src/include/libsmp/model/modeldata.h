#pragma once

#include <list>
#include <QString>

namespace libsmp {

struct Node {
    std::string key;
    QString name;
};

using Nodes = std::list<Node>;

struct Object {
    Node current_node;
    Nodes child_nodes_;
};

}
