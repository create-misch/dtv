#pragma once

#include <model/nodeinterface.h>

namespace libsmp {

class PrefixNode : public NodeInterface {
public:
    PrefixNode();
    PrefixNode(char key) :
        key_(key) {}
    virtual ~PrefixNode();

    void setKey(char key) override final;
    char key() const override final;
    std::string fullKey() const override final;

    void setParent(NodeInterface *node) override final;
    NodeInterface * parent() const override final;

    void addChild(NodeInterface *node) override final;
    ChildNodes childs() const override final;

    bool serialize(QByteArray &data) const override final;
    bool desirialize(const QByteArray &data) override final;

    void setName(const QString &name);
    QString getName() const;

    void setDescription(const QString &description);
    QString getDescription() const;

private:
    char key_ = 0x00;
    QString name_ = "New Object";
    QString description_ = "Description";
    NodeInterface * parent_ = nullptr;
    ChildNodes childNodes_;
};

}
