//
// Created by Riki on 6/21/2024.
//

#ifndef OOPPRACTICALEXAM_GUI_H
#define OOPPRACTICALEXAM_GUI_H

#include <QWidget>
#include "Observer.h"
#include "Service.h"
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class GUI; }
QT_END_NAMESPACE

class GUI : public QWidget, public Observer {
Q_OBJECT

public:
    explicit GUI(QWidget *parent = nullptr, Service* service = nullptr, string doctorName = "", string doctorSpec = "");
    void update();
    void populateList();
    void connectSignalsAndSlots();
    ~GUI() override;

private:
    Ui::GUI *ui;
    Service* service;
    string doctorName;
    string doctorSpec;
};


#endif //OOPPRACTICALEXAM_GUI_H
