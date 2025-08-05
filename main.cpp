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
          " 4. Ratings by Range \n"
          " 5. EXIT \n"
          "\n Type your answer here: \n";
  }

int main() {

movieHashMap movieHashMap;
MovieTrie myTrie;

    movieHashMap.parsingDataSet("moviesDataset.csv");
    myTrie.parseCSV("moviesDataset.csv");

    cout << "By: The Popcorn Programmers" << endl;
    cout << "Credits: Keyla Perez, Zi Xuan Weng, Sydney Fung" << endl;
    cout << endl;

    int choice;
    do {
        mainMenu();
        choice = getChoice();

        switch (choice) {
            case 1: { //movie title search
                cout << "Enter Movie Title (Exact title for Trie): ";
                string title;
                getline(cin, title); //getting input

                clock_t start = clock(); //start clock
                cout << "Hash Map Results: " << endl;
                movieHashMap.titleSearch(title); //do title search in hash map
                clock_t end = clock(); //end clock
                double elapsed = double(end - start) / CLOCKS_PER_SEC;
                cout << "\nSearch took: " << elapsed << " seconds.\n\n"; //print search time
                clock_t startt = clock(); //start clock for trie
                cout << "Trie Results: " << endl;
                myTrie.printTitles(title); //search title from trie
                clock_t endt = clock(); //end clock
                double elapsedt = double(endt - startt) / CLOCKS_PER_SEC;
                cout << "\nSearch took: " << elapsedt << " seconds.\n"; //print search time
                break;
            }
            case 2: { //searching by release year
                cout << "Enter Release Year: ";
                int year;
                cin >> year; //getting year
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                clock_t start = clock(); //start clock for hash map
                cout << "Hash Map Results: " << endl;
                movieHashMap.yearFilter(year); //search by year in hash map
                clock_t end = clock();
                double elapsed = double(end - start) / CLOCKS_PER_SEC;
                cout << "\nSearch took: " << elapsed << " seconds.\n\n"; //prints search time

                clock_t startt = clock(); //clock start for trie
                cout << "Trie Results: " << endl;
                myTrie.printYear(year); //searches by year in trie
                clock_t endt = clock(); //end clock
                double elapsedt = double(endt - startt) / CLOCKS_PER_SEC;
                cout << "\nSearch took: " << elapsedt << " seconds.\n"; //printing time for trie
                break;
            }
            case 3: { //for movie genre search
                cout << "Enter Movie Genre: ";
                string genre;
                getline(cin, genre);  //get genre search from user

                clock_t start = clock(); //start clock for hash map
                cout << "Hash Map Results: " << endl;
                movieHashMap.genreFilter(genre); //hash map genre search
                clock_t end = clock();
                double elapsed = double(end - start) / CLOCKS_PER_SEC;
                cout << "\nSearch took: " << elapsed << " seconds.\n\n"; //printing hash map time

                clock_t startt = clock(); //starting clock again for trie
                cout << "Trie Results: " << endl;
                myTrie.printGenre(genre); //searches trie for genre
                clock_t endt = clock();
                double elapsedt = double(endt - startt) / CLOCKS_PER_SEC;
                cout << "\nSearch took: " << elapsedt << " seconds.\n"; //serach time for trie
                break;
            }
            case 4: { //ratings by range filter
                cout << "Enter Lower Rating (0-9.9): ";
                float lowerRate;
                cin >> lowerRate; //gets the lower range for rating

                cout << "Enter Higher Rating (0.1-10): ";
                float highRate;
                cin >> highRate; //gets the higher range for rating

                clock_t start = clock(); //start clock for hash map
                cout << "Hash Map Results: " << endl;
                movieHashMap.ratingByRange(lowerRate, highRate); //searching for movies within rating range
                clock_t end = clock();
                double elapsed = double(end - start) / CLOCKS_PER_SEC;
                cout << "\nSearch took: " << elapsed << " seconds.\n\n"; //prints clock time for hash map

                clock_t startt = clock(); //start clock time for trie
                cout << "Trie Results: " << endl;
                myTrie.printRatings(lowerRate, highRate); //searches trie for ratings within range
                clock_t endt = clock();
                double elapsedt = double(endt - startt) / CLOCKS_PER_SEC;
                cout << "\nSearch took: " << elapsedt << " seconds.\n"; //prints out time for trie
                break;
            }
            case 5: //exit
                cout <<"Good Bye!";
                break;
                default:
                    cout << "Invalid Choice!";
                break;
            }
        } while (choice != 5);
        return 0;
    }


