//
// Created by Keyla Perez on 8/2/25.
//
#include <iostream>
#include <limits>
#include <vector>
#include "movieHashMap.h"

using namespace std;

//read the choice from the menu
int getChoice() {
    int choice;
    if (!(cin >> choice)) {
        cin.clear();
        choice = -1;
    }
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
    int choice;
    do {
        mainMenu();
        choice = getChoice();

        switch (choice) {
            case 1: {
                cout << "Enter Movie Title: ";
                string title;
                cin >> title;
                break;
            }
            case 2: {
                cout << "Enter Release Year: ";
                int year;
                cin >> year;
                break;
            }
            case 3: {
                cout << "Enter Movie Genre: ";
                string genre;
                cin >> genre;
                break;
            }
            case 4: {
                cout << "Enter Rating by Genre: ";
                double rating;
                cin >> rating;
                break;
            }
            case 5: {
                cout <<"Good Bye!";
                break;
            }
        }
        return 0;
    } while (choice != 5);
}