// MovieTableModel.cpp
#include "MovieTableModel.h"

MovieTableModel::MovieTableModel(const std::vector<Movie>& movies, QObject* parent)
        : QAbstractTableModel(parent), movies(movies) {}

int MovieTableModel::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return static_cast<int>(movies.size());
}

int MovieTableModel::columnCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    // title, genre, year, likes, trailer
    return 5;
}

QVariant MovieTableModel::data(const QModelIndex& index, int role) const {
    if (role == Qt::DisplayRole) {
        Movie movie = movies.at(index.row());
        switch (index.column()) {
            case 0:
                return QString::fromStdString(movie.getTitle());
            case 1:
                return QString::fromStdString(movie.getGenre());
            case 2:
                return movie.getReleaseYear();
            case 3:
                return movie.getNumberOfLikes();
            case 4:
                return QString::fromStdString(movie.getTrailer());
            default:
                return QVariant();
        }
    }
    return QVariant();
}

QVariant MovieTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
                case 0:
                    return QString("Title");
                case 1:
                    return QString("Genre");
                case 2:
                    return QString("Year");
                case 3:
                    return QString("Likes");
                case 4:
                    return QString("Trailer");
                default:
                    return QVariant();
            }
        }
    }
    return QVariant();
}
