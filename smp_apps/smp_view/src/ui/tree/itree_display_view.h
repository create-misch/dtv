#pragma once

#include <common/global.h>

namespace ui
{
namespace tree
{

class TreeNode;

class ITreeDisplayView
{
public:
    virtual ~ITreeDisplayView() = default;

    virtual void AddNodeDisplay(const Key& parentNodeKey, const Key& nodeKey, const CellName& cellName) = 0;
    virtual void DeleteNodeDisplay(const Key& nodeKey) = 0;
    virtual void SetNameForNodeDisplay(const Key& nodeKey, const CellName& cellName) = 0;
    virtual void SetActiveNodeDisplay(const Key& nodeKey) = 0;
};

} // namespace tree
} // namespace ui
