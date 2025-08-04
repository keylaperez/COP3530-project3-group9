#include "movieTrie.h"
#include <cstring>


TrieNode::TrieNode() {
    end = false; // initially false
    movie = nullptr; // no movies yet
    for (int i = 0; i < 128; ++i) {
        children[i] = nullptr; // nothing in the children
    }
}


MovieTrie::MovieTrie() {
    root = new TrieNode(); // new node for root
    movieCount = 0; // count initially 0
    movieList = new Movie[8000];
    //parseCSV("movies.csv");
}


static void deleteNode(TrieNode *node) {
    if (!node) return;
    for (int i = 0; i < 128; ++i) {
        deleteNode(node->children[i]);
    }
    delete node;
}


MovieTrie::~MovieTrie() {
    deleteNode(root);
    delete[] movieList;
}


void MovieTrie::insertMovie(const char *title, int year, const char *genre, float rating) {
    if (movieCount >= 800000) {
        // 800,000 max movie count
        return; // unsuccessful
    }


    Movie &m = movieList[movieCount]; // reference array of movies
    strncpy(m.title, title, 100); //https://cplusplus.com/reference/cstring/strncpy/
    m.title[100 - 1] = '\0';
    strncpy(m.genre, genre, 50);
    m.genre[50 - 1] = '\0';
    m.year = year;
    m.rating = rating;


    // each character in the title is added to the trie
    TrieNode *node = root;
    for (int i = 0; title[i] != '\0'; ++i) {
        unsigned char ch = static_cast<unsigned char>(title[i]);
        if (!node->children[ch]) {
            node->children[ch] = new TrieNode();
        }
        node = node->children[ch];
    }


    node->end = true; // this node has reached the end of the movie title
    node->movie = &m; // now this node is assigned with the movie object


    movieCount++; // amt of movies updated
    //return; // successful!
}


void MovieTrie::parseCVS(string &file) {
    cout << "hi";
}


Movie *MovieTrie::titleSearch(const char *title) {
    // given character array of title
    TrieNode *node = root;
    for (int i = 0; title[i] != '\0'; ++i) {
        // traverse trie using each letter and each node
        unsigned char ch = static_cast<unsigned char>(title[i]);
        if (!node->children[ch]) {
            return nullptr;
        }
        node = node->children[ch];
    }
    if (node->end) {
        // this is at the end of a title
        return node->movie; // return movie
    }
    return nullptr;
}


void MovieTrie::collectAllFromNode(TrieNode *node, Movie *results[], int &count, int maxResults) {
    if (!node || count >= maxResults) {
        return; // stoppppp
    }


    if (node->end && count < maxResults) {
        results[count++] = node->movie; // reached the end of a movie title so add to results array
    }


    for (int i = 0; i < 128; ++i) {
        if (node->children[i]) {
            collectAllFromNode(node->children[i], results, count, maxResults); // recursively go thru movies
        }
    }
}


int MovieTrie::genreSearch(const char *genre, Movie *results[], int maxResults) {
    int count = 0;
    for (int i = 0; i < movieCount && count < maxResults; ++i) {
        // goes thru movies
        if (strcmp(movieList[i].genre, genre) == 0) {
            // https://cplusplus.com/reference/cstring/strcmp/
            results[count++] = &movieList[i]; // traverse movie list for genre
        }
    }
    return count;
}


int MovieTrie::yearSearch(int year, Movie *results[], int maxResults) {
    int count = 0;
    for (int i = 0; i < movieCount && count < maxResults; ++i) {
        if (movieList[i].year == year) {
            results[count++] = &movieList[i]; // traverse movie list for year
        }
    }
    return count;
}


int MovieTrie::ratingsSearch(float minRating, float maxRating, Movie *results[], int maxResults) {
    int count = 0;
    for (int i = 0; i < movieCount && count < maxResults; ++i) {
        if (movieList[i].rating >= minRating && movieList[i].rating <= maxRating) {
            results[count++] = &movieList[i]; // traverse movie list for rating
        }
    }
    return count;
}


void MovieTrie::printTitles(const string &title) {
    // print movies with title
    Movie *result = titleSearch(title.c_str());
    if (result) {
        printMovie(result);
    } else {
        cout << "No movie found with title: " << title << "\n";
    }
}


void MovieTrie::printGenre(const string &genre) {
    // print movies with genre
    Movie *results[100];
    int found = genreSearch(genre.c_str(), results, 100);
    //cout << "\nMovies with genre '" << genre << "': " << found << "\n";
    for (int i = 0; i < found; ++i) {
        printMovie(results[i]);
    }
}


void MovieTrie::printYear(int year) {
    // print movies with year
    Movie *results[100];
    int found = yearSearch(year, results, 100);
    //cout << "\nMovies from year " << year << ": " << found << "\n";
    for (int i = 0; i < found; ++i) {
        printMovie(results[i]);
    }
}


void MovieTrie::printRatings(float lowerRate, float upperRate) {
    // print movies with ratings
    Movie *results[100];
    int found = ratingsSearch(lowerRate, upperRate, results, 100);
    //cout << "\nMovies with ratings between " << lowerRate << " and " << upperRate << ": " << found << "\n";
    for (int i = 0; i < found; ++i) {
        printMovie(results[i]);
    }
}


void MovieTrie::printMovie(const Movie *m) {
    cout << "Title: " << m->title
            << "| Year: " << m->year
            << "| Genre: " << m->genre
            << "| Rating: " << m->rating << "\n";
}
