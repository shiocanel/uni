#pragma once
#include <string>
#include <iostream>

using std::string;

class Movie {
private:
    string title;
    string genre;
    int releaseYear;
    string mainActor;

public:
    Movie() = default;

    Movie(const string& title, const string& genre, int releaseYear, const string& mainActor)
        : title(title), genre(genre), releaseYear(releaseYear), mainActor(mainActor) {
    }

    Movie(const Movie& other)
        : title(other.title), genre(other.genre), releaseYear(other.releaseYear), mainActor(other.mainActor) {
        std::cout << "COPY CONSTRUCTOR!\n";
    }

    Movie(Movie&& other) noexcept
        : title(std::move(other.title)),
        genre(std::move(other.genre)),
        releaseYear(other.releaseYear),
        mainActor(std::move(other.mainActor)) {
    }

    const string& getTitle() const;
    const string& getGenre() const;
    int getReleaseYear() const;
    const string& getMainActor() const;

    void setTitle(const string& newTitle);
    void setGenre(const string& newGenre);
    void setReleaseYear(int newYear);
    void setMainActor(const string& newActor);

    bool operator==(const Movie& other) const;
    Movie& operator=(const Movie& other) = default;
};