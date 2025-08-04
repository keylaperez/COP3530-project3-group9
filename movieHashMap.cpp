//
// Created by Winni Weng on 8/2/25.
//

#include "movieHashMap.h"

vector<string> movieHashMap::splitGenre(std::string genreStr) { //splitting the different genres up
    vector <string> genres;
    string temp;

    for (char c : genreStr) {
        if (c == '-') {
            if (!temp.empty()) {
                genres.push_back(temp);
                temp.clear();
            }
        } else {
            temp += c;
        }
    }

    if (!temp.empty()) {
        genres.push_back(temp);
    }

    return genres;
}

void movieHashMap::genreFilter(std::string genre) {

    for (const auto& pair : movies) { //looping through movies
        string title = pair.first;
        vector<string> info = pair.second;

        string currentGenre = info[2];

        if (currentGenre.find(genre) != std::string::npos) { //if genre is found then prints movie out
            cout << "Title: " << title;
            cout << " | Year: " << info[0];
            cout << " | Rating: " << info[1];
            cout << " | Genre(s): " << info[2] << endl;

        }
    }


}

void movieHashMap::insertMovie(std::string name, int year, std::string genre, int rating) { //inserting movie in the unordered map

    movies[name].push_back(to_string(year));
    movies[name].push_back(to_string(rating));
    movies[name].push_back(genre);

    //below is just in case if we need to splitGenre again while inserting

//    vector<string> genreList = splitGenre(genre);
//
//    for (int i = 0; i < genreList.size(); i++) { //inserting each genre
//        movies[name].push_back(genreList[i]);
//    }


}

void movieHashMap::ratingByGenre(string genre) { //user selects a genre and system prints out top movie for it
    vector<pair<string, vector<string>>> topMovies;
    int highestRating = 0;

    for (const auto& pair : movies) { //looping through movies
        string title = pair.first;
        vector<string> info = pair.second;
        int currentRating = stoi(info[1]);
        string currentGenre = info[2];

        if (currentGenre.find(genre) != std::string::npos) { //if find string finds the genre
            if (topMovies.empty() || currentRating > highestRating) { //checks if top movies is empty of if new one found is better rating
                topMovies.clear();
                topMovies.push_back({title, info});
                highestRating = currentRating;

            } else if (currentRating == highestRating) { //if same rating then we add
                topMovies.push_back({title, info});
            }

        }
    }

    for (int i = 0; i < topMovies.size(); i++) { //printing each genre

        cout << "Genre: " << genre << endl;
        cout << "Top movie: " << topMovies[i].first;
        cout << " | Year: " << topMovies[i].second[0];
        cout << " | Rating: " << topMovies[i].second[1];
        cout << " | Genre(s): " << topMovies[i].second[2] << endl;
    }

}

    //below is for if we wanted to print out every genre and its top movie again. Currently not using it for the option
//    unordered_map<string, vector<string>> bestGenres;
//
//    for (const auto& pair : movies) { //loops through each movie and puts the top in bestGenres map
//        string title = pair.first;
//        vector<string> info = pair.second;
//
//        vector<string> genreList = splitGenre(info[2]);
//
//        for (const string& g : genreList) {
//            if (bestGenres.find(g) == bestGenres.end() || stoi(info[1]) > stoi(bestGenres[g][1])) { //checking if its in or is bigger than a genre already in
//                bestGenres[g] = info;
//
//            }
//        }
//    }
//
//    for (const auto& pair : bestGenres) { //printing each genre
//        string genre = pair.first;
//        vector<string> info = pair.second;
//
//        cout << "Genre: " << genre << endl;
//        cout << "Top movie: " << info[0];
//        cout << " | Year: " << info[1];
//        cout << " | Rating: " << info[2];
//        cout << " | Genre(s): " << info[3] << endl;
//    }
//
//}

void movieHashMap::titleSearch(std::string name) {

    for (const auto& pair : movies) { //looping through movies
        string title = pair.first;
        vector<string> info = pair.second;

        string currentTitle = title;

        if (currentTitle.find(name) != std::string::npos) { //if genre is found then prints movie out
            cout << "Title: " << title;
            cout << " | Year: " << info[0];
            cout << " | Rating: " << info[1];
            cout << " | Genre(s): " << info[2] << endl;

        }
    }

}

void movieHashMap::yearFilter(int year) { //filter by year

    for (const auto& pair : movies) { //looping through movies
        string title = pair.first;
        vector<string> info = pair.second;

        if (year == stoi(info[0])) { //if year matches then prints movie out
        cout << "Title: " << title;
        cout << " | Year: " << info[0];
        cout << " | Rating: " << info[1];
        cout << " | Genre(s): " << info[2] << endl;

        }
    }


}
