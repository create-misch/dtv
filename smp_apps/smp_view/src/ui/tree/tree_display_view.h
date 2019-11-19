#pragma once

#include <map>
#include <QTreeWidget>

#include "itree_display_view.h"

namespace ui
{
namespace tree
{

class ITreeDisplayPresenter;

class TreeDisplayView final : public ITreeDisplayView, public QTreeWidget
{
public:
    TreeDisplayView(std::shared_ptr<ITreeDisplayPresenter> presenter);

    void AddNodeDisplay(const Key& parentNodeKey, const Key& nodeKey, const CellName& cellName) final;
    void DeleteNodeDisplay(const Key& nodeKey) final;
    void SetNameForNodeDisplay(const Key& nodeKey, const CellName& cellName) final;
    void SetActiveNodeDisplay(const Key& nodeKey) final;

private:
    std::shared_ptr<ITreeDisplayPresenter> m_presenter;

    Key m_rootKey;
    using CacheKeyItem = std::map<Key, QTreeWidgetItem*>;
    CacheKeyItem m_cacheKeyItem;
};

} // namespace tree
} // namespace ui
