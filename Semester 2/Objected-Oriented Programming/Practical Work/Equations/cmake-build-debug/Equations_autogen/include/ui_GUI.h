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
#include <QtWidgets/QGridLayout>
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
    QListWidget *equationsListWidget;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLabel *label;
    QLineEdit *aCoeffLineEdit;
    QLabel *label_3;
    QLineEdit *bCoeffLineEdit;
    QLabel *label_4;
    QLineEdit *cCoeffLineEdit;
    QPushButton *updateCoeffButton;
    QPushButton *computeSolutionsButton;
    QLabel *solutionsLabel;

    void setupUi(QWidget *GUI)
    {
        if (GUI->objectName().isEmpty())
            GUI->setObjectName("GUI");
        GUI->resize(606, 482);
        verticalLayout = new QVBoxLayout(GUI);
        verticalLayout->setObjectName("verticalLayout");
        equationsListWidget = new QListWidget(GUI);
        equationsListWidget->setObjectName("equationsListWidget");

        verticalLayout->addWidget(equationsListWidget);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        label_2 = new QLabel(GUI);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 0, 2, 1, 4);

        label = new QLabel(GUI);
        label->setObjectName("label");

        gridLayout->addWidget(label, 1, 0, 1, 1);

        aCoeffLineEdit = new QLineEdit(GUI);
        aCoeffLineEdit->setObjectName("aCoeffLineEdit");

        gridLayout->addWidget(aCoeffLineEdit, 1, 1, 1, 1);

        label_3 = new QLabel(GUI);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 1, 2, 1, 1);

        bCoeffLineEdit = new QLineEdit(GUI);
        bCoeffLineEdit->setObjectName("bCoeffLineEdit");

        gridLayout->addWidget(bCoeffLineEdit, 1, 3, 1, 1);

        label_4 = new QLabel(GUI);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 1, 4, 1, 1);

        cCoeffLineEdit = new QLineEdit(GUI);
        cCoeffLineEdit->setObjectName("cCoeffLineEdit");

        gridLayout->addWidget(cCoeffLineEdit, 1, 5, 1, 1);

        updateCoeffButton = new QPushButton(GUI);
        updateCoeffButton->setObjectName("updateCoeffButton");

        gridLayout->addWidget(updateCoeffButton, 1, 6, 1, 1);

        computeSolutionsButton = new QPushButton(GUI);
        computeSolutionsButton->setObjectName("computeSolutionsButton");

        gridLayout->addWidget(computeSolutionsButton, 2, 1, 1, 6);


        verticalLayout->addLayout(gridLayout);

        solutionsLabel = new QLabel(GUI);
        solutionsLabel->setObjectName("solutionsLabel");

        verticalLayout->addWidget(solutionsLabel);


        retranslateUi(GUI);

        QMetaObject::connectSlotsByName(GUI);
    } // setupUi

    void retranslateUi(QWidget *GUI)
    {
        GUI->setWindowTitle(QCoreApplication::translate("GUI", "GUI", nullptr));
        label_2->setText(QCoreApplication::translate("GUI", "Coefficients update", nullptr));
        label->setText(QCoreApplication::translate("GUI", "a", nullptr));
        label_3->setText(QCoreApplication::translate("GUI", "b", nullptr));
        label_4->setText(QCoreApplication::translate("GUI", "c", nullptr));
        updateCoeffButton->setText(QCoreApplication::translate("GUI", "Update", nullptr));
        computeSolutionsButton->setText(QCoreApplication::translate("GUI", "Compute solutions", nullptr));
        solutionsLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class GUI: public Ui_GUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
