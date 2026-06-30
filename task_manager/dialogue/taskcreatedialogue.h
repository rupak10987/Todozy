#ifndef TASKCREATEDIALOGUE_H
#define TASKCREATEDIALOGUE_H
#include <QDialog>

class QLineEdit;
class QComboBox;

class TaskCreateDialog : public QDialog
{
    Q_OBJECT

public:

    explicit TaskCreateDialog(QWidget* parent=nullptr);

    QString taskName() const;

    QString priority() const;

    QString status() const;

    QString duration() const;

private:

    QLineEdit* m_name;

    QComboBox* m_priority;

    QComboBox* m_status;

    QLineEdit* m_duration;
};
#endif // TASKCREATEDIALOGUE_H
