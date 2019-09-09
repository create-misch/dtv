#pragma once

#include <model/nodeinterface.h>

namespace libsmp {

class Node : public NodeInterface {
public:    
    Node() = default;
    Node(const Key &key, NodeInterface *parent = nullptr);    
    virtual ~Node();

    void setKey(const Key &key) override final;
    Key key() const override final;

    void setParent(NodeInterface *node) override final;
    NodeInterface *parent() const override final;

    void addChild(NodeInterface *node) override final;
    bool deleteChild(NodeInterface *node) override final;
    ChildNodes childs() const override final;
    ChildNodes &childs() override final;

    bool serialize(QByteArray &data) const override final;
    bool desirialize(const QByteArray &data) override final;

    int size() const;

private:
    Key key_ = -1;
    NodeInterface *parent_ = nullptr;
    ChildNodes childs_;
};

}
