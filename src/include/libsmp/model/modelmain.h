#pragma once

#include <memory>

#include <libsmp/model/modelinterface.h>

namespace libsmp {

class PrefixTree;

class ModelMain final : public ModelInterface {
public:
    ModelMain();
    ~ModelMain();

    void addChildObject(const std::string &key) override final;
    void setNameForObject(const std::string &key, const QString &name) override final;
    void setDescriptionForObject(const std::string &key, const QString &description) override final;
    void requestObject(const std::string &key) override final;

private:
    std::unique_ptr<PrefixTree> tree_;

};

}
