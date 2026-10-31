#include "Service.h"

Service::Service(Repository& repo) : repo(repo) {}

void Service::sort(VectorDinamic<Movie>& v, bool (*maiMic)(const Movie&, const Movie&)) const {
    for (int i = 0; i < v.size() - 1; i++) {
        for (int j = i + 1; j < v.size(); j++) {
            if (!maiMic(v[i], v[j])) {
                Movie aux = v[i];
                v[i] = v[j];
                v[j] = aux;
            }
        }
    }
}

void Service::addMovie(const string& title, const string& genre, int year, const string& actor) {
    MovieValidator::validate(title, genre, year, actor);

    Movie m(title, genre, year, actor);
    repo.store(m);
}

void Service::deleteMovie(const string& title) {
    repo.remove(title);
}

void Service::modifyMovie(const string& oldTitle, const string& newTitle, const string& newGenre, int newYear, const string& newActor) {
    MovieValidator::validate(newTitle, newGenre, newYear, newActor);
    Movie updated(newTitle, newGenre, newYear, newActor);
    repo.update(oldTitle, updated);
}

const VectorDinamic<Movie>& Service::getAllMovies() const {
    return repo.getAll();
}

VectorDinamic<Movie> Service::filterByTitle(const string& title) const {
    VectorDinamic<Movie> filtered;
    const auto& all = repo.getAll();
    for (int i = 0; i < all.size(); i++) {
        if (all[i].getTitle().find(title) != string::npos) {
            filtered.push_back(all[i]);
        }
    }
    return filtered;
}

VectorDinamic<Movie> Service::filterByYear(int year) const {
    VectorDinamic<Movie> filtered;
    const auto& all = repo.getAll();
    for (int i = 0; i < all.size(); i++) {
        if (all[i].getReleaseYear() == year) {
            filtered.push_back(all[i]);
        }
    }
    return filtered;
}

VectorDinamic<Movie> Service::sortByTitle() const {
    VectorDinamic<Movie> sorted = repo.getAll();
    sort(sorted, [](const Movie& a, const Movie& b) {
        return a.getTitle() < b.getTitle();
        });
    return sorted;
}

VectorDinamic<Movie> Service::sortByActor() const {
    VectorDinamic<Movie> sorted = repo.getAll();
    sort(sorted, [](const Movie& a, const Movie& b) {
        return a.getMainActor() < b.getMainActor();
        });
    return sorted;
}

VectorDinamic<Movie> Service::sortByYearAndGenre() const {
    VectorDinamic<Movie> sorted = repo.getAll();
    sort(sorted, [](const Movie& a, const Movie& b) {
        if (a.getReleaseYear() == b.getReleaseYear()) {
            return a.getGenre() < b.getGenre();
        }
        return a.getReleaseYear() < b.getReleaseYear();
        });
    return sorted;
}