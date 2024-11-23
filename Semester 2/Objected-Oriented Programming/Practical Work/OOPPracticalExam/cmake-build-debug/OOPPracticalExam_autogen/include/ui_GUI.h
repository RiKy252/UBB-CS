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
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QListWidget *patientsListWidget;
    QCheckBox *yourPatientsCheckBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *nameLineEdit;
    QLabel *label_3;
    QLineEdit *diagnosisLineEdit;
    QLabel *label_4;
    QLineEdit *specialisationNeededLineEdit;
    QLabel *label_2;
    QLineEdit *currentDoctorLineEdit;
    QLabel *label_5;
    QLineEdit *admissionDateLineEdit;
    QPushButton *addPatientButton;
    QPushButton *updateDiagnosisButton;

    void setupUi(QWidget *GUI)
    {
        if (GUI->objectName().isEmpty())
            GUI->setObjectName("GUI");
        GUI->resize(504, 578);
        verticalLayout_2 = new QVBoxLayout(GUI);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        patientsListWidget = new QListWidget(GUI);
        patientsListWidget->setObjectName("patientsListWidget");

        verticalLayout->addWidget(patientsListWidget);

        yourPatientsCheckBox = new QCheckBox(GUI);
        yourPatientsCheckBox->setObjectName("yourPatientsCheckBox");

        verticalLayout->addWidget(yourPatientsCheckBox);


        verticalLayout_2->addLayout(verticalLayout);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(GUI);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        nameLineEdit = new QLineEdit(GUI);
        nameLineEdit->setObjectName("nameLineEdit");

        gridLayout->addWidget(nameLineEdit, 0, 1, 1, 1);

        label_3 = new QLabel(GUI);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        diagnosisLineEdit = new QLineEdit(GUI);
        diagnosisLineEdit->setObjectName("diagnosisLineEdit");

        gridLayout->addWidget(diagnosisLineEdit, 1, 1, 1, 1);

        label_4 = new QLabel(GUI);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        specialisationNeededLineEdit = new QLineEdit(GUI);
        specialisationNeededLineEdit->setObjectName("specialisationNeededLineEdit");

        gridLayout->addWidget(specialisationNeededLineEdit, 2, 1, 1, 1);

        label_2 = new QLabel(GUI);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        currentDoctorLineEdit = new QLineEdit(GUI);
        currentDoctorLineEdit->setObjectName("currentDoctorLineEdit");

        gridLayout->addWidget(currentDoctorLineEdit, 3, 1, 1, 1);

        label_5 = new QLabel(GUI);
        label_5->setObjectName("label_5");

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        admissionDateLineEdit = new QLineEdit(GUI);
        admissionDateLineEdit->setObjectName("admissionDateLineEdit");

        gridLayout->addWidget(admissionDateLineEdit, 4, 1, 1, 1);

        addPatientButton = new QPushButton(GUI);
        addPatientButton->setObjectName("addPatientButton");

        gridLayout->addWidget(addPatientButton, 5, 0, 1, 2);

        updateDiagnosisButton = new QPushButton(GUI);
        updateDiagnosisButton->setObjectName("updateDiagnosisButton");

        gridLayout->addWidget(updateDiagnosisButton, 6, 0, 1, 2);


        verticalLayout_2->addLayout(gridLayout);


        retranslateUi(GUI);

        QMetaObject::connectSlotsByName(GUI);
    } // setupUi

    void retranslateUi(QWidget *GUI)
    {
        GUI->setWindowTitle(QCoreApplication::translate("GUI", "GUI", nullptr));
        yourPatientsCheckBox->setText(QCoreApplication::translate("GUI", "See your patients", nullptr));
        label->setText(QCoreApplication::translate("GUI", "Name", nullptr));
        label_3->setText(QCoreApplication::translate("GUI", "Diagnosis", nullptr));
        label_4->setText(QCoreApplication::translate("GUI", "Specialisation needed", nullptr));
        label_2->setText(QCoreApplication::translate("GUI", "Current doctor", nullptr));
        label_5->setText(QCoreApplication::translate("GUI", "Admission date", nullptr));
        addPatientButton->setText(QCoreApplication::translate("GUI", "Add patient", nullptr));
        updateDiagnosisButton->setText(QCoreApplication::translate("GUI", "Update diagnosis / specialisation", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GUI: public Ui_GUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
