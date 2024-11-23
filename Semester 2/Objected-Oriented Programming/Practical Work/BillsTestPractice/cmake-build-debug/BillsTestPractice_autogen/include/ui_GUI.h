/********************************************************************************
** Form generated from reading UI file 'gui.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_H
#define UI_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GUI
{
public:
    QVBoxLayout *verticalLayout;
    QListWidget *billsListWidget;
    QHBoxLayout *horizontalLayout;
    QCheckBox *paidCheckbox;
    QCheckBox *unpaidCheckbox;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QPushButton *calculateButton;
    QLineEdit *unpaidBillsLineEdit;
    QLineEdit *userCompanyNameLineEdit;
    QLabel *label;

    void setupUi(QWidget *GUI)
    {
        if (GUI->objectName().isEmpty())
            GUI->setObjectName("GUI");
        GUI->resize(568, 588);
        verticalLayout = new QVBoxLayout(GUI);
        verticalLayout->setObjectName("verticalLayout");
        billsListWidget = new QListWidget(GUI);
        billsListWidget->setObjectName("billsListWidget");

        verticalLayout->addWidget(billsListWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        paidCheckbox = new QCheckBox(GUI);
        paidCheckbox->setObjectName("paidCheckbox");

        horizontalLayout->addWidget(paidCheckbox);

        unpaidCheckbox = new QCheckBox(GUI);
        unpaidCheckbox->setObjectName("unpaidCheckbox");

        horizontalLayout->addWidget(unpaidCheckbox);


        verticalLayout->addLayout(horizontalLayout);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        label_2 = new QLabel(GUI);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 2, 0, 1, 2);

        calculateButton = new QPushButton(GUI);
        calculateButton->setObjectName("calculateButton");

        gridLayout->addWidget(calculateButton, 1, 0, 1, 3);

        unpaidBillsLineEdit = new QLineEdit(GUI);
        unpaidBillsLineEdit->setObjectName("unpaidBillsLineEdit");

        gridLayout->addWidget(unpaidBillsLineEdit, 2, 2, 1, 1);

        userCompanyNameLineEdit = new QLineEdit(GUI);
        userCompanyNameLineEdit->setObjectName("userCompanyNameLineEdit");

        gridLayout->addWidget(userCompanyNameLineEdit, 0, 2, 1, 1);

        label = new QLabel(GUI);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 2);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(GUI);
        QObject::connect(paidCheckbox, SIGNAL(clicked()), GUI, SLOT(showPaid()));
        QObject::connect(unpaidCheckbox, SIGNAL(clicked()), GUI, SLOT(showUnpaied()));

        QMetaObject::connectSlotsByName(GUI);
    } // setupUi

    void retranslateUi(QWidget *GUI)
    {
        GUI->setWindowTitle(QCoreApplication::translate("GUI", "GUI", nullptr));
        paidCheckbox->setText(QCoreApplication::translate("GUI", "Paid", nullptr));
        unpaidCheckbox->setText(QCoreApplication::translate("GUI", "Unpaid", nullptr));
        label_2->setText(QCoreApplication::translate("GUI", "The total of unpaid bills:", nullptr));
        calculateButton->setText(QCoreApplication::translate("GUI", "Calculate total", nullptr));
        label->setText(QCoreApplication::translate("GUI", "Company name:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GUI: public Ui_GUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
