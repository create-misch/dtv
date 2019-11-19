#include "tree_node.h"

namespace ui
{
namespace tree
{

TreeNode::TreeNode() = default;

TreeNode::TreeNode(const Key& key, const CellName& cellName, TreeNode* parent)
    : m_key(key)
    , m_cellName(cellName)
    , m_parent(parent)
{
}

TreeNode::~TreeNode()
{
    for (auto child : m_childs)
    {
        delete child;
    }
}

void TreeNode::SetKey(const Key& key)
{
    m_key = key;
}

Key TreeNode::GetKey() const
{
    return m_key;
}

void TreeNode::SetCellName(const CellName& cellName)
{
    m_cellName = cellName;
}

CellName TreeNode::GetCellName() const
{
    return m_cellName;
}

void TreeNode::SetParent(TreeNode* node)
{
    m_parent = node;
}

TreeNode* TreeNode::Parent() const
{
    return m_parent;
}

void TreeNode::AddChild(TreeNode* node)
{
    m_childs.push_back(node);
}

void TreeNode::DeleteChild(TreeNode* node)
{
    m_childs.remove_if([node](TreeNode* n) { return node == n; });
}

void TreeNode::DeleteChild(const Key& key)
{
    m_childs.remove_if([key](TreeNode* n) { return n->GetKey() == key; });
}

TreeNodes TreeNode::GetChilds() const
{
    return m_childs;
}

TreeNodes& TreeNode::GetChilds()
{
    return m_childs;
}

} // namespace tree

} // namespace ui
