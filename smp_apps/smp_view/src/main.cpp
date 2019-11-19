#include <QApplication>

#include <ui/mainwindow.h>

#include <ui/tree/tree_node.h>
#include <ui/tree/tree_display_presenter.h>
#include <ui/tree/tree_display_view.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    using namespace ui::tree;
    TreeNode* treeNode = new TreeNode{0, "Root item", nullptr};
    auto presenter = std::shared_ptr<TreeDisplayPresenter>(new TreeDisplayPresenter{treeNode});

    TreeDisplayView view{presenter};

    presenter->AddChildToNode(0, "lol");
    presenter->AddChildToNode(1, "lol1");
    presenter->AddChildToNode(2, "lol2");
    presenter->AddChildToNode(3, "lol3");

    view.show();

//    auto window = std::make_shared<MainWindow>();
//    window->show();

    return a.exec();
}
