#include"tasklayoutengine.h"
#include"../task/task.h"
#include "../widget/taskcard.h"
#include "../layoutconstant.h"
TaskLayoutEngine::TaskLayoutEngine()
{
}

QHash<Task*, QRect> TaskLayoutEngine::calculate(Task* root)
{
    QHash<Task*, QRect> layout;

    if(root == nullptr)
        return layout;

    layoutChildren(root, layout);

    return layout;
}

void TaskLayoutEngine::layoutChildren(Task* root, QHash<Task*, QRect>& layout)
{
    int y = LayoutConstant::TopMargin;
    for(Task* child:root->children)
    {
        QRect c_rect = QRect(LayoutConstant::LeftMargin,y,LayoutConstant::CardWidth,LayoutConstant::CardHeight);
        layout.insert(child,c_rect);
        int x = LayoutConstant::LeftMargin + LayoutConstant::ColumnSpacing;
        for(Task* g_child:child->children)
        {
            QRect gc_rect = QRect(x, y, LayoutConstant::CardWidth,LayoutConstant::CardHeight);
            layout.insert(g_child, gc_rect);
            x += LayoutConstant::ColumnSpacing;
        }
         y += LayoutConstant::RowSpacing;
    }

}