//
// Created by Riki on 5/24/2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_GUI.h" resolved

#include "gui.h"
#include "ui_GUI.h"


GUI::GUI(Service& service, QWidget *parent) :
        QWidget(parent), ui(new Ui::GUI), service(service) {
    ui->setupUi(this);
    this->populateList();
    this->connectSignalsAndSlots();
}

GUI::~GUI() {
    delete ui;
}

void GUI::populateList() {
    ui->billsListWidget->clear();
    for (const auto& bill : *service.getBills()) {
        QString item = QString::fromStdString(bill.getCompanyName() + ", " + std::to_string(bill.getSum()));
        QListWidgetItem* listItem = new QListWidgetItem(item);
        if (!bill.isItPaid()) {
            listItem->setForeground(Qt::red);
        }
        else
            listItem->setForeground(Qt::green);
        ui->billsListWidget->addItem(listItem);
    }
}

void GUI::showPaidList() {
    ui->billsListWidget->clear();
    for (const auto& bill : *this->service.getBills()) {
        if (bill.isItPaid()) {
            QString item = QString::fromStdString(bill.getCompanyName() + ", " + std::to_string(bill.getSum()));
            QListWidgetItem* listItem = new QListWidgetItem(item);
            if (!bill.isItPaid()) {
                listItem->setForeground(Qt::red);
            }
            else
                listItem->setForeground(Qt::green);
            ui->billsListWidget->addItem(listItem);
        }
    }
}

void GUI::showUnpaidList() {
    ui->billsListWidget->clear();
    for (const auto& bill : *this->service.getBills()) {
        if (!bill.isItPaid()) {
            QString item = QString::fromStdString(bill.getCompanyName() + ", " + std::to_string(bill.getSum()));
            QListWidgetItem* listItem = new QListWidgetItem(item);
            if (!bill.isItPaid()) {
                listItem->setForeground(Qt::red);
            }
            else
                listItem->setForeground(Qt::green);
            ui->billsListWidget->addItem(listItem);
        }
    }
}

void GUI::connectSignalsAndSlots() {
    QObject::connect(ui->paidCheckbox, &QCheckBox::stateChanged, this, [this](bool state) {
        if (state) {
            this->showPaidList();
            ui->unpaidCheckbox->setChecked(false);
        }
        else if (!ui->paidCheckbox->isChecked() && !ui->unpaidCheckbox->isChecked()){
            this->populateList();
        }
    });
    QObject::connect(ui->unpaidCheckbox, &QCheckBox::stateChanged, this, [this](bool state) {
        if (state) {
            this->showUnpaidList();
            ui->paidCheckbox->setChecked(false);
        }
        else if (!ui->paidCheckbox->isChecked() && !ui->unpaidCheckbox->isChecked()){
            this->populateList();
        }
    });
    QObject::connect(ui->calculateButton, &QPushButton::clicked, this, [this] {
        QString companyName = ui->userCompanyNameLineEdit->text();
        std::string companyNameString = companyName.toStdString();
        float result = this->service.calculateUnpaidBills(companyNameString);
        if (result == 0) {
            QMessageBox::warning(this, "Unpaid bills", "No unpaid bills for this company");
        }
        else {
            QString resultString = QString::number(result);
            this->ui->unpaidBillsLineEdit->setText(resultString);
        }
    });
}
