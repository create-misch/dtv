#include <log4app/log4app.h>

#include "itree_display_view.h"
#include "tree_display_presenter.h"
#include "tree_node.h"

namespace ui
{

namespace tree
{

TreeDisplayPresenter::TreeDisplayPresenter(TreeNode* treeNode)
    : m_treeNode(treeNode)
{
    Q_ASSERT(m_treeNode);
}

TreeDisplayPresenter::~TreeDisplayPresenter()
{
    delete m_treeNode;
}

void TreeDisplayPresenter::SetTreeDisplayView(ITreeDisplayView* view)
{
    Q_ASSERT(view);
    m_view = view;
}

void TreeDisplayPresenter::AddChildToNode(const Key& nodeKey, const CellName& cellName)
{
    auto parentNode = FindNodeWithKey(m_treeNode, nodeKey);
    if (parentNode == nullptr)
    {
        log4app::Log()->error(QString("Node with key %1 dont found").arg(nodeKey));
        return;
    }

    auto node = new TreeNode{GetNewKey(), cellName, parentNode};
    parentNode->AddChild(node);

    m_view->AddNodeDisplay(nodeKey, node->GetKey(), node->GetCellName());
}

void TreeDisplayPresenter::SetNodeName(const Key& nodeKey, const CellName& cellName)
{
    auto node = FindNodeWithKey(m_treeNode, nodeKey);
    if (node == nullptr)
    {
        log4app::Log()->error(QString("Node with key %1 dont found").arg(nodeKey));
        return;
    }

    node->SetCellName(cellName);
    m_view->SetNameForNodeDisplay(nodeKey, cellName);
}

void TreeDisplayPresenter::DeleteNode(const Key& nodeKey)
{
    auto node = FindNodeWithKey(m_treeNode, nodeKey);
    if (node == nullptr)
    {
        log4app::Log()->error(QString("Node with key %1 dont found").arg(nodeKey));
        return;
    }

    auto parentNode = node->Parent();
    parentNode->DeleteChild(node);

    m_view->DeleteNodeDisplay(nodeKey);
}

void TreeDisplayPresenter::SelectNode(const Key& nodeKey)
{
    emit NodeSelected(nodeKey);
}

void TreeDisplayPresenter::SetActiveNodeDispaly(const Key& nodeKey)
{
    auto node = FindNodeWithKey(m_treeNode, nodeKey);
    if (node == nullptr)
    {
        log4app::Log()->error(QString("Node with key %1 dont found").arg(nodeKey));
        return;
    }

    m_view->SetActiveNodeDisplay(nodeKey);
}

} // namespace tree
} // namespace ui
