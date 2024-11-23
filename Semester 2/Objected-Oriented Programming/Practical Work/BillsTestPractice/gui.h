//
// Created by Riki on 5/24/2024.
//

#ifndef BILLSTESTPRACTICE_GUI_H
#define BILLSTESTPRACTICE_GUI_H

#include <QWidget>
#include <QMessageBox>
#include "Service.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GUI; }
QT_END_NAMESPACE

class GUI : public QWidget {
Q_OBJECT

public:
    explicit GUI(Service& service, QWidget *parent = nullptr);

    ~GUI() override;

private:
    Service& service;
    Ui::GUI *ui;
    void populateList();
    void connectSignalsAndSlots();
    void showPaidList();
    void showUnpaidList();
};


#endif //BILLSTESTPRACTICE_GUI_H
