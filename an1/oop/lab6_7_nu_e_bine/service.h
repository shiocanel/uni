#pragma once
#include "repository.h"
#include "vector_dinamic.h"
#include "exceptions.h"
#include <string>

using std::string;

class Service {
private:
    Repository& repo;

    void sort(VectorDinamic<Movie>& v, bool (*maiMic)(const Movie&, const Movie&)) const;

public:
    Service(Repository& repo);

    void addMovie(const string& title, const string& genre, int year, const string& actor);
    void deleteMovie(const string& title);
    void modifyMovie(const string& oldTitle, const string& newTitle, const string& newGenre, int newYear, const string& newActor);

    const VectorDinamic<Movie>& getAllMovies() const;

    VectorDinamic<Movie> filterByTitle(const string& title) const;
    VectorDinamic<Movie> filterByYear(int year) const;

    VectorDinamic<Movie> sortByTitle() const;
    VectorDinamic<Movie> sortByActor() const;
    VectorDinamic<Movie> sortByYearAndGenre() const;
};