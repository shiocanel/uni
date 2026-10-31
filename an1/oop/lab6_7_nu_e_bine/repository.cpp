#include "Repository.h"

using std::vector;
using std::string;

void Repository::store(const Movie& m) {
    if (find(m.getTitle()) != -1) {
        throw RepoException("Filmul exista deja in lista!\n");
    }
    movies.push_back(m);
}

void Repository::remove(const string& title) {
    int pos = find(title);
    if (pos == -1) {
        throw RepoException("Filmul nu exista si nu a putut fi sters!\n");
    }
    movies.erase(pos);
}

void Repository::update(const string& title, const Movie& updatedMovie) {
    int pos = find(title);
    if (pos == -1) {
        throw RepoException("Filmul nu exista si nu a putut fi modificat!\n");
    }
    movies[pos] = updatedMovie;
}

int Repository::find(const string& title) const {
    for (int i = 0; i < (int)movies.size(); ++i)
        if (movies[i].getTitle() == title) 
            return i;

    return -1;
}

const VectorDinamic<Movie>& Repository::getAll() const {
    return movies;
}