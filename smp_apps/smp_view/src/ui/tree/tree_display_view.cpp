#include "itree_display_presenter.h"

#include "tree_display_view.h"

namespace ui
{
namespace tree
{

// TODO make single searce item

TreeDisplayView::TreeDisplayView(std::shared_ptr<ITreeDisplayPresenter> presenter)
    : m_presenter(std::move(presenter))
{
    m_presenter->SetTreeDisplayView(this);
}

void TreeDisplayView::AddNodeDisplay(const Key& parentNodeKey, const Key& nodeKey, const CellName& cellName)
{
    if (m_cacheKeyItem.empty())
    {
        m_rootKey = parentNodeKey;
        QTreeWidgetItem* item = new QTreeWidgetItem{this, QStringList{cellName}};
        addTopLevelItem(item);
        m_cacheKeyItem[nodeKey] = item;
        return;
    }

    auto it = m_cacheKeyItem.find(parentNodeKey);
    if (it == std::end(m_cacheKeyItem))
    {
        return;
    }

    QTreeWidgetItem* item = new QTreeWidgetItem{it->second, QStringList{cellName}};
    m_cacheKeyItem[nodeKey] = item;
}

void TreeDisplayView::DeleteNodeDisplay(const Key& nodeKey)
{
    auto it = m_cacheKeyItem.find(nodeKey);
    if (it == std::end(m_cacheKeyItem))
    {
        return;
    }

    auto item = it->second;
    auto parent = item->parent();
    parent->removeChild(item);
}

void TreeDisplayView::SetNameForNodeDisplay(const Key& nodeKey, const CellName& cellName)
{
    auto it = m_cacheKeyItem.find(nodeKey);
    if (it == std::end(m_cacheKeyItem))
    {
        return;
    }

    it->second->setText(0, cellName);
}

void TreeDisplayView::SetActiveNodeDisplay(const Key& nodeKey)
{
    auto it = m_cacheKeyItem.find(nodeKey);
    if (it == std::end(m_cacheKeyItem))
    {
        return;
    }

    setCurrentItem(it->second);
}

} // namespace tree
} // namespace ui
