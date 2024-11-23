//
// Created by Riki on 5/25/2024.
//

#ifndef A8_9_MOVIETABLEVIEW_H
#define A8_9_MOVIETABLEVIEW_H

#include <QWidget>
#include <QTableView>
#include <QVBoxLayout>
#include "Service.h"
#include "MovieTableModel.h"

class MovieTableView : public QWidget {
    Q_OBJECT

public:
    explicit MovieTableView(Service* userService, QWidget* parent = nullptr);

private:
    QTableView* tableView;
    MovieTableModel* tableModel;
};


#endif //A8_9_MOVIETABLEVIEW_H
