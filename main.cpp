//
// Created by Keyla Perez on 8/2/25.
//
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <fstream>
#include "movieHashMap.h"

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
movieHashMap movieHashMap;

    movieHashMap.insertMovie("Inception", 2010, "Sci-fi",      9);
    movieHashMap.insertMovie("Titanic", 1997, "Drama-Romance",  8);
    movieHashMap.insertMovie("Parastite", 2019, "Thriller-Drama",8);


    int choice;
    do {
        mainMenu();
        choice = getChoice();

        switch (choice) {
            case 1: {
                cout << "Enter Movie Title: ";
                string title;
                cin >> title;
                movieHashMap.titleSearch(title);
                break;
            }
            case 2: {
                cout << "Enter Release Year: ";
                int year;
                cin >> year;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                movieHashMap.yearFilter(year);
                break;
            }
            case 3: {
                cout << "Enter Movie Genre: ";
                string genre;
                cin >> genre;
                movieHashMap.genreFilter(genre);
                break;
            }
            case 5:
                cout <<"Good Bye!!";
                break;
                default:
                    cout << "Invalid Choice!";
                break;
            }
        } while (choice != 5);
        return 0;
    }


