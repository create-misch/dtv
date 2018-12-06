#include <QStringList>

#include "treeitem.h"

using namespace libsmp;

TreeItem::TreeItem(const PrefixNode &node, NodeInterface *parent) :
    PrefixNode() {
    setParent(parent);

    setKey(node.key());
    setName(node.getName());
    setDescription(node.getDescription());

    for (auto child : node.childs()) {
        auto prefixNode = dynamic_cast<PrefixNode *>(child);
        addChild(new TreeItem(*prefixNode, this));
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
    return getName();
}

int TreeItem::row() const {
    if (parent()) {
        auto childs = parent()->childs();
        for (int i = 0; i < childs.size(); i++) {
            if (fullKey() == childs.at(i)->fullKey()) {
                return i;
            }
        }
    }

    return 0;
}
