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

void mainMenu() {
  cout << "\n === Welcome to the Movie Recommender! === \n"
          "\n Please select an option from the following menu: \n"
          " 1. Movie Title \n"
          " 2. Release Year \n"
          " 3. Movie Genre\n"
          " 4. Rating by Genre \n"
          " 5. EXIT \n";
  }

int main() {
    int choice;
    do {
        mainMenu();
        choice = getChoice();
    }
  return 0;
}