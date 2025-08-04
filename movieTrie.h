//
// Created by Sydney Fung on 8/2/25.
//

#ifndef MOVIETRIE_H
#define MOVIETRIE_H

#include <string>
#include <iostream>

using namespace std;

/*
Trie trie;
trie.parseCSV("movies.csv");
 */

using namespace std;

struct Movie {
    char title[100];
    char genre[50];
    int year;
    float rating;
};

struct TrieNode {
    TrieNode* children[128];
    bool end;
    Movie* movie;

    TrieNode();
};

class MovieTrie {
private:
    TrieNode* root;
    Movie movieList[800000];
    int movieCount;

    void collectAllFromNode(TrieNode* node, Movie* results[], int& count, int maxResults);

public:
    MovieTrie();
    ~MovieTrie();

    bool insertMovie(const char* title, const char* genre, int year, float rating);
    Movie* titleSearch(const char* title);
    int genreSearch(const char* genre, Movie* results[], int maxResults);
    int yearSearch(int year, Movie* results[], int maxResults);
    int ratingsSearch(float minRating, float maxRating, Movie* results[], int maxResults);
};

void printTitles(MovieTrie* trie, const string& title);
void printGenre(MovieTrie* trie, const string& genre);
void printYear(MovieTrie* trie, int year);
void printRatings(MovieTrie* trie, float lowerRate, float upperRate);
void printMovie(const Movie* m);

#endif
