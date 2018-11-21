#pragma once

#include <model/nodeinterface.h>

namespace libsmp {

struct Object;

class PrefixNode final : public NodeInterface,
        public std::enable_shared_from_this<PrefixNode> {
public:
    PrefixNode();
    PrefixNode(char key) :
        key_(key) {}
    ~PrefixNode();

    char key() const override final;
    std::string fullKey() const override final;

    void setParent(sp<NodeInterface> node) override final;
    sp<NodeInterface> parent() const override final;

    void addChild(sp<NodeInterface> node) override final;
    ChildNodes childs() const override final;

    bool serialize(QByteArray &data) const override final;
    bool desirialize(const QByteArray &data) override final;

    void setName(const QString &name);
    QString getName() const;

    void setDescription(const QString &description);
    QString getDescription() const;

    Object toObject() const;

private:
    char key_ = 0x00;
    QString name_;
    QString description_;
    sp<NodeInterface> parent_ = nullptr;
    ChildNodes childNodes_;
};

}
