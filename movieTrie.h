//
// Created by Sydney Fung on 8/2/25.
//

#ifndef MOVIETRIE_H
#define MOVIETRIE_H

#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;


class movieTrie {
private:
    unordered_map<string,vector<string>> movies;

public:
    void insertMovie(string name, string year, string genre, string rating);
    void titleSearch(string name);
    void yearFilter(string year);
    void genreFilter(string genre);
    void ratingByGenre(string genre);
};



#endif //MOVIETRIE_H
