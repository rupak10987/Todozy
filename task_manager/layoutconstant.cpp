#include "layoutconstant.h"
// ===================== Card Colors =====================
QColor LayoutConstant::CardBg        = QColor(44, 44, 44);
QColor LayoutConstant::CardBgHover   = QColor(69, 72, 247);

QColor LayoutConstant::CardBorder      = QColor(90, 90, 90);
QColor LayoutConstant::CardBorderHover = QColor(255, 200, 0);

QColor LayoutConstant::CardText      = QColor(255, 255, 255);
QColor LayoutConstant::CardTextHover = QColor(30, 30, 30);

// ===================== Priority =====================
QColor LayoutConstant::PriorityHigh   = QColor(229, 57, 53);
QColor LayoutConstant::PriorityMedium = QColor(251, 140, 0);
QColor LayoutConstant::PriorityLow    = QColor(67, 160, 71);

// ===================== Status =====================
QColor LayoutConstant::StatusPending    = QColor(120, 120, 120);
QColor LayoutConstant::StatusInProgress = QColor(33, 150, 243);
QColor LayoutConstant::StatusDone       = QColor(76, 175, 80);

// ===================== Add Button =====================
QColor LayoutConstant::TextColor    = QColor(120, 120, 120);
QColor LayoutConstant::AccentColor = QColor(69, 72, 247);
QColor LayoutConstant::SurfaceColor       = QColor(44, 44, 44);

// ===================== Icons =====================
QString LayoutConstant::IconEdit   = ":/icons/edit.svg";
QString LayoutConstant::IconDelete = ":/icons/delete.svg";
QString LayoutConstant::IconAdd    = ":/icons/add.svg";

// ===================== Helpers =====================
QColor LayoutConstant::priorityColor(const QString& p)
{
    if (p == "High") return PriorityHigh;
    if (p == "Medium") return PriorityMedium;
    return PriorityLow;
}

QColor LayoutConstant::statusColor(const QString& s)
{
    if (s == "Done") return StatusDone;
    if (s == "In Progress") return StatusInProgress;
    return StatusPending;
}