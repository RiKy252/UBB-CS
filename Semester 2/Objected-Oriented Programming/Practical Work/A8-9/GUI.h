#pragma once
#include "ui.h"
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QListWidget>
#include <QLineEdit>
#include <QMessageBox>
#include <QPainter>
#include <QtGui>
#include <QtCore>
#include <QtCharts/QtCharts>
#include "Action.h"
#include "MovieTableView.h"

void clearLayout(QLayout* layout);

class GUI : public QWidget {
private:
    Service* adminService;
    Service* userService;
    QShortcut* undoShortcut;
    QShortcut* redoShortcut;
private slots:
    void displayWatchList();
public slots:
    void performUndo();
    void performRedo();
public:
    GUI();
    ~GUI();
    void adminOrUserChoseMenu();
    void adminMenu();
    void userMenu();
    void startApp();
    void displayMovies();
    void addMovie();
    void removeMovie();
    void updateMovie();
    void seeMovies();
    void openMovie(const std::vector<Movie>& movies, int index);
    void removeMovieFromWatchList();
    void openWatchList();
    void drawBarChart();
};
