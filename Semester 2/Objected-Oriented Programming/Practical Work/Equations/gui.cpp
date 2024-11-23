//
// Created by Riki on 5/28/2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_GUI.h" resolved

#include "gui.h"
#include "ui_GUI.h"


GUI::GUI(Service* service, QWidget *parent) :
        QWidget(parent), ui(new Ui::GUI), service{ service } {
    ui->setupUi(this);
    this->populateList();
}

GUI::~GUI() {
    delete ui;
}

void GUI::populateList() {
    std::vector<Equations>* v = this->service->getEquations();
    for (Equations& eq : *v) {
        if (eq.delta() >= 0) {
            auto* item = new QListWidgetItem(QString::fromStdString(std::to_string(eq.getA()) + "*x^2 + " + std::to_string(eq.getB()) + "*x + " + std::to_string(eq.getC())));
            QFont font = item->font();
            font.setBold(true);
            item->setFont(font);
            ui->equationsListWidget->addItem(item);
        }
        else {
            ui->equationsListWidget->addItem(QString::fromStdString(std::to_string(eq.getA()) + "*x^2 + " + std::to_string(eq.getB()) + "*x + " + std::to_string(eq.getC())));
        }
    }
}

void GUI::connectSignalsAndSlots() {
    connect(ui->updateCoeffButton, &QPushButton::clicked, this, [this]() {
        int index = ui->equationsListWidget->currentRow();
        Equations eq = this->service->getEquations()->at(index);
       std::string a = this->ui->aCoeffLineEdit->text().toStdString();
       std::string b = this->ui->bCoeffLineEdit->text().toStdString();
       std::string c = this->ui->cCoeffLineEdit->text().toStdString();
       QListWidgetItem* selectedEquation = this->ui->equationsListWidget->currentItem();
    });
}
