#include "movieTrie.h"
#include <cstring>


TrieNode::TrieNode() {
    end = false; // initially false
    for (int i = 0; i < 128; ++i) {
        children[i] = nullptr; // nothing in the children
    }
}

TrieNode::~TrieNode() {
    for (int i = 0; i < 128; ++i)
        delete children[i]; // recursively deletes children
}


MovieTrie::MovieTrie() {
    rootTitle = new TrieNode(); // new root for each trie
    rootGenre = new TrieNode();
    rootYear = new TrieNode();
    rootRating = new TrieNode();
    movieCount = 0; // count initially 0
    movieList = new Movie[8000];
    //parseCSV("movies.csv");
}

MovieTrie::~MovieTrie() {
    delete rootTitle;
    delete rootGenre;
    delete rootYear;
    delete rootRating;
    delete[] movieList;
}


void MovieTrie::insertMovie(const char *title, int year, const char *genre, float rating) {
    if (movieCount >= 8000) {
        // 8,000 max movie count
        return; // unsuccessful
    }


    Movie &m = movieList[movieCount]; // reference array of movies
    strncpy(m.title, title, sizeof(m.title)); //https://cplusplus.com/reference/cstring/strncpy/
    m.title[sizeof(m.title) - 1] = '\0';
    strncpy(m.genre, genre, sizeof(m.genre));
    m.genre[sizeof(m.genre) - 1] = '\0';
    m.year = year;
    m.rating = rating;
    Movie *mPtr = &m;


    // each character in the title is added to the title trie
    TrieNode *node = rootTitle;
    for (int i = 0; title[i] != '\0'; ++i) {
        unsigned char ch = static_cast<unsigned char>(title[i]);
        if (!node->children[ch]) {
            node->children[ch] = new TrieNode();
        }
        node = node->children[ch];
        node->movies.push_back(mPtr);
    }

    node->end = true; // this node has reached the end of the movie title

    // Genre trie
    node = rootGenre;
    for (int i = 0; genre[i]; ++i) {
        unsigned char c = static_cast<unsigned char>(genre[i]);
        if (!node->children[c])
            node->children[c] = new TrieNode();
        node = node->children[c];
        node->movies.push_back(mPtr);
    }
    node->end = true;

    // Year trie
    char yearStr[5];
    snprintf(yearStr, sizeof(yearStr), "%d", year);
    node = rootYear;
    for (int i = 0; yearStr[i]; ++i) {
        unsigned char c = static_cast<unsigned char>(yearStr[i]);
        if (!node->children[c])
            node->children[c] = new TrieNode();
        node = node->children[c];
        node->movies.push_back(mPtr);
    }
    node->end = true;

    // Rating trie
    char ratingStr[10];
    snprintf(ratingStr, sizeof(ratingStr), "%.1f", rating);
    node = rootRating;
    for (int i = 0; ratingStr[i]; ++i) {
        unsigned char c = static_cast<unsigned char>(ratingStr[i]);
        if (!node->children[c])
            node->children[c] = new TrieNode();
        node = node->children[c];
        node->movies.push_back(mPtr);
    }
    node->end = true;

    movieCount++; // amt of movies updated
    //return; // successful!
}


void MovieTrie::parseCVS(string &file) {
    cout << "hi";
}


Movie *MovieTrie::titleSearch(const char *title) {
    // given character array of title
    TrieNode *node = rootTitle;
    for (int i = 0; title[i] != '\0'; ++i) {
        // traverse trie using each letter and each node
        unsigned char ch = static_cast<unsigned char>(title[i]);
        if (!node->children[ch]) {
            return nullptr;
        }
        node = node->children[ch];
    }
    if (node->end && !node->movies.empty()) {
        // this is at the end of a title and there is a movie there
        return node->movies[node->movies.size() - 1]; // return movie
    }
    return nullptr;
}


void MovieTrie::collectAllFromNode(TrieNode *node, Movie *results[], int &count, int maxResults) {
    if (!node || count >= maxResults) {
        return; // stoppppp
    }


    for (Movie *m: node->movies) {
        if (count >= maxResults) {
            break;
        }
        results[count++] = m;
    }


    for (int i = 0; i < 128; ++i) {
        if (node->children[i]) {
            collectAllFromNode(node->children[i], results, count, maxResults); // recursively go thru movies
        }
    }
}


int MovieTrie::genreSearch(const char *genre, Movie *results[], int maxResults) {
    TrieNode *node = rootGenre;
    for (int i = 0; genre[i]; ++i) {
        unsigned char c = static_cast<unsigned char>(genre[i]);
        if (!node->children[c]) return 0;
        node = node->children[c];
    }

    int count = 0;
    for (Movie *m: node->movies) {
        if (count >= maxResults) break;
        results[count++] = m;
    }
    return count;
}


int MovieTrie::yearSearch(int year, Movie *results[], int maxResults) {
    char yearStr[5];
    snprintf(yearStr, sizeof(yearStr), "%d", year);
    TrieNode *node = rootYear;
    for (int i = 0; yearStr[i]; ++i) {
        unsigned char c = static_cast<unsigned char>(yearStr[i]);
        if (!node->children[c]) return 0;
        node = node->children[c];
    }

    int count = 0;
    for (Movie *m: node->movies) {
        if (count >= maxResults) break;
        results[count++] = m;
    }
    return count;
}


int MovieTrie::ratingsSearch(float minRating, float maxRating, Movie *results[], int maxResults) {
    int count = 0;
    for (int i = 0; i < movieCount && count < maxResults; ++i) {
        if (movieList[i].rating >= minRating && movieList[i].rating <= maxRating)
            results[count++] = &movieList[i];
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
