//
// Created by Riki on 5/25/2024.
//

#ifndef A8_9_MOVIETABLEMODEL_H
#define A8_9_MOVIETABLEMODEL_H

#include <QAbstractTableModel>
#include <vector>
#include "domain.h"

class MovieTableModel : public QAbstractTableModel {
    Q_OBJECT

public:
    MovieTableModel(const std::vector<Movie>& movies, QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    std::vector<Movie> movies;
};


#endif //A8_9_MOVIETABLEMODEL_H
