//
// Created by Riki on 5/25/2024.
//

#include "MovieTableView.h"

MovieTableView::MovieTableView(Service* userService, QWidget* parent)
        : QWidget(parent) {
    tableView = new QTableView(this);

    // Get the movies from the user service
    std::vector<Movie> movies = userService->getMovies();

    // Create the table model
    tableModel = new MovieTableModel(movies, this);

    // Set the model to the table view
    tableView->setModel(tableModel);

    // Set up the layout
    auto* layout = new QVBoxLayout(this);
    layout->addWidget(tableView);
    setLayout(layout);
}