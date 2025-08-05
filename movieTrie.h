#ifndef MOVIETRIE_H
#define MOVIETRIE_H

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

struct Movie {
    // Where data on each movie is stored
    char title[100];
    char genre[50];
    int year;
    float rating;
};

struct TrieNode {
    // node for the trie structure
    TrieNode *children[128]; // each node that has children for each ascii character
    bool end; // for end of title
    vector<Movie *> movies; // vector of movie objects

    TrieNode(); // constructor
    ~TrieNode(); // destructor
};

class MovieTrie {
    TrieNode *rootTitle; // title trie has a root node
    TrieNode *rootGenre; // genre trie has a root node
    TrieNode *rootYear; // year trie has a root node
    TrieNode *rootRating; // rating trie has a root node

    Movie *movieList;
    int movieCount; // how many movies

    void collectAllFromNode(TrieNode *node, Movie *results[], int &count, int maxResults);

    // collect data from the movies

public:
    MovieTrie(); // constructs trie structure
    ~MovieTrie(); // destructor

    // inserts movies into trie structure
    // initialize this, it is not called unless testinf
    void insertMovie(const char *title, int year, const char *genre, float rating);

    // parses through CSV file and inputs into trie
    void parseCSV(const string &filename);

    // returns movie object based on title searched
    Movie *titleSearch(const char *title);

    // searches through genre trie
    int genreSearch(const char *genre, Movie *results[], int maxResults);

    // searches through year trie
    int yearSearch(int year, Movie *results[], int maxResults);

    // searches through ratings trie
    int ratingsSearch(float minRating, float maxRating, Movie *results[], int maxResults);

    // prints movies based on title trie
    void printTitles(const string &title);

    // prints movies based on genre trie
    void printGenre(const string &genre);

    // prints movies based on year trie
    void printYear(int year);

    // prints movies based on movies array
    void printRatings(float lowerRate, float upperRate);

    // prints movies
    void printMovie(const Movie *m);
};


#endif
