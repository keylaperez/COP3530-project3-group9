//
// Created by Winni Weng on 8/2/25.
//

#include "movieHashMap.h"


int movieHashMap::hash(const string& key) const { //hashing to return where the movie should be
    int h = 0;
    for (char c : key) {
        h = h*31 + c;
    }
    return (h % capacity + capacity) % capacity;
}

movieHashMap::movieHashMap(int initialC) : size(0), capacity(initialC) { //constructor for our structure initalizing it
    movies.resize(capacity);
}

void movieHashMap::insert(const string& key, const vector<string>& value) { //inserting core
    int index = hash(key);
    movies[index].push_back({key, value});
    size++;

    if (size > capacity * 0.75) { //if capacity is at 75% then we gotta resize
        capacity *= 2;
        vector<vector<pair<string, vector<string>>>> newBuckets(capacity); //putting in new bucket
        for (auto& bucket : movies) {
            for (auto& p : bucket) {
                int newIndex = hash(p.first);
                newBuckets[newIndex].push_back(p);
            }
        }
        movies = move(newBuckets); //changing buckets
    }
}

void movieHashMap::insertMovie(string name, int year, string genre, int rating) { //helperInsert from outside with the variables
    vector<string> info = {to_string(year), to_string(rating), genre};
    insert(name, info);
}

std::string toLower(const std::string& str) { //for capitialization stuff so that way we can search uppercase or lowercase
    std::string lower = str;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    return lower;
}

void movieHashMap::genreFilter(std::string genre) { //genre filter, looping through and if genre is found then we print it out with a max of 10

    int count = 0;

    for (const auto& bucket : movies) {
        for (const auto& pair : bucket) {
            const string& title = pair.first;
            const vector<string>& info = pair.second;

            string currentGenre = info[2];

            if (currentGenre.find(genre) != string::npos) { //if the genre is found then we print it
                cout << "Title: " << title;
                cout << " | Year: " << info[0];
                cout << " | Rating: " << info[1];
                cout << " | Genre(s): " << info[2] << endl;

                count++;
                if (count == 10) { //for counter if results over 10 then we stop because too much data
                    return;
                }
            }
        }
    }


}

void movieHashMap::ratingByRange(float minRating, float maxRating) { //between two ratings print the first ten movies

    vector<pair<string, vector<string>>> matchingMovies; // loop of matching movies

    for (const auto& bucket : movies) {
        for (const auto& pair : bucket) {
            const string& title = pair.first;
            const vector<string>& info = pair.second;

            float currentRating = stof(info[1]);

            if (currentRating >= minRating && currentRating <= maxRating) { //putting in the loop
                matchingMovies.push_back({title, info});
            }
        }
    }

    if (matchingMovies.empty()) { // if matching movies loop is empty then print out
        cout << "No movies found in the rating range " << minRating << " to " << maxRating << "." << endl;
        return;
    }
    int count = 0;

    for (const auto& movie : matchingMovies) { //looping through the first ten movies that match the rating
        cout << "Title: " << movie.first;
        cout << " | Year: " << movie.second[0];
        cout << " | Rating: " << movie.second[1];
        cout << " | Genre(s): " << movie.second[2] << endl;

        count++;
        if (count == 10) { //for counter if results over 10 then we stop because too much data
            return;
        }
    }
}

void movieHashMap::titleSearch(std::string name) { //searching for title with specified string

    int count = 0;
    for (const auto& bucket : movies) {
        for (const auto &pair: bucket) {
            const string &title = pair.first;
            const vector<string> &info = pair.second;

            string currentTitle = title;

            if (toLower(currentTitle).find(toLower(name)) != std::string::npos) { //if title is found then prints movie out
                cout << "Title: " << title;
                cout << " | Year: " << info[0];
                cout << " | Rating: " << info[1];
                cout << " | Genre(s): " << info[2] << endl;

                count++;
                if (count == 10) { //for counter if results over 10 then we stop because too much data
                    return;
                }

            }
        }
    }

}

void movieHashMap::parsingDataSet(std::string name) { //for parsing in the movie set
    ifstream file(name); // read file
    if (!file.is_open()) {
        cerr << "Error opening file: " << name << "\n"; // in case it is not opened
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
            genreStr.erase(std::remove(genreStr.begin(), genreStr.end(), '['), genreStr.end());
            genreStr.erase(std::remove(genreStr.begin(), genreStr.end(), ']'), genreStr.end());
            genreStr.erase(std::remove(genreStr.begin(), genreStr.end(), '\''), genreStr.end());

            size_t pos = 0; // https://en.cppreference.com/w/cpp/types/size_t.html
            while ((pos = genreStr.find(", ", pos)) != string::npos) {
                genreStr.replace(pos, 2, ","); // replace ", " with ","
            }

            insertMovie(title, year, genreStr, static_cast<int>(rating)); // insert movie with that data

        } catch (...) { continue;} // skips anything invalid
    }
    file.close(); // done
}

void movieHashMap::yearFilter(int year) { //filter by year

    int count = 0;

    for (const auto &bucket: movies) {
        for (const auto &pair: bucket) {
            const string &title = pair.first;
            const vector<string> &info = pair.second;

            if (year == stoi(info[0])) { //if year matches then prints movie out
                cout << "Title: " << title;
                cout << " | Year: " << info[0];
                cout << " | Rating: " << info[1];
                cout << " | Genre(s): " << info[2] << endl;

                count++;
                if (count == 10) { //for counter if results over 10 then we stop because too much data
                    return;
                }

            }
        }

    }
}
