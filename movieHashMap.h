//
// Created by Winni Weng on 8/2/25.
//

#ifndef COP3530_PROJECT3_GROUP9_MOVIEHASHMAP_H
#define COP3530_PROJECT3_GROUP9_MOVIEHASHMAP_H

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class movieHashMap {

private:
    unordered_map<string,vector<string>> movies;

public:
    void insertMovie(string name, string year, string genre, string rating);
    void titleSearch(string name);
    void yearFilter(string year);
    void genreFilter(string genre);
    void ratingByGenre(string genre);

};


#endif //COP3530_PROJECT3_GROUP9_MOVIEHASHMAP_H
