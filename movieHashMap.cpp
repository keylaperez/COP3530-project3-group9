//
// Created by Winni Weng on 8/2/25.
//

#include "movieHashMap.h"

vector<string> movieHashMap::splitGenre(std::string genreStr) {
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


}

void movieHashMap::insertMovie(std::string name, int year, std::string genre, int rating) {

    movies[name].push_back(to_string(year));
    movies[name].push_back(to_string(rating));

    vector<string> genreList = splitGenre(genre);

    for (int i = 0; i < genreList.size(); i++) {
        movies[name].push_back(genreList[i]);
    }


}

void movieHashMap::ratingByGenre(std::string genre) {
//    unordered_map<string, vector<string>> bestGenres;
//
//    for (const auto& pair : movies) {
//        string title = pair.first;
//        vector<string> info = pair.second;
//
//        if (bestGenres.size() == 0) {
//            bestGenres[title].push_back(info[0]);
//            bestGenres[title].push_back(info[1]);
//            bestGenres[title].push_back(info[2]);
//        } else {
//            for (const auto& pairGenres : bestGenres) {
//                string genre = pairGenres.first;
//                vector<string> infoGenres = pairGenres.second;
//
//                if (bestGenres[title].info[2] < infoGenres[2]) {
//                    //replace
//                }
//
//            }
//        }
//
//
//    }

}

void movieHashMap::titleSearch(std::string name) {

}

void movieHashMap::yearFilter(int year) {

    for (const auto& pair : movies) {
        string title = pair.first;
        vector<string> info = pair.second;

        if (year == stoi(info[0])) {
            cout << "Title: " << title << endl;
            cout << "Year: " << info[0] << endl;
            cout << "Rating: " << info[1] << endl;
            cout << "Genre: " << info[2] << endl;

        }
    }


}
