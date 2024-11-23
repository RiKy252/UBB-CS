#include "ui.h"

UI::UI()
{
	this->service = new Service();
	this->service->addMovie(Movie("The Godfather", "Crime", 1972, 3, "https://www.youtube.com/watch?v=sY1S34973zA"));
	this->service->addMovie(Movie("Furious 7", "Action", 2015, 0, "https://www.youtube.com/watch?v=Skpu5HaVkOc&t=1s"));
	this->service->addMovie(Movie("The Fast and the Furious", "Action", 2001, 10, "https://www.youtube.com/watch?v=ZsJz2TJAPjw"));
	this->service->addMovie(Movie("Avengers: Infinity War", "Action", 2018, 12, "https://www.youtube.com/watch?v=6ZfuNTqbHE8"));
	this->service->addMovie(Movie("Rampage", "Sci-Fi", 2018, 15, "https://www.youtube.com/watch?v=coOKvrsmQiI"));
	this->service->addMovie(Movie("The Matrix", "Sci-Fi", 1999, 20, "https://www.youtube.com/watch?v=m8e-FF8MsqU"));
	this->service->addMovie(Movie("Interstellar", "Sci-Fi", 2014, 11, "https://www.youtube.com/watch?v=zSWdZVtXT7E"));
	this->service->addMovie(Movie("The Dark Knight", "Crime", 2008, 13, "https://www.youtube.com/watch?v=EXeTwQWrcwY"));
	this->service->addMovie(Movie("Joker", "Crime", 2019, 2, "https://www.youtube.com/watch?v=zAGVQLHvwOY"));
	this->service->addMovie(Movie("Batman Begins", "Action", 2005, 8, "https://www.youtube.com/watch?v=neY2xVmOfUM"));
	this->userService = new Service();
}

UI::~UI()
{
	delete this->service;
	delete this->userService;
}

bool UI::validIntegerInput()
{
	if (cin.fail()) {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Please insert a valid integer!\n";
		return false;
	}
	return true;
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
	cout << "0. Go back\n";
}

void UI::startMessage()
{
	cout << "Choose which mode to use:" << endl;
	cout << "1. Administrator mode" << endl;
	cout << "2. User mode" << endl;
	cout << "0. Exit" << endl;
}

void UI::startApp()
{
	startMessage();
	int userOption;
	while (true) {
		cin >> userOption;
		if (!validIntegerInput())
			continue;
		else if (userOption == 1 || userOption == 2 || userOption == 0)
			break;
		else
			cout << "Please insert a valid menu option!\n";
	}
	if (userOption == 1) {
		while (true) {
			string userTitle, userGenre, userTrailer;
			int userYear, userLikes;
			adminMenu();
			cin >> userOption;
			if (!validIntegerInput())
				continue;
			else
				if (userOption == 1) {
					cout << "Title of the movie to be added: ";
					cin.ignore();
					getline(cin, userTitle);
					cout << "Genre: ";
					getline(cin, userGenre);
					cout << "Year of release: ";
					cin >> userYear;
					if (validIntegerInput() == false)
						continue;
					cout << "Number of likes: ";
					cin >> userLikes;
					if (validIntegerInput() == false)
						continue;
					cout << "Trailer link: ";
					cin.ignore();
					getline(cin, userTrailer);
					Movie userMovie{ userTitle, userGenre, userYear, userLikes, userTrailer };
					if (this->service->addMovie(userMovie))
						cout << "Movie added successfully!\n";
					else
						cout << "Movie already exists!\n";
				}
				else if (userOption == 2) {
					cout << "Title of the movie to be removed: ";
					cin.ignore();
					getline(cin, userTitle);
					cout << "Genre of the movie to be removed: ";
					getline(cin, userGenre);
					if (this->service->removeMovie(userTitle, userGenre))
						cout << "Movie deleted successfully!\n";
					else
						cout << "Movie does not exist!\n";
				}
				else if (userOption == 3) {
					cout << "Title of the movie to be updated: ";
					cin.ignore();
					getline(cin, userTitle);
					cout << "Genre of the movie to be updated: ";
					getline(cin, userGenre);
					Movie tempMovie{ userTitle, userGenre, 0, 0, "" };
					if (this->service->doesMovieExist(tempMovie)) {
						cout << "New title: ";
						getline(cin, userTitle);
						cout << "New genre: ";
						getline(cin, userGenre);
						cout << "New year of release: ";
						cin >> userYear;
						if (validIntegerInput() == false)
							continue;
						cout << "New number of likes: ";
						cin >> userLikes;
						if (validIntegerInput() == false)
							continue;
						cout << "New trailer link: ";
						cin.ignore();
						getline(cin, userTrailer);
						Movie userMovie{ userTitle, userGenre, userYear, userLikes, userTrailer };
						if (this->service->updateMovie(tempMovie.getTitle(), tempMovie.getGenre(), userMovie))
							cout << "Movie updated successfully!\n";
						else
							cout << "Movie not updated because it already exists!\n";
					}
					else
						cout << "Movie does not exist!\n";
				}
				else if (userOption == 4) {
					cout << this->service->displayMovies();
				}
				else if (userOption == 0) {
					startApp();
					break;
				}
				else
					cout << "Invalid input!\n";
		}
	}
	else if (userOption == 2) {
		while (1) {
			userMenu();
			cin >> userOption;
			if (!validIntegerInput())
				continue;
			else {
				if (userOption == 1) {
					string userGenre;
					bool ok = false;
					cout << "Enter the genre: ";
					cin.clear();
					cin.ignore(10000, '\n');
					getline(cin, userGenre);
					if (userGenre.empty()) {
						for (int i = 0; i < this->service->getRepoLength(); i++) {
							cout << this->service->getMovie(i).toString() << endl;
							string trailer = this->service->getMovie(i).getTrailer();
							wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
							wstring wideTrailer = converter.from_bytes(trailer);
							ShellExecute(NULL, L"open", wideTrailer.c_str(), NULL, NULL, SW_SHOWNORMAL);
							int liked;
							while (1) {
								cout << "Add this movie to the watch list?\n1. Yes\n2. No\n";
								cout << ">> ";
								cin >> liked;
								if (liked != 1 && liked != 2)
									cout << "Enter a valid option!\n";
								else
									break;
							}
							if (liked == 1) {
								if (this->userService->addMovie(this->service->getMovie(i)))
									cout << "Movie added to the watchlist!\n";
								else
									cout << "Movie already in the watchlist!\n";
							}
							int option;
							while (1) {
								cout << "Select an option:\n";
								cout << "1. Next trailer\n2. Stop\n";
								cout << ">> ";
								cin >> option;
								if (option != 1 && option != 2)
									cout << "Enter a valid option!\n";
								else
									break;
							}
							if (option == 2)
								break;
							if (i == this->service->getRepoLength() - 1) {
								if (!ok) {
									cout << "No movies in the database!\n";
									break;
								}
								i = -1;
							}
						}
					}
					else {
						for (int i = 0; i < this->service->getRepoLength(); i++) {
							if (this->service->getMovie(i).getGenre() == userGenre) {
								ok = true;
								cout << this->service->getMovie(i).toString() << endl;
								string trailer = this->service->getMovie(i).getTrailer();
								wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
								wstring wideTrailer = converter.from_bytes(trailer);
								ShellExecute(NULL, L"open", wideTrailer.c_str(), NULL, NULL, SW_SHOWNORMAL);
								int liked;
								while (1) {
									cout << "Add this movie to the watch list?\n1. Yes\n2. No\n";
									cout << ">> ";
									cin >> liked;
									if (liked != 1 && liked != 2)
										cout << "Enter a valid option!\n";
									else
										break;
								}
								if (liked == 1) {
									if (this->userService->addMovie(this->service->getMovie(i)))
										cout << "Movie added to the watchlist!\n";
									else
										cout << "Movie already in the watchlist!\n";
								}
								int option;
								while (1) {
									cout << "Select an option:\n";
									cout << "1. Next trailer\n2. Stop\n";
									cout << ">> ";
									cin >> option;
									if (option != 1 && option != 2)
										cout << "Enter a valid option!\n";
									else
										break;
								}
								if (option == 2)
									break;
							}
							if (i == this->service->getRepoLength() - 1) {
								if (!ok) {
									cout << "No movies with that genre found!\n";
									break;
								}
								i = -1;
							}
						}
					}
				}
				else if (userOption == 2) { 
					string userTitle, userGenre;
					int enjoyed;
					cout << "Title of the movie to be removed: ";
					cin.ignore();
					getline(cin, userTitle);
					cout << "Genre of the movie to be removed: ";
					getline(cin, userGenre);
					if (this->userService->removeMovie(userTitle, userGenre)) {
						cout << "Did you enjoy the movie?\n1. Yes\n2. No\n";
						cout << ">> ";
						cin >> enjoyed;
						if (enjoyed == 1) {
							Movie temp(userTitle, userGenre, 0, 0, "url");
							this->service->incrementLikes(temp);
							cout << "Liked!\n";
						}
					}
					else
						cout << "Movie does not exist!\n";
				}
				else if (userOption == 3) {
					cout << this->userService->displayMovies();
				}
				else if (userOption == 0) {
					startApp();
					break;
				}
				else
					cout << "Invalid input\n";
			}
		}
	}
}
