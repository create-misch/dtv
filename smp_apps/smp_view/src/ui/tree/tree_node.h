#pragma once

#include <list>
#include <string>

#include <common/global.h>

namespace ui
{
namespace tree
{

constexpr Key DefaultKey = -1;
constexpr Key RootKey = 0;

static Key CurrentKey = 0;

class TreeNode;
using TreeNodes = std::list<TreeNode*>;

class TreeNode
{
public:
    TreeNode();
    TreeNode(const Key& key, const CellName& cellName, TreeNode* parent);

    virtual ~TreeNode();

    void SetKey(const Key& key);
    Key GetKey() const;

    void SetCellName(const CellName& cellName);
    CellName GetCellName() const;

    void SetParent(TreeNode* node);
    TreeNode* Parent() const;

    void AddChild(TreeNode* node);
    void DeleteChild(TreeNode* node);
    void DeleteChild(const Key& key);

    TreeNodes GetChilds() const;
    TreeNodes& GetChilds();

protected:
    Key m_key = -1;
    CellName m_cellName = "";
    TreeNode* m_parent = nullptr;
    TreeNodes m_childs;
};

inline TreeNode* FindNodeWithKey(TreeNode* root, const Key& key)
{
    TreeNode* findNode = nullptr;

    if (!root)
        return findNode;
    if (root->GetKey() == key)
        return root;
    if (root->GetChilds().size() == 0)
        return findNode;

    for (const auto& node : root->GetChilds())
    {
        if (node->GetKey() == key)
        {
            return node;
        }

        findNode = FindNodeWithKey(node, key);
        if (findNode != nullptr)
            return findNode;
    }
    return findNode;
}

static Key GetNewKey()
{
    return ++CurrentKey;
}

} // namespace tree
} // namespace ui
