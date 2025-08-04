#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <fstream>
#include "movieHashMap.h"
#include "movieTrie.h"
#include <ctime>

using namespace std;

//read the choice from the menu
int getChoice() {
    int choice;
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return -1;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}

//the main menu the user will see
void mainMenu() {
  cout << "\n === Welcome to the Movie Recommender! === \n"
          "\n Please select an option from the following menu: \n"
          " 1. Movie Title \n"
          " 2. Release Year \n"
          " 3. Movie Genre\n"
          " 4. Rating by Genre \n"
          " 5. EXIT \n"
          "\n Type your answer here: \n";
  }

int main() {
    ifstream test("moviesDataset.csv");
    if (!test.is_open()) {
        cerr << "Couldn't find the file.\n";
    } else {
        cout << "File loaded successfully.\n";
    }
movieHashMap movieHashMap;
MovieTrie myTrie;

    movieHashMap.parsingDataSet("moviesDataset.csv");

    //movieHashMap.insertMovie("Inception", 2010, "Sci-fi",      9);
    //movieHashMap.insertMovie("Titanic", 1997, "Drama-Romance",  8);
    //movieHashMap.insertMovie("Parastite", 2019, "Thriller-Drama",8);
    //myTrie.insertMovie("Inception", 2010, "Sci-fi",      9);
    //myTrie.insertMovie("Titanic", 1997, "Drama-Romance",  8);
    //myTrie.insertMovie("Parastite", 2019, "Thriller-Drama",8);
    myTrie.parseCSV("moviesDataset.csv");


    int choice;
    do {
        mainMenu();
        choice = getChoice();

        switch (choice) {
            case 1: {
                cout << "Enter Movie Title: ";
                string title;
                getline(cin, title);

                cout << "Hash Map Results: " << endl;
                movieHashMap.titleSearch(title);

                clock_t start = clock();
                cout << "Trie Results: " << endl;
                myTrie.printTitles(title);
                clock_t end = clock();
                double elapsed = double(end - start) / CLOCKS_PER_SEC;
                cout << "Search took: " << elapsed << " seconds.\n";
                break;
            }
            case 2: {
                cout << "Enter Release Year: ";
                int year;
                cin >> year;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                clock_t start = clock();
                cout << "Hash Map Results: " << endl;
                movieHashMap.yearFilter(year);
                clock_t end = clock();
                double elapsed = double(end - start) / CLOCKS_PER_SEC;
                cout << "Search took: " << elapsed << " seconds.\n";

                clock_t startt = clock();
                cout << "Trie Results: " << endl;
                myTrie.printYear(year);
                clock_t endt = clock();
                double elapsedt = double(endt - startt) / CLOCKS_PER_SEC;
                cout << "Search took: " << elapsedt << " seconds.\n";
                break;
            }
            case 3: {
                cout << "Enter Movie Genre: ";
                string genre;
                getline(cin, genre);

                clock_t start = clock();
                cout << "Hash Map Results: " << endl;
                movieHashMap.genreFilter(genre);
                clock_t end = clock();
                double elapsed = double(end - start) / CLOCKS_PER_SEC;
                cout << "Search took: " << elapsed << " seconds.\n";

                clock_t startt = clock();
                cout << "Trie Results: " << endl;
                myTrie.printGenre(genre);
                clock_t endt = clock();
                double elapsedt = double(endt - startt) / CLOCKS_PER_SEC;
                cout << "Search took: " << elapsedt << " seconds.\n";
                break;
            }
            case 4: {
                cout << "Enter Lower Rating: ";
                float lowerRate;
                cin >> lowerRate;

                cout << "Enter Higher Rating: ";
                float highRate;
                cin >> highRate;

                clock_t startt = clock();
                cout << "Trie Results: " << endl;
                myTrie.printRatings(lowerRate, highRate);
                clock_t endt = clock();
                double elapsedt = double(endt - startt) / CLOCKS_PER_SEC;
                cout << "Search took: " << elapsedt << " seconds.\n";
                break;
            }
            case 5:
                cout <<"Good Bye!";
                break;
                default:
                    cout << "Invalid Choice!";
                break;
            }
        } while (choice != 5);
        return 0;
    }


