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
    movieList = new Movie[8000]; // 8000 for storage purposes
    //parseCSV("movies.csv"); // add everything into this trie
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
        return; // unsuccessful if exceeds array size
    }

    // update values in movie object
    Movie &mov = movieList[movieCount]; // reference array of movies
    strncpy(mov.title, title, sizeof(mov.title)); //https://cplusplus.com/reference/cstring/strncpy/
    mov.title[sizeof(mov.title) - 1] = '\0';
    strncpy(mov.genre, genre, sizeof(mov.genre));
    mov.genre[sizeof(mov.genre) - 1] = '\0';
    mov.year = year;
    mov.rating = rating;
    Movie* movPtr = &mov; // make a pointer to that movie object

    // each character in the title is added to the title trie
    TrieNode* node = rootTitle;
    for (int i = 0; title[i] != '\0'; ++i) {
        unsigned char ch = static_cast<unsigned char>(title[i]);
        if (!node->children[ch]) {
            node->children[ch] = new TrieNode();
        }
        node = node->children[ch];
        node->movies.push_back(movPtr);
    }

    node->end = true; // this node has reached the end of the movie title

    // Genre trie added in parse function

    // Year trie
    char yearStr[5];
    snprintf(yearStr, sizeof(yearStr), "%d", year); // https://cplusplus.com/reference/cstdio/snprintf/
    node = rootYear;
    for (int i = 0; yearStr[i]; ++i) {
        unsigned char ch = static_cast<unsigned char>(yearStr[i]);
        if (!node->children[ch])
            node->children[ch] = new TrieNode();
        node = node->children[ch];
        node->movies.push_back(movPtr);
    }
    node->end = true;

    // Rating trie
    char ratingStr[10];
    snprintf(ratingStr, sizeof(ratingStr), "%.1f", rating);
    node = rootRating;
    for (int i = 0; ratingStr[i]; ++i) {
        unsigned char ch = static_cast<unsigned char>(ratingStr[i]);
        if (!node->children[ch])
            node->children[ch] = new TrieNode();
        node = node->children[ch];
        node->movies.push_back(movPtr);
    }
    node->end = true;

    movieCount++; // amt of movies updated
}

void MovieTrie::parseCSV(const std::string &filename) {
    ifstream file(filename); // read file
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << "\n"; // in case it is not opened
        return;
    }

    string line;
    // ex: Lightyear,"['Animation', 'Action', 'Adventure']",2022,5.2
    getline(file, line); // skips the header

    while (getline(file, line)) {
        // traverse file
        stringstream ss(line); // https://cplusplus.com/reference/cstdio/snprintf/
        string title, genreStr, yearStr, ratingStr;

        if (!getline(ss, title, ',') || !getline(ss, genreStr, ',')) {
            continue; // if title/genre doesn't exist then skip (troubleshooting)
        }

        if (!genreStr.empty() && genreStr[0] == '"') { // genre has quotes
            string temp;
            while (!genreStr.empty() && genreStr[genreStr.size() - 1] != '"' && getline(ss, temp, ',')) {
                genreStr += "," + temp;
            }
            if (!genreStr.empty() && genreStr[0] == '"') {
                genreStr.erase(0, 1);
            }
            if (!genreStr.empty() && genreStr[genreStr.size() - 1] == '"') {
                genreStr.erase(genreStr.size() - 1, 1);
            }

        }

        if (!getline(ss, yearStr, ',') || !getline(ss, ratingStr, ',')) {
            continue; // if year and ratings don't exist (troubleshooting)
        }

        try {
            int year = stoi(yearStr); // int year
            float rating = stof(ratingStr); // float rating

            // remove [,], and ' in the genreStr
            genreStr.erase(remove(genreStr.begin(), genreStr.end(), '['), genreStr.end());
            genreStr.erase(remove(genreStr.begin(), genreStr.end(), ']'), genreStr.end());
            genreStr.erase(remove(genreStr.begin(), genreStr.end(), '\''), genreStr.end());

            size_t pos = 0; // https://en.cppreference.com/w/cpp/types/size_t.html
            while ((pos = genreStr.find(", ", pos)) != string::npos) {
                genreStr.replace(pos, 2, ","); // replace ", " with ","
            }

            insertMovie(title.c_str(), year, genreStr.c_str(), rating); // insert movie with that data

            // add to genre trie
            Movie *movPtr = &movieList[movieCount - 1]; // pointer to that movie

            stringstream genreSS(genreStr);
            string individualGenre;
            while (getline(genreSS, individualGenre, ',')) { // parse through genre string
                individualGenre.erase(remove_if(individualGenre.begin(), individualGenre.end(), ::isspace),individualGenre.end());

                if (!individualGenre.empty()) { // till genre string not empty
                    TrieNode* node = rootGenre;
                    for (char ch: individualGenre) {
                        unsigned char child = static_cast<unsigned char>(ch);
                        if (!node->children[child]) {
                            node->children[child] = new TrieNode(); // new node if none exist
                        }
                        node = node->children[child];
                        node->movies.push_back(movPtr);
                    }
                    node->end = true;
                }
            }
        } catch (...) { continue;} // skips anything invalid
    }
    file.close(); // done
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
        return; // unsuccessful if exceeds count or doesn't exist
    }

    for (Movie *m: node->movies) { // iterate over each movie pointer
        if (count >= maxResults) {
            break;
        }
        results[count++] = m;
    }
    for (int i = 0; i < 128; ++i) { // traverse recursively through each child
        if (node->children[i]) {
            collectAllFromNode(node->children[i], results, count, maxResults); // recursively go thru movies
        }
    }
}

int MovieTrie::genreSearch(const char *genre, Movie *results[], int maxResults) {
    TrieNode* node = rootGenre;
    for (int i = 0; genre[i]; ++i) { // traverse down tree
        unsigned char ch = static_cast<unsigned char>(genre[i]);
        if (!node->children[ch]) {return 0;}
        node = node->children[ch];
    }

    int count = 0;
    for (Movie *mov: node->movies) {
        if (count >= maxResults) {break;}
        results[count++] = mov; // collects the resulting movies
    }
    return count;
}

int MovieTrie::yearSearch(int year, Movie *results[], int maxResults) {
    char yearStr[5]; // year should only be four nums long
    snprintf(yearStr, sizeof(yearStr), "%d", year);
    TrieNode* node = rootYear;
    for (int i = 0; yearStr[i]; ++i) { // traverse down
        unsigned char ch = static_cast<unsigned char>(yearStr[i]);
        if (!node->children[ch]) return 0;
        node = node->children[ch];
    }

    int count = 0;
    for (Movie *m: node->movies) {
        if (count >= maxResults) break;
        results[count++] = m; // resulting movies
    }
    return count;
}

int MovieTrie::ratingsSearch(float minRating, float maxRating, Movie *results[], int maxResults) {
    int count = 0;
    for (int i = 0; i < movieCount && count < maxResults; ++i) { // traversal
        if (movieList[i].rating >= minRating && movieList[i].rating <= maxRating)
            results[count++] = &movieList[i];
    }
    return count;
}

void MovieTrie::printTitles(const string &title) {
    // print movies with title
    Movie* result = titleSearch(title.c_str());
    if (result) {
        printMovie(result);
    } else {
        cout << "No movie found with title: " << title << "\n";
    }
}

void MovieTrie::printGenre(const string &genre) {
    // print movies with genre
    Movie* results[100];
    int found = genreSearch(genre.c_str(), results, 100);
    //cout << "\nMovies with genre '" << genre << "': " << found << "\n";
    for (int i = 0; i < found && i < 10; ++i) {
        printMovie(results[i]);
    }
}

void MovieTrie::printYear(int year) {
    // print movies with year
    Movie* results[100];
    int found = yearSearch(year, results, 100);
    //cout << "\nMovies from year " << year << ": " << found << "\n";
    for (int i = 0; i < found && i < 10; ++i) {
        printMovie(results[i]);
    }
}

void MovieTrie::printRatings(float lowerRate, float upperRate) {
    // print movies with ratings
    Movie* results[100];
    int found = ratingsSearch(lowerRate, upperRate, results, 100);
    //cout << "\nMovies with ratings between " << lowerRate << " and " << upperRate << ": " << found << "\n";
    for (int i = 0; i < found && i < 10; ++i) {
        printMovie(results[i]);
    }
}

void MovieTrie::printMovie(const Movie *mov) {
    cout << "Title: " << mov->title
            << " | Year: " << mov->year
            << " | Rating: " << mov->rating
            << " | Genre(s): " << mov->genre << "\n";
}
