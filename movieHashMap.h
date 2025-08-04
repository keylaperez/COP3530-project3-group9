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
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

class movieHashMap {

private:

    vector<vector<pair<string, vector<string>>>> movies;
    int size;
    int capacity;

    int hash(const string& key) const;

public:
    void titleSearch(string name);
    void yearFilter(int year);
    void genreFilter(string genre);
    void ratingByGenre(string genre);
    vector<string> splitGenre(string genre);
    void parsingDataSet(string name);
    movieHashMap(int initialC = 10);
    void insert(const string& key, const vector<string>& value);
    bool get(const string& key, vector<string>& value) const;
    void remove(const string& key);
    void insertMovie(string name, int year, string genre, int rating);
    void ratingByRange(float minRating, float maxRating);
};


#endif //COP3530_PROJECT3_GROUP9_MOVIEHASHMAP_H

