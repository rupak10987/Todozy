#include"./taskcreatedialogue.h"
#include <qboxlayout.h>
#include <qlabel.h>
#include <QComboBox>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QFile>
TaskCreateDialog::TaskCreateDialog(QWidget* parent)
    :QDialog(parent)
{
    setWindowTitle("New Task");

    resize(250,350);


    auto* layout = new QVBoxLayout(this);

    layout->addWidget(new QLabel("Task Name"));

    m_name = new QLineEdit;

    layout->addWidget(m_name);

    layout->addWidget(new QLabel("Priority"));

    m_priority = new QComboBox;

    m_priority->addItems(
        {
            "None",
            "Low",
            "Medium",
            "High"
        });

    layout->addWidget(m_priority);

    layout->addWidget(new QLabel("Status"));

    m_status = new QComboBox;

    m_status->addItems(
        {
            "Pending",
            "In Progress",
            "Done"
        });

    layout->addWidget(m_status);

    layout->addWidget(new QLabel("Duration"));

    m_duration = new QLineEdit;

    layout->addWidget(m_duration);

    auto* buttons =
        new QDialogButtonBox(
            QDialogButtonBox::Ok|
            QDialogButtonBox::Cancel);

    connect(buttons,
            &QDialogButtonBox::accepted,
            this,
            &QDialog::accept);

    connect(buttons,
            &QDialogButtonBox::rejected,
            this,
            &QDialog::reject);

    layout->addWidget(buttons);
}
QString TaskCreateDialog::taskName() const
{
    return m_name->text();
}

QString TaskCreateDialog::priority() const
{
    return m_priority->currentText();
}

QString TaskCreateDialog::status() const
{
    return m_status->currentText();
}

QString TaskCreateDialog::duration() const
{
    return m_duration->text();
}