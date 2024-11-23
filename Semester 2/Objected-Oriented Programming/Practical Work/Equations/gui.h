//
// Created by Riki on 5/28/2024.
//

#ifndef EQUATIONS_GUI_H
#define EQUATIONS_GUI_H

#include <QWidget>
#include "Service.h"


QT_BEGIN_NAMESPACE
namespace Ui { class GUI; }
QT_END_NAMESPACE

class GUI : public QWidget {
Q_OBJECT

public:
    explicit GUI(Service* service, QWidget *parent = nullptr);

    ~GUI() override;

private:
    Ui::GUI *ui;
    Service* service;
    void populateList();
    void connectSignalsAndSlots();
};


#endif //EQUATIONS_GUI_H
