#include <QStringList>

#include "treeitem.h"

using namespace libsmp;

TreeItem::TreeItem(const Node &node, NodeInterface *parent) :
    Node() {
    setParent(parent);    
    setKey(node.key());

    for (auto child : node.childs()) {
        auto node = dynamic_cast<Node *>(child);
        addChild(new TreeItem(*node, this));
    }
}

TreeItem::~TreeItem() {}

NodeInterface* TreeItem::child(int row) {
    return childs()[row];
}

int TreeItem::childCount() const {
    return childs().size();
}

int TreeItem::columnCount() const {
    return 1;
}

QVariant TreeItem::data(int column) const {
    Q_UNUSED(column)
    return name_;
}

int TreeItem::row() const {
    if (parent()) {
        auto childs = parent()->childs();
        for (int i = 0; i < childs.size(); i++) {
            if (key() == childs.at(i)->key()) {
                return i;
            }
        }
    }

    return 0;
}

void TreeItem::setName(const QString &name) {
    name_ = name;
}
