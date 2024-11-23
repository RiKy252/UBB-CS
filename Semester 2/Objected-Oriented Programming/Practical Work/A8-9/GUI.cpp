#include "GUI.h"

void clearLayout(QLayout* layout) {
    QLayoutItem* item;
    while ((item = layout->takeAt(0))) {
        delete item->widget();
        delete item;
    }
}

GUI::GUI() {
    this->setWindowTitle("Movie Database");
    CSVRepo* adminRepo = new AdminCSVRepo("MovieList");
    adminService = new Service(adminRepo);
    userService = nullptr;
    this->undoShortcut = new QShortcut(QKeySequence("Ctrl+Z"), this);
    this->redoShortcut = new QShortcut(QKeySequence("Ctrl+Y"), this);
    QObject::connect(this->undoShortcut, &QShortcut::activated, this, &GUI::performUndo);
    QObject::connect(this->redoShortcut, &QShortcut::activated, this, &GUI::performRedo);
}

void GUI::performUndo() {
    try {
        this->adminService->undo();
        adminService->writeToFile();
        this->displayMovies();
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Error!", e.what());
    }
}

void GUI::performRedo() {
    try {
        this->adminService->redo();
        adminService->writeToFile();
        this->displayMovies();
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Error!", e.what());
    }
}

GUI::~GUI() {
    delete adminService;
    delete userService;
}

void GUI::adminOrUserChoseMenu() {

    clearLayout(layout());

    auto* label = new QLabel("Choose the mode:");
    label->setAlignment(Qt::AlignCenter);
    auto* adminButton = new QPushButton("Administrator");
    auto* userButton = new QPushButton("User");
    adminButton->setCursor(Qt::PointingHandCursor);
    userButton->setCursor(Qt::PointingHandCursor);
    layout()->addWidget(label);
    layout()->addWidget(adminButton);
    layout()->addWidget(userButton);
    QObject::connect(adminButton, &QPushButton::clicked, this, [this]() {
        this->adminMenu();
    });
    QObject::connect(userButton, &QPushButton::clicked, this, [this]() {
        this->userMenu();
    });
}

void GUI::startApp() {
    auto* label = new QLabel("Choose the file type:");
    label->setAlignment(Qt::AlignCenter);
    auto* csvButton = new QPushButton("CSV");
    auto* htmlButton = new QPushButton("HTML");
    csvButton->setCursor(Qt::PointingHandCursor);
    htmlButton->setCursor(Qt::PointingHandCursor);
    auto* layout = new QVBoxLayout();
    layout->addWidget(label);
    layout->addWidget(csvButton);
    layout->addWidget(htmlButton);
    setLayout(layout);
    connect(csvButton, &QPushButton::clicked, this, [this]() {
        userService = new Service(new CSVRepo("WatchList.CSV"));
        this->adminOrUserChoseMenu();
    });
    connect(htmlButton, &QPushButton::clicked, this, [this]() {
        userService = new Service(new HTMLRepo("WatchList.html"));
        this->adminOrUserChoseMenu();
    });
}

void GUI::adminMenu() {

    clearLayout(layout());

    auto* label = new QLabel("Administrator Menu");
    label->setAlignment(Qt::AlignCenter);
    auto* addButton = new QPushButton("Add movie");
    auto* removeButton = new QPushButton("Remove movie");
    auto* updateButton = new QPushButton("Update movie");
    auto* displayButton = new QPushButton("Display movies");
    auto* backButton = new QPushButton("Back");
    addButton->setCursor(Qt::PointingHandCursor);
    removeButton->setCursor(Qt::PointingHandCursor);
    updateButton->setCursor(Qt::PointingHandCursor);
    displayButton->setCursor(Qt::PointingHandCursor);
    backButton->setCursor(Qt::PointingHandCursor);
    layout()->addWidget(label);
    layout()->addWidget(addButton);
    layout()->addWidget(removeButton);
    layout()->addWidget(updateButton);
    layout()->addWidget(displayButton);
    layout()->addWidget(backButton);
    QObject::connect(addButton, &QPushButton::clicked, this, [this]() {
        this->addMovie();
    });
    QObject::connect(removeButton, &QPushButton::clicked, this, [this]() {
        this->removeMovie();
    });
    QObject::connect(updateButton, &QPushButton::clicked, this, [this]() {
        this->updateMovie();
    });
    QObject::connect(displayButton, &QPushButton::clicked, this, [this]() {
        this->displayMovies();
    });
    QObject::connect(backButton, &QPushButton::clicked, this, [this]() {
        this->adminOrUserChoseMenu();
    });

}

void GUI::displayMovies() {
    clearLayout(layout());
    auto* movieListWidget = new QListWidget();

    unsigned int length = adminService->getRepoLength();

    for (int i = 0; i < length; i++) {
        Movie movie = adminService->getMovie(i);
        movieListWidget->addItem(QString::fromStdString(movie.toString()));
    }

    auto* undoButton = new QPushButton("Undo");
    undoButton->setCursor(Qt::PointingHandCursor);
    auto* redoButton = new QPushButton("Redo");
    redoButton->setCursor(Qt::PointingHandCursor);
    auto* backButton = new QPushButton("Back");
    backButton->setCursor(Qt::PointingHandCursor);

    layout()->addWidget(movieListWidget);
    layout()->addWidget(undoButton);
    layout()->addWidget(redoButton);
    layout()->addWidget(backButton);

    QObject::connect(backButton, &QPushButton::clicked, this, [this]() {
        this->adminMenu();
    });
    QObject::connect(undoButton, &QPushButton::clicked, this, &GUI::performUndo);
    QObject::connect(redoButton, &QPushButton::clicked, this, &GUI::performRedo);
}

void GUI::addMovie() {
    clearLayout(layout());
    auto* titleLabel = new QLabel("Title:");
    auto* genreLabel = new QLabel("Genre:");
    auto* yearLabel = new QLabel("Year:");
    auto* likesLabel = new QLabel("Likes:");
    auto* trailerLabel = new QLabel("Trailer:");
    auto* titleEdit = new QLineEdit();
    auto* genreEdit = new QLineEdit();
    auto* yearEdit = new QLineEdit();
    auto* likesEdit = new QLineEdit();
    auto* trailerEdit = new QLineEdit();
    auto* addButton = new QPushButton("Add movie");
    auto* backButton = new QPushButton("Back");
    addButton->setCursor(Qt::PointingHandCursor);
    backButton->setCursor(Qt::PointingHandCursor);
    layout()->addWidget(titleLabel);
    layout()->addWidget(titleEdit);
    layout()->addWidget(genreLabel);
    layout()->addWidget(genreEdit);
    layout()->addWidget(yearLabel);
    layout()->addWidget(yearEdit);
    layout()->addWidget(likesLabel);
    layout()->addWidget(likesEdit);
    layout()->addWidget(trailerLabel);
    layout()->addWidget(trailerEdit);
    layout()->addWidget(addButton);
    layout()->addWidget(backButton);
    QObject::connect(addButton, &QPushButton::clicked, this, [this, titleEdit, genreEdit, yearEdit, likesEdit, trailerEdit]() {
        try {
            Movie movie{ titleEdit->text().toStdString(), genreEdit->text().toStdString(), yearEdit->text().toInt(), likesEdit->text().toInt(), trailerEdit->text().toStdString() };
            MovieValidator::validateMovie(movie);
            adminService->addMovie(movie);
            adminService->writeToFile();
            QMessageBox::information(this, "Success!", "Movie added successfully!");
        } catch (const std::exception& e) {
            QMessageBox::warning(this, "Error!", e.what());
        }
    });
    QObject::connect(backButton, &QPushButton::clicked, this, [this]() {
        this->adminMenu();
    });
}

void GUI::removeMovie() {
    clearLayout(layout());
    auto* titleLabel = new QLabel("Title of the movie to be removed:");
    auto* genreLabel = new QLabel("Genre of the movie to be removed:");
    auto* titleEdit = new QLineEdit();
    auto* genreEdit = new QLineEdit();
    auto* removeButton = new QPushButton("Remove movie");
    auto* backButton = new QPushButton("Back");
    removeButton->setCursor(Qt::PointingHandCursor);
    backButton->setCursor(Qt::PointingHandCursor);
    layout()->addWidget(titleLabel);
    layout()->addWidget(titleEdit);
    layout()->addWidget(genreLabel);
    layout()->addWidget(genreEdit);
    layout()->addWidget(removeButton);
    layout()->addWidget(backButton);
    QObject::connect(removeButton, &QPushButton::clicked, this, [this, titleEdit, genreEdit]() {
        try {
            Movie movie{ titleEdit->text().toStdString(), genreEdit->text().toStdString(), 0, 0, "link" };
            MovieValidator::validateMovie(movie);
            adminService->removeMovie(titleEdit->text().toStdString(), genreEdit->text().toStdString());
            adminService->writeToFile();
            QMessageBox::information(this, "Success!", "Movie removed successfully!");
        } catch (const std::exception& e) {
            QMessageBox::warning(this, "Error!", e.what());
        }
    });
    QObject::connect(backButton, &QPushButton::clicked, this, [this]() {
        this->adminMenu();
    });
}

void GUI::updateMovie() {
    clearLayout(layout());
    auto* titleLabel = new QLabel("Title of the movie to be updated:");
    auto* genreLabel = new QLabel("Genre of the movie to be updated:");
    auto* newTitleLabel = new QLabel("New title:");
    auto* newGenreLabel = new QLabel("New genre:");
    auto* newYearLabel = new QLabel("New year:");
    auto* newLikesLabel = new QLabel("New likes:");
    auto* newTrailerLabel = new QLabel("New trailer:");
    auto* titleEdit = new QLineEdit();
    auto* genreEdit = new QLineEdit();
    auto* newTitleEdit = new QLineEdit();
    auto* newGenreEdit = new QLineEdit();
    auto* newYearEdit = new QLineEdit();
    auto* newLikesEdit = new QLineEdit();
    auto* newTrailerEdit = new QLineEdit();
    auto* updateButton = new QPushButton("Update movie");
    auto* backButton = new QPushButton("Back");
    updateButton->setCursor(Qt::PointingHandCursor);
    backButton->setCursor(Qt::PointingHandCursor);
    layout()->addWidget(titleLabel);
    layout()->addWidget(titleEdit);
    layout()->addWidget(genreLabel);
    layout()->addWidget(genreEdit);
    layout()->addWidget(newTitleLabel);
    layout()->addWidget(newTitleEdit);
    layout()->addWidget(newGenreLabel);
    layout()->addWidget(newGenreEdit);
    layout()->addWidget(newYearLabel);
    layout()->addWidget(newYearEdit);
    layout()->addWidget(newLikesLabel);
    layout()->addWidget(newLikesEdit);
    layout()->addWidget(newTrailerLabel);
    layout()->addWidget(newTrailerEdit);
    layout()->addWidget(updateButton);
    layout()->addWidget(backButton);
    QObject::connect(updateButton, &QPushButton::clicked, this, [this, titleEdit, genreEdit, newTitleEdit, newGenreEdit, newYearEdit, newLikesEdit, newTrailerEdit]() {
        try {
            Movie movie{ titleEdit->text().toStdString(), genreEdit->text().toStdString(), 0, 0, "link" };
            MovieValidator::validateMovie(movie);
            Movie updatedMovie{ newTitleEdit->text().toStdString(), newGenreEdit->text().toStdString(), newYearEdit->text().toInt(), newLikesEdit->text().toInt(), newTrailerEdit->text().toStdString() };
            MovieValidator::validateMovie(updatedMovie);
            adminService->updateMovie(titleEdit->text().toStdString(), genreEdit->text().toStdString(), updatedMovie);
            adminService->writeToFile();
            QMessageBox::information(this, "Success!", "Movie updated successfully!");
        } catch (const std::exception& e) {
            QMessageBox::warning(this, "Error!", e.what());
        }
    });
    QObject::connect(backButton, &QPushButton::clicked, this, [this]() {
        this->adminMenu();
    });
}

void GUI::userMenu() {
    clearLayout(layout());
    auto* label = new QLabel("User Menu");
    label->setAlignment(Qt::AlignCenter);
    auto* seeMoviesButton = new QPushButton("See movies");
    auto* removeMovieButton = new QPushButton("Remove movie");
    auto* displayWatchListButton = new QPushButton("Display watch list");
    auto* openWatchListButton = new QPushButton("Open watch list");
    auto* barChartButton = new QPushButton("Bar chart");
    auto* backButton = new QPushButton("Back");
    seeMoviesButton->setCursor(Qt::PointingHandCursor);
    removeMovieButton->setCursor(Qt::PointingHandCursor);
    displayWatchListButton->setCursor(Qt::PointingHandCursor);
    openWatchListButton->setCursor(Qt::PointingHandCursor);
    barChartButton->setCursor(Qt::PointingHandCursor);
    backButton->setCursor(Qt::PointingHandCursor);
    layout()->addWidget(label);
    layout()->addWidget(seeMoviesButton);
    layout()->addWidget(removeMovieButton);
    layout()->addWidget(displayWatchListButton);
    layout()->addWidget(openWatchListButton);
    layout()->addWidget(barChartButton);
    layout()->addWidget(backButton);
    QObject::connect(seeMoviesButton, &QPushButton::clicked, this, [this]() {
        this->seeMovies();
    });
    QObject::connect(removeMovieButton, &QPushButton::clicked, this, [this]() {
        this->removeMovieFromWatchList();
    });
    QObject::connect(displayWatchListButton, &QPushButton::clicked, this, [this]() {
        this->displayWatchList();
    });
    QObject::connect(openWatchListButton, &QPushButton::clicked, this, [this]() {
        this->openWatchList();
    });
    QObject::connect(barChartButton, &QPushButton::clicked, this, [this]() {
        this->drawBarChart();
    });
    QObject::connect(backButton, &QPushButton::clicked, this, [this]() {
        this->adminOrUserChoseMenu();
    });
}

void GUI::seeMovies() {
    clearLayout(layout());
    auto* genreLabel = new QLabel("Enter the genre:");
    auto* genreEdit = new QLineEdit();
    auto* seeButton = new QPushButton("See movies");
    auto* backButton = new QPushButton("Back");
    seeButton->setCursor(Qt::PointingHandCursor);
    backButton->setCursor(Qt::PointingHandCursor);
    layout()->addWidget(genreLabel);
    layout()->addWidget(genreEdit);
    layout()->addWidget(seeButton);
    layout()->addWidget(backButton);
    QObject::connect(seeButton, &QPushButton::clicked, this, [this, genreEdit]() {
        std::string userGenre = genreEdit->text().toStdString();
        std::vector<Movie> filteredMovies;
        if (!userGenre.empty())
            filteredMovies = this->adminService->filterMoviesByGenre(userGenre);
        else
            filteredMovies = this->adminService->getMovies();
        if (!filteredMovies.empty()) {
            openMovie(filteredMovies, 0);
        }
    });
    QObject::connect(backButton, &QPushButton::clicked, this, [this]() {
        this->userMenu();
    });
}

void GUI::openMovie(const std::vector<Movie>& movies, int index) {
    clearLayout(layout());
    Movie currentMovie = movies[index];
    auto* titleLabel = new QLabel("Title: " + QString::fromStdString(currentMovie.getTitle()));
    auto* genreLabel = new QLabel("Genre: " + QString::fromStdString(currentMovie.getGenre()));
    auto* yearLabel = new QLabel("Year: " + QString::number(currentMovie.getReleaseYear()));
    auto* likesLabel = new QLabel("Likes: " + QString::number(currentMovie.getNumberOfLikes()));
    auto* trailerLabel = new QLabel("<a href=\"" + QString::fromStdString(currentMovie.getTrailer()) + "\">Trailer: " + QString::fromStdString(currentMovie.getTrailer()) + "</a>");
    trailerLabel->setOpenExternalLinks(true);
    auto* addToWatchListButton = new QPushButton("Add to watch list");
    addToWatchListButton->setCursor(Qt::PointingHandCursor);
    auto* nextButton = new QPushButton("Next");
    nextButton->setCursor(Qt::PointingHandCursor);
    layout()->addWidget(titleLabel);
    layout()->addWidget(genreLabel);
    layout()->addWidget(yearLabel);
    layout()->addWidget(likesLabel);
    layout()->addWidget(trailerLabel);
    layout()->addWidget(addToWatchListButton);
    layout()->addWidget(nextButton);
    auto* stopButton = new QPushButton("Stop");
    stopButton->setCursor(Qt::PointingHandCursor);
    layout()->addWidget(stopButton);
    openURL(currentMovie.getTrailer());
    QObject::connect(addToWatchListButton, &QPushButton::clicked, this, [this, currentMovie]() {
        try {
            userService->addMovie(currentMovie);
            QMessageBox::information(this, "Success!", "Movie added to watch list successfully!");
        } catch (const std::exception& e) {
            QMessageBox::warning(this, "Error!", e.what());
        }
    });
    QObject::connect(stopButton, &QPushButton::clicked, this, [this]() {
        this->userMenu();
    });
    QObject::connect(nextButton, &QPushButton::clicked, this, [this, movies, index]() {
        if (index + 1 < movies.size()) {
            openMovie(movies, index + 1);
        } else {
            openMovie(movies, 0);
        }
    });
}

void GUI::removeMovieFromWatchList() {
    // get name and genre and attempt to remove catch exceptions if necessary
    clearLayout(layout());
    auto* titleLabel = new QLabel("Title of the movie to be removed:");
    auto* genreLabel = new QLabel("Genre of the movie to be removed:");
    auto* titleEdit = new QLineEdit();
    auto* genreEdit = new QLineEdit();
    auto* removeButton = new QPushButton("Remove movie");
    auto* backButton = new QPushButton("Back");
    removeButton->setCursor(Qt::PointingHandCursor);
    backButton->setCursor(Qt::PointingHandCursor);
    layout()->addWidget(titleLabel);
    layout()->addWidget(titleEdit);
    layout()->addWidget(genreLabel);
    layout()->addWidget(genreEdit);
    layout()->addWidget(removeButton);
    layout()->addWidget(backButton);
    QObject::connect(removeButton, &QPushButton::clicked, this, [this, titleEdit, genreEdit]() {
        try {
            Movie movie{ titleEdit->text().toStdString(), genreEdit->text().toStdString(), 0, 0, "link" };
            MovieValidator::validateMovie(movie);
            userService->removeMovie(titleEdit->text().toStdString(), genreEdit->text().toStdString());
            // ask user if they want to rate the movie by incrementing the likes
            clearLayout(layout());
            auto* textLabel = new QLabel("Did you like the movie?");
            auto* yesButton = new QPushButton("Yes");
            auto* noButton = new QPushButton("No");
            yesButton->setCursor(Qt::PointingHandCursor);
            noButton->setCursor(Qt::PointingHandCursor);
            layout()->addWidget(textLabel);
            layout()->addWidget(yesButton);
            layout()->addWidget(noButton);
            QObject::connect(yesButton, &QPushButton::clicked, this, [this, movie]() {
                userService->incrementLikes(movie);
                QMessageBox::information(this, "Success!", "Movie rated and removed successfully!");
                this->userMenu();
            });
            QObject::connect(noButton, &QPushButton::clicked, this, [this]() {
                QMessageBox::information(this, "Success!", "Movie removed successfully!");
                this->userMenu();
            });
        } catch (const std::exception& e) {
            QMessageBox::warning(this, "Error!", e.what());
        }
    });
    QObject::connect(backButton, &QPushButton::clicked, this, [this]() {
        this->userMenu();
    });
}

void GUI::displayWatchList() {
    clearLayout(layout());

    // Assuming userService has a method to get the list of movies
    std::vector<Movie> movies = userService->getMovies();
    MovieTableModel* model = new MovieTableModel(movies, this);
    QTableView* tableView = new QTableView();
    tableView->setModel(model);

    layout()->addWidget(tableView);

    auto* backButton = new QPushButton("Back");
    backButton->setCursor(Qt::PointingHandCursor);
    layout()->addWidget(backButton);

    QObject::connect(backButton, &QPushButton::clicked, this, [this]() {
        this->userMenu();
    });
}

void GUI::openWatchList() {
    this->userService->writeToFile();
    this->userService->openFile();
}

void GUI::drawBarChart() {
    clearLayout(layout());

    auto* chart = new QChart();
    chart->setAnimationOptions(QChart::SeriesAnimations);
    for (const Movie& movie : adminService->getMovies()) {
        auto* set = new QBarSet(QString::fromStdString(movie.getTitle()));
        set->append(movie.getNumberOfLikes());
        auto* series = new QBarSeries();
        series->append(set);
        chart->addSeries(series);
    }

    auto* axisX = new QBarCategoryAxis();
    axisX->append("Movies");
    chart->addAxis(axisX, Qt::AlignBottom);

    for (auto* series : chart->series()) {
        series->attachAxis(axisX);
    }

    auto* axisY = new QValueAxis();
    axisY->setRange(0, 3000000);
    axisY->setTitleText("Number of likes");
    chart->addAxis(axisY, Qt::AlignLeft);

    for (auto* series : chart->series()) {
        series->attachAxis(axisY);
    }

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->setVisible(true);

    auto* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setVisible(true);

    layout()->addWidget(chartView);
}
