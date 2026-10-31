#include "movie.h"

using std::string;

const string& Movie::getTitle() const { 
    return title; 
}
const string& Movie::getGenre() const { 
    return genre; 
}
int Movie::getReleaseYear() const { 
    return releaseYear; 
}
const string& Movie::getMainActor() const { 
    return mainActor; 
}

void Movie::setTitle(const string& newTitle) { 
    title = newTitle; 
}
void Movie::setGenre(const string& newGenre) { 
    genre = newGenre; 
}
void Movie::setReleaseYear(int newYear) { 
    releaseYear = newYear; 
}
void Movie::setMainActor(const string& newActor) { 
    mainActor = newActor; 
}

bool Movie::operator==(const Movie& other) const {
    return title == other.title && releaseYear == other.releaseYear;
}