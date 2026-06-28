#ifndef LAYOUTCONSTANT_H
#define LAYOUTCONSTANT_H
#include<QColor>
class LayoutConstant
{
public:
    // ===================== Layout =====================
    static constexpr int CardWidth = 220;
    static constexpr int CardHeight = 110;

    static constexpr int RowSpacing = 160;
    static constexpr int ColumnSpacing = 260;

    static constexpr int LeftMargin = 40;
    static constexpr int TopMargin = 40;

    static constexpr int TextLeft = 18;

    // ===================== Colors - Card =====================
    static QColor CardBg;
    static QColor CardBgHover;

    static QColor CardBorder;
    static QColor CardBorderHover;

    static QColor CardText;
    static QColor CardTextHover;

    // ===================== Priority Colors =====================
    static QColor PriorityHigh;
    static QColor PriorityMedium;
    static QColor PriorityLow;

    // ===================== Status Colors =====================
    static QColor StatusPending;
    static QColor StatusInProgress;
    static QColor StatusDone;

    // ===================== Icons =====================
    static QString IconEdit;
    static QString IconDelete;
    static QString IconAdd;

    // ===================== Helpers =====================
    static QColor priorityColor(const QString& p);
    static QColor statusColor(const QString& s);
};
#endif // LAYOUTCONSTANT_H
