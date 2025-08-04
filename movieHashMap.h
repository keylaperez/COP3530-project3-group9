//
// Created by Winni Weng on 8/2/25.
//

#ifndef COP3530_PROJECT3_GROUP9_MOVIEHASHMAP_H
#define COP3530_PROJECT3_GROUP9_MOVIEHASHMAP_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class movieHashMap {

private:
    unordered_map<string,vector<string>> movies;

public:
    void insertMovie(string name, int year, string genre, int rating);
    void titleSearch(string name);
    void yearFilter(int year);
    void genreFilter(string genre);
    void ratingByGenre(string genre);
    vector<string> splitGenre(string genre);
    void parsingDataSet(string name);
};


#endif //COP3530_PROJECT3_GROUP9_MOVIEHASHMAP_H

