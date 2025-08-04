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

    //hashing based similar to Geeks for Geeks example of hashMap and hashing in data structure and some of COP3530 lectures and discussions
    vector<vector<pair<string, vector<string>>>> movies; //vector of vectors and the inner vector is storing the key value pairs
    int size; //for current size
    int capacity; //for capacity of buckets
    int hash(const string& key) const; //hashing function
    void insert(const string& key, const vector<string>& value); //core insertion function

public:
    void titleSearch(string name);
    void yearFilter(int year);
    void genreFilter(string genre);
    void ratingByGenre(string genre);
    vector<string> splitGenre(string genre);
    void parsingDataSet(string name);
    movieHashMap(int initialC = 10);
    void insertMovie(string name, int year, string genre, int rating);
    void ratingByRange(float minRating, float maxRating);
};


#endif //COP3530_PROJECT3_GROUP9_MOVIEHASHMAP_H

