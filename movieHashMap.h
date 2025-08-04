//
// Created by Winni Weng on 8/2/25.
//

#ifndef COP3530_PROJECT3_GROUP9_MOVIEHASHMAP_H
#define COP3530_PROJECT3_GROUP9_MOVIEHASHMAP_H

#include <iostream>
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
    movieHashMap(int initialC = 10);
    void titleSearch(string name); //searching by title
    void yearFilter(int year);// filters through by year specified
    void genreFilter(string genre); //searches through genre for specified
    void parsingDataSet(string name); //used to parse in the data set
    void insertMovie(string name, int year, string genre, int rating); //inserting movie helper
    void ratingByRange(float minRating, float maxRating); //looking for movies within range specified
};


#endif //COP3530_PROJECT3_GROUP9_MOVIEHASHMAP_H

