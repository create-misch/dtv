#pragma once

#include <QObject>

#include <common/global.h>

namespace ui
{
namespace tree
{

class ITreeDisplayView;

class ITreeDisplayPresenter : public QObject
{
    Q_OBJECT
public:
    virtual ~ITreeDisplayPresenter() = default;

    virtual void SetTreeDisplayView(ITreeDisplayView* view) = 0;

    virtual void AddChildToNode(const Key& nodeKey, const CellName& cellName) = 0;
    virtual void SetNodeName(const Key& nodeKey, const CellName& cellName) = 0;
    virtual void DeleteNode(const Key& nodeKey) = 0;
    virtual void SelectNode(const Key& nodeKey) = 0;

    virtual void SetActiveNodeDispaly(const Key& nodeKey) = 0;

signals:
    void NodeSelected(const Key& key);
};

} // namespace tree
} // namespace ui
