#ifndef MOVIETRIE_H
#define MOVIETRIE_H

#include <string>
#include <iostream>

using namespace std;

/*
Trie trie;
trie.parseCSV("movies.csv");
*/

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
    Movie *movie; // holds a movie object

    TrieNode(); // constructor
};

class MovieTrie {
    TrieNode *root; // each trie has a root node
    Movie movieList[800000]; // an array with max 800,000 movies
    int movieCount; // how many movies

    void collectAllFromNode(TrieNode *node, Movie *results[], int &count, int maxResults);

    // collect data from the movies

public:
    MovieTrie(); // constructs trie structure
    ~MovieTrie(); // destructor

    // inserts movies into trie structure
    // initialize this, it is not called
    bool insertMovie(const char *title, const char *genre, int year, float rating);

    void parseCVS(string &file);

    // returns movie object based on title searched
    Movie *titleSearch(const char *title);


    int genreSearch(const char *genre, Movie *results[], int maxResults);

    int yearSearch(int year, Movie *results[], int maxResults);

    int ratingsSearch(float minRating, float maxRating, Movie *results[], int maxResults);
};


void printTitles(MovieTrie *trie, const string &title);

void printGenre(MovieTrie *trie, const string &genre);

void printYear(MovieTrie *trie, int year);

void printRatings(MovieTrie *trie, float lowerRate, float upperRate);

void printMovie(const Movie *m);


#endif
