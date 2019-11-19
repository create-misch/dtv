#pragma once

#include "itree_display_presenter.h"

namespace ui
{

namespace tree
{

class TreeNode;
class ITreeDisplayView;

class TreeDisplayPresenter final : public ITreeDisplayPresenter
{
public:
    explicit TreeDisplayPresenter(TreeNode* treeNode);
    ~TreeDisplayPresenter();

    void SetTreeDisplayView(ITreeDisplayView* view) final;

    void AddChildToNode(const Key& nodeKey, const CellName& cellName) final;
    void SetNodeName(const Key& nodeKey, const CellName& cellName) final;
    void DeleteNode(const Key& nodeKey) final;
    void SelectNode(const Key& nodeKey) final;

    void SetActiveNodeDispaly(const Key& nodeKey) final;

private:
    ITreeDisplayView* m_view = nullptr;
    TreeNode* m_treeNode = nullptr;
};

} // namespace tree
} // namespace ui
