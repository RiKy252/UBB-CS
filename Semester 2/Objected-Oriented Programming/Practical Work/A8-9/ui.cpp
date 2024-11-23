#include "ui.h"

void openURL(const std::string &url) {
    std::string command = "start " + url;
    std::system(command.c_str());
}

UI::UI(const std::string& fileType)
{
    CSVRepo* adminRepo = new AdminCSVRepo("MovieList");
	this->service = new Service(adminRepo);
    if (fileType == "CSV")
        this->userService = new Service(new CSVRepo("WatchList.CSV"));
    else
        this->userService = new Service(new HTMLRepo("WatchList.html"));
}

UI::~UI()
{
	delete this->service;
	delete this->userService;
}

void UI::adminMenu()
{
	cout << "1. Add movie" << endl;
	cout << "2. Delete movie" << endl;
	cout << "3. Update movie" << endl;
	cout << "4. Display movies" << endl;
	cout << "0. Go back" << endl;
}

void UI::userMenu()
{
	cout << "1. See the movies\n";
	cout << "2. Remove movie from watchlist\n";
	cout << "3. Display watchlist\n";
    cout << "4. Open watchlist\n";
	cout << "0. Go back\n";
}

void UI::startMessage()
{
	cout << "Choose which mode to use:" << endl;
	cout << "1. Administrator mode" << endl;
	cout << "2. User mode" << endl;
	cout << "0. Exit" << endl;
}

void UI::startApp() {
    startMessage();
    int userOption;
    while (true) {
        try {
            cin >> userOption;
            IntegerValidator::validateInteger();
            MenuValidator::validateUserStartMenuOption(userOption);
            break;
        } catch (const std::invalid_argument &e) {
            std::cerr << "Caught an IntegerException: " << e.what() << '\n';
            continue;
        } catch (const MenuException &e) {
            std::cerr << "Caught a MenuException: " << e.what() << '\n';
            continue;
        }
    }
    if (userOption == 1) { // admin mode
        while (true) {
            try {
                string userTitle, userGenre, userTrailer;
                int userYear, userLikes;
                adminMenu();
                cin >> userOption;
                IntegerValidator::validateInteger();
                MenuValidator::validateAdminMenuOption(userOption);
                if (userOption == 1) {
                    cout << "Title of the movie to be added: ";
                    cin.ignore();
                    getline(cin, userTitle);
                    cout << "Genre: ";
                    getline(cin, userGenre);
                    cout << "Year of release: ";
                    cin >> userYear;
                    IntegerValidator::validateInteger();
                    cout << "Number of likes: ";
                    cin >> userLikes;
                    IntegerValidator::validateInteger();
                    cout << "Trailer link: ";
                    cin.ignore();
                    getline(cin, userTrailer);
                    Movie userMovie{userTitle, userGenre, userYear, userLikes, userTrailer};
                    try {
                        MovieValidator::validateMovie(userMovie);
                        this->service->addMovie(userMovie);
                        cout << "Movie added!\n";
                    }
                    catch (const MovieException &e) {
                        std::cerr << "Caught a MovieException: " << e.what() << '\n';
                        continue;
                    }
                    catch (const RepoException &e) {
                        std::cerr << "Caught a RepoException: " << e.what() << '\n';
                        continue;
                    }
                } else if (userOption == 2) {
                    cout << "Title of the movie to be removed: ";
                    cin.ignore();
                    getline(cin, userTitle);
                    cout << "Genre of the movie to be removed: ";
                    getline(cin, userGenre);
                    try {
                        this->service->removeMovie(userTitle, userGenre);
                        cout << "Movie deleted!\n";
                    }
                    catch (const RepoException &e) {
                        std::cerr << "Caught a RepoException: " << e.what() << '\n';
                        continue;
                    }
                } else if (userOption == 3) {
                    cout << "Title of the movie to be updated: ";
                    cin.ignore();
                    getline(cin, userTitle);
                    cout << "Genre of the movie to be updated: ";
                    getline(cin, userGenre);
                    Movie tempMovie{userTitle, userGenre, 0, 0, ""};
                    if (this->service->doesMovieExist(tempMovie)) {
                        cout << "New title: ";
                        getline(cin, userTitle);
                        cout << "New genre: ";
                        getline(cin, userGenre);
                        cout << "New year of release: ";
                        cin >> userYear;
                        IntegerValidator::validateInteger();
                        cout << "New number of likes: ";
                        cin >> userLikes;
                        IntegerValidator::validateInteger();
                        cout << "New trailer link: ";
                        cin.ignore();
                        getline(cin, userTrailer);
                        Movie userMovie{userTitle, userGenre, userYear, userLikes, userTrailer};
                        MovieValidator::validateMovie(userMovie);
                        this->service->updateMovie(tempMovie.getTitle(), tempMovie.getGenre(), userMovie);
                        cout << "Movie updated successfully!\n";
                    } else
                        cout << "Movie does not exist!\n";
                } else if (userOption == 4) {
                    cout << this->service->displayMovies();
                } else if (userOption == 0) {
                    startApp();
                    break;
                }
            } catch (const std::invalid_argument &e) {
                std::cerr << "Caught an IntegerException: " << e.what() << '\n';
                continue;
            } catch (const MenuException &e) {
                std::cerr << "Caught a MenuException: " << e.what() << '\n';
                continue;
            } catch (const MovieException &e) {
                std::cerr << "Caught a MovieException: " << e.what() << '\n';
                continue;
            }
            catch (const RepoException &e) {
                std::cerr << "Caught a RepoException: " << e.what() << '\n';
                continue;
            }
        }
    } else if (userOption == 2) { // user mode
        while (true) {
            try {
                userMenu();
                cin >> userOption;
                IntegerValidator::validateInteger();
                MenuValidator::validateUserMenuOption(userOption);
                if (userOption == 1) { // open movies
                    string userGenre;
                    cout << "Enter the genre: ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                    getline(cin, userGenre);
                    int index = 0;
                    Movie currentMovie;
                    std::vector<Movie> filteredMovies;
                    if (!userGenre.empty())
                        filteredMovies = this->service->filterMoviesByGenre(userGenre);
                    else
                        filteredMovies = this->service->getMovies();

                    while (index < filteredMovies.size()) {
                        currentMovie = filteredMovies[index];
                        cout << currentMovie.toString() << '\n';
                        string trailer = currentMovie.getTrailer();
                        openURL(trailer);
                        int liked;
                        while (true) {
                            try {
                                cout << "Add this movie to the watch list?\n1. Yes\n2. No\n";
                                cout << ">> ";
                                cin >> liked;
                                MenuValidator::validateLikedMenuOption(liked);
                                IntegerValidator::validateInteger();
                                break;
                            }
                            catch (const std::invalid_argument &e) {
                                std::cerr << "Caught an IntegerException: " << e.what() << '\n';
                                continue;
                            }
                            catch (const MenuException &e) {
                                std::cerr << "Caught a MenuException: " << e.what() << '\n';
                                continue;
                            }
                        }
                        if (liked == 1) {
                            this->userService->addMovie(currentMovie);
                            cout << "Movie added to watchlist!\n";
                        }
                        int option;
                        while (true) {
                            try {
                                cout << "Select an option:\n";
                                cout << "1. Next trailer\n2. Stop\n";
                                cout << ">> ";
                                cin >> option;
                                IntegerValidator::validateInteger();
                                MenuValidator::validateLikedMenuOption(option);
                                break;
                            }
                            catch (const std::invalid_argument &e) {
                                std::cerr << "Caught an IntegerException: " << e.what() << '\n';
                                continue;
                            }
                            catch (const MenuException &e) {
                                std::cerr << "Caught a MenuException: " << e.what() << '\n';
                                continue;
                            }
                        }
                        if (option == 2)
                            break;
                        index++;
                        if (index == filteredMovies.size())
                            index = 0;
                    }
                } else if (userOption == 2) {
                    string userTitle, userGenre;
                    int enjoyed;
                    cout << "Title of the movie to be removed: ";
                    cin.ignore();
                    getline(cin, userTitle);
                    cout << "Genre of the movie to be removed: ";
                    getline(cin, userGenre);
                    this->userService->removeMovie(userTitle, userGenre);
                    cout << "Did you enjoy the movie?\n1. Yes\n2. No\n";
                    cout << ">> ";
                    cin >> enjoyed;
                    IntegerValidator::validateInteger();
                    MenuValidator::validateLikedMenuOption(enjoyed);
                    if (enjoyed == 1) {
                        Movie temp(userTitle, userGenre, 0, 0, "url");
                        this->service->incrementLikes(temp);
                        cout << "Liked!\n";
                    }
                } else if (userOption == 3) {
                    cout << this->userService->displayMovies();
                }
                else if (userOption == 4) {
                    this->userService->writeToFile();
                    this->userService->openFile();
                }
                else if (userOption == 0) {
                    startApp();
                    break;
                }
            } catch (const std::invalid_argument &e) {
                std::cerr << "Caught an IntegerException: " << e.what() << '\n';
                continue;
            } catch (const MenuException &e) {
                std::cerr << "Caught a MenuException: " << e.what() << '\n';
                continue;
            } catch (const MovieException &e) {
                std::cerr << "Caught a MovieException: " << e.what() << '\n';
                continue;
            }
            catch (const RepoException &e) {
                std::cerr << "Caught a RepoException: " << e.what() << '\n';
                continue;
            }
        }
    }
    this->service->writeToFile();
    this->userService->writeToFile();
}