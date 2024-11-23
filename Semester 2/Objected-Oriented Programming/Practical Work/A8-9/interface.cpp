#include "interface.h"

QWidget* interfaceA8() {
    CSVRepo* adminRepo = new AdminCSVRepo("MovieList");
    Service* adminService = new Service(adminRepo);
    QWidget* window = new QWidget();
    window->setWindowTitle("Movie Database");

    QVBoxLayout* layout = new QVBoxLayout();

    QListWidget* movieListWidget = new QListWidget();

    int length = adminService->getRepoLength();

    for (int i = 0; i < length; i++) {
        Movie movie = adminService->getMovie(i);
        movieListWidget->addItem(QString::fromStdString(movie.toString()));
    }

    layout->addWidget(movieListWidget);

    window->setLayout(layout);

    window->show();
    return window;

}

/*

    QLabel* label = new QLabel("Select the type of file to save the watch list:");
    QPushButton* csvButton = new QPushButton("CSV");
    QPushButton* htmlButton = new QPushButton("HTML");
    QTextEdit* textEdit = new QTextEdit();
    textEdit->setReadOnly(true);

    layout->addWidget(label);
    layout->addWidget(csvButton);
    layout->addWidget(htmlButton);
    window->setLayout(layout);

    QObject::connect(csvButton, &QPushButton::clicked, [&]() {
    Service* userService = new Service(new CSVRepo("WatchList.CSV"));
    });

    QObject::connect(htmlButton, &QPushButton::clicked, [&]() {
    Service* userService = new Service(new HTMLRepo("WatchList.html"));
    });

*/