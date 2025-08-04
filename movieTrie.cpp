//
// Created by Sydney Fung on 8/2/25.
//

#include "movieTrie.h"
#include <cstring>

TrieNode::TrieNode() {
    end = false;
    movie = nullptr;
    for (int i = 0; i < 128; ++i) {
        children[i] = nullptr;
    }
}

MovieTrie::MovieTrie() {
    root = new TrieNode();
    movieCount = 0;
}

static void deleteNode(TrieNode* node) {
    if (!node) return;
    for (int i = 0; i < 128; ++i) {
        deleteNode(node->children[i]);
    }
    delete node;
}

MovieTrie::~MovieTrie() {
    deleteNode(root);
}

bool MovieTrie::insertMovie(const char* title, const char* genre, int year, float rating) {
    if (movieCount >= 800000) return false;

    Movie& m = movieList[movieCount];
    strncpy(m.title, title, 100);
    m.title[100 - 1] = '\0';
    strncpy(m.genre, genre, 50);
    m.genre[50 - 1] = '\0';
    m.year = year;
    m.rating = rating;

    TrieNode* node = root;
    for (int i = 0; title[i] != '\0'; ++i) {
        unsigned char ch = static_cast<unsigned char>(title[i]);
        if (!node->children[ch]) {
            node->children[ch] = new TrieNode();
        }
        node = node->children[ch];
    }

    node->end = true;
    node->movie = &m;

    movieCount++;
    return true;
}

Movie* MovieTrie::titleSearch(const char* title) {
    TrieNode* node = root;
    for (int i = 0; title[i] != '\0'; ++i) {
        unsigned char ch = static_cast<unsigned char>(title[i]);
        if (!node->children[ch]) {
            return nullptr;
        }
        node = node->children[ch];
    }
    return node->end ? node->movie : nullptr;
}

void MovieTrie::collectAllFromNode(TrieNode* node, Movie* results[], int& count, int maxResults) {
    if (!node || count >= maxResults) return;

    if (node->end && count < maxResults) {
        results[count++] = node->movie;
    }

    for (int i = 0; i < 128; ++i) {
        if (node->children[i]) {
            collectAllFromNode(node->children[i], results, count, maxResults);
        }
    }
}

int MovieTrie::genreSearch(const char* genre, Movie* results[], int maxResults) {
    int count = 0;
    for (int i = 0; i < movieCount && count < maxResults; ++i) {
        if (strcmp(movieList[i].genre, genre) == 0) {
            results[count++] = &movieList[i];
        }
    }
    return count;
}

int MovieTrie::yearSearch(int year, Movie* results[], int maxResults) {
    int count = 0;
    for (int i = 0; i < movieCount && count < maxResults; ++i) {
        if (movieList[i].year == year) {
            results[count++] = &movieList[i];
        }
    }
    return count;
}

int MovieTrie::ratingsSearch(float minRating, float maxRating, Movie* results[], int maxResults) {
    int count = 0;
    for (int i = 0; i < movieCount && count < maxResults; ++i) {
        if (movieList[i].rating >= minRating && movieList[i].rating <= maxRating) {
            results[count++] = &movieList[i];
        }
    }
    return count;
}

// --- Utility Print Functions ---
void printTitles(MovieTrie* trie, const string& title) {
    Movie* result = trie->titleSearch(title.c_str());
    if (result) {
        printMovie(result);
    } else {
        cout << "No movie found with title: " << title << "\n";
    }
}

void printGenre(MovieTrie* trie, const string& genre) {
    Movie* results[100];
    int found = trie->genreSearch(genre.c_str(), results, 100);
    cout << "\nMovies with genre '" << genre << "': " << found << "\n";
    for (int i = 0; i < found; ++i) {
        printMovie(results[i]);
    }
}

void printYear(MovieTrie* trie, int year) {
    Movie* results[100];
    int found = trie->yearSearch(year, results, 100);
    cout << "\nMovies from year " << year << ": " << found << "\n";
    for (int i = 0; i < found; ++i) {
        printMovie(results[i]);
    }
}

void printRatings(MovieTrie* trie, float lowerRate, float upperRate) {
    Movie* results[100];
    int found = trie->ratingsSearch(lowerRate, upperRate, results, 100);
    cout << "\nMovies with ratings between " << lowerRate << " and " << upperRate << ": " << found << "\n";
    for (int i = 0; i < found; ++i) {
        printMovie(results[i]);
    }
}

void printMovie(const Movie* m) {
    cout << "Title: " << m->title
         << ", Genre: " << m->genre
         << ", Year: " << m->year
         << ", Rating: " << m->rating << "\n";
}
